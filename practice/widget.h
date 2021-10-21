#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPropertyAnimation>

#include "canvas.h"

namespace Ui {
class Widget;
}

// Класс виджета
class Widget : public QWidget
{
    Q_OBJECT
    // Настройки виджета для отрисовки анимации
    Q_PROPERTY(float animeTime READ animeTime WRITE setTime)

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    // Переоределение перерисовки и масштабируемости
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    // Геттеры Сеттеры
    float animeTime() const;
    void setTime(float animeTime);

private slots:
    // Слот для запуска анимации
    void on_animation_clicked(bool checked);
    // Слот для смены координатой сетки
    void on_polar_clicked(bool checked);
    // Слот для перерисовки с новыми параметрами
    void on_drawBotton_clicked();

private:
    // Виджет
    Ui::Widget      *ui;
    // Сцена
    QGraphicsScene  *scene;
    // Область рисования
    Canvas          *canvas;
    // Настройки анимации
    QPropertyAnimation *animation;
    // Время анимации
    float time = 0.f;
};

#endif // WIDGET_H
