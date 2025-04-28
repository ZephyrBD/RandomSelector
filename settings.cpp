#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent,const node pre)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
    //设置窗口大小
    this->setMaximumSize(windowWidth,windowHigh);
    this->setMinimumSize(windowWidth,windowHigh);
    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);
    setWindowTitle("设置");
    ui->maxX->setValue(pre.MaxX);
    ui->maxY->setValue(pre.MaxY);
    ui->maxG->setValue(pre.MaxG);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    if(pre.FilePath.isEmpty()) ui->pathShow->setText("C:/");
    else ui->pathShow->setText(pre.FilePath);
    path = pre.FilePath;
    if(pre.MODE==1)
    {
        ui->zbSelect->setChecked(true);
        ui->groupSelect->setChecked(false);
        ui->nameSelect->setChecked(false);
    }
    else if(pre.MODE==2)
    {
        ui->zbSelect->setChecked(false);
        ui->groupSelect->setChecked(true);
        ui->nameSelect->setChecked(false);
    }
    else if(pre.MODE==3)
    {
        ui->zbSelect->setChecked(false);
        ui->groupSelect->setChecked(false);
        ui->nameSelect->setChecked(true);
    }
    connect(ui->selectFileButton, &QPushButton::clicked, this, &Settings::showFileDialog);
}

void Settings::showFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("文本文档 (*.txt)"));
    if (!filePath.isEmpty()) {
        ui->pathShow->setText(filePath);
        path = filePath;
    }
}


node Settings::getSettings(node pre)
{
    node edit = pre;
    if(ui->zbSelect->isChecked()) edit.MODE = 1;
    else if(ui->groupSelect->isChecked()) edit.MODE = 2;
    else if(ui->nameSelect->isChecked())
    {
        if(path.isEmpty()) errorSolve();
        else edit.MODE = 3;
    }
    if(!path.isEmpty()) edit.FilePath = path;
    edit.MaxX = ui->maxX->value();
    edit.MaxY = ui->maxY->value();
    edit.MaxG = ui->maxG->value();
    return edit;
}

Settings::~Settings()
{
    delete ui;
}


