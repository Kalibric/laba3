#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QPolygon>
#include <vector>
#include <QRegularExpression>
#include "shape_global.h"
using namespace std;
class SHAPE_CORE_EXPORT Shape : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
    Q_PROPERTY(int canvasSizeX READ getCanvasSizeX)
    Q_PROPERTY(int canvasSizeY READ getCanvasSizeY)
    Q_PROPERTY(int id READ getID)
    Q_PROPERTY(bool selected READ isSelect)
    Q_PROPERTY(QColor color READ getColor WRITE changeColor)
public:
    using moveCallback = function<void(int, int)>;
    struct callback
    {
        int id;
        moveCallback func;
    };

    Shape();
    Shape(Shape &iShape);
    Shape(int iX, int iY, QColor iColor, int _id);
    virtual bool isContaints(int iX, int iY) { return false; }
    virtual void draw(QPainter *painter) {}
    virtual void changeCanvasSize(int iX, int iY);
    virtual void resizeRelative(int iSize) {}
    virtual bool isResizeArea(int iX, int iY) { return false; }
    virtual bool validateCoord(int iX, int iY);
    virtual bool validateCoordRelative(int iX, int iY);
    virtual void correctionCoord();
    virtual void changeColor(QColor iColor);
    virtual void select();
    virtual void unSelect();
    virtual bool isSelect();
    virtual void moveRelative(int iX, int iY);
    virtual void saveInFile(QTextStream &out, int level) = 0;
    virtual void load(QTextStream &file, QString &text) = 0;
    virtual Shape* clone() = 0;
    virtual int getSize() = 0;
    virtual std::string type();
    virtual void setSize(int size) = 0;
    int getX() { return x; }
    int getY() { return y; }
    QColor getColor() { return color; }
    int getID() { return id; }
    int getCanvasSizeX() { return canvasSizeX; }
    int getCanvasSizeY() { return canvasSizeY; }
    void setX(int iX);
    void setY(int iY);

    // Composite
    virtual bool isGroup() { return false; }
    virtual void add(Shape* child) {}
    virtual vector<Shape*> unGrouping() { return vector<Shape*>(); }
    int addOnMoved(moveCallback func);
    void removeOnMoved(int id);


protected:
    int id;
    int x = 0;
    int y = 0;
    int canvasSizeX;
    int canvasSizeY;
    bool selected = false;
    QColor color = Qt::green;
    vector<callback> onMoved;
    int callbackIdCounter = 0;
};
#endif // SHAPE_H
