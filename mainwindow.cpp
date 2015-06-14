#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
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
    addedItem = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == scene) {
        if (e->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *) e;
            startPos = mouseEvent->scenePos();
            // Check if there is already an item where we're clicking, otherwise we
            // would both create a new item and start moving the old one.
            QGraphicsItem *item = scene->itemAt(startPos, ui->graphicsView->transform());
            if (!item) {
                qreal radius = 10;
                addedItem = scene->addEllipse(startPos.x()-radius, startPos.y()-radius, 2*radius, 2*radius);
            } else if (mouseEvent->button() == Qt::RightButton) {
                delete item;
            }
        } else if (e->type() == QEvent::GraphicsSceneMouseRelease && addedItem) {
            addedItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            addedItem = 0;
        } else if (e->type() == QEvent::GraphicsSceneMouseMove && addedItem) {
            QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *) e;
            QPointF delta = startPos - mouseEvent->scenePos();
            qreal radius = sqrt(delta.x()*delta.x()+delta.y()*delta.y());
            if (radius >= 10) {
                addedItem->setRect(startPos.x()-radius, startPos.y()-radius, 2*radius, 2*radius);
            }
        }
    }

    return QMainWindow::eventFilter(obj, e);
}
