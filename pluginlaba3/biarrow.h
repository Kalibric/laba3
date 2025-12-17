#ifndef BIARROW_H
#define BIARROW_H

#include "arrow.h"
#include "QPointF"

class BiArrow : public Arrow
{
public:
    BiArrow(Shape *iA, Shape *iB);
    BiArrow(BiArrow &iArrow);
    virtual ~BiArrow();
    Arrow* clone() override;
    void draw(QPainter *painter) override;
    void updateA(int x, int y) override;
    void updateB(int x, int y) override;

private:
    bool move = false;
};

#endif // BIARROW_H
