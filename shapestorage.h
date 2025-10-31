#ifndef SHAPESTORAGE_H
#define SHAPESTORAGE_H

#include <QDebug>
#include <vector>
#include "shape.h"
using namespace std;
class ShapeStorage
{
public:
    ShapeStorage();
    void add(Shape *iShape);
    void drawAll(QPainter *painter);
    bool selectShape(int iX, int iY, bool unSelectOther = false);
    void removeShape(Shape *iShape);
    void removeSelectedShapes();

private:
    vector<Shape*> storage;
};

#endif // SHAPESTORAGE_H
