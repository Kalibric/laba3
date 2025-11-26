#ifndef SHAPESTORAGE_H
#define SHAPESTORAGE_H

#include <QDebug>
#include <vector>
#include "shape.h"
#include <QFile>
#include <QRegularExpression>
using namespace std;

class ShapeStorage
{
public:
    Shape* createShape(int x, int y, QColor color = Qt::green);
    vector<Shape*> clone(ShapeType::FilterParams params);
    vector<Shape*> get(ShapeType::FilterParams type);
    void add(Shape *iShape);
    void draw(ShapeType::FilterParams params, QPainter *painter);
    bool select(ShapeType::FilterParams params);
    bool unSelect(ShapeType::FilterParams params);
    void remove(ShapeType::FilterParams params);
    void remove(Shape* iShape);
    void moveRelative(ShapeType::FilterParams params, int x, int y);
    void moveRelative(Shape* shape, int x, int y);
    void resizeRelative(ShapeType::FilterParams params, int iSize);
    void resizeRelative(Shape* shape, int iSize);
    bool isExists(ShapeType::FilterParams params);
    void changeCanvasSize(int x, int y);
    void changeColor(ShapeType::FilterParams params, QColor color);
    void changeColor(Shape* shape, QColor color);
    void addGroup(ShapeType::FilterParams params);
    void unGroup(ShapeType::FilterParams params);
    bool isSelectedInOneGroup();
    int count(ShapeType::FilterParams params);
    void changeShapeType(Shape* shape, QString newType);

    void saveInFile(QString iFile);
    void load(QString iFile);

private:
    vector<Shape*> storage;
    vector<Shape*> createShapes(QTextStream &in);
    int canvasSizeX = 0;
    int canvasSizeY = 0;
};
#endif // SHAPESTORAGE_H
