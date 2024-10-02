#ifndef CONFIG_H_
#define CONFIG_H_
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QHash>
#include <QMutex>
#include <QString>
#include <QDebug>

class ConfigFile : public QObject {
    Q_OBJECT

public://这个确实是单例,不知道为啥
    static ConfigFile& getInstance() {
        static ConfigFile instance;
        return instance;
    }

    bool loadConfig(const QString& filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Cannot open config file:" << filePath;
            return false;
        }

        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        if (!jsonDoc.isObject()) {
            qWarning() << "Config file is not a valid JSON object";
            return false;
        }

        QJsonObject jsonObj = jsonDoc.object();
        configMap.clear();
        for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
            configMap.insert(it.key(), it.value().toString());
        }

        return true;
    }

    QString getConfig(const QString& key) const {
        return configMap.value(key, QString());
    }

    void setConfig(const QString& key, const QString& value) {
        QMutexLocker locker(&mutex);
        configMap.insert(key, value);
        dirty = true;
    }

    bool saveConfig(const QString& filePath) const {
        if (!dirty) return true; // No changes, no need to save

        QJsonObject jsonObj;
        for (auto it = configMap.begin(); it != configMap.end(); ++it) {
            jsonObj.insert(it.key(), QJsonValue(it.value()));
        }

        QJsonDocument jsonDoc(jsonObj);
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Cannot open config file for writing:" << filePath;
            return false;
        }

        file.write(jsonDoc.toJson(QJsonDocument::Indented));

        return true;
    }

    ~ConfigFile() {
        if (dirty) {

        }
    }

private:
    ConfigFile(QObject* parent = nullptr) : QObject(parent), dirty(false) {}

    QHash<QString, QString> configMap;
    mutable QMutex mutex;
    bool dirty;

    Q_DISABLE_COPY(ConfigFile)
};


#endif // CONFIG_H
