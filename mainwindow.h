#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool eventFilter(QObject *obj, QEvent *e);
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    QPointF mousePressPos;
};

#endif // MAINWINDOW_H
