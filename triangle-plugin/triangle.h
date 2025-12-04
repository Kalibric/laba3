#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "shapefactory.h"

class Triangle: public Shape
{
public:
    Triangle();
    Triangle(Triangle &iTriangle);
    Triangle(int iX, int iY, QColor iColor = Qt::green, int h = 50, int _id = -1);
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void resizeRelative(int iSize) override;
    bool validateCoord(int iX, int iY) override;
    bool validateCoordRelative(int iX, int iY) override;
    void correctionCoord() override;
    bool isResizeArea(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    void load(QTextStream &file, QString &text) override;
    Triangle* clone() override;
    int getSize() override;

protected:
    int h = 50;
};

#endif // TRIANGLE_H
