#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void triangleSerpinsky(int x1, int y1, int x2, int y2, int x3, int y3, int order, double sideLength);
private slots:
void on_drawButton_clicked();


private:
    Ui::MainWindow *ui;
<<<<<<< HEAD
    QString *str;
    QString *str1;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *outPut;
    QPushButton *drawButton;
    QWidget *widget;
=======

    QPixmap H;
    QPainter paint;
    QPen pen;
QColor getRandColor();

>>>>>>> f11695e941634871664633494ee95e0b9997c2a4
};
#endif // MAINWINDOW_H
