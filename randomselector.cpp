#include "randomselector.h"
#include "ui_randomselector.h"
#include "UIhelp.h"
#include "settings.h"
#include "Filehelp.h"

RandomSelector::RandomSelector(QWidget *parent): QWidget(parent), ui(new Ui::RandomSelector)
{
    ui->setupUi(this);
    //设置窗口大小
    this->setMaximumSize(windowWidth,windowHigh);
    this->setMinimumSize(windowWidth,windowHigh);
    setWindowTitle("随机器-ZBD V4.0.Beta.1");
    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);
    //设置背景
    bglabel = new QLabel("", this);
    bglabel->setMinimumSize(windowWidth,windowHigh);
    bglabel->setMaximumSize(windowWidth,windowHigh);
    setBackGround(bglabel);

    // 开始按钮
    startButton = new QPushButton("开始", this);
    setButtonStyle(startButton,windowWidth/2-100, windowHigh-120, 200, 50);

    //设置按钮
    settingButton = new QPushButton("设置",this);
    setButtonStyle(settingButton,windowWidth/2-50, windowHigh-50, 100, 30);
    //初始化
    initLabel();
    connect(startButton, &QPushButton::clicked, [this]() {
        onStartButtonClicked(1);
    });
    connect(settingButton,&QPushButton::clicked,this,&RandomSelector::onSettingButtonClicked);
}

void RandomSelector::initLabel()
{
    zblabelA = new QLabel("8",this);
    zblabelA->setGeometry((windowWidth-50)/2-90, 150, labelWidth, labelHigh);
    setZBLabelStyle(zblabelA);

    zblabelB = new QLabel("8",this);
    zblabelB->setGeometry((windowWidth-50)/2+60, 150, labelWidth, labelHigh);
    setZBLabelStyle(zblabelB);

    midLabel = new QLabel(",",this);
    midLabel->setGeometry((windowWidth-50)/2+10, 150, labelWidth+20, labelHigh);
    setZBLabelStyle(midLabel);

    RSSettings = readSettings();
    modChange();
}

void RandomSelector::modChange()
{
    switch (RSSettings.MODE)
    {
    case 1:
        setupLabels(",", "8", true, true);
        break;
    case 2:
        setupLabels("组", "8", true, false);
        break;
    case 3:
        handleMode3();
        break;
    default:
        break;
    }
}

void RandomSelector::setupLabels(const QString& midText, const QString& aText, bool showMid, bool showB)
{
    midLabel->setText(midText);
    setZbLabelA(aText);
    midLabel->setVisible(showMid);
    zblabelB->setVisible(showB);
}

void RandomSelector::setZbLabelA(const QString& text)
{
    zblabelA->setText(text);
    QFontMetrics fm(zblabelA->font());
    zblabelA->setGeometry((windowWidth-50)/2-90, 150, labelWidth, labelHigh);
}

void RandomSelector::handleMode3()
{
    vt = readName(RSSettings.FilePath);
    if (vt.empty())
    {
        RSSettings.MODE = 1;
        modChange();
        QMessageBox::information(this, "RandomSelector", "名单文件无法读取");
        return;
    }
    zblabelA->setText(vt.front());
    QFontMetrics fm(zblabelA->font());
    int width = 6 * fm.horizontalAdvance(vt.front());
    zblabelA->setGeometry((windowWidth - width) / 2, 150, width, labelHigh);
    zblabelB->hide();
    midLabel->hide();
}

void RandomSelector::onStartButtonClicked(int i)
{
    if(i>15)
    {
        effect.setSource(QUrl("qrc:/sounds/bigstar.wav"));
        effect.setVolume(1.0);
        effect.play();
    }
    if (i <= 15)
    {
        if(RSSettings.MODE==1||RSSettings.MODE==2) zblabelA->setText(QString::number(getRandomNumber(1,RSSettings.MODE==1 ? RSSettings.MaxX : RSSettings.MaxG)));
        else if(vt.size())
        {
            QString tmp = vt[getRandomNumber(0,vt.size()-1)];
            zblabelA->setText(tmp);
            QFontMetrics fm(zblabelA->font());
            zblabelA->setGeometry((windowWidth-6*fm.horizontalAdvance(tmp))/2, 150, 6*fm.horizontalAdvance(tmp), labelHigh);
        }
        zblabelB->setText(QString::number(getRandomNumber(1,RSSettings.MaxY)));

        QTimer::singleShot(50, [this, i]() {
            onStartButtonClicked(i + 1);
        });
    }
}

void RandomSelector::onSettingButtonClicked()
{
    Settings settingsWindow(this,RSSettings);
    if (settingsWindow.exec() == QDialog::Accepted)
    {
        RSSettings = settingsWindow.getSettings(RSSettings);
        modChange();
        saveSettings(RSSettings);
    }
}

RandomSelector::~RandomSelector()
{
    delete ui;
}
