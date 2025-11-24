#include "paintwidget.h"
using namespace std;
int s = 0;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    storage.changeCanvasSize(this->size().width(), this->size().height());
    setMouseTracking(true);
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
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    storage.draw(ShapeType::FilterParams(ShapeType::Type::ALL), painter);
    painter->end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    storage.changeCanvasSize(size().width(), size().height());
    QWidget::resizeEvent(event);
}

void PaintWidget::wheelEvent(QWheelEvent *event)
{
    storage.resizeRelative(
        ShapeType::FilterParams(ShapeType::Type::SELECTED),
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
    setGroupingEvent({}); // TODO: Adapt to use your actual default value
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        isResizeEvent = false;
        isMoveEvent = false;
        setCursor(Qt::ArrowCursor);
        if (lastPosition == lastPositionBefore)
        {
            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            if (!isSelectEvent)
            {
                if (storage.isExists(ShapeType::FilterParams(ShapeType::Type::SELECTED, x, y)))
                {
                    if (ctrlPressed)
                        unSelect(ShapeType::FilterParams(ShapeType::Type::TO_COORDS_SELECTED, x, y));
                    else
                        unSelect(ShapeType::FilterParams(ShapeType::Type::ALL));
                }
                else
                {
                    unSelect(ShapeType::FilterParams(ShapeType::Type::ALL));
                    storage.add(x, y);
                }
                update();
            }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        contextMenu = new QMenu(this);
        if (storage.isExists(ShapeType::FilterParams(ShapeType::Type::SELECTED)))
        {
            contextMenu->addAction(removeEvent);
            contextMenu->addAction(setColorEvent);
            if (storage.count(ShapeType::FilterParams(ShapeType::Type::SELECTED)) > 1)
            {
                contextMenu->addAction(menuGroupingEvent);
            }
            else if (storage.count(ShapeType::FilterParams(ShapeType::Type::SELECTED)) == 1 && storage.isSelectedInOneGroup())
            {
                contextMenu->addAction(menuUnGroupingEvent);
            }
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
        if (storage.isExists(ShapeType::FilterParams(ShapeType::Type::TO_COORDS_UNSELECTED, x, y)))
        {
            if (!ctrlPressed)
                unSelect(ShapeType::FilterParams(ShapeType::Type::ALL));
            isSelectEvent = true;
            select(ShapeType::FilterParams(ShapeType::Type::TO_COORDS_UNSELECTED, x, y));
        }

        lastPositionBefore = event->pos();
        lastPosition = event->pos();
        update();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (storage.isExists(ShapeType::FilterParams(ShapeType::Type::SELECTED)))
    {
        bool isResizeArea = storage.isExists(ShapeType::FilterParams(ShapeType::Type::RESIZE_AREA_SELECTED, x, y));
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
                if (!isResizeEvent)
                    setCursor(Qt::SizeFDiagCursor);
                isResizeEvent = true;
                storage.resizeRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), (dx + dy) / 2);
            }
            else
            {
                if (!isMoveEvent)
                    setCursor(Qt::ClosedHandCursor);
                isMoveEvent = true;
                storage.moveRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), dx, dy);
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
        storage.remove(ShapeType::FilterParams(ShapeType::Type::SELECTED));
        update();
    }
    else if (event->key() == Qt::Key_A && ctrlPressed)
    {
        select(ShapeType::FilterParams(ShapeType::Type::ALL));
        update();
    }
    else if (event->key() == Qt::Key_Equal)
    {
        storage.resizeRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), 5);
        update();
    }
    else if (event->key() == Qt::Key_Minus)
    {
        storage.resizeRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), -5);
        update();
    }
    else if (event->key() == Qt::Key_Left)
    {
        storage.moveRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), -1, 0);
        update();
    }
    else if (event->key() == Qt::Key_Up)
    {
        storage.moveRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), 0, -1);
        update();
    }
    else if (event->key() == Qt::Key_Right)
    {
        storage.moveRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), 1, 0);
        update();
    }
    else if (event->key() == Qt::Key_Down)
    {
        storage.moveRelative(ShapeType::FilterParams(ShapeType::Type::SELECTED), 0, 1);
        update();
    }
}

void PaintWidget::changeSelectedShape(QString iSelectedShape)
{
    storage.changeCurrentShape(iSelectedShape);
}

void PaintWidget::changeColor(QColor iColor)
{
    color = iColor;
    storage.changeColor(ShapeType::FilterParams(ShapeType::Type::SELECTED), iColor);
}

void PaintWidget::groupingButtonClick()
{
    if (storage.isSelectedInOneGroup())
        storage.unGroup(ShapeType::FilterParams(ShapeType::Type::SELECTED));
    else
        storage.addGroup(ShapeType::FilterParams(ShapeType::Type::SELECTED));
    if (storage.isSelectedInOneGroup())
        emit unGroupingButton();
    else
        emit groupingButton();
    update();
}

void PaintWidget::select(ShapeType::FilterParams params)
{
    storage.select(params);
    if (storage.isSelectedInOneGroup())
        emit unGroupingButton();
    else if (storage.count(ShapeType::FilterParams(ShapeType::Type::SELECTED)) > 1)
        emit groupingButton();
}

void PaintWidget::unSelect(ShapeType::FilterParams params)
{
    storage.unSelect(params);
    if (storage.isSelectedInOneGroup())
        emit unGroupingButton();
    else if (storage.count(ShapeType::FilterParams(ShapeType::Type::SELECTED)) > 1)
        emit groupingButton();
    else
        emit deactivateButton();
}

void PaintWidget::saveButton()
{
    storage.saveInFile();
}

void PaintWidget::loadButton()
{
    storage.load();
    update();
}

void PaintWidget::removeAction()
{
    storage.remove(ShapeType::FilterParams(ShapeType::Type::SELECTED));
}

void PaintWidget::setColorAction()
{
    storage.changeColor(ShapeType::FilterParams(ShapeType::Type::SELECTED), color);
}

void PaintWidget::groupingAction()
{
    storage.addGroup(ShapeType::FilterParams(ShapeType::Type::SELECTED));
}

void PaintWidget::unGroupingAction()
{
    storage.unGroup(ShapeType::FilterParams(ShapeType::Type::SELECTED));
}

void PaintWidget::selectAllAction()
{
    storage.select(ShapeType::FilterParams(ShapeType::Type::ALL));
}
