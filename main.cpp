#include "widget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "windowscheduler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "my_snake_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    WindowScheduler m_scheduler;//创建界面调度器
    return a.exec();
}
