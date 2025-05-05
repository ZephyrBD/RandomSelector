#ifndef RANDOMSELECTOR_H
#define RANDOMSELECTOR_H

#include "ElaWindow.h"
#include <QLabel>
#include "ElaPushButton.h"
#include "ElaPivot.h"
#include <QTimer>
#include <QSoundEffect>
#include <QRandomGenerator>
#include "node.h"
#include <vector>
#include "ElaContentDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class RandomSelector;
}
QT_END_NAMESPACE

class RandomSelector : public ElaWindow
{
    Q_OBJECT

public:
    const int windowWidth = 480;
    const int windowHigh = 755;
    int labelHigh = 150;


    int getRandomNumber(int minRange,int maxRange) {
        return QRandomGenerator::global()->bounded(minRange, maxRange+1);
    }
    QSoundEffect effect;
    std::vector<QString> vt;
    node RSSettings;
    RandomSelector(QWidget *parent = nullptr);
    ~RandomSelector();

private slots:
    void onStartButtonClicked(int i);
    void onSettingButtonClicked();
    void modChange(int index);

private:
    Ui::RandomSelector *ui;
    QLabel *bglabel;
    QLabel *zblabelA,*zblabelB,*midLabel;
    ElaPushButton *startButton;
    ElaPushButton *settingButton;
    ElaPivot *rsPivot;
    ElaContentDialog* _closeDialog{nullptr};
    int getWindowHeight();
    int getWindowWidth();
    void resizeEvent(QResizeEvent *event);
    void updateUI();
};
#endif // RANDOMSELECTOR_H
