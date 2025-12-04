#include "pluginloader.h"

void PluginLoader::loadPlugins(const QString& path)
{
    QDir pluginsDir(path);

    if (!pluginsDir.exists())
        return;

    for (QString file : pluginsDir.entryList(QDir::Files)) {
        QString abs = pluginsDir.absoluteFilePath(file);
        QPluginLoader loader(abs);

        QObject* pluginObj = loader.instance();
        if (!pluginObj)
        {
            qWarning() << "Ошибка загрузки плагина: " << abs << loader.errorString();
            continue;
        }

        IShapePlugin* shapePlugin = qobject_cast<IShapePlugin*>(pluginObj);
        if (!shapePlugin)
        {
            qWarning() << "В плагине не реализован интерфейс IShapePlugin: " << abs;
            continue;
        }

        QString typeName = shapePlugin->name();
        qDebug() << "Загружен плагин: " << typeName;

        ShapeFactory::registerShape(typeName, [shapePlugin](int x, int y, QColor color, int size, int id) -> Shape* {
            Shape* shape = shapePlugin->create(x, y, color, size, id);
            return shape;
        });
    }
}
