#ifndef INDICATEURDEBUG_H
#define INDICATEURDEBUG_H

#include "indicateur.h"
#include "controleurindicateurs.h"

namespace Ui {
class IndicateurDebug;
}

class IndicateurDebug : public Indicateur
{
    Q_OBJECT

public:
    explicit IndicateurDebug(QWidget *parent = 0);
    ~IndicateurDebug();
    void init(ControleurIndicateurs *ctrlIndic);
    void setMesures();

public slots:
    void mettreAJourValeur();

private:
    Ui::IndicateurDebug *ui;
    ControleurIndicateurs *_ctrlIndic;
};

#endif // INDICATEURDEBUG_H
