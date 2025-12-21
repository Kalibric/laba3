#include "shapestorage.h"

vector<Shape*> ShapeStorage::clone(FilterShape params)
{
    vector<Shape*> result;
    for (Shape* shape : ShapeStorage::get(params))
        result.push_back(shape->clone());
    return result;

}

vector<Shape*> ShapeStorage::get(FilterShape params)
{
    vector<Shape*> result;
    if (params.type == TypeShape::ALL)
    {
        result = storage;
    }
    else if (params.type == TypeShape::SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == TypeShape::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == TypeShape::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == TypeShape::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == TypeShape::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == TypeShape::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                result.push_back(shape);
    }
    else if (params.type == TypeShape::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == TypeShape::SELECTED_IS_GROUP)
    {
        for (Shape* shape : storage)
            if (shape->isGroup() && shape->isSelect())
                result.push_back(shape);
    }
    return result;
}

void ShapeStorage::add(Shape *iShape, bool isEmit)
{
    iShape->changeCanvasSize(canvasSizeX, canvasSizeY);
    storage.push_back(iShape);
    if (isEmit)
        emit storageUpdated();
}

void ShapeStorage::add(vector<Shape*> shapes, bool isEmit)
{
    for (Shape *shape : shapes)
    {
        shape->changeCanvasSize(canvasSizeX, canvasSizeY);
        storage.push_back(shape);
    }
    if (isEmit)
        emit storageUpdated();
}

void ShapeStorage::draw(FilterShape type, QPainter *painter)
{
    vector<Shape*> result = get(type);
    for (Shape *shape : result)
        shape->draw(painter);
}

bool ShapeStorage::select(FilterShape params)
{
    bool success = false;
    vector<Shape*> result = get(params);
    for (Shape *shape : result)
        if (!shape->isSelect())
        {
            shape->select();
            success = true;
        }
    if (success)
        emit selectUpdated();
    return success;
}

bool ShapeStorage::unSelect(FilterShape params)
{
    bool success = false;
    vector<Shape*> result = get(params);
    for (Shape *shape : result)
        if (shape->isSelect())
        {
            shape->unSelect();
            success = true;
        }
    if (success)
        emit selectUpdated();

    return success;
}

bool ShapeStorage::select(Shape *shape)
{
    bool success = false;
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == shape->getID())
        {
            success = true;
            storage[i]->select();
            break;
        }
    if (success)
        emit selectUpdated();
    return success;
}

bool ShapeStorage::unSelect(Shape *shape)
{
    bool success = false;
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == shape->getID())
        {
            success = true;
            storage[i]->unSelect();
            break;
        }
    if (success)
        emit selectUpdated();
    return success;
}

void ShapeStorage::remove(FilterShape params, bool isEmit)
{
    vector<Shape*> result = get(params);
    bool success = false;
    for (Shape* shape : result)
    {
        delete shape;
        auto it = std::find(storage.begin(), storage.end(), shape);
        if (it != storage.end())
        {
            emit shapeDeletedBefore(shape);
            success = true;
            storage.erase(it);
        }
    }
    if (success && isEmit)
        emit storageUpdated();
}

void ShapeStorage::remove(Shape *iShape, bool isEmit)
{
    if (iShape == nullptr)
        return;

    bool success = false;
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == iShape->getID())
        {
            emit shapeDeletedBefore(storage[i]);
            delete storage[i];
            storage.erase(storage.begin() + i);
            success = true;
            break;
        }

    if (success && isEmit)
        emit storageUpdated();
}

void ShapeStorage::remove(vector<Shape*> shapes, bool isEmit)
{
    bool success = false;
    for (Shape *shape : shapes)
    {
        for (size_t i = 0; i < storage.size(); i++)
            if (storage[i]->getID() == shape->getID())
            {
                emit shapeDeletedBefore(storage[i]);
                success = true;
                delete storage[i];
                storage.erase(storage.begin() + i);
                break;
            }
    }
    if (success && isEmit)
        emit storageUpdated();
}

void ShapeStorage::moveRelative(FilterShape params, int x, int y)
{
    vector<Shape*> result = get(params);
    for (Shape* shape : result)
        shape->moveRelative(x, y);
    if (!result.empty())
        emit storageUpdated();
}

void ShapeStorage::moveRelative(Shape* shape, int x, int y)
{
    bool success = false;
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == shape->getID())
        {
            success = true;
            storage[i]->moveRelative(x, y);
        }
    if (success)
        emit storageUpdated();
}

void ShapeStorage::resizeRelative(FilterShape params, int iSize)
{
    vector<Shape*> result = get(params);
    for (Shape *shape : result)
        shape->resizeRelative(iSize);
}

void ShapeStorage::resizeRelative(Shape* shape, int iSize)
{
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == shape->getID())
            storage[i]->resizeRelative(iSize);
}

bool ShapeStorage::isExists(FilterShape params)
{
    return ShapeStorage::get(params).size() > 0;
}

void ShapeStorage::changeCanvasSize(int iX, int iY)
{
    vector<Shape*> result = get(TypeShape::ALL);
    canvasSizeX = iX;
    canvasSizeY = iY;
    for (Shape *shape : result)
        shape->changeCanvasSize(iX, iY);
}

void ShapeStorage::changeColor(FilterShape params, QColor color)
{
    vector<Shape*> result = get(params);
    for (Shape *shape : result)
        shape->changeColor(color);
}

void ShapeStorage::changeColor(Shape* shape, QColor color)
{
    for (size_t i = 0; i < storage.size(); i++)
        if (storage[i]->getID() == shape->getID())
            storage[i]->changeColor(color);
}

void ShapeStorage::addGroup(FilterShape params)
{
    // Shape* group = new GroupShape;
    // vector<Shape*> result = get(params);
    // for (Shape* shape : result)
    // {
    //     group->add(shape);
    //     storage.erase(std::remove(storage.begin(), storage.end(), shape), storage.end());
    // }
    // storage.push_back(group);
}

void ShapeStorage::unGroup(FilterShape params)
{
    vector<Shape*> result = get(params);
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
    if (!result.empty())
        emit storageUpdated();
}

int ShapeStorage::count(FilterShape params)
{
    vector<Shape*> result = get(params);
    return result.size();
}

void ShapeStorage::changeShapeType(Shape* shape, QString newType)
{
    bool success = false;
    for (size_t i = 0; i < storage.size(); ++i)
    {
        if (storage[i]->getID() == shape->getID())
        {
            success = true;
            storage[i] = ShapeFactory::changeType(storage[i], newType);
            storage[i]->changeCanvasSize(canvasSizeX, canvasSizeY);
            storage[i]->select();
            break;
        }
    }
    if (success)
        emit storageUpdated();
}

void ShapeStorage::changeShapeType(vector<Shape*> shapes, QString newType)
{
    bool success = false;
    for (Shape* shape : shapes)
    {
        for (size_t i = 0; i < storage.size(); ++i)
        {
            if (storage[i]->getID() == shape->getID())
            {
                success = true;
                storage[i] = ShapeFactory::changeType(storage[i], newType);
                storage[i]->changeCanvasSize(canvasSizeX, canvasSizeY);
                storage[i]->select();
                break;
            }
        }
    }
    if (success)
        emit storageUpdated();
}

void ShapeStorage::saveInFile(QString iFile)
{
    QFile file(iFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "<ShapeStorage>" << "\n";
        ShapeLoader::save(out, storage, 1);
        out << "</ShapeStorage>";
        file.close();
    }
}

void ShapeStorage::load(QString iFile)
{
    QFile file(iFile);
    if (file.open(QIODevice::ReadOnly))
    {
        remove(TypeShape::ALL);
        QTextStream in(&file);
        vector<Shape*> newStorage = ShapeLoader::load(in);
        for (Shape* shape : newStorage)
        {
            shape->changeCanvasSize(canvasSizeX, canvasSizeY);
            storage.push_back(shape);
        }
    }
}

void ShapeStorage::setProperty(FilterShape params, const char *key, QVariant value)
{
    bool success = false;
    vector<Shape*> shapes = get(params);
    for (Shape *shape : shapes)
    {
        success = true;
        shape->setProperty(key, value);
    }
    if (success)
        emit storageUpdated();
}
