#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QPixmap>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPainter>

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


void MainWindow::on_pushButton_clicked()
{
    pathToImage = QFileDialog::getOpenFileName(nullptr, "Open Image", nullptr, "jpg / png files(*.jpg *.png)");

    ui->label->setPixmap(QPixmap::fromImage(blurImage(QImage(pathToImage), ui->horizontalSlider->value()).scaled(
                                        ui->label->width(),
                                        ui->label->height(), Qt::KeepAspectRatio)));
}

QImage MainWindow::blurImage(QImage source, int blurRadius)
{
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));
    return result;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setPixmap(QPixmap::fromImage(blurImage(QImage(pathToImage), value).scaled(
                                        ui->label->width(),
                                        ui->label->height(), Qt::KeepAspectRatio)));
}

