#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "node.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr,const node pre = node());
    const int windowWidth = 400;
    const int windowHigh = 370;
    node getSettings(node pre);
    ~Settings();

private slots:
    void showFileDialog();
    void errorSolve()
    {
        QMessageBox::information(this, "RandomSelector", "必须有有效的名单才能选择该模式！");
    }
private:
    QString path;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
