#include "trame.h"

Trame::Trame(const QByteArray donnees) : QByteArray(donnees)
{
}

qint32 Trame::getBit(quint8 pos,quint8 bit) const
{
    return (this->at(pos) & (1<<bit)) == (1<<bit);
}

qint32 Trame::getUnsignedByte(quint8 pos) const
{
    return (quint8)this->at(pos);
}

qint32 Trame::getSignedByte(quint8 pos) const
{
    return (qint8)this->at(pos);
}

qint32 Trame::getSignedWord(quint8 pos) const
{
    /*
    quint16 msb,lsb;
    qint16 r;
    msb=this->at(pos);
    msb=(quint16)this->at(pos);
    r=((quint16)this->at(pos) << 8);
    */

    return (qint16)((quint8)this->at(pos) << 8) | ((quint8)this->at(pos+1));
}

qint32 Trame::getUnsignedWord(quint8 pos) const
{
    /*
    quint16 msb,lsb;
    qint16 r;
    msb=this->at(pos);
    msb=(quint8)this->at(pos);
    r=((quint8)this->at(pos) << 8);
    lsb=(this->at(pos+1));
    lsb=((quint8)this->at(pos+1));
    r=r | lsb;
    */

    return (quint16)((quint8)this->at(pos) << 8) | ((quint8)this->at(pos+1));
}


