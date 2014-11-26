#ifndef INDICATEUR_H
#define INDICATEUR_H

#include <QDialog>

#include "controleurindicateurs.h"

class Indicateur : public QDialog
{
    Q_OBJECT
public:
    explicit Indicateur(QWidget *parent = 0);
    virtual void init(ControleurIndicateurs *ctrlIndic);

public slots:
    virtual void mettreAJourValeur() =0;

private:
    ControleurIndicateurs *_ctrlIndic;
signals:

public slots:

};

#endif // INDICATEUR_ABSTR_H



