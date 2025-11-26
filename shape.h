#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QDebug>
#include <QPolygon>
#include <vector>
#include <QRegularExpression>
using namespace std;
class Shape
{
public:
    Shape();
    Shape(Shape &iShape);
    virtual bool isContaints(int iX, int iY) { return false; }
    virtual void draw(QPainter *painter) {}
    virtual void changeCanvasSize(int iX, int iY);
    virtual void resizeRelative(int iSize) {}
    virtual bool isResizeArea(int iX, int iY) {return false;}
    virtual bool validateCoord(int iX, int iY);
    virtual void changeColor(QColor iColor);
    virtual void select();
    virtual void unSelect();
    virtual bool isSelect();
    virtual void moveRelative(int iX, int iY);
    virtual void saveInFile(QTextStream &out, int level) {}
    virtual void load(QString &text) {}
    virtual Shape* clone() = 0;
    virtual int getSize() = 0;

    // Composite
    virtual bool isGroup() { return false; }
    virtual void add(Shape* child) {}
    virtual vector<Shape*> unGrouping() { return vector<Shape*>(); }


protected:
    int x = 0;
    int y = 0;
    int canvasSizeX;
    int canvasSizeY;
    bool selected = false;
    QColor color = Qt::green;
};

class GroupShape : public Shape
{
private:
    vector<Shape*> storage;

public:
    GroupShape() = default;
    GroupShape(GroupShape &iGroup);
    ~GroupShape();
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void changeCanvasSize(int iX, int iY) override;
    void resizeRelative(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord(int iX, int iY) override;
    void changeColor(QColor color) override;
    void select() override;
    void unSelect() override;
    bool isSelect() override;
    void moveRelative(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    GroupShape* clone() override;
    int getSize() override {return 0;}

    // Composite
    bool isGroup() override {return true;}
    void add(Shape* shape) override;
    vector<Shape*> unGrouping() override;
};

class Circle: public Shape
{
public:
    Circle();
    Circle(Circle &iCircle);
    Circle(int iX, int iY, QColor iColor = Qt::green, int iRadius = 50);
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void resizeRelative(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    void load(QString &text) override;
    Circle* clone() override;
    int getSize() override;

protected:
    int radius = 50;
};

class Square: public Shape
{
public:
    Square();
    Square(Square &iSquare);
    Square(int iX, int iY, QColor iColor = Qt::green, int length = 50);
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void resizeRelative(int iSize) override;
    bool validateCoord(int iX, int iY) override;
    bool isResizeArea(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    void load(QString &text) override;
    Square* clone() override;
    int getSize() override;

protected:
    int lenght = 50;
};

class Triangle: public Shape
{
public:
    Triangle();
    Triangle(Triangle &iTriangle);
    Triangle(int iX, int iY, QColor iColor = Qt::green, int h = 50);
    bool isContaints(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void resizeRelative(int iSize) override;
    bool validateCoord(int iX, int iY) override;
    bool isResizeArea(int iX, int iY) override;
    void saveInFile(QTextStream &out, int level) override;
    void load(QString &text) override;
    Triangle* clone() override;
    int getSize() override;

protected:
    int h = 50;
};

class ShapeFactory {
public:
    static Shape* create(const QString& type, int x, int y, QColor color, int size = 50);
};

namespace ShapeType {
class ShapeTypes final
{
public:
    ShapeTypes();
    static const QString CIRCLE;
    static const QString SQUARE;
    static const QString TRIANGLE;
    virtual ~ShapeTypes();

};

enum class Type
{
    ALL = 0,
    SELECTED = 1,
    UNSELECTED = 2,
    RESIZE_AREA = 3,
    TO_COORDS = 4,
    TO_COORDS_UNSELECTED = 5,
    TO_COORDS_SELECTED = 6,
    RESIZE_AREA_SELECTED = 7
};
struct FilterParams
{
    Type type = Type::ALL;
    int x = 0;
    int y = 0;

    FilterParams(Type iType=Type::ALL, int iX=0, int iY=0) : type(iType), x(iX), y(iY)
    {

    }
};
}
#endif // SHAPE_H
