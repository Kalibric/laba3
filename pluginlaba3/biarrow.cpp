#include "biarrow.h"

BiArrow::BiArrow(Shape *iA, Shape *iB) : Arrow(iA, iB)
{

}

BiArrow::BiArrow(BiArrow &iArrow) : Arrow(iArrow)
{

}

BiArrow::~BiArrow()
{

}

Arrow* BiArrow::clone()
{
    return new BiArrow(*this);
}

void BiArrow::draw(QPainter *painter)
{
    QPointF Apos(A->getX(), A->getY());
    QPointF Bpos(B->getX(), B->getY());

    int arrowSize  = 10.0;
    double arrowAngle = M_PI / 6;

    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(Apos, Bpos);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);

    double angleAB = std::atan2(Bpos.y() - Apos.y(),
                                Bpos.x() - Apos.x());

    QPolygonF arrowHeadB;
    arrowHeadB << Bpos
               << QPointF(
                      Bpos.x() - arrowSize * std::cos(angleAB - arrowAngle),
                      Bpos.y() - arrowSize * std::sin(angleAB - arrowAngle))
               << QPointF(
                      Bpos.x() - arrowSize * std::cos(angleAB + arrowAngle),
                      Bpos.y() - arrowSize * std::sin(angleAB + arrowAngle));

    painter->drawPolygon(arrowHeadB);

    double angleBA = angleAB + M_PI;

    QPolygonF arrowHeadA;
    arrowHeadA << Apos
               << QPointF(
                      Apos.x() - arrowSize * std::cos(angleBA - arrowAngle),
                      Apos.y() - arrowSize * std::sin(angleBA - arrowAngle))
               << QPointF(
                      Apos.x() - arrowSize * std::cos(angleBA + arrowAngle),
                      Apos.y() - arrowSize * std::sin(angleBA + arrowAngle));

    painter->drawPolygon(arrowHeadA);
}

void BiArrow::updateA(int x, int y)
{
    if (!move)
    {
        move = true;
        B->moveRelative(x, y);
        move = false;
    }
}

void BiArrow::updateB(int x, int y)
{
    if (!move)
    {
        move = true;
        A->moveRelative(x, y);
        move = false;
    }
}
