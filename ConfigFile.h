#pragma once
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMutex>
#include <QDebug>
#include <vector>
#include <string>
#include <unordered_map>
class ConfigFile : public QObject {
    Q_OBJECT

public:
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
        mapData.clear();

        // Load all maps from JSON
        for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
            if (it.value().isArray()) { // Assume it's a map if it's an array
                QString mapName = it.key();
                if (!loadMapFromJson(mapName, it.value().toArray())) {
                    qWarning() << "Failed to load map" << mapName << "from JSON";
                    return false;
                }
            } else {
                // Store other config values
                configMap.insert(it.key(), it.value().toString());
            }
        }

        return true;
    }

    QString getConfig(const QString& key) const {
        auto it = configMap.find(key);
        if (it == configMap.end()) {
            qWarning() << "Config key" << key << "not found.";
            return QString();
        }
        return it.value();
    }

    void setConfig(const QString& key, const QString& value) {
        QMutexLocker locker(&mutex);

        if (!configMap.contains(key)) {
            qDebug() << "Key already exists, no operation performed.";
            return;
        }
        // 如果键存在，则更新值并标记为脏
        configMap.insert(key, value);
        dirty = true;
    }

    bool saveConfig(const QString& filePath) {
        if (!dirty) return true; // No changes, no need to save

        QJsonObject jsonObj;
        // 添加配置数据到 JSON 对象
        for (auto it = configMap.begin(); it != configMap.end(); ++it) {
            jsonObj.insert(it.key(), QJsonValue(it.value()));
        }

        // 直接添加地图数据到 JSON 对象，不使用 "maps" 这个中间层
        for (const auto& [mapName, map] : mapData) {
            QJsonArray mapArray;
            for (const auto& row : map) {
                QJsonArray rowArray;
                for (int cell : row) {
                    rowArray.append(cell);
                }
                mapArray.append(rowArray);
            }
            jsonObj.insert(QString::fromStdString(mapName), QJsonValue(mapArray));
        }

        QJsonDocument jsonDoc(jsonObj);
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Cannot open config file for writing:" << filePath;
            return false;
        }

        file.write(jsonDoc.toJson(QJsonDocument::Indented));
        dirty = false; // 保存后标记为不脏

        return true;
    }

    // Function to load a specific map from JSON
    bool loadMapFromJson(const QString& mapName, const QJsonArray& mapArray) {
        std::vector<std::vector<int>> map;
        for (const QJsonValue& rowValue : mapArray) {
            if (!rowValue.isArray()) {
                qWarning() << "Map row for" << mapName << "is not an array";
                return false;
            }
            std::vector<int> row;
            for (const QJsonValue& cellValue : rowValue.toArray()) {

                int cell = cellValue.toInt();
                row.push_back(cell);
            }
            map.push_back(row);
        }
        mapData.insert({mapName.toStdString(), map});
        return true;
    }

    std::vector<std::vector<bool>> getMap(const std::string& mapName) const {
        auto it = mapData.find(mapName);
        if (it == mapData.end()) {
            qWarning() << "Map with name" << QString::fromStdString(mapName) << "not found.";
            return std::vector<std::vector<bool>>{};
        }

        // 创建一个新的 vector<vector<bool>> 并进行转换
        std::vector<std::vector<bool>> boolMap(it->second.size());
        for (size_t i = 0; i < it->second.size(); ++i) {
            boolMap[i].resize(it->second[i].size());
            std::transform(it->second[i].begin(), it->second[i].end(), boolMap[i].begin(),
                           [](int value) { return value == 1; });
        }
        return boolMap;
    }
    std::vector<std::vector<int>> getIntMap(const std::string& mapName) const {
        auto it = mapData.find(mapName);
        if (it == mapData.end()) {
            qWarning() << "Map with name" << QString::fromStdString(mapName) << "not found.";
            return std::vector<std::vector<int>>{};
        }
        return it->second;
    }
    bool setMap(const std::string& mapName, const std::vector<std::vector<int>>& intMap) {
        QMutexLocker locker(&mutex);
        // 更新或插入地图数据
        mapData[mapName]=intMap;
        dirty = true;
        return true;
    }
    ~ConfigFile() {
        // No need to do anything special for the map data in the destructor
    }

private:
    ConfigFile(QObject* parent = nullptr) : QObject(parent), dirty(false) {}

    QHash<QString, QString> configMap;
    mutable QMutex mutex;
    bool dirty;

    std::unordered_map<std::string, std::vector<std::vector<int>>> mapData; // Store the map data here

    Q_DISABLE_COPY(ConfigFile)
};
