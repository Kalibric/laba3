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
    connect(ui->GroupingButton, &QAbstractButton::clicked, this, &MainWindow::grouping);
    connect(ui->SaveShapesButton, &QAbstractButton::clicked, this, &MainWindow::saveButtonClick);
    connect(ui->paintContainer, &PaintWidget::groupingButton, this, &MainWindow::groupingButton);
    connect(ui->paintContainer, &PaintWidget::unGroupingButton, this, &MainWindow::unGroupingButton);
    connect(ui->paintContainer, &PaintWidget::deactivateButton, this, &MainWindow::deactivateGroupingButton);
    connect(ui->loadButton, &QAbstractButton::clicked, this, &MainWindow::loadButtonClick);
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

void MainWindow::grouping()
{
    ui->paintContainer->groupingButtonClick();
}

void MainWindow::groupingButton()
{
    ui->GroupingButton->setEnabled(true);
    ui->GroupingButton->setText("Сгруппировать");
}

void MainWindow::unGroupingButton()
{
    ui->GroupingButton->setEnabled(true);
    ui->GroupingButton->setText("Разгруппировать");
}

void MainWindow::deactivateGroupingButton()
{
    ui->GroupingButton->setText("Нет выделенных");
    ui->GroupingButton->setEnabled(false);
}

void MainWindow::saveButtonClick()
{
    ui->paintContainer->saveButton();
}

void MainWindow::loadButtonClick()
{
    ui->paintContainer->loadButton();
}


// void MainWindow::setGroupingButton(std::string text)
// {
//     ui->GroupingButton->setText(text);
// }
