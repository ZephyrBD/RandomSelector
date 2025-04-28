#ifndef RANDOMSELECTOR_H
#define RANDOMSELECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QSoundEffect>
#include "node.h"
#include "vector"

QT_BEGIN_NAMESPACE
namespace Ui {
class RandomSelector;
}
QT_END_NAMESPACE

class RandomSelector : public QWidget
{
    Q_OBJECT

public:
    const int windowWidth = 480;
    const int windowHigh = 755;
    const int labelHigh = 150;
    const int labelWidth = 100;
    QSoundEffect effect;
    std::vector<QString> vt;
    node RSSettings;
    RandomSelector(QWidget *parent = nullptr);
    ~RandomSelector();

private slots:
    void initLabel();
    void onStartButtonClicked(int i);
    void onSettingButtonClicked();
    void modChange();
    void setupLabels(const QString& midText, const QString& aText, bool showMid, bool showB);
    void setZbLabelA(const QString& text);
    void handleMode3();

private:
    Ui::RandomSelector *ui;
    void setBackGround(QLabel *&bg)
    {
        QString imagePath = ":/images/background.png";
        QImage img;
        img.load(imagePath);
        bg->setPixmap(QPixmap::fromImage(img));
    }
    QLabel *bglabel;
    QLabel *zblabelA,*zblabelB,*midLabel;
    QPushButton *startButton;
    QPushButton *settingButton;
};
#endif // RANDOMSELECTOR_H
