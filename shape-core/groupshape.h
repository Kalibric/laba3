#ifndef GROUPSHAPE_H
#define GROUPSHAPE_H

#include "shape.h"
#include "shape_global.h"
#include "shapeloader.h"
#include <QtGlobal>

class SHAPE_CORE_EXPORT GroupShape : public Shape
{
private:
    vector<Shape*> storage;
    struct Register {
        Register();
    };
    static Register reg;

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
    int getSize() override {return 0;}
    void changeTypeTo(QString newType);
    void load(QTextStream &file, QString &line) override;

    // Composite
    bool isGroup() override;
    void add(Shape* shape) override;
    vector<Shape*> unGrouping() override;
};

#endif // GROUPSHAPE_H
