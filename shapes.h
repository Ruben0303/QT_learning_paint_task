#ifndef SHAPE_H
#define SHAPE_H
#include<QPainter>
#include<QWidget>
#include<QBrush>
#include<QPen>

class Shape
{
public:
    Shape(int x = 0, int y = 0,int width = 0, int height = 0, QPen pen = Qt::SolidLine, QBrush brush = Qt::white):
        x(x),
        y(y),
        width(width),
        height(height),
        selected(false),
        pen(pen),
        brush(brush)
        {}
    bool contain(const QPoint& p) const
    {
        return (p.x() >= x && p.x() <=  x + width  && p.y() >= y && p.y() <= y + height);
    }
    void set_pen(const QPen& oth_pen)
    {
        pen = oth_pen;
    }
    void set_brush(const QBrush& oth_brush)
    {
        brush = oth_brush;
    }
    void set_brush(const QString& oth_brush);

    void set_pen_color(const QBrush &oth_brush)
    {
        pen.setBrush(oth_brush);

    }
    void set_pen_color(const QString &oth_brush);

    QPen get_pen() const
    {
        return pen;
    }
    QBrush get_brush() const
    {
        return brush;
    }
    void set_selected()
    {
       selected = true;
    }
    void un_select()
    {
       selected = false;
    }

    bool is_selected() const
    {
        return selected;
    }
    int get_width()const
    {
        return width;
    }
    int get_height()const
    {
        return height;
    }
    virtual void draw(QPainter &painter) = 0;
    virtual ~Shape(){}
    void set_pos(const QPoint &point)
    {
        x = point.x();
        y = point.y();
    }
    void set_widheight(const QPoint &point);
    int getx() const{return x;}
    int gety() const{return y;}

protected:
    int x;
    int y;
    int width;
    int height;
    bool selected;
    QPen pen;
    QBrush brush;


};

class Rectangle : public Shape{
public:
    Rectangle(){}
    Rectangle(int x, int y,int width = 0, int height = 0):Shape(x,y,width,height){}
    virtual void draw(QPainter &painter) override
    {
            painter.drawRect(x,y,width,height);

    }


};

class Elipse : public Shape{
public:
    Elipse(int x , int y,int width = 0, int height = 0):Shape(x,y,width,height){}
    virtual void draw(QPainter &painter) override
    {
            painter.drawEllipse(x,y,width,height);
    }
};

#endif // SHAPE_H
