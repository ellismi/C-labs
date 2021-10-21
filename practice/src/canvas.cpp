#include "canvas.h"

Canvas::Canvas():
    QGraphicsItem()
{
    rect.setCoords(-250,-250,500,500);

}

Canvas::~Canvas()
{

}

QRectF Canvas::boundingRect() const
{
    return rect;
}


void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Получение размеров окна
    int w = this->getW();
    int h = this->getH();
    // Переустановка координат для масштабирования
    rect.setCoords(-w/2,-h/2,w,h);
    // Переустановка области отрисовки
    this->boundingRect();
    // Отрисовка сетки (полярной или прямоугольной)
    if(this->isPolar()){
        drawGridPolar(painter, w, h);
    } else {
        drawGridCartesian(painter, w, h);
    }
    // Отрисовка осей
    drawGrid(painter, w, h);
    // Отрисовка кривой
    drawCurve(painter, w, h);
    // Отрисовка анимации
    if(isAnime()){
        drawAnime(painter, w, h);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Canvas::drawCurve(QPainter *painter, int w, int h){
    // Установка настроек рисовальщика
    painter->setPen(Qt::black | Qt::PenStyle::SolidLine);
    // Многоугольник для построения кривой
    QPolygonF plots;
    // Коэффициент масштабирования
    float xScale = (float)w/500;
    float yScale = (float)h/500;
    // Координаты точек и шаг для отрисовки
    float x, y, delta = 0.25;
    // Для масштабирования в полярной системе координат
    float polarX = xScale < yScale ? xScale : yScale;
    // Получение параметра асимптота
    float a = this->getA();
    // Отрисовка
    if(isPolar()){
        for (float i=0.2f; i<30; i+=delta){
            x = a*25.f*polarX*cos(i)/i;
            y = a*25.f*polarX*sin(i)/i;
            y*=-1;
            plots << QPointF(x,y);
        }
    } else{
        for (float i=0.2f; i<30; i+=delta){
            x = a*25.f*xScale*cos(i)/i;
            y = a*25.f*yScale*sin(i)/i;
            y*=-1;
            plots << QPointF(x,y);
        }
    }
    painter->drawPolyline(plots);
}

void Canvas::drawGridCartesian(QPainter *painter, int w, int h){
    // Установка настроек рисовальщика
    painter->setPen(Qt::gray);
    // Надписи на координатной сетке
    QString str("1");
    str.setNum(0);
    // Координаты центра области рисования
    int centerOfWidget_X, centerOfWidget_Y;
    centerOfWidget_X = w/2;
    centerOfWidget_Y = h/2;
    // Шаг сетки
    int stepX = w/10;
    int stepY = h/10;
    // Отрисовка сетки
    for(int i=-4;i<5;i++){
        str.setNum(i*2);
        painter->drawLine(i*stepX,-centerOfWidget_Y,i*stepX,centerOfWidget_Y);
        if(!(i==0)){
        painter->drawText(i*stepX+5,10,str);
        }
    }
    for(int i=-4;i<5;i++){
        str.setNum(-2*i);
        painter->drawLine(-centerOfWidget_X,i*stepY,centerOfWidget_X,i*stepY);
        if(!(i==0)){
        painter->drawText(10,i*stepY+10,str);
        }
    }
}

void Canvas::drawGridPolar(QPainter *painter, int w, int h){
    // Установка настроек рисовальщика
    painter->setPen(Qt::gray);
    // Шаг для построения сетки
    float radianToRotate = 0.523599f;
    // Точки для построения сетки
    int xPolar = 0;
    int yPolar = w;
    int centerOfWidget_X = w/2;
    // Шаг для вычисления и построения сетки (окружностей)
    int stepX = w/10;
    int stepY = h/10;
    int stepPolar = stepX > stepY ? stepY : stepX;
    int polarSize = w < h ? w : h;
    // Надписи на сетке
    QString str("1");
    str.setNum(0);
    // Подпись угла
    int angle = 360;
    // Вычисление точки для построения лучей
    for(float i = 0; i<6.28319; i += radianToRotate){
        if(angle == 0) angle = 360;
        str.setNum(angle);
        xPolar = centerOfWidget_X * cos(i) * 2;
        yPolar = centerOfWidget_X * sin(i) * 2;
        painter->drawLine(0,0,xPolar,yPolar);
        painter->drawText(stepPolar * cos(i)* 4, stepPolar* sin(i)* 4,str);
        angle -= 30;
    }
    // Отрисовка окружностей
    for(int i = stepPolar; i < polarSize/2; i += stepPolar){
        painter->drawEllipse(-i,-i,2*i,2*i);
    }
    // Отрисовка подписей к оси х
    for(int i=0; i<6; i++){
        str.setNum(i*2);
        painter->drawText(i*stepPolar+5,15,str);
    }
}

void Canvas::drawGrid(QPainter *painter, int w, int h){
    // Установка настроек рисовальщика
    painter->setPen(Qt::black);
    // Координаты центра области рисования
    int centerOfWidget_X, centerOfWidget_Y;
    centerOfWidget_X = w/2;
    centerOfWidget_Y = h/2;
    // Отрисовка
    painter->drawLine(-centerOfWidget_X,0,centerOfWidget_X,0);
    painter->drawLine(0,-centerOfWidget_Y,0,centerOfWidget_Y);
}

void Canvas::drawAnime(QPainter *painter, int w, int h){
    // Установка настроек рисовальщика
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(Qt::red));
    // Тик рисования анимации
    float delta = this->getTime();
    // Коэффициенты масштабирования
    float xScale = (float)w/500;
    float yScale = (float)h/500;
    // Координаты отрисовки спрайта
    float x, y;
    // Коэффициент для полярной системы координат
    float polarX = xScale < yScale ? xScale : yScale;
    // Получение параметра асимптоты
    float a = this->getA();
    // Отрисовка
    if(isPolar()){
         x = a*25.f*polarX*cos(delta)/delta;
         y = a*25.f*polarX*sin(delta)/delta;
         y*=-1;
     } else {
         x = a*25.f*xScale*cos(delta)/delta;
         y = a*25.f*yScale*sin(delta)/delta;
         y*=-1;
     }
    painter->drawEllipse(x-3,y-3,6,6);

}

// Геттеры Сеттеры
void Canvas::setW(int w){
    this->width = w;
}
void Canvas::setH(int h){
    this->height = h;
}
void Canvas::setA(float a){
    this->asymptote = a;
}
void Canvas::setPolar(bool state){
    this->polar = state;
}
void Canvas::setAnime(bool state){
    this->anime = state;
}
int  Canvas::getW(){
    return this->width;
}
int  Canvas::getH(){
    return this->height;
}
int  Canvas::getA(){
    return this->asymptote;
}
bool Canvas::isPolar(){
    return this->polar;
}
bool Canvas::isAnime(){
    return this->anime;
}

void Canvas::setTime(float time){
    this->time = time;
    this->update();
}

float Canvas::getTime(){
    return this->time;
}
