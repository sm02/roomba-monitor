#ifndef WDGSELECTIONMESURE_H
#define WDGSELECTIONMESURE_H

#include <QWidget>
#include "roomba.h"

namespace Ui {
class WdgSelectionMesure;
}

class WdgSelectionMesure : public QWidget
{
    Q_OBJECT

public:
    explicit WdgSelectionMesure(QWidget *parent = 0);
    ~WdgSelectionMesure();
    void init(Roomba *r);

signals:

    /**
     * @brief Signal envoyé la sélection de la mesure a changé.
     *
     * Le signal est généré par le déplacement du curseur ou par l'acquisition d'une nouvelle mesure.
     */
    void mesureSelectionnee(int noMesure);

public slots:
    /**
     * @brief Mise à jour de la vue lors de l'acquisition d'un nouvel échantillon
     *
     */
    void mesureAjoutee();

private:
    Ui::WdgSelectionMesure *ui;
    Roomba *_rmb;

    void setNbMesures(int nbMesures);
};

#endif // WDGSELECTIONMESURE_H
