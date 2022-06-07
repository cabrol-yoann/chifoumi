#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExpValidator>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->Bok,SIGNAL(clicked()),this,SLOT(test()));
    connect(ui->Bcancel,SIGNAL(clicked()),this,SLOT(cancel()));

    //gestion des caractère
    QRegExp carAutorises("[0-4]{0,1}[0-9]{0,2}");
    QRegExpValidator *validateur = new QRegExpValidator(carAutorises);
    ui->lPoint->setValidator(validateur);
    ui->lTemps->setValidator(validateur);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::test()
{
    if(ui->lNom->isModified() && ui->lPoint->isModified() && ui->lTemps->isModified())
    {
        nom=ui->lNom->text();
        point=ui->lPoint->text().toInt();
        temps=ui->lTemps->text().toInt();
        this->close();
        ui->lNom->clear();
        ui->lPoint->clear();
        ui->lTemps->clear();
    }
    else
        QMessageBox::information(this, "Information", "Il vous manque des informations dans les champs");
}

void Dialog::cancel()
{
    this->close();
}
