#include "uniarrow.h"
using namespace std;
UniArrow::UniArrow(Shape *iA, Shape *iB) : Arrow(iA, iB)
{

}

UniArrow::UniArrow(UniArrow &iArrow) : Arrow(iArrow)
{

}

UniArrow::~UniArrow()
{

}

Arrow* UniArrow::clone()
{
    return new UniArrow(*this);
}

void UniArrow::draw(QPainter *painter)
{
    QPointF Apos(A->getX(), A->getY());
    QPointF Bpos(B->getX(), B->getY());
    int arrowSize  = 10.0;
    double arrowAngle = M_PI / 6;
    double angleAB = std::atan2(Bpos.y() - Apos.y(),
                                Bpos.x() - Apos.x());

    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(A->getX(), A->getY(), B->getX(), B->getY());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);

    QPolygonF arrowHeadB;
    arrowHeadB << Bpos
               << QPointF(
                      Bpos.x() - arrowSize * std::cos(angleAB - arrowAngle),
                      Bpos.y() - arrowSize * std::sin(angleAB - arrowAngle))
               << QPointF(
                      Bpos.x() - arrowSize * std::cos(angleAB + arrowAngle),
                      Bpos.y() - arrowSize * std::sin(angleAB + arrowAngle));

    painter->drawPolygon(arrowHeadB);
}

void UniArrow::updateA(int x, int y)
{
    B->moveRelative(x, y);
}

void UniArrow::updateB(int x, int y)
{
    return;
}
