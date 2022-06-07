#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>

namespace Ui {
class parametre;
}

class parametre : public QDialog
{
    Q_OBJECT

public:
    explicit parametre(QWidget *parent = nullptr);
    ~parametre();

public:
    /*ecrire le nom du joueur*/
    void setNom(QString nom);
    /*ecrire le nombre de point pour gagner une partie*/
    void setPoints(unsigned int points);
    /*ecrire le temps max de la partie */
    void setTemps(unsigned int temps);

public:
    /*return le nom saisie*/
    QString getNom();
    /*return le nombre max saisie*/
    unsigned int getPoints();
    /*return le temp saisie*/
    unsigned int getTemps();

private:
    Ui::parametre *ui;
};

#endif // PARAMETRE_H
