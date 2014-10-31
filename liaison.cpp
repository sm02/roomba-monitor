#include "liaison.h"
#include "cserie.h"

#include <QElapsedTimer>
#include <QDebug>


Liaison::Liaison(QObject *parent) :
    QObject(parent)
{
    _connexionEtablie=false;
}

void Liaison::configurer(ConfigLiaison &cfg)
{
    _cfg=cfg;
}

bool Liaison::connecter() {
    _ls.SetBaudRate(_cfg.debit());
    _ls.SetCommPort(_cfg.port().toStdString());
    _ls.SetTimeout(10);

    if (! _connexionEtablie) {
        if (_ls.OpenCommPort()) {
            _connexionEtablie=true;
        }
    }
    return _connexionEtablie;
}

bool Liaison::deconnecter() {
    if (_ls.CloseCommPort()) {
        _connexionEtablie=false;
        return true;
    }
    return false;
}

bool Liaison::connexionEtablie() const
{
    return _connexionEtablie;
}

void Liaison::envoyerCommande(QByteArray& commande)
{
    long unsigned int nbOctetsEnvoyes;

    _ls.PurgeCommPort();
    _ls.WriteBuffer((BYTE*)commande.constData(),2,&nbOctetsEnvoyes);
    qDebug("Nb octets envoyés:%ld",nbOctetsEnvoyes);
}

Trame Liaison::lireTrame()
{
    BYTE bufReception[200];
    long unsigned int nbOctetsRecus,nbOctetsRecus2;

    QElapsedTimer timer;
    timer.start();

    _ls.ReadBytes(bufReception,200,&nbOctetsRecus);  //Retourne ce qui est déjà reçu, sinon attend jusqu'au premier caractère et le renvoie.

    while (nbOctetsRecus<80 && timer.nsecsElapsed()<100*1000000) {  //max attente : 100ms
        _ls.ReadBytes(bufReception+nbOctetsRecus,200-nbOctetsRecus,&nbOctetsRecus2);
        nbOctetsRecus+=nbOctetsRecus2;
    }

    qDebug("Total octets reçus:%ld",nbOctetsRecus);
    Trame tr( QByteArray::fromRawData(
                  (char*)bufReception,nbOctetsRecus) );
    qDebug() << tr.toHex();
    return tr;
}
