#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD?LE ---------------------------

Chifoumi::Chifoumi():


    //ctor
    // partie mod?le
     scoreJoueur(0),
     scoreMachine(0),
     coupJoueur(rien),
     coupMachine(rien)
{}

Chifoumi::~Chifoumi()
{
    //dtor
}

        /// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
    return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi? dans l'un des cas suivants
    if(getCoupJoueur() < getCoupMachine())
    {gagnantARetourner='M';}

    else if (getCoupJoueur() == ciseau && getCoupMachine() == pierre){
        gagnantARetourner= 'M';
    }


    else if(getCoupJoueur() > getCoupMachine())
    {gagnantARetourner='J';}

    else if (getCoupJoueur() == pierre && getCoupMachine() == ciseau){
        gagnantARetourner= 'J';
    }

    return gagnantARetourner;
}

         ///* M?thodes utilitaires du Mod?le

int randMinMax(int min, int max){
    /* pr?-condition : min<max ;
       Le nbre al?atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    unsigned int nbAleatoire;
    nbAleatoire = randMinMax(1,4);
    switch (nbAleatoire)
    {
    case 1 :
        valeurGeneree = pierre;
        break;
    case 2 :
        valeurGeneree = papier;
        break;
    case 3 :
        valeurGeneree = ciseau;
        break;
    default:
        break;
    }

    return valeurGeneree;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    scoreJoueur = p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    scoreMachine = p_score;
}

void Chifoumi::majScores(char p_gagnant) {

    if(determinerGagnant() == 'M')
    {p_gagnant = 'M';}

    else if(determinerGagnant() == 'J')
    {p_gagnant = 'J';}

    else if(determinerGagnant() == 'N')
    {p_gagnant = 'N';}

    switch (p_gagnant)
    {
    case 'M' :
        setScoreMachine(getScoreMachine()+1);
        break;
    case 'J':
        setScoreJoueur(getScoreJoueur()+1);
        break;
    case 'N':
        break;
    default:
        break;
    }
    return;
}

void Chifoumi::initScores() {
    scoreJoueur = 0;
    scoreMachine = 0;
}

void Chifoumi::initCoups() {
    setCoupJoueur(rien);
    setCoupMachine(rien);
}
