#ifndef SHAPESTORAGE_H
#define SHAPESTORAGE_H

#include <QDebug>
#include <vector>
#include "shape.h"
#include <QFile>
#include <QRegularExpression>
using namespace std;

class ShapeStorage
{
public:
    ShapeStorage();
    void add(Shape *iShape);
    void draw(ShapeType::FilterParams params, QPainter *painter);
    bool select(ShapeType::FilterParams params);
    bool unSelect(ShapeType::FilterParams params);
    void remove(ShapeType::FilterParams params);
    void moveRelative(ShapeType::FilterParams params, int x, int y);
    void resizeRelative(ShapeType::FilterParams params, int iSize);
    bool isExists(ShapeType::FilterParams params);
    void changeCanvasSize(int x, int y);
    void changeColor(ShapeType::FilterParams params, QColor color);
    void addGroup(ShapeType::FilterParams params);
    void unGroup(ShapeType::FilterParams params);
    bool isSelectedInOneGroup();
    int count(ShapeType::FilterParams params);
    void saveInFile();
    void load();

private:
    vector<Shape*> storage;
    vector<Shape*> get(ShapeType::FilterParams type);
    vector<Shape*> createShapes(QTextStream &in);
    int canvasSizeX = 0;
    int canvasSizeY = 0;
};

// class GroupStorage : public ShapeStorage
// {
// public:
//     GroupStorage()
//     {
//         name = "G-" + 1;
//     }

//     void Grouping(ShapeStorage &storage){
//         for (int i = storage.storage.size()-1; i>=0; i--)
//         {
//             if (storage.storage[i]->isSelect())
//             {
//                 this->storage.push_back(storage.storage[i]);
//                 storage.storage.erase(storage.storage.begin()+i, storage.storage.begin()+i+1);
//             }
//         }
//         //storage->storage.push_back(this->storage);

//     }

// private:
//     vector<Shape*> storage;
//     vector<GroupStorage*> s;
//     string name;
// };

#endif // SHAPESTORAGE_H
