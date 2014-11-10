#include "liaison.h"

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
    //_ls.setTimeout(10);
    //QSerialPortInfo serialInfo(_cfg.port());
    _ls.setPortName(_cfg.port());

    if (! _connexionEtablie) {
        if (_ls.open(QIODevice::ReadWrite)) {
            _ls.setBaudRate(_cfg.debit());
            _connexionEtablie=true;
        }
    }
    return _connexionEtablie;
}

bool Liaison::deconnecter() {
    _ls.close();
    return true;
}

bool Liaison::connexionEtablie() const
{
    return _connexionEtablie;
}

void Liaison::envoyerCommande(QByteArray& commande)
{
    _ls.write(commande);
}

Trame Liaison::lireTrame()
{
    QByteArray bufReception;

    _ls.waitForReadyRead(50);
    bufReception = _ls.readAll();
    while (_ls.waitForReadyRead(5))
        bufReception += _ls.readAll();

    qDebug("Total octets reçus:%d",bufReception.size());
    Trame tr(bufReception);
    qDebug() << tr.toHex();
    return tr;
}
