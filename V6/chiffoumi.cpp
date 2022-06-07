#include "chiffoumi.h"
#include "ui_chiffoumi.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QString>
#include "dialog.h"

        ///Définition constructeur et destructeur
chifoumi::chifoumi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumi)
{
    ui->setupUi(this);
    connect(ui -> bNPartie, SIGNAL(clicked()),this, SLOT(lancerPartie()));
    connect(ui -> bCiseau, SIGNAL(clicked()),this, SLOT(choixCiseau()));
    connect(ui -> bPierre, SIGNAL(clicked()),this, SLOT(choixPierre()));
    connect(ui -> bPapier, SIGNAL(clicked()),this, SLOT(choixPapier()));
    connect(ui -> actionAide, SIGNAL(triggered()),this, SLOT(infoTexte()));
    connect(chrono,SIGNAL(timeout()),this,SLOT(demanderEteindre()));
    connect(ui->bPause,SIGNAL(clicked()),this,SLOT(mettreEnPause()));
    connect(ChronoAfficher,SIGNAL(timeout()),this,SLOT(affichageTimer()));
    connect(ui->action_Param_trer,SIGNAL(triggered()),this,SLOT(parametrage()));
}

chifoumi::~chifoumi()
{
    delete ui;
}


    ///Définition méthode
void chifoumi::modificationLogo(UnCoup coupMachine, UnCoup coupJoueur)
{
    //initialisation des logos
    QPixmap logoCiseau;
    logoCiseau.load(":/images/ciseau_115.png");
    QPixmap logoPierre;
    logoPierre.load(":/images/pierre_115.png");
    QPixmap logoPapier;
    logoPapier.load(":/images/papier_115.png");

    // modification du logo en fonction du coup généré
    switch (coupMachine)
    {
        case ciseau :
        ui -> coupMachine -> setPixmap(logoCiseau);
        break;

        case pierre :
        ui -> coupMachine -> setPixmap(logoPierre);
        break;

        case papier :
        ui -> coupMachine -> setPixmap(logoPapier);
        break;

        case rien :
        break;
    }

    // modification du logo du joueur en fonction de son coup
    switch (coupJoueur)
    {
        case ciseau :
        ui -> coupJoueur -> setPixmap(logoCiseau);
        break;

        case pierre :
        ui -> coupJoueur -> setPixmap(logoPierre);
        break;

        case papier :
        ui -> coupJoueur -> setPixmap(logoPapier);
        break;

        case rien :
        break;

    }
}

char chifoumi::determinerGagnant(UnCoup coupMachine, UnCoup coupJoueur)
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi? dans l'un des cas suivants
    if(coupJoueur == pierre && coupMachine == ciseau){
        gagnantARetourner= 'J';
    }

    else if (coupJoueur == ciseau && coupMachine == pierre){
        gagnantARetourner= 'M';
    }


    else if(coupJoueur > coupMachine){
        gagnantARetourner='J';
    }

    else if (coupJoueur < coupMachine){
        gagnantARetourner='M';
    }

    return gagnantARetourner;
}

void chifoumi::majScores(char p_gagnant)
{
    // Variable pour convertir la valeur et la modifier
    bool ok = true;
    int val = 0;
    QString txt = " ";

    // modification des score incrémentation en cas de victoire sinon aucune modification
    switch (p_gagnant)
    {
    case 'M' :
        val = ui -> scoreMachine -> text().toInt(&ok);
        val = val +1;
        txt = QString::number(val);
        ui -> scoreMachine -> setText(txt);
        break;
    case 'J':
        val = ui -> scoreJoueur -> text().toInt(&ok);
        val = val +1;
        txt = QString::number(val);
        ui -> scoreJoueur -> setText(txt);
        break;
    case 'N':
        break;
    default:
        break;
    }
    checkScore();
    return;
}
void chifoumi::checkScore()
{
    int valJ = 0;
    int valM = 0;
    valJ = ui->scoreJoueur->text().toInt();
    valM = ui->scoreMachine->text().toInt();

    if(valJ == point)
    {
        chrono->stop();
        ChronoAfficher->stop();
        QMessageBox maBox;
        maBox.setIcon(QMessageBox::Information);
        maBox.setWindowTitle("R");
        maBox.setText("bravo "+ nom +"! Vous gagnez avec "+QString::number(point)+" points");
        maBox.exec();
        lancerPartie();

    }
    else if(valM == point)
    {
        chrono->stop();
        ChronoAfficher->stop();
        QString change;
        QMessageBox maBox;
        maBox.setIcon(QMessageBox::Information);
        maBox.setText("bravo machine! Vous gagnez avec "+QString::number(point)+" points");
        maBox.exec();
        lancerPartie();

    }
}
void chifoumi::mettreEnPause()
{

    if(ouiPause==false)
    {
    ouiPause = true;
    tempsRestant = chrono->remainingTime();
    tempsAffichageRestant = ChronoAfficher->remainingTime();
    chrono->stop();
    ChronoAfficher->stop();
    ui->bPause->setText("reprendre partie");
    }
    else
    {
    ouiPause = false;
    chrono->start(tempsRestant);
    ChronoAfficher->start(tempsAffichageRestant);
    ui->bPause->setText("pause");
    }

}

void chifoumi::affichageTimer()
{
    tempsAffichageRestant = chrono->remainingTime();
    tempsAffichageRestant = tempsAffichageRestant/1000;
    ui->labelTimer->setText("tps restant (s):"+ QString::number(tempsAffichageRestant));
    if(tempsAffichageRestant==0)
        ChronoAfficher->stop();
}

void chifoumi::parametrage()
{
    D->exec();
    nom=D->nom;
    point=D->point;
    ui->label_2->setText(QString::number(point));
    temps=D->temps;
}

chifoumi::UnCoup chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    unsigned int nbAleatoire;
    nbAleatoire = rand()%(4-1) + 1;
    switch (nbAleatoire)
    {
    case 1 :
        valeurGeneree = ciseau;
        break;
    case 2 :
        valeurGeneree = pierre;
        break;
    case 3 :
        valeurGeneree = papier;
        break;
    }
    return valeurGeneree;
}

    ///SLOTS
void chifoumi::lancerPartie()
{
    // Initialisation du joueur
    ui -> LJoueur -> setText(nom);
    ui -> scoreJoueur -> setStyleSheet("color : blue");
    ui -> LJoueur -> setStyleSheet("color : blue");

    // initialisation des boutons
    ui -> bCiseau -> setEnabled(true);
    ui -> bPierre -> setEnabled(true);
    ui -> bPapier -> setEnabled(true);
    ui->bPause->setEnabled(true);
    ui->action_Param_trer->setDisabled(true);

    // initialisation des scores
    ui -> scoreJoueur -> setText("0");
    ui -> scoreMachine -> setText("0");

    //initialisation des logos
    QPixmap logoRien;
    logoRien.load(":/images/rien_115.png");
    ui -> coupJoueur -> setPixmap(logoRien);
    ui -> coupMachine -> setPixmap(logoRien);

    //initialisation chrono
    ChronoAfficher->start(975);
    chrono->start(temps*1000);
    tempsRestant = chrono->remainingTime();
    tempsRestant = tempsRestant/1000;
    ui->labelTimer->setText("tps restant (s):"+QString::number(tempsRestant));
    ouiPause =false;

}

void chifoumi::demanderEteindre()
{
int valJ = 0;
int valM = 0;
valJ = ui->scoreJoueur->text().toInt();
valM = ui->scoreMachine->text().toInt();

   if(valJ > valM)
    {
    QMessageBox maBox;
    maBox.setIcon(QMessageBox::Information);
    maBox.setText("le timer est terminé mais"+ nom +" gagne quand même avec "+QString::number(valJ)+" point");
    maBox.exec();
    lancerPartie();
    }
   else if(valJ <valM)
   {
       QMessageBox maBox;
       maBox.setIcon(QMessageBox::Information);
       maBox.setText("le timer est terminé mais la machine gagne quand même avec "+QString::number(valM)+"points");
       maBox.exec();
       lancerPartie();
   }
   else
   {
       QMessageBox maBox;
       maBox.setIcon(QMessageBox::Information);
       maBox.setText("le timer est terminé égalité");
       maBox.exec();
       lancerPartie();
   }
}
void chifoumi::choixCiseau()
{
    // modification des logos (joueur/machine)
    UnCoup coupJoueur;
    coupJoueur = ciseau;
    UnCoup coupMachine;
    coupMachine = genererUnCoup();
    modificationLogo(coupMachine,coupJoueur);

    // modification du score
    majScores(determinerGagnant(coupMachine, coupJoueur));
}

void chifoumi::choixPierre()
{
    // modification des logos (joueur/machine)
    UnCoup coupJoueur;
    coupJoueur = pierre;
    UnCoup coupMachine;
    coupMachine = genererUnCoup();
    modificationLogo(coupMachine,coupJoueur);

    // modification du score
    majScores(determinerGagnant(coupMachine, coupJoueur));
}

void chifoumi::choixPapier()
{
    // modification des logos (joueur/machine)
    UnCoup coupJoueur;
    coupJoueur = papier;
    UnCoup coupMachine;
    coupMachine = genererUnCoup();
    modificationLogo(coupMachine,coupJoueur);

    // modification du score
    majScores(determinerGagnant(coupMachine, coupJoueur));
}

void chifoumi::infoTexte()
{
    QMessageBox maBox;
    maBox.setText("version: 6. \n Date de creation:04/05/2022. \n Créer par Cabrol Yoann, Da Silva Eduardo et Lauriou Tanguy. ");
    maBox.exec();
}

