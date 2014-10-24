/*! \file trame.h
\brief Définition de la classe trame

*/

#ifndef TRAME_H
#define TRAME_H

#include <qglobal.h>
#include <QByteArray>

/*! \brief Analyse la trame envoyée par le Roomba
 *
 *Fournit des fonctions pour extraire les mesures, suivant les types employés dans le protocole Open Interface.
*/

class Trame : public QByteArray
{
public:
    /*! \brief Construit une trame
     *
     *\param donnees Les données brutes reçues par la liaison série.
     */
    Trame(const QByteArray donnees);



    /*! \brief Extrait de la trame la valeur d'un bit
     *
     *  \param pos L'adresse de l'octet dans la trame.
     *  \param bit Le rang du bit à extraire (en commençant à 0).
     *  \return La valeur du bit.
   */
    qint32 getBit(quint8 pos,quint8 bit) const;



    /*! \brief Extrait de la trame un octet non signé
     *
     *  \param pos L'adresse de l'octet dans la trame.
     *  \return La valeur de l'octet à [pos]
   */
   qint32 getUnsignedByte(quint8 pos) const;



   /*! \brief Extrait de la trame un octet signé
    *
    *  \param pos L'adresse de l'octet dans la trame.
    *  \return La valeur de l'octet à [pos]
  */
   qint32 getSignedByte(quint8 pos) const;



   /*! \brief Extrait de la trame un mot 16 bit non signé
    *
    *  \param pos L'adresse de l'octet dans la trame.
    *  \return La valeur obtenue à [pos] (MSB) et [pos+1] (LSB)
    */
    qint32 getUnsignedWord(quint8 pos) const;



    /*! \brief Extrait de la trame un mot 16 bit signé
   *
   *  \param pos L'adresse de l'octet dans la trame.
   *  \return La valeur obtenue à [pos] (MSB) et [pos+1] (LSB)
   */
   qint32 getSignedWord(quint8 pos) const;


private:

};
#endif // TRAME_H
