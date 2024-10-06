#include "widget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "windowscheduler.h"

void initSystem();
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
    ///////////////////////////////////////////


    initSystem();
    WindowScheduler m_scheduler;//创建界面调度器
    return a.exec();
}

void initSystem()
{
    ConfigFile& m_configfile= ConfigFile::getInstance();
    m_configfile.loadConfig("E:\\qt_project\\eat_snake\\my_snake\\config.json");
    GAME_HEIGHT=m_configfile.getConfig("game_height").toInt();
    GAME_WIDTH=m_configfile.getConfig("game_width").toInt();
    GAME_STEP=m_configfile.getConfig("game_step").toInt();
}
