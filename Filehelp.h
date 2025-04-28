#ifndef FILEHELP_H
#define FILEHELP_H

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QMessageBox>
#include <vector>
#include "node.h"

std::vector<QString> readName(QString path)
{
    std::vector<QString> vt;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return vt;
    }
    QByteArray data = file.readAll();
    file.close();
    QString content = QString::fromUtf8(data);
    QStringList lines = content.split('\n');
    for (const QString& line : lines)
    {
        if (!line.isEmpty()) {
            vt.push_back(line);
        }
    }
    return vt;
}

node readSettings()
{
    node settings;
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    //QString path = QCoreApplication::applicationDirPath();
    path += "/RandomSelector_settings.json";
    path.remove("/RandomSelector");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return settings;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    settings.MODE = obj["MODE"].toInt();
    settings.MaxX = obj["MaxX"].toInt();
    settings.MaxY = obj["MaxY"].toInt();
    settings.MaxG = obj["MaxG"].toInt();
    settings.FilePath = obj["nameFile"].toString();
    return settings;
}

void saveSettings(node setting)
{
    QJsonObject obj
        {
            {"MODE", setting.MODE},
            {"MaxX", setting.MaxX},
            {"MaxY", setting.MaxY},
            {"MaxG", setting.MaxG},
            {"nameFile",setting.FilePath}
        };
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    path.remove("/RandomSelector");
    //QString path = QCoreApplication::applicationDirPath();
    if (path.isEmpty())
    {
        qDebug() << "Failed to get AppData path.";
        return;
    }
    path += "/RandomSelector_settings.json";
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(QJsonDocument(obj).toJson());
        file.close();
    }
    else
        QMessageBox::information(NULL,"RandomSelector","无法打开文件进行写入！");
}

#endif // FILEHELP_H
