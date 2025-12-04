#include "square.h"

Square::Square()
{

}

Square::Square(Square &iSquare) : Shape(iSquare)
{
    lenght = iSquare.lenght;
}

Square::Square(int iX, int iY, QColor iColor, int iLength, int _id) : Shape(iX, iY, iColor, _id)
{
    lenght = iLength;
}

bool Square::isContaints(int iX, int iY)
{
    return (iX >= x - lenght && iX <= x + lenght &&
            iY >= y - lenght && iY <= y + lenght);
}

void Square::draw(QPainter *painter)
{
    painter->setPen(selected ? QPen(Qt::white, 2, Qt::DashLine) : QPen(Qt::black, 1));
    painter->setBrush(color);
    painter->drawRect(x-lenght, y-lenght, lenght*2, lenght*2);
    if (selected)
    {
        painter->setBrush(Qt::gray);
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(x+lenght-10, y+lenght-10, 10, 10);
    }
}

void Square::resizeRelative(int iSize)
{
    if (lenght + iSize < 5)
        lenght = 5;
    else if (lenght + iSize > 150)
        lenght = 150;
    else
        lenght += iSize;

    if (!validateCoord(x, y))
        correctionCoord();
}

bool Square::validateCoord(int iX, int iY)
{
    return (iX + lenght) < canvasSizeX &&
           (iX - lenght) > 0 &&
           (iY + lenght) < canvasSizeY &&
           (iY - lenght) > 0;
}

bool Square::validateCoordRelative(int iX, int iY)
{
    return (x + iX + lenght) < canvasSizeX &&
           (x + iX - lenght) > 0 &&
           (y + iY + lenght) < canvasSizeY &&
           (y + iY - lenght) > 0;
}

void Square::correctionCoord()
{
    if ((x + lenght) > canvasSizeX)
        x = canvasSizeX - lenght;
    else if ((x - lenght) < 0)
        x = lenght;

    if ((y + lenght) > canvasSizeY)
        y = canvasSizeY - lenght;
    else if ((y - lenght) < 0)
        y = lenght;
}

bool Square::isResizeArea(int iX, int iY)
{
    return iX >= x + lenght - 10 && iX <= x + lenght &&
           iY >= y + lenght - 10 && iY <= y + lenght;
}

void Square::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<Square>" << "lenght:" << lenght << ", x:" << x << ", y:" << y << ", color:" << color.name() << "</Square>" << "\n";
}

void Square::load(QTextStream &file, QString &text)
{
    QRegularExpression lenghtExp("lenght:\\s*(\\d+)");
    QRegularExpression xExp("x:\\s*(\\d+)");
    QRegularExpression yExp("y:\\s*(\\d+)");
    QRegularExpression colorExp("color:\\s*(#[0-9A-Fa-f]{6})");

    QRegularExpressionMatch lenghtMatch = lenghtExp.match(text);
    QRegularExpressionMatch xMatch = xExp.match(text);
    QRegularExpressionMatch yMatch = yExp.match(text);
    QRegularExpressionMatch colorMatch = colorExp.match(text);

    if (lenghtMatch.hasMatch())
        lenght = lenghtMatch.captured(1).toInt();
    if (xMatch.hasMatch())
        x = xMatch.captured(1).toInt();
    if (yMatch.hasMatch())
        y = yMatch.captured(1).toInt();
    if (colorMatch.hasMatch())
        color = colorMatch.captured(1);
}

Square* Square::clone()
{
    return new Square(*this);
}

int Square::getSize()
{
    return lenght;
}
