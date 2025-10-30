#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shape.h"
#include "shapestorage.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShapeStorage storage = ShapeStorage();
    PaintWidget *paintContainer = new PaintWidget(ui->paintContainer); // paintContainer - это ваш виджет из UI
    //paintContainer->setGeometry(ui->paintContainer->geometry());  // Устанавливаем его размер и положение
    //paintContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //ui->paintContainer->setGeometry(ui->paintContainer->geometry());
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
