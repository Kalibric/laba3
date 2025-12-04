#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle: public Shape
{
public:
    Circle();
    Circle(Circle &iCircle);
    Circle(int iX, int iY, QColor iColor = Qt::green, int iRadius = 50, int _id = -1);
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void resizeRelative(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord(int iX, int iY) override;
    bool validateCoordRelative(int iX, int iY) override;
    void correctionCoord() override;
    void saveInFile(QTextStream &out, int level) override;
    void load(QTextStream &file, QString &text) override;
    Circle* clone() override;
    int getSize() override;

protected:
    int radius = 50;
};

#endif // CIRCLE_H
