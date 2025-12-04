#ifndef ISHAPEPLUGIN_H
#define ISHAPEPLUGIN_H

#include <QString>
#include "shape.h"

// Интерфейс для плагина фигуры
class IShapePlugin
{
public:
    virtual ~IShapePlugin() {}

    // Создать фигуру
    virtual Shape* create(int x, int y, QColor color = Qt::green, int size=50, int id=-1) = 0;

    // Уникальное имя фигуры
    virtual QString name() const = 0;
};

#define IShapePlugin_iid "com.example.IShapePlugin"
Q_DECLARE_INTERFACE(IShapePlugin, IShapePlugin_iid)

#endif // ISHAPEPLUGIN_H
