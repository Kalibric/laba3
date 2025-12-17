#include "arrow.h"

Arrow::Arrow(Shape *iA, Shape *iB)
{
    A = iA;
    B = iB;
    idA = A->addOnMoved([this](int x, int y)
    {
        updateA(x, y);
    });
    idB = B->addOnMoved([this](int x, int y)
    {
        updateB(x, y);
    });
}

Arrow::Arrow(Arrow &iArrow)
{
    A = iArrow.A;
    B = iArrow.B;
}

Arrow::~Arrow()
{
    if (A)
        A->removeOnMoved(idA);
    if (B)
        B->removeOnMoved(idB);
}

bool Arrow::shapeIs(Shape* shape)
{
    return shape == A || shape == B;
}
