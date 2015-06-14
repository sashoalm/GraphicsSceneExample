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
    if (obj == scene && e->type() == QEvent::GraphicsSceneMouseRelease) {
        QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *) e;
        QPointF pos = mouseEvent->scenePos();
        // Check if there is already an item where we're clicking, otherwise we
        // would both create a new item and start moving the old one.
        if (!scene->itemAt(pos, ui->graphicsView->transform())) {
            qreal radius = 10;
            QGraphicsItem *item = scene->addEllipse(pos.x()-radius, pos.y()-radius, 2*radius, 2*radius);
            item->setFlag(QGraphicsItem::ItemIsMovable, true);
        }
    }

    return QMainWindow::eventFilter(obj, e);
}
