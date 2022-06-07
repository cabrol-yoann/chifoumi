#include "parametre.h"
#include "ui_parametre.h"

parametre::parametre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parametre)
{
    ui->setupUi(this);
    parametre *maDlg = new parametre(this);
    maDlg->open();
}

parametre::~parametre()
{
    delete ui;
}
