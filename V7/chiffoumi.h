#ifndef CHIFOUMI_H
#define CHIFOUMI_H
#include <QTimer>
#include <QMainWindow>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class chifoumi; }
QT_END_NAMESPACE

class chifoumi : public QMainWindow
{
    Q_OBJECT

    ///* Une d�finition de type �num�r�
public:
    enum UnCoup {pierre, papier, ciseau, rien};

    /// Définition constructeur et destructeur
public:
    chifoumi(QWidget *parent = nullptr);
    ~chifoumi();
    Dialog *D= new Dialog();

    /// Définition méthode
private :
    QTimer*chrono=new QTimer(this);
    bool ouiPause;
    bool parametrer;
    int tempsRestant;
    int tempsAffichageRestant;
    QString nom = "Vous";
    int point = 5;
    int temps = 30;
    QTimer*ChronoAfficher=new QTimer(this);

    UnCoup genererUnCoup();
/* retourne une valeur al�atoire = pierre, papier ou ciseau.
   Utilis�e pour faire jouer la machine */
public:
    void modificationLogo(UnCoup, UnCoup);
    char determinerGagnant(UnCoup,UnCoup);
/* Retourne un caractère en fonction du gagnant de la partie.
   Soit J pour le joueur, M pour la machine et N en cas de match Null */
    void majScores(char p_gagnant);
/* mise à jour des score en fonction de determinerGagnant */
    void checkScore();

    /// Définition SLOTS
private slots:
    void lancerPartie();
/* Slot qui initialise la partie score à 0, des logo vide et activation des bouton */
    void choixCiseau();
    void choixPierre();
    void choixPapier();
/*Slots qui execute la manche en fonction du choix du joueur */
    void infoTexte();
/*Slots pour arreter la partie après la fin du timer */
    void demanderEteindre();
 /*Slots pour mettre en pause et relancer le tour*/
    void mettreEnPause();
 /*Slots pour gerer l'affiche en temp réel du timer*/
    void affichageTimer();
 /*Slots qui vas lancer et gerer le paramétrage de début de partie*/
    void parametrage();

private:
    Ui::chifoumi *ui;
};
#endif // CHIFOUMI_H

