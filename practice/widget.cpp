#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // Инициализация сцены и области рисования
    scene = new QGraphicsScene();
    canvas = new Canvas();
    // Установка сцены в graphicview
    ui->graphicsView->setScene(scene);
    // Настройка graphicview
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Установка системы координат холста
    scene->setSceneRect(-250,-250, 500, 500);
    // Инициализация аниматора
    animation = new QPropertyAnimation(this, "animeTime");
    // Добавление на сцену области рисования
    scene->addItem(canvas);
    // Установка позиции холста относительно координат сцены
    canvas->setPos(0,0);

    // Установка слотов и сигналов для обработки событий
    connect(ui->polar,SIGNAL(clicked(bool)), this, SLOT(on_polar_clicked(bool)));
    connect(ui->animation,SIGNAL(clicked(bool)), this, SLOT(on_animation_clicked(bool)));
    connect(ui->drawBotton,SIGNAL(clicked()), this, SLOT(on_drawBotton_clicked()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
    // Получение измененных параметров холста
    int w = this->ui->graphicsView->width();
    int h = this->ui->graphicsView->height();
    // Изменение размера сцены
    this->scene->setSceneRect(-w/2,-h/2,w,h);
    // Отправка холсту изменений размера
    this->canvas->setW(w);
    this->canvas->setH(h);
}

void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    // Перерисовка холста
    this->canvas->update();
}

void Widget::on_animation_clicked(bool checked)
{
    // Включение/выключение анимации
    this->canvas->setAnime(checked);
    if(checked){
        // Настройка анимации
        animation->setDuration(15000);
        animation->setLoopCount(-1);
        animation->setStartValue(0.f);
        animation->setEndValue(15.f);
        animation->start();
    } else{
        animation->stop();
        setTime(0.f);
    }
}

void Widget::on_polar_clicked(bool checked)
{
    // Включение/выключение полярной сетки
    if(checked){
       this->canvas->setPolar(true);
    }
    else{
        this->canvas->setPolar(false);
    }
    // Перерисовка холста
    this->canvas->update();

}

void Widget::on_drawBotton_clicked()
{
    // Отправление изменения асимптоты
    double a = this->ui->asymptote->value();
    this->canvas->setA(a);
    // Перерисовка холста
    this->canvas->update();
}

// Геттеры Сеттеры
void Widget::setTime(float time){
    this->time = time;
    this->canvas->setTime(time);
    this->canvas->update();
}

float Widget::animeTime() const{
    return this->time;
}
