#include "squareplugin.h"


Shape* SquarePlugin::create(int x, int y, QColor color, int size, int id)
{
    return new Square(x, y, color, size, id);
}
