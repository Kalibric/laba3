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

private:
    vector<Shape> storage;
};

#endif // SHAPESTORAGE_H
