#ifndef CIRCLEPLUGIN_H
#define CIRCLEPLUGIN_H

#include <QObject>
#include "IShapePlugin.h"
#include "circle.h"

class CirclePlugin : public QObject, public IShapePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IShapePlugin_iid)
    Q_INTERFACES(IShapePlugin)

public:
    Shape* create(int x, int y, QColor color = Qt::green, int size=50, int id=-1) override;
    QString name() const override
    {
        return "Circle";
    }
};

#endif // CIRCLEPLUGIN_H
