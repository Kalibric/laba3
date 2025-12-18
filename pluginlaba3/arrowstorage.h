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
    int add(Arrow *iArrow);
    void draw(QPainter *painter);
    bool isExists(Shape *iA, Shape *iB);
    void remove(int id);

private:
    struct ArrowEntry
    {
        int id;
        Arrow *arrow;
    };
    vector<ArrowEntry*> arrows;
    ShapeStorage *storage;
    int arrowID = 0;

private slots:
    void shapeDeletedBefore(Shape* shape);
};

#endif // ARROWSTORAGE_H
