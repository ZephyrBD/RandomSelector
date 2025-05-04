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
    setWindowTitle("随机器-ZBD V4.0.Beta.2");
    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);


    // 开始按钮
    startButton = new ElaPushButton("开始", this);
    startButton->show();
    //设置按钮
    settingButton = new ElaPushButton("设置",this);
    settingButton->show();

    menuBar = new ElaMenuBar(this);
    menuBar->show();

    zblabelA = new QLabel("8",this);
    zblabelB = new QLabel("8",this);
    midLabel = new QLabel(",",this);


    // 设置标签字体
    zblabelA->setFont(getLabelFont());
    zblabelB->setFont(getLabelFont());
    midLabel->setFont(getLabelFont());

    // 设置标签颜色和样式
    zblabelA->setStyleSheet("color: black;");
    zblabelB->setStyleSheet("color: black;");
    midLabel->setStyleSheet("color: black;");

    // 显示标签
    zblabelA->show();
    zblabelB->show();
    midLabel->show();

    RSSettings = readSettings();
    //初始化
    connect(startButton, &QPushButton::clicked, [this]() {
        onStartButtonClicked(1);
    });
    connect(settingButton,&QPushButton::clicked,this,&RandomSelector::onSettingButtonClicked);
    // 初始化UI
    updateUI();
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
    QWidget::resizeEvent(event);  // 调用基类处理
    updateUI();  // 窗口大小改变时更新UI
}

void RandomSelector::updateUI() {
    int windowWidth = getWindowWidth();
    int windowHeight = getWindowHeight();
    const int START_BUTTON_WIDTH = windowWidth/4;
    const int SETTING_BUTTON_WIDTH = windowWidth/6;
    const int BUTTON_HEIGHT = 50;
    startButton->setGeometry((windowWidth - START_BUTTON_WIDTH) / 2, windowHeight-BUTTON_HEIGHT*2, START_BUTTON_WIDTH, 50);
    settingButton->setGeometry((windowWidth - SETTING_BUTTON_WIDTH) / 2, windowHeight-BUTTON_HEIGHT, SETTING_BUTTON_WIDTH, 50);
    menuBar->setGeometry(0, 0, windowWidth, 20);

    // 更新标签位置（如果需要）
    if(zblabelA && zblabelB && midLabel) {
        QFontMetrics fm(zblabelA->font());
        int labelWidth = fm.horizontalAdvance(zblabelA->text());
        zblabelA->setGeometry((windowWidth - labelWidth*3)/2, 150, labelWidth*3, 50);
        midLabel->setGeometry(windowWidth/2 - 10, 150, 20, 50);
        zblabelB->setGeometry(windowWidth/2 + 10, 150, labelWidth*3, 50);
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
