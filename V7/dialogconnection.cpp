#include "dialogconnection.h"
#include "ui_dialogconnection.h"
#include "QMessageBox"
#include <QSqlQuery>
Dialogconnection::Dialogconnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogconnection)
{
    ui->setupUi(this);
    connect(ui->Bconnection,SIGNAL(clicked()),this,SLOT(connection()));
    connect(ui->Bcancel,SIGNAL(clicked()),this,SLOT(annuler()));
}

Dialogconnection::~Dialogconnection()
{
    delete ui;
}

void Dialogconnection::connection()
{
    if(ui->lMDP->isModified() && ui->lUser->isModified())
    {

        bd->openDataBase();
        QSqlQuery query("SELECT User,MDP FROM BDConnexion;");
        while(query.next())
        {
            if(ui->lUser->text() == query.value(0).toString() || ui->lUser->text() == query.value(1).toString())
            {
                connecter=true;
                QMessageBox::information(this, "Connexion réussite", "Compte trouver");
                this->close();
                bd->closeDataBase();
                break;
            }
            QMessageBox::information(this, "Mauvais mot de passe", "Votre mot de passe ou votre pseudonyme ne font pas partie de nos bases de données");
        }
    }
    else
        QMessageBox::information(this, "Information", "Il vous manque des informations dans les champs");
}

void Dialogconnection::annuler()
{
    this->close();
}
