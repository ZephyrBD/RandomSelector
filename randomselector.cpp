#include "randomselector.h"
#include "ui_randomselector.h"
#include "UIhelp.h"
#include "settings.h"
#include "Filehelp.h"

RandomSelector::RandomSelector(QWidget *parent):
    ElaWindow(parent), ui(new Ui::RandomSelector)
{
    ui->setupUi(this);
    //设置窗口大小
    //this->setMaximumSize(windowWidth,windowHigh);
    this->setMinimumSize(windowWidth,windowHigh);
    setWindowTitle("随机器-ZBD V4.1.Beta.1");
    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);


    // 开始按钮
    startButton = new ElaPushButton("开始", this);

    //设置按钮
    settingButton = new ElaPushButton("设置",this);
    if (startButton && settingButton) {
        startButton->show();
        settingButton->show();
    }

    rsPivot = new ElaPivot(this);
    if (rsPivot) {
        rsPivot->appendPivot("坐标模式");
        rsPivot->appendPivot("小组模式");
        rsPivot->appendPivot("名单模式");
    }
    //标签
    zblabelA = new QLabel("8",this);
    zblabelB = new QLabel("8",this);
    midLabel = new QLabel(",",this);

    RSSettings = readSettings();

    _closeDialog = new ElaContentDialog(this);
    _closeDialog->setLeftButtonText("取消");
    _closeDialog->setRightButtonText("退出");
    _closeDialog->setMiddleButtonText("最小化");
    connect(_closeDialog, &ElaContentDialog::rightButtonClicked, this, &RandomSelector::closeWindow);
    connect(_closeDialog, &ElaContentDialog::middleButtonClicked, this, [=]() {
        _closeDialog->close();
        showMinimized();
    });
    this->setIsDefaultClosed(false);
    connect(this, &RandomSelector::closeButtonClicked, this, [=]() {
        _closeDialog->exec();
    });


    //初始化
    connect(startButton, &QPushButton::clicked, [this]() {
        onStartButtonClicked(1);
    });

    connect(rsPivot, &ElaPivot::pivotClicked, this, [this](int index) {
        qDebug() << "Signal received with index:" << index;
        modChange(index);
    });
    connect(settingButton,&QPushButton::clicked,this,&RandomSelector::onSettingButtonClicked);
    // 初始化UI
    updateUI();
}

void RandomSelector::modChange(int index) {
    qDebug() << "Pivot clicked, index:" << index;
    switch (index) {
    case 0:
        RSSettings.MODE = 1;
        break;
    case 1:
        RSSettings.MODE = 2;
        break;
    case 2:
        RSSettings.MODE = 3;
        break;
    }
    qDebug() << "Current mode:" << RSSettings.MODE;
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
            zblabelA->setGeometry((getWindowWidth()-6*fm.horizontalAdvance(tmp))/2, 150, 6*fm.horizontalAdvance(tmp), labelHigh);
        }
        zblabelB->setText(QString::number(getRandomNumber(1,RSSettings.MaxY)));

        QTimer::singleShot(50, [this, i]() {
            onStartButtonClicked(i + 1);
        });
    }
}

void RandomSelector::onSettingButtonClicked() {
    Settings settingsWindow(this,RSSettings);
    if (settingsWindow.exec() == QDialog::Accepted) {
        RSSettings = settingsWindow.getSettings(RSSettings);
        //modChange();
        saveSettings(RSSettings);
    }
}

void RandomSelector::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateUI();
}

void RandomSelector::updateUI() {
    int windowWidth = getWindowWidth();
    int windowHeight = getWindowHeight();
    if(startButton && settingButton) {
        const int START_BUTTON_WIDTH = windowWidth/4;
        const int SETTING_BUTTON_WIDTH = windowWidth/6;
        const int BUTTON_HEIGHT = windowHeight/10;
        startButton->setGeometry((windowWidth - START_BUTTON_WIDTH) / 2, windowHeight-BUTTON_HEIGHT*2, START_BUTTON_WIDTH, BUTTON_HEIGHT);
        settingButton->setGeometry((windowWidth - SETTING_BUTTON_WIDTH) / 2, windowHeight-BUTTON_HEIGHT, SETTING_BUTTON_WIDTH, BUTTON_HEIGHT);
    }

    if (rsPivot) {
        const int Pivot_WIDTH = 95*3;
        rsPivot->setCurrentIndex(0);
        rsPivot->setGeometry((windowWidth - Pivot_WIDTH) / 2, 50, Pivot_WIDTH, 50);
        rsPivot->show();
    }

    if(zblabelA && zblabelB && midLabel) {
        QFontMetrics fm(zblabelA->font());
        int labelWidthA = fm.horizontalAdvance(zblabelA->text());
        int labelWidthB = fm.horizontalAdvance(zblabelB->text());
        int midWidth = fm.horizontalAdvance(midLabel->text());


        setLabelStyle(zblabelA,"150");
        setLabelStyle(zblabelB,"150");
        setLabelStyle(midLabel,"150");
        // 计算总宽度
        int totalWidth = labelWidthA + midWidth + labelWidthB;

        // 计算起始X坐标
        int startX = (windowWidth - totalWidth) / 2;

        // 设置几何位置
        zblabelA->setGeometry(startX, 150, labelWidthA, labelHigh);
        midLabel->setGeometry(startX + labelWidthA, 150, midWidth, labelHigh);
        zblabelB->setGeometry(startX + labelWidthA + midWidth, 150, labelWidthB, labelHigh);
    }
}

int RandomSelector::getWindowHeight() {
    return this->height();
}

int RandomSelector::getWindowWidth() {
    return this->width();
}

RandomSelector::~RandomSelector() {
    delete ui;
}
