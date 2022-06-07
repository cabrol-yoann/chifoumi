#ifndef DIALOGCONNECTION_H
#define DIALOGCONNECTION_H

#include <QDialog>
#include <QString>
#include "database.h"

namespace Ui {
class Dialogconnection;
}

class Dialogconnection : public QDialog
{
    Q_OBJECT


public:
    explicit Dialogconnection(QWidget *parent = nullptr);
    ~Dialogconnection();
    bool connecter=false;

private slots:
    void connection();
    void annuler();

private:
    Ui::Dialogconnection *ui;
    Database*  bd=new Database();
};

#endif // DIALOGCONNECTION_H
