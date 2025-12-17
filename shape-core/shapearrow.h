#ifndef SHAPEARROW_H
#define SHAPEARROW_H

#include "shape.h"

class ShapeArrow : public Shape
{
public:
    ShapeArrow();
    void set(Shape *a, Shape *b);
    Shape* a;
    Shape* b;
};

#endif // SHAPEARROW_H
