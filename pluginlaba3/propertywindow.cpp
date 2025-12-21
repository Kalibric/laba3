#include "propertywindow.h"
PropertyWindow::PropertyWindow(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this, &QTableWidget::cellChanged, this, &PropertyWindow::onCellChanged);
}

void PropertyWindow::setStorage(ShapeStorage *iStorage)
{
    if (iStorage == nullptr)
        return;
    if (storage != nullptr)
    {
        disconnect(storage, &ShapeStorage::selectUpdated, this, &PropertyWindow::selectedUpdate);
        disconnect(storage, &ShapeStorage::storageUpdated, this, &PropertyWindow::selectedUpdate);
    }
    storage = iStorage;
    connect(storage, &ShapeStorage::selectUpdated, this, &PropertyWindow::selectedUpdate);
    connect(storage, &ShapeStorage::storageUpdated, this, &PropertyWindow::selectedUpdate);
}

void PropertyWindow::selectedUpdate()
{
    std::unordered_map<string, Property> propArr;
    currentSelected = storage->get(TypeShape::SELECTED);
    for (::Shape *shape : currentSelected)
    {
        const QMetaObject *meta = shape->metaObject();
        for (int i = 0; i < meta->propertyCount(); ++i)
        {
            QMetaProperty prop = meta->property(i);

            if (!prop.isReadable())
                continue;

            if (QString(prop.name()) == "objectName")
                continue;

            if (propArr.count(prop.name()) && prop.read(shape).toString().toStdString() != propArr[prop.name()].value)
                propArr[prop.name()] = Property("", prop.isWritable());
            else
                propArr.emplace(prop.name(), Property(prop.read(shape).toString().toStdString(), prop.isWritable()));
        }
    }
    setRowCount(0);
    blockSignals(true);
    if (!propArr.empty())
    {
        for (const auto& [key, value] : propArr)
        {
            int row = rowCount();
            insertRow(row);
            QTableWidgetItem *keyItem = new QTableWidgetItem(QString::fromStdString(key));
            keyItem->setFlags(keyItem->flags() & ~Qt::ItemIsEditable);
            setItem(row, 0, keyItem);

            QTableWidgetItem *valueItem = new QTableWidgetItem(QString::fromStdString(value.value));
            if (!value.isWrite)
                valueItem->setFlags(keyItem->flags() & ~Qt::ItemIsEditable);
            setItem(row, 1, valueItem);
        }
    }
    blockSignals(false);
}


void PropertyWindow::onCellChanged(int row, int column)
{
    QString key = item(row, 0)->text();
    QString newValue = item(row, column)->text();
    storage->setProperty(TypeShape::SELECTED, key.toStdString().c_str(), newValue);
}
