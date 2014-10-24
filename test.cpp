#include "test.h"

#include <QTimer>
#include <QFile>
#include <stdio.h>
#include "logger.h"

Test::Test(QObject *parent) :
    QObject(parent)
{
}

void Test::test1()
{
    Log::log(QString("Essai"));
    cfg.setDebit(115200);
    cfg.setPort("COM5");
    rmb.configurerLiaison(cfg);
    connect(&rmb,SIGNAL(nouvelleMesure()),this,SLOT(afficher()));
    rmb.debuterEnregistrement();

}

void Test::test2()
{
    printf("Trames incompletes:%d\n",rmb.nbTramesIncompletes());
    printf("Trames Completes:%d\n",rmb.nbTrames());

    rmb.finirEnregistrement();
    rmb.deconnecter();

    QString nf("d:\\smw\\test.rmbdata");
    rmb.charger(nf);
    printf("Test sauvegarde\n");

    rmb.sauvegarder(nf);
    printf("Test rechargement\n");
    rmb.charger(nf);
    for (uint j=0;j<rmb.nbTrames();j++) {
        printf("Jeu #%d\n",j);
        for (uint i=eMin;i<=eMax;i++)
            printf("%d:%x ",i,rmb.mesure((eCapt)i,j));
    }
}

void Test::afficher()
{
    for (int i=eMin;i<=eMax;i++)
        printf("%d:%x ",i,rmb.mesure((eCapt)i));
}
