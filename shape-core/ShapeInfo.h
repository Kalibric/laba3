#ifndef SHAPEINFO_H
#define SHAPEINFO_H

#include "vector"
#include "string"

using namespace std;
struct ShapeInfo
{
    string type;
    vector<ShapeInfo> children;
};


#endif // SHAPEINFO_H
