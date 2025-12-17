#ifndef SHAPELOADER_H
#define SHAPELOADER_H

#include "shape.h"
#include "shape_global.h"
#include "shapefactory.h"

class SHAPE_CORE_EXPORT ShapeLoader
{
public:
    static std::vector<Shape*> load(QTextStream &file);
    static void save(QTextStream &file, std::vector<Shape*> shapes, int level = 0);
};

#endif // SHAPELOADER_H
