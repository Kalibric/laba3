#include "paintwidget.h"
using namespace std;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    changeShapeType = new QMenu("Изменить фигуру", this);
    circleType = new QAction("Круг", this);
    squareType = new QAction("Квадрат", this);
    triangleType = new QAction("Триугольник", this);
    changeShapeType->addAction(circleType);
    changeShapeType->addAction(squareType);
    changeShapeType->addAction(triangleType);
    removeEvent = new QAction("Удалить", this);
    setColorEvent = new QAction("Изменить цвет", this);
    menuGroupingEvent = new QAction("Сгруппировать", this);
    menuUnGroupingEvent = new QAction("Разгруппировать", this);
    selectAllEvent = new QAction("Выделить все", this);
    connect(removeEvent, &QAction::triggered, this, &PaintWidget::removeAction);
    connect(setColorEvent, &QAction::triggered, this, &PaintWidget::setColorAction);
    connect(menuGroupingEvent, &QAction::triggered, this, &PaintWidget::groupingAction);
    connect(menuUnGroupingEvent, &QAction::triggered, this, &PaintWidget::unGroupingAction);
    connect(selectAllEvent, &QAction::triggered, this, &PaintWidget::selectAllAction);
    connect(circleType, &QAction::triggered, this, &PaintWidget::changeShapeTypeToCircle);
    connect(squareType, &QAction::triggered, this, &PaintWidget::changeShapeTypeToSquare);
    connect(triangleType, &QAction::triggered, this, &PaintWidget::changeShapeTypeToTriangle);

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    storage->draw(TypeShape::ALL, painter);
    arrowStorage->draw(painter);
    painter->end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    storage->changeCanvasSize(size().width(), size().height());
    QWidget::resizeEvent(event);
}

void PaintWidget::wheelEvent(QWheelEvent *event)
{
    storage->resizeRelative(
        TypeShape::SELECTED,
        event->angleDelta().y() > 0 ? 5 : -5);
    update();
}

void PaintWidget::setGroupingEvent(QAction *newGroupingEvent)
{
    if (menuGroupingEvent == newGroupingEvent)
        return;
    menuGroupingEvent = newGroupingEvent;
    emit groupingEventChanged();
}

void PaintWidget::resetGroupingEvent()
{
    setGroupingEvent({});
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        if (isMoveEvent)
            manager.add(new MoveShape(storage, TypeShape::SELECTED, lastPosition.x() - lastPositionBefore.x(), lastPosition.y() - lastPositionBefore.y()), false);
        else if (isResizeEvent)
            manager.add(new ResizeShape(storage, TypeShape::SELECTED, resize), false);
        resize = 0;
        isResizeEvent = false;
        isMoveEvent = false;
        setCursor(Qt::ArrowCursor);
        if (lastPosition == lastPositionBefore)
        {
            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            if (!isSelectEvent)
            {
                if (storage->isExists(FilterShape(TypeShape::SELECTED, x, y)))
                {
                    if (ctrlPressed)
                        unSelect(FilterShape(TypeShape::TO_COORDS_SELECTED, x, y));
                    else
                        unSelect(TypeShape::ALL);
                }
                else
                {
                    unSelect(TypeShape::ALL);
                    manager.add(new AddShape(storage, x, y, color, currentShapeType));
                }
                update();
            }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        contextMenu = new QMenu(this);
        if (storage->isExists(TypeShape::SELECTED))
        {
            contextMenu->addAction(removeEvent);
            contextMenu->addAction(setColorEvent);
            contextMenu->addMenu(changeShapeType);
            if (storage->count(TypeShape::SELECTED) > 1)
                   contextMenu->addAction(menuGroupingEvent);
            else if (storage->count(TypeShape::SELECTED) == 1 && storage->isExists(TypeShape::SELECTED_IS_GROUP))
                contextMenu->addAction(menuUnGroupingEvent);
        }
        contextMenu->addAction(selectAllEvent);
        contextMenu->exec(event->globalPos());
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    isSelectEvent = false;
    if (event->button() == Qt::LeftButton)
    {
        bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
        if (storage->isExists(FilterShape(TypeShape::TO_COORDS_UNSELECTED, x, y)))
        {
            if (!ctrlPressed)
                unSelect(TypeShape::ALL);
            isSelectEvent = true;
            select(FilterShape(TypeShape::TO_COORDS_UNSELECTED, x, y));
        }

        lastPositionBefore = event->pos();
        lastPosition = event->pos();
        update();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (storage->isExists(TypeShape::SELECTED))
    {
        bool isResizeArea = storage->isExists(FilterShape(TypeShape::RESIZE_AREA_SELECTED, x, y));
        if (!isResizeEvent && !isMoveEvent)
        {
            if (isResizeArea)
                setCursor(Qt::SizeFDiagCursor);
            else
                setCursor(Qt::ArrowCursor);
        }
        if (event->buttons() & Qt::LeftButton)
        {
            int dx = event->pos().x() - lastPosition.x();
            int dy = event->pos().y() - lastPosition.y();
            if ((isResizeArea || isResizeEvent) && !isMoveEvent)
            {
                resize += (dx + dy) / 2;
                if (!isResizeEvent)
                    setCursor(Qt::SizeFDiagCursor);
                isResizeEvent = true;
                storage->resizeRelative(TypeShape::SELECTED, (dx + dy) / 2);
            }
            else
            {
                if (!isMoveEvent)
                    setCursor(Qt::ClosedHandCursor);
                isMoveEvent = true;
                storage->moveRelative(TypeShape::SELECTED, dx, dy);
            }
            lastPosition = event->pos();
        }
        update();
    }

}

void PaintWidget::keyPressEvent(QKeyEvent *event)
{
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
    if (event->key() == Qt::Key_Delete)
    {
        manager.add(new RemoveShape(storage, TypeShape::SELECTED));
        update();
    }
    else if (event->key() == Qt::Key_A && ctrlPressed)
    {
        select(TypeShape::ALL);
        update();
    }
    else if (event->key() == Qt::Key_Equal)
    {
        storage->resizeRelative(TypeShape::SELECTED, 5);
        update();
    }
    else if (event->key() == Qt::Key_Minus)
    {
        storage->resizeRelative(TypeShape::SELECTED, -5);
        update();
    }
    else if (event->key() == Qt::Key_Left)
    {
        storage->moveRelative(TypeShape::SELECTED, -1, 0);
        update();
    }
    else if (event->key() == Qt::Key_Up)
    {
        storage->moveRelative(TypeShape::SELECTED, 0, -1);
        update();
    }
    else if (event->key() == Qt::Key_Right)
    {
        storage->moveRelative(TypeShape::SELECTED, 1, 0);
        update();
    }
    else if (event->key() == Qt::Key_Down)
    {
        storage->moveRelative(TypeShape::SELECTED, 0, 1);
        update();
    }
    else if (event->key() == Qt::Key_Z && ctrlPressed)
    {
        manager.undo();
        validateGroupingButton();
        update();
    }
    else if (event->key() == Qt::Key_Y && ctrlPressed)
    {
        manager.execute();
        validateGroupingButton();
        update();
    }
    else if (event->key() == Qt::Key_C && ctrlPressed)
    {
        copyShapes = storage->clone(TypeShape::SELECTED);
    }
    else if (event->key() == Qt::Key_V && ctrlPressed)
    {
        for (Shape* shape : copyShapes)
        {
            if (shape->isGroup())
            {
                manager.add(new AddShape(storage, shape, false));
                vector<Shape*> shapes = storage->get(TypeShape::ALL);
                if (shapes.size() > 0)
                    shapes[shapes.size() - 1]->moveRelative(30, 30);
            }
            else
                manager.add(new AddShape(storage, shape->getX()+30, shape->getY()+30, shape->getColor(), QString::fromStdString(shape->type())));
        }
    }
}

void PaintWidget::validateGroupingButton()
{
    int count = storage->count(TypeShape::SELECTED);
    if (count > 1)
        emit groupingButton();
    else if (count == 1 && storage->isExists(TypeShape::SELECTED_IS_GROUP))
        emit unGroupingButton();
    else
        emit deactivateButton();
}

void PaintWidget::setStorage(ShapeStorage *iStorage)
{
    disconnect(storage, &ShapeStorage::selectUpdated, this, &PaintWidget::selectUpdated);
    delete arrowStorage;
    delete storage;
    storage = iStorage;
    arrowStorage = new ArrowStorage(storage);
    connect(storage, &ShapeStorage::selectUpdated, this, &PaintWidget::selectUpdated);
}

void PaintWidget::changeSelectedShape(QString iSelectedShape)
{
    currentShapeType = iSelectedShape;
}

void PaintWidget::changeColor(QColor iColor)
{
    if (storage->isExists(TypeShape::SELECTED))
        manager.add(new ChangeColorShape(storage, TypeShape::SELECTED, color, iColor));
    color = iColor;
}

void PaintWidget::groupingButtonClick()
{
    if (storage->count(TypeShape::SELECTED_IS_GROUP) == 1 && storage->count(TypeShape::SELECTED) == 1)
    {
        manager.add(new UnGroupingShape(storage, TypeShape::SELECTED));
        emit groupingButton();
    }
    else if (storage->count(TypeShape::SELECTED) > 1)
    {
        manager.add(new GroupingShape(storage, TypeShape::SELECTED));
        emit unGroupingButton();
    }
    update();
}

void PaintWidget::select(FilterShape params)
{
    storage->select(params);
    vector<Shape*> shapes = storage->get(TypeShape::SELECTED);
    if (storage->count(TypeShape::SELECTED_IS_GROUP) == 1 && shapes.size() == 1)
    {
        emit unGroupingButton();
        emit arrowButtonDisable();
    }
    else if (shapes.size() > 1)
        emit groupingButton();
    if (shapes.size() == 1)
    {
        firstSelected = shapes[0];
    }
    if (shapes.size() == 2 && !arrowStorage->isExists(firstSelected, shapes[0] == firstSelected ? shapes[1] : shapes[0]))
        emit arrowButtonEnable();
    else
        emit arrowButtonDisable();

}

void PaintWidget::unSelect(FilterShape params)
{
    storage->unSelect(params);
    if (storage->count(TypeShape::SELECTED_IS_GROUP) == 1)
        emit unGroupingButton();
    else if (storage->count(TypeShape::SELECTED) > 1)
        emit groupingButton();
    else
    {
        emit deactivateButton();
        emit arrowButtonDisable();
    }
}

void PaintWidget::saveButton()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранение", "Shape.txt");
    storage->saveInFile(filename);
}

void PaintWidget::loadButton()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выбор файла", "Shape.txt");
    manager.clear();
    storage->load(filename);
    update();
}

void PaintWidget::removeAction()
{
    storage->remove(TypeShape::SELECTED);
}

void PaintWidget::setColorAction()
{
    QColor newColor = QColorDialog::getColor(Qt::green, this, "");
    if (newColor.isValid())
        manager.add(new ChangeColorShape(storage, TypeShape::SELECTED, color, newColor));
}

void PaintWidget::groupingAction()
{
    manager.add(new GroupingShape(storage, TypeShape::SELECTED));
}

void PaintWidget::unGroupingAction()
{
    manager.add(new UnGroupingShape(storage, TypeShape::SELECTED));
}

void PaintWidget::selectAllAction()
{
    storage->select(TypeShape::ALL);
}

void PaintWidget::changeShapeTypeToCircle()
{
    manager.add(new ChangeShapeType(storage, TypeShape::SELECTED, "Circle"));
    update();
}

void PaintWidget::changeShapeTypeToSquare()
{
    manager.add(new ChangeShapeType(storage, TypeShape::SELECTED, "Square"));
    update();
}

void PaintWidget::changeShapeTypeToTriangle()
{
    manager.add(new ChangeShapeType(storage, TypeShape::SELECTED, "Triangle"));
    update();
}

void PaintWidget::selectUpdated()
{
    update();
}

void PaintWidget::uniArrowButton()
{
    vector<Shape*> shapes = storage->get(TypeShape::SELECTED);
    if (shapes.size() > 1)
    {
        if (!arrowStorage->isExists(firstSelected, shapes[0] == firstSelected ? shapes[1] : shapes[0]))
        {
            arrowStorage->addArrow(new UniArrow(firstSelected, shapes[0] == firstSelected ? shapes[1] : shapes[0]));
            update();
        }
    }
}

void PaintWidget::biArrowButton()
{
    vector<Shape*> shapes = storage->get(TypeShape::SELECTED);
    if (shapes.size() > 1)
    {
        if (!arrowStorage->isExists(firstSelected, shapes[0] == firstSelected ? shapes[1] : shapes[0]))
        {
            arrowStorage->addArrow(new BiArrow(firstSelected, shapes[0] == firstSelected ? shapes[1] : shapes[0]));
            update();
        }
    }
}
