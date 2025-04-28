#ifndef UIHELP_H
#define UIHELP_H

#include <QPushButton>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QRandomGenerator>

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

QFont setLabelFont()
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

void setZBLabelStyle(QLabel *&label)
{
    label->setAlignment(Qt::AlignCenter);
    label->setFont(setLabelFont());
    label->setStyleSheet("color: rgb(108, 92, 219);font-size:130px");
    label->raise();
}

void setButtonStyle(QPushButton *&button,int width,int high,int x,int y)
{
    button->setGeometry(width, high, x, y);
    button->setFont(setUIFont());
    button->setStyleSheet(
        "QPushButton {"
        "    font-size: 1rem;"
        "    font-weight: bold;"
        "    color: white;"
        "    background-color: #007BFF;"
        "    border: none;"
        "    border-radius: 0.3125rem;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0056b3;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #d0d0d0;"
        "}"
        );
    button->show();
}

int getRandomNumber(int minRange,int maxRange)
{
    return QRandomGenerator::global()->bounded(minRange, maxRange+1);
}
#endif // UIHELP_H
