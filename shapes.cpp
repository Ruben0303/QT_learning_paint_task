#include "shapes.h"
void Shape::set_brush(const QString& oth_brush)
{
    if(oth_brush == "Red" || oth_brush == "red")
        brush = Qt::red;
    else if(oth_brush == "Yellow" || oth_brush == "yellow")
        brush = Qt::yellow;
    else if(oth_brush == "Blue" || oth_brush == "blue")
        brush = Qt::blue;
    else if(oth_brush == "Green" || oth_brush == "green")
        brush = Qt::green;
    else if(oth_brush == "Black" || oth_brush == "black")
        brush = Qt::black;
    else if(oth_brush == "White" || oth_brush == "white")
        brush = Qt::white;
}
void Shape::set_pen_color(const QString &oth_brush)
{
    if(oth_brush == "Red" || oth_brush == "red")
        pen.setBrush(Qt::red);
    else if(oth_brush == "Yellow" || oth_brush == "yellow")
        pen.setBrush(Qt::yellow);
    else if(oth_brush == "Blue" || oth_brush == "blue")
        pen.setBrush(Qt::blue);
    else if(oth_brush == "Green" || oth_brush == "green")
        pen.setBrush(Qt::green);
    else if(oth_brush == "Black" || oth_brush == "black")
        pen.setBrush(Qt::black);
    else if(oth_brush == "White" || oth_brush == "white")
        pen.setBrush(Qt::white);

}
void Shape::set_widheight(const QPoint &point)
{
    if(point.x() < x)
    {
        width =  x - point.x();
        x = point.x();
    }
    else
        width =  point.x() - x;
    if(point.y() < y)
    {
        height = y - point.y();
        y = point.y();
    }
    else
        height =  point.y() - y;

}
