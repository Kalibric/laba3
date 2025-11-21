#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event) override;
    void shapeSelector(int index);
    void colorSelector();
    void grouping();
    void saveButtonClick();

public slots:
    void groupingButton();
    void unGroupingButton();
    void deactivateGroupingButton();

};
#endif // MAINWINDOW_H
