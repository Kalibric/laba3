#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ShapeSelector, &QComboBox::currentIndexChanged, this, &MainWindow::shapeSelector);
    ui->ShapeSelector->addItem("Круг", "Circle");
    ui->ShapeSelector->addItem("Квадрат", "Square");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->paintContainer->keyPressEvent(event);
}

void MainWindow::shapeSelector(int index)
{
    QString shapeType = ui->ShapeSelector->currentData().toString();
    if (shapeType == ShapeTypes::CIRCLE)
        ui->paintContainer->changeSelectedShape(ShapeTypes::CIRCLE);
    //ShapeTypes s;
}
