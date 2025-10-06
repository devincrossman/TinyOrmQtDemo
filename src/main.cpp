#include <QApplication>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Load stylesheet from external file
    QFile file(":/styles/darkstyle.qss");
    if(file.open(QFile::ReadOnly)) {
        QString style = QLatin1String(file.readAll());
        app.setStyleSheet(style);
        file.close();
    } else {
        qWarning() << "Could not open stylesheet file";
    }
    MainWindow window;
    window.show();
    return app.exec();
}
