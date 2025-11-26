#include "shapestorage.h"
using namespace std;

vector<Shape*> ShapeStorage::clone(ShapeType::FilterParams params)
{
    vector<Shape*> result;
    if (params.type == ShapeType::Type::ALL)
    {
        for (Shape* shape : storage)
        {
            result.push_back(shape->clone());
        }
    }
    else if (params.type == ShapeType::Type::SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect())
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                result.push_back(shape->clone());
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                result.push_back(shape->clone());
    }
    return result;
}

vector<Shape*> ShapeStorage::get(ShapeType::FilterParams params)
{
    vector<Shape*> result;
    if (params.type == ShapeType::Type::ALL)
    {
        result = storage;
    }
    else if (params.type == ShapeType::Type::SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                result.push_back(shape);
    }

    return result;
}

void ShapeStorage::add(Shape *iShape)
{
    iShape->changeCanvasSize(canvasSizeX, canvasSizeY);
    storage.push_back(iShape);
}

void ShapeStorage::draw(ShapeType::FilterParams type, QPainter *painter)
{
    vector<Shape*> result = ShapeStorage::get(type);
    for (Shape *shape : result)
        shape->draw(painter);
}

bool ShapeStorage::select(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->select();

    return result.size() > 0;
}

bool ShapeStorage::unSelect(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->unSelect();
    return result.size() > 0;
}

void ShapeStorage::remove(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* shape : result)
    {
        delete shape;
        auto it = std::find(storage.begin(), storage.end(), shape);
        if (it != storage.end())
            storage.erase(it);
    }
}

void ShapeStorage::remove(Shape *iShape)
{
    auto it = find(storage.begin(), storage.end(), iShape);
    if (it != storage.end())
    {
        storage.erase(it);
        // delete iShape;
    }
}

void ShapeStorage::moveRelative(ShapeType::FilterParams params, int x, int y)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* shape : result)
        shape->moveRelative(x, y);
}

void ShapeStorage::moveRelative(Shape* shape, int x, int y)
{
    shape->moveRelative(x, y);
}

void ShapeStorage::resizeRelative(ShapeType::FilterParams params, int iSize)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->resizeRelative(iSize);
}

void ShapeStorage::resizeRelative(Shape* shape, int iSize)
{
    shape->resizeRelative(iSize);
}

bool ShapeStorage::isExists(ShapeType::FilterParams params)
{
    if (params.type == ShapeType::Type::ALL)
    {
        return storage.size() > 0;
    }
    else if (params.type == ShapeType::Type::SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect())
                return true;
    }
    else if (params.type == ShapeType::Type::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                return true;
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                return true;
    }

    return false;
}

void ShapeStorage::changeCanvasSize(int iX, int iY)
{
    vector<Shape*> result = ShapeStorage::get(ShapeType::FilterParams(ShapeType::Type::ALL));
    canvasSizeX = iX;
    canvasSizeY = iY;
    for (Shape *shape : result)
        shape->changeCanvasSize(iX, iY);
}

void ShapeStorage::changeColor(ShapeType::FilterParams params, QColor color)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->changeColor(color);
}

void ShapeStorage::changeColor(Shape* shape, QColor color)
{
    shape->changeColor(color);
}

void ShapeStorage::addGroup(ShapeType::FilterParams params)
{
    Shape* group = new GroupShape();
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* shape : result)
    {
        group->add(shape);
        storage.erase(std::remove(storage.begin(), storage.end(), shape), storage.end());
    }
    storage.push_back(group);
}

void ShapeStorage::unGroup(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* group : result)
    {
        vector<Shape*> shapes = group->unGrouping();
        for (Shape* shape : shapes)
        {
            storage.push_back(shape);
        }
        auto it = std::remove(storage.begin(), storage.end(), group);
        storage.erase(it, storage.end());
    }
}

bool ShapeStorage::isSelectedInOneGroup()
{
    vector<Shape*> result = ShapeStorage::get(ShapeType::FilterParams(ShapeType::Type::SELECTED));
    return result.size() == 1 && result[0]->isGroup();
}

int ShapeStorage::count(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    return result.size();
}

void ShapeStorage::changeShapeType(Shape* shape, QString newType)
{
    Shape* newShape = ShapeFactory::create(newType, x, y, color, size);
    for (size_t i = 0; i < storage.size(); ++i)
    {
        if (storage[i] == shape)
        {
            storage[i] =
        }
    }
    // Shape* newShape = shape->changeTypeTo(newType);
    remove(shape);
    // add(newShape);
}

void ShapeStorage::saveInFile(QString iFile)
{
    QFile file(iFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "<ShapeStorage>" << "\n";
        for (auto shape : storage)
            shape->saveInFile(out, 1);
        out << "</ShapeStorage>";
        file.close();
    }
}

void ShapeStorage::load(QString iFile)
{
    QFile file(iFile);
    if (file.open(QIODevice::ReadOnly))
    {
        remove(ShapeType::FilterParams(ShapeType::Type::ALL));
        QTextStream in(&file);
        for (auto shape : createShapes(in))
            storage.push_back(shape);
    }
}

vector<Shape*> ShapeStorage::createShapes(QTextStream &in)
{
    QString line;
    vector<Shape*> localStorage;
    while (!in.atEnd())
    {
        line = in.readLine();
        QRegularExpression type("<(.*?)>");
        QRegularExpressionMatch typeMatch = type.match(line);
        if (typeMatch.hasMatch())
        {
            QString typeShape = typeMatch.captured(1);
            if (typeShape == "Circle")
            {
                Shape* shape = new Circle();
                shape->load(line);
                shape->changeCanvasSize(canvasSizeX, canvasSizeY);
                localStorage.push_back(shape);
            }
            else if (typeShape == "Square")
            {
                Shape* shape = new Square();
                shape->load(line);
                shape->changeCanvasSize(canvasSizeX, canvasSizeY);
                localStorage.push_back(shape);
            }
            else if (typeShape == "Triangle")
            {
                Shape* shape = new Triangle();
                shape->load(line);
                shape->changeCanvasSize(canvasSizeX, canvasSizeY);
                localStorage.push_back(shape);
            }
            else if (typeShape == "GroupStorage")
            {
                Shape* shape = new GroupShape();
                for (auto sh : createShapes(in))
                    shape->add(sh);
                localStorage.push_back(shape);
            }
            else if (typeShape == "/GroupStorage")
            {
                return localStorage;
            }
        }
    }
    return localStorage;
}
