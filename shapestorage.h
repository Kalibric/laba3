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
    // Shape* createShape(int x, int y, QColor color = Qt::green);
    void add(Shape *iShape);
    void add(int x, int y, QColor color = Qt::green);
    void draw(ShapeType::FilterParams params, QPainter *painter);
    bool select(ShapeType::FilterParams params);
    bool unSelect(ShapeType::FilterParams params);
    void remove(ShapeType::FilterParams params);
    void remove(Shape* iShape);
    void moveRelative(ShapeType::FilterParams params, int x, int y);
    void resizeRelative(ShapeType::FilterParams params, int iSize);
    bool isExists(ShapeType::FilterParams params);
    void changeCanvasSize(int x, int y);
    void changeColor(ShapeType::FilterParams params, QColor color);
    void addGroup(ShapeType::FilterParams params);
    void unGroup(ShapeType::FilterParams params);
    bool isSelectedInOneGroup();
    int count(ShapeType::FilterParams params);
    void changeCurrentShape(QString iCurrentShape);
    void saveInFile();
    void load();

private:
    vector<Shape*> storage;
    vector<Shape*> get(ShapeType::FilterParams type);
    vector<Shape*> createShapes(QTextStream &in);
    QString currentShape = ShapeType::ShapeTypes::CIRCLE;
    int canvasSizeX = 0;
    int canvasSizeY = 0;
};
#endif // SHAPESTORAGE_H
