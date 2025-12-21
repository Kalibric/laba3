#ifndef UNIARROW_H
#define UNIARROW_H

#include "arrow.h"

class UniArrow : public Arrow
{
public:
    UniArrow(Shape *iA, Shape *iB);
    UniArrow(UniArrow &iArrow);
    virtual ~UniArrow();
    Arrow* clone() override;
    void draw(QPainter *painter) override;
    void updateA(int x, int y) override;
    void updateB(int x, int y) override;

private:
    bool move = false;
};

#endif // UNIARROW_H
