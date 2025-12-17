#ifndef GROUPSHAPE_H
#define GROUPSHAPE_H

#include "shape.h"
#include "shape_global.h"
#include "shapeloader.h"
#include <QtGlobal>

class SHAPE_CORE_EXPORT GroupShape : public Shape
{

public:
    GroupShape();
    GroupShape(GroupShape &iGroup);
    GroupShape(int iX, int iY, QColor iColor, int length, int _id);
    ~GroupShape();
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void changeCanvasSize(int iX, int iY) override;
    void resizeRelative(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord(int iX, int iY) override;
    bool validateCoordRelative(int iX, int iY) override;
    void changeColor(QColor color) override;
    void select() override;
    void unSelect() override;
    bool isSelect() override;
    void moveRelative(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    GroupShape* clone() override;
    int getSize() override;
    void changeTypeTo(QString newType);
    void load(QTextStream &file, QString &line) override;
    std::string type() override;
    virtual int getSizeX();
    virtual int getSizeY();

    // Composite
    bool isGroup() override;
    void add(Shape* shape) override;
    std::vector<Shape*> unGrouping() override;
    std::vector<Shape*> storage;

protected:
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

private:
    void updateBounds();
    void updateCenter();
};

#endif // GROUPSHAPE_H
