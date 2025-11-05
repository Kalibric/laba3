#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ShapeSelector, &QComboBox::currentIndexChanged, this, &MainWindow::shapeSelector);
    connect(ui->ColorSelector, &QAbstractButton::clicked, this, &MainWindow::colorSelector);
    ui->ShapeSelector->addItem("Круг", "Circle");
    ui->ShapeSelector->addItem("Квадрат", "Square");
    ui->ShapeSelector->addItem("Треугольник", "Triangle");
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
    ui->paintContainer->changeSelectedShape(shapeType);
}

void MainWindow::colorSelector()
{
    QColor color = QColorDialog::getColor(Qt::green, this, "Выбор цвета");
    if (color.isValid())
    {
        ui->paintContainer->changeColor(color);
    }
}
