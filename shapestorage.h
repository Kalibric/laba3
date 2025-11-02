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
    void drawAllShapes(QPainter *painter);
    bool selectShapeToCoord(int iX, int iY);
    bool unSelectShapeToCoord(int iX, int iY);
    void unselectAll();
    void removeSelectedShapes();
    void moveSelectedShapesRelative(int iX, int iY);
    bool isExistsSelectedToCoors(int iX, int iY);
    bool isExistsSelectedShapes();
    bool isExistsShapeToCoors(int iX, int iY);

private:
    vector<Shape*> storage;
};

#endif // SHAPESTORAGE_H
