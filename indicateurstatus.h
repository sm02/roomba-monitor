#ifndef INDICATEURSTATUS_H
#define INDICATEURSTATUS_H

#include <QDialog>
#include "controleurindicateurs.h"

namespace Ui {
class IndicateurStatus;
}

class IndicateurStatus : public QDialog
{
    Q_OBJECT

public:
    explicit IndicateurStatus(QWidget *parent = 0);
    ~IndicateurStatus();
    void init(ControleurIndicateurs *ctrlIndic);
    void setMesures();

public slots:
    void mettreAJourValeur();

private:
    Ui::IndicateurStatus *ui;
    ControleurIndicateurs *_ctrlIndic;
};

#endif // INDICATEURSTATUS_H
