#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString nom = "Vous";
    int point = 5;
    int temps = 30;


private slots:
    void test();
    void cancel();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
