#ifndef ARROWSTORAGE_H
#define ARROWSTORAGE_H

#include "arrow.h"
#include "shapestorage.h"
#include <QObject>
class ArrowStorage : public QObject
{
    Q_OBJECT
public:
    ArrowStorage(ShapeStorage *iStorage);
    ~ArrowStorage();
    void addArrow(Arrow *iArrow);
    void draw(QPainter *painter);
    bool isExists(Shape *iA, Shape *iB);

private:
    vector<Arrow*> arrows;
    ShapeStorage *storage;

private slots:
    void shapeDeletedBefore(Shape* shape);
};

#endif // ARROWSTORAGE_H
