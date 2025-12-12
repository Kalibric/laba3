#include "shapeloader.h"

vector<Shape*> ShapeLoader::load(QTextStream &file)
{
    QString line;
    vector<Shape*> result;
    while (!file.atEnd())
    {
        line = file.readLine();
        QRegularExpression type("<(.*?)>");
        QRegularExpressionMatch typeMatch = type.match(line);
        if (typeMatch.hasMatch())
        {
            QString typeShape = typeMatch.captured(1);
            for (ShapeFactory::RegisterShape shapeType : ShapeFactory::getRegistredShapes())
                if (shapeType.name == typeShape)
                {
                    Shape* shape = ShapeFactory::create(shapeType.name, 0, 0);
                    if (shape != nullptr)
                    {
                        shape->load(file, line);
                        result.push_back(shape);
                    }
                }
                else if (typeShape[0] == "/")
                    return result;
        }
    }
    return result;
}

void ShapeLoader::save(QTextStream &file, vector<Shape*> shapes, int level)
{
    for (Shape* shape : shapes)
        shape->saveInFile(file, level);
}
