#include "triangleplugin.h"

Shape* TrianglePlugin::create(int x, int y, QColor color, int size, int id)
{
    return new Triangle(x, y, color, size, id);
}
