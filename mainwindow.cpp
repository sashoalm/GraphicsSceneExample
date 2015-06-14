#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->installEventFilter(this);
    scene->setSceneRect(0, 0, 10000, 10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == scene && e->type() == QEvent::GraphicsSceneMousePress) {
        QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *) e;
        QPointF pos = mouseEvent->scenePos();
        qreal radius = 10;
        scene->addEllipse(pos.x()-radius, pos.y()-radius, 2*radius, 2*radius);
    }

    return QMainWindow::eventFilter(obj, e);
}
