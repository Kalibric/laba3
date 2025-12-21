#ifndef PROPERTYWINDOW_H
#define PROPERTYWINDOW_H

#include <QWidget>
#include "shapestorage.h"
#include <QMetaProperty>
#include <QTableWidget>
#include <QHeaderView>

class PropertyWindow : public QTableWidget
{
    Q_OBJECT
public:
    PropertyWindow(QWidget *parent = nullptr);
    void setStorage(ShapeStorage *iStorage);

private:
    ShapeStorage *storage = nullptr;
    vector<::Shape*> currentSelected;
    struct Property
    {
        string value;
        bool isWrite;
        Property() : value(""), isWrite(false) {}
        Property(string iValue, bool iIsWrite) : value(iValue), isWrite(iIsWrite) {}
    };

private slots:
    void selectedUpdate();
    void onCellChanged(int row, int column);
};

#endif // PROPERTYWINDOW_H
