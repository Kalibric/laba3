#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QString>
#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include "IShapePlugin.h"
#include "shapefactory.h"
#include "shape_global.h"


class SHAPE_CORE_EXPORT PluginLoader
{
public:
    static void loadPlugins(const QString& path);
};

#endif // PLUGINLOADER_H
