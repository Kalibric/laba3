#ifndef SQUAREPLUGIN_H
#define SQUAREPLUGIN_H

#include <QObject>
#include "IShapePlugin.h"
#include "square.h"

class SquarePlugin : public QObject, public IShapePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IShapePlugin_iid)
    Q_INTERFACES(IShapePlugin)

public:
    Shape* create(int x, int y, QColor color = Qt::green, int size=50, int id=-1) override;
    QString name() const override
    {
        return "Square";
    }
};

#endif // SQUAREPLUGIN_H
