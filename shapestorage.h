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
    void selectAll();
    bool unSelectShapeToCoord(int iX, int iY);
    void unselectAll();
    void removeSelectedShapes();
    void moveSelectedShapesRelative(int iX, int iY);
    void resizeSelectedShapesRelative(int iSize);
    bool isExistsSelectedToCoord(int iX, int iY);
    bool isExistsSelectedShapes();
    bool isExistsShapeToCoord(int iX, int iY);
    void changeCanvasSize(int x, int y);
    bool isResizeAreaShapeSelectedToCoord(int iX, int iY);
    void changeColorSelectedShapes(QColor color);

private:
    vector<Shape*> storage;
    int canvasSizeX = 0;
    int canvasSizeY = 0;
};

#endif // SHAPESTORAGE_H
