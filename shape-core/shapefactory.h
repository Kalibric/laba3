#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "shape.h"
#include "groupshape.h"
#include <functional>
#include "shape_global.h"
#include <QDebug>
#include "IShapePlugin.h"
#include <vector>
#include <functional>

class SHAPE_CORE_EXPORT ShapeFactory {
public:
    struct RegisterShape
    {
        QString name;
        function<Shape*(int x, int y, QColor color, int size, int id)> creator;
        bool isCanCreate;
    };
    static void registerShape(QString name, function<Shape*(int x, int y, QColor color, int size, int id)> create, bool isCanCreate = true);
    static Shape* create(QString name, int x, int y, QColor color=Qt::green, int size=50, int id=-1);
    static Shape* clone(Shape* shape);
    static Shape* changeType(Shape* shape, QString &type);
    static vector<QString> getNames();
    static vector<RegisterShape> getRegistredShapes();
private:
    static vector<RegisterShape> registredShapes;
};

#endif // SHAPEFACTORY_H
