#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapes.h"
#include <QEvent>
#include<QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtAlgorithms>
#include<iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for(int i = 0; i < shapes.size(); ++i)
    {
            painter.setPen(shapes[i]->get_pen());
            painter.setBrush(shapes[i]->get_brush());
            shapes[i]->draw(painter);
    }

}

void MainWindow::brush_and_pen(const QBrush & br)
{
    for(int i = 0; i < shapes.size(); ++i)
    {
        if(shapes[i]->is_selected())
        {
            if(ui->brush_box->isChecked())
            {
              shapes[i]->set_brush(br);
            }
            if(ui->pen_box->isChecked())
            {
              shapes[i]->set_pen_color(br);
            }

        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        for(auto it = shapes.begin(); it != shapes.end();)
        {
            if((*it)->is_selected())
            {
                delete *it;
                it = shapes.erase(it);
            }
            else
                ++it;
        }
        update();

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Shape *shape = nullptr;
    if(ui->Rect_But->isChecked())
    {
        shape = new Rectangle(event->x(),event->y());
        shapes.push_back(shape);
        update();
    }

    else if(ui->Elipse_But->isChecked())
    {

        shape = new Elipse(event->x(),event->y());
        shapes.push_back(shape);
        update();
    }
    else if(ui->Select_But->isChecked())
    {
       for(int i = 0; i < shapes.size(); ++i)
       {
           if(shapes[i]->contain(event->pos()))
           {
               shapes[i]->set_selected();
               shapes[i]->set_pen(Qt::DashDotLine);
               update();
           }
           else
           {
               shapes[i]->un_select();
               QBrush old_pen_brush = shapes[i]->get_pen().color();
               shapes[i]->set_pen(Qt::SolidLine);
               shapes[i]->set_pen_color(old_pen_brush);
               update();
           }

       }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    if(ui->Rect_But->isChecked())
    {
       shapes.last()->set_widheight(event->pos());
       update();
    }
    else if(ui->Elipse_But->isChecked())
    {
         shapes.last()->set_widheight(event->pos());
         update();
    }
    else if(ui->Select_But->isChecked())
    {
        for(int i = 0; i < shapes.size(); ++i)
        {
            if(shapes[i]->is_selected())
            {
                if(!shapes[i]->contain(event->pos()))
                {
                    shapes[i]->set_pos(event->pos());
                    update();
                }
            }
        }
    }

}


void MainWindow::on_colorButton_Red_clicked()
{
    brush_and_pen(Qt::red);
    update();
}

void MainWindow::on_colorButton_Yellow_clicked()
{
    brush_and_pen(Qt::yellow);
    update();
}

void MainWindow::on_colorButton_Blue_clicked()
{

    brush_and_pen(Qt::blue);
    update();
}

void MainWindow::on_colorButton_Black_clicked()
{
    brush_and_pen(Qt::black);
    update();
}

void MainWindow::on_colorButton_Green_clicked()
{
    brush_and_pen(Qt::green);
    update();
}

void MainWindow::on_colorButton_White_clicked()
{
    brush_and_pen(Qt::white);
    update();
}


QString color_to_string(const QColor & brush)
{
    if(brush ==Qt::red )
        return  "Red";
    if(brush ==Qt::yellow)
        return  "Yellow";
    if(brush ==Qt::blue)
        return  "Blue";
    if(brush ==Qt::green)
        return  "Green";
    if(brush ==Qt::black)
        return  "Black";
    if(brush ==Qt::white)
        return  "white";
}
void MainWindow::on_save_button_clicked()
{
    QString filename =  QFileDialog::getSaveFileName(this , tr("Open File"),"C://", "All files(*.*);;Text File(*.txt*)");
    QFile data(filename);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&data);
        for(const auto & shp :shapes)
        {
            if(dynamic_cast<Rectangle*>(shp))
            {
                out << "Rectangle ";
            }
            else if(dynamic_cast<Elipse*>(shp))
            {
                out << "Elipse ";
            }
            out << shp->getx() << " " <<shp->gety() <<" " << shp->get_width() <<" " << shp->get_height()
            <<" " <<color_to_string(shp->get_brush().color()) <<" " <<color_to_string(shp->get_pen().color())
            << "\n";

        }
    }
}
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
void MainWindow::on_open_button_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(this , tr("Open File"),"C://", "All files(*.*);;Text File(*.txt*)");
    if(!shapes.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("");
        msgBox.setText("DO YOU WANT SAVE CHANGES?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes)
        {
          on_save_button_clicked();
        }
        else
        {
            for(auto it = shapes.begin(); it != shapes.end();)
            {
                delete *it;
                it = shapes.erase(it);
            }

        }
    }
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString shape_type;
          in >> shape_type;
          int  x0 , y0;
          in >> x0 >> y0;
          int  width0 , height0;
          in >> width0 >> height0;
          QString brush_col , pen_col;
          in >> brush_col >> pen_col;
          if(shape_type == "Rectangle")
          {
              shapes.push_back(new Rectangle(x0,y0,width0,height0));
          }
          else if(shape_type == "Elipse")
          {
              shapes.push_back(new Elipse(x0,y0,width0,height0));
          }
          shapes.last()->set_brush(brush_col);
          shapes.last()->set_pen_color(pen_col);
          QString line = in.readLine();

       }
       inputFile.close();
    }
    update();
}
