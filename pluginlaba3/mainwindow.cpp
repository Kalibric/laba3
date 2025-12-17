#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->paintContainer->setStorage(storage);
    ui->ShapeTreeView->setStorage(storage);

    connect(ui->ShapeSelector, &QComboBox::currentIndexChanged, this, &MainWindow::shapeSelector);
    connect(ui->ColorSelector, &QAbstractButton::clicked, this, &MainWindow::colorSelector);
    connect(ui->GroupingButton, &QAbstractButton::clicked, this, &MainWindow::grouping);
    connect(ui->SaveShapesButton, &QAbstractButton::clicked, this, &MainWindow::saveButtonClick);
    connect(ui->paintContainer, &PaintWidget::groupingButton, this, &MainWindow::groupingButton);
    connect(ui->paintContainer, &PaintWidget::unGroupingButton, this, &MainWindow::unGroupingButton);
    connect(ui->paintContainer, &PaintWidget::deactivateButton, this, &MainWindow::deactivateGroupingButton);
    connect(ui->loadButton, &QAbstractButton::clicked, this, &MainWindow::loadButtonClick);

    connect(ui->UniArrowButton, &QAbstractButton::clicked, ui->paintContainer, &PaintWidget::uniArrowButton);
    connect(ui->BiArrowButton, &QAbstractButton::clicked, ui->paintContainer, &PaintWidget::biArrowButton);
    connect(ui->paintContainer, &PaintWidget::arrowButtonEnable, this, &MainWindow::arrowButtonEnable);
    connect(ui->paintContainer, &PaintWidget::arrowButtonDisable, this, &MainWindow::arrowButtonDisable);
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
    ui->paintContainer->changeSelectedShape(ui->ShapeSelector->currentText());
}

void MainWindow::colorSelector()
{
    QColor color = QColorDialog::getColor(Qt::green, this, "");
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
    ui->GroupingButton->setText("");
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

void MainWindow::updateShapeTypes()
{
    for (QString name : ShapeFactory::getNames())
        ui->ShapeSelector->addItem(name);
}

void MainWindow::arrowButtonEnable()
{
    qDebug() << "a";
    ui->UniArrowButton->setEnabled(true);
    ui->BiArrowButton->setEnabled(true);
}

void MainWindow::arrowButtonDisable()
{
    ui->UniArrowButton->setEnabled(false);
    ui->BiArrowButton->setEnabled(false);
}

// void MainWindow::setGroupingButton(std::string text)
// {
//     ui->GroupingButton->setText(text);
// }
