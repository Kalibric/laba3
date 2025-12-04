#include "mainwindow.h"
#include "shapefactory.h"
#include "groupshape.h"
#include "pluginloader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    PluginLoader::loadPlugins(
        QCoreApplication::applicationDirPath() + "/plugins"
        );
    ShapeFactory::registerShape(
        "GroupShape",
        [](int x, int y, QColor color, int size, int id) -> Shape* {
            return new GroupShape(x, y, color, size, id);
        },
        false
        );
    w.updateShapeTypes();
    w.show();
    return a.exec();
}
