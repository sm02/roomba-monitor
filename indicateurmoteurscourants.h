#ifndef INDICATEURMOTEURSCOURANTS_H
#define INDICATEURMOTEURSCOURANTS_H

#include <QWidget>
#include "indicateur.h"
#include "controleurindicateurs.h"
#include "analogwidgets/manometer.h"

namespace Ui {
class indicateurMoteursCourants;
}

class indicateurMoteursCourants : public Indicateur
{
    Q_OBJECT
    
public:
    explicit indicateurMoteursCourants(QWidget *parent = 0);
    ~indicateurMoteursCourants();
    void init(ControleurIndicateurs *ctrlIndic);
    void setMesures();
    
public slots:
    void mettreAJourValeur();

private:
    Ui::indicateurMoteursCourants *ui;
    ControleurIndicateurs *_ctrlIndic;
    ManoMeter *manoCourantMoteurG;
    ManoMeter *manoCourantMoteurD;
    ManoMeter *manoCourantMoteurBrossePrinc;
    ManoMeter *manoCourantMoteurBrosseLateral;
};



#endif // INDICATEURMOTEURSCOURANTS_H
