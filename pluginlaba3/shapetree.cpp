#include "shapetree.h"

ShapeTree::ShapeTree(QWidget *parent)
    : QTreeWidget(parent)
{
    connect(this, &QTreeWidget::itemClicked, this, &ShapeTree::onItemSelected);
}

void ShapeTree::setStorage(ShapeStorage *iStorage)
{
    if (storage != nullptr)
    {
        disconnect(storage, &ShapeStorage::storageUpdated, this, &ShapeTree::storageUpdated);
        disconnect(storage, &ShapeStorage::selectUpdated, this, &ShapeTree::selectUpdated);
    }
    storage = iStorage;
    connect(storage, &ShapeStorage::storageUpdated, this, &ShapeTree::storageUpdated);
    connect(storage, &ShapeStorage::selectUpdated, this, &ShapeTree::selectUpdated);
}

void ShapeTree::storageUpdated()
{
    this->clear();
    vector<::Shape*> shapeList = storage->get(TypeShape::ALL);
    fillTree(nullptr, shapeList);
    this->expandAll();
}

void ShapeTree::fillTree(QTreeWidgetItem* parent, vector<::Shape*> shapes)
{
    for (::Shape* shape : shapes)
    {
        QTreeWidgetItem *item;
        if (parent == nullptr)
            item = new QTreeWidgetItem(this);
        else
            item = new QTreeWidgetItem(parent);
        item->setText(0, QString::fromStdString(shape->type()));
        item->setText(1, QString::number(shape->getID()));
        item->setData(0, Qt::UserRole, QVariant::fromValue(shape));
        if (shape->isGroup())
        {
            GroupShape* group = dynamic_cast<GroupShape*>(shape);
            if (group != nullptr)
                fillTree(item, group->storage);
        }
    }
}

void ShapeTree::onItemSelected(QTreeWidgetItem* item, int column)
{
    selectEvent = true;
    QTreeWidgetItem* firstParent = getFirstParent(item);
    firstParent->setSelected(item->isSelected());
    setSelectChild(firstParent, item->isSelected());
    ::Shape* shape = firstParent->data(0, Qt::UserRole).value<::Shape*>();
    if (item->isSelected())
        storage->select(shape);
    else
        storage->unSelect(shape);
    selectEvent = false;
}

void ShapeTree::setSelectChild(QTreeWidgetItem* item, bool status)
{    if (item == nullptr)
        return;

    for (int i = 0; i < item->childCount(); i++)
    {
        item->child(i)->setSelected(status);
        setSelectChild(item->child(i), status);
    }
}

QTreeWidgetItem* ShapeTree::getFirstParent(QTreeWidgetItem* item)
{
    if (item == nullptr)
        return nullptr;

    QTreeWidgetItem* parent = item->parent();
    if (parent == nullptr)
        return item;

    return getFirstParent(parent);
}

void ShapeTree::selectUpdated()
{
    if (selectEvent)
        return;
    vector<::Shape*> list = storage->get(TypeShape::ALL);
    for (int i = 0; i < list.size(); i++)
    {
        bool select = list[i]->isSelect();
        ::Shape *shape = this->topLevelItem(i)->data(0, Qt::UserRole).value<::Shape*>();
        if (shape->getID() == list[i]->getID())
        {
            this->topLevelItem(i)->setSelected(select);
            setSelectChild(this->topLevelItem(i), select);
        }
    }
}
