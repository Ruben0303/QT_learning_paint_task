#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVector>
#include <QMainWindow>
#include "shapes.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void paintEvent(QPaintEvent *event) override;
    void brush_and_pen(const QBrush & br);
    virtual void keyPressEvent(QKeyEvent *event);


private slots:
    void on_colorButton_Red_clicked();

    void on_colorButton_Yellow_clicked();

    void on_colorButton_Blue_clicked();

    void on_colorButton_Black_clicked();

    void on_colorButton_Green_clicked();

    void on_colorButton_White_clicked();



    void on_open_button_clicked();

    void on_save_button_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Shape *> shapes;
};
#endif // MAINWINDOW_H
