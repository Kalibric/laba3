#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QColorDialog>
#include "shapestorage.h"
#include "shape.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void keyPressEvent(QKeyEvent *event) override;
    void shapeSelector(int index);
    void colorSelector();
    void grouping();
    void saveButtonClick();
    ShapeStorage *storage = new ShapeStorage();

public slots:
    void groupingButton();
    void unGroupingButton();
    void deactivateGroupingButton();
    void loadButtonClick();
    void updateShapeTypes();
    void arrowButtonEnable();
    void arrowButtonDisable();

};
#endif // MAINWINDOW_H
