#include "circleplugin.h"

Shape* CirclePlugin::create(int x, int y, QColor color, int size, int id)
{
    return new Circle(x, y, color, size, id);
}
