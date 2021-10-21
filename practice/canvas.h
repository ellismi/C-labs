#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

// Класс холста (области рисования)
class Canvas : public QGraphicsItem
{

public:
    Canvas();
    ~Canvas();
    // Отрисовка кривой
    void drawCurve(QPainter *painter, int w, int h);
    // Отрисовка осей
    void drawGrid(QPainter *painter, int w, int h);
    // Отрисовка прямоугольной системы координат
    void drawGridCartesian(QPainter *painter, int w, int h);
    // Отрисовка полярной системы координат
    void drawGridPolar(QPainter *painter, int w, int h);
    // Отрисовка анимации
    void drawAnime(QPainter *painter, int w, int h);
    // Геттеры Сеттеры
    void setW(int w);
    void setH(int h);
    void setA(float a);
    void setPolar(bool state);
    void setAnime(bool state);
    bool isPolar();
    bool isAnime();
    int getW();
    int getH();
    int getA();
    float getTime();
    void setTime(float time);

protected:
    // Область отрисовки
    QRectF boundingRect() const;
    // Переопределение функции отрисовки
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    // Ширина и высота области рисования
    int width;
    int height;
    // Параметр асимптота
    float asymptote = 4.f;
    // Сетка полярная или нет
    bool polar = false;
    // Анимация есть или нет
    bool anime = false;
    // Время анимации
    float time;
    // Область отрисоки
    QRectF rect;

};

#endif // CANVAS_H
