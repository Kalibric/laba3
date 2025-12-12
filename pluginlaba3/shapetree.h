#ifndef SHAPETREE_H
#define SHAPETREE_H

#include <QTreeWidget>
#include <QDebug>
#include <vector>
#include <QString>
#include "shapestorage.h"
#include "shape.h"
#include "ShapeInfo.h"

using namespace std;
class ShapeTree : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ShapeTree(QWidget *parent = nullptr);
    void setStorage(ShapeStorage *iStorage);

private:
    vector<QTreeWidgetItem*> tree;
    ShapeStorage *storage;
    void fillTree(QTreeWidgetItem* parent, vector<::Shape*> shapes);
    QTreeWidgetItem* getFirstParent(QTreeWidgetItem* item);
    void setSelectChild(QTreeWidgetItem* item, bool status);

    bool selectEvent = false;

public slots:
    void storageUpdated();
    void onItemSelected(QTreeWidgetItem* item, int column);
    void selectUpdated();
};

#endif // SHAPETREE_H
