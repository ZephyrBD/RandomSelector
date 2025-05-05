#ifndef UIHELP_H
#define UIHELP_H

#include "ElaPushButton.h"
#include <QFont>
#include <QFontDatabase>

QFont setUIFont()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/MiSans-Normal.ttf");
    if(fontId != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty())
        {
            QString miSans = fontFamilies.first();
            QFont font(miSans, 16, QFont::Normal, false);
            return font;
        }
    }
    qDebug() << "Failed to get font families for MiSans-Normal.ttf";
    QFont font("Segoe UI", 16, QFont::Normal, false);
    return font;
}

QFont getLabelFont()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/custom.ttf");
    if(fontId != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty())
        {
            QString custom = fontFamilies.first();
            QFont font(custom, 16, QFont::Normal, false);
            return font;
        }
    }
    qDebug() << "Failed to get font families for custom.ttf";
    QFont font("Segoe UI", 16, QFont::Normal, false);
    return font;
}

void setLabelStyle(QLabel* &label,QString fsize) {
    label->setStyleSheet("color: #000000;"
        "font-size: "+fsize+"px;");
    label->setFont(getLabelFont());
    label->show();
}
#endif // UIHELP_H
