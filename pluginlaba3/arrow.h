#ifndef ARROW_H
#define ARROW_H

#include "shape.h"

class Arrow
{
public:
    Arrow(Shape *iA, Shape *iB);
    Arrow(Arrow &iArrow);
    virtual ~Arrow();
    virtual Arrow* clone() = 0;
    virtual void draw(QPainter *painter) = 0;
    virtual void updateA(int x, int y) = 0;
    virtual void updateB(int x, int y) = 0;
    bool shapeIs(Shape* shape);

protected:
    Shape *A;
    Shape *B;
    int idA;
    int idB;
};

#endif // ARROW_H
