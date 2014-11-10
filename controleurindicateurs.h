#ifndef CONTROLEURINDICATEURS_H
#define CONTROLEURINDICATEURS_H

#include <QObject>
#include "roomba.h"

class IndicateurStatus;  //déclaration avancée
class IndicateurDebug;  //déclaration avancée

class ControleurIndicateurs : public QObject
{
    Q_OBJECT
public:
    explicit ControleurIndicateurs(QObject *parent = 0,Roomba *r = 0);
    ~ControleurIndicateurs();

    qint32 numMesureActive() const;
    void setNumMesureActive(const qint32 &numMesureActive);
    void ouvrirIndicateurs();

    qint32 mesureActive(eCapt capt) const;
private:
    Roomba *_rmb;
    qint32 _numMesureActive;
    IndicateurStatus *indic1;
    IndicateurDebug *indic2;

signals:

public slots:
    void majIndicateurs();
    void selectionnerMesure(qint32 numMesure);
    void close();
};

#endif // CONTROLEURINDICATEURS_H
