/*! \file trame.h
\brief D�finition de la classe trame

*/

#ifndef TRAME_H
#define TRAME_H

#include <qglobal.h>
#include <QByteArray>

/*! \brief Analyse la trame envoy�e par le Roomba
 *
 *Fournit des fonctions pour extraire les mesures, suivant les types employ�s dans le protocole Open Interface.
*/

class Trame : public QByteArray
{
public:
    /*! \brief Construit une trame
     *
     *\param donnees Les donn�es brutes re�ues par la liaison s�rie.
     */
    Trame(const QByteArray donnees);



    /*! \brief Extrait de la trame la valeur d'un bit
     *
     *  \param pos L'adresse de l'octet dans la trame.
     *  \param bit Le rang du bit � extraire (en commen�ant � 0).
     *  \return La valeur du bit.
   */
    qint32 getBit(quint8 pos,quint8 bit) const;



    /*! \brief Extrait de la trame un octet non sign�
     *
     *  \param pos L'adresse de l'octet dans la trame.
     *  \return La valeur de l'octet � [pos]
   */
   qint32 getUnsignedByte(quint8 pos) const;



   /*! \brief Extrait de la trame un octet sign�
    *
    *  \param pos L'adresse de l'octet dans la trame.
    *  \return La valeur de l'octet � [pos]
  */
   qint32 getSignedByte(quint8 pos) const;



   /*! \brief Extrait de la trame un mot 16 bit non sign�
    *
    *  \param pos L'adresse de l'octet dans la trame.
    *  \return La valeur obtenue � [pos] (MSB) et [pos+1] (LSB)
    */
    qint32 getUnsignedWord(quint8 pos) const;



    /*! \brief Extrait de la trame un mot 16 bit sign�
   *
   *  \param pos L'adresse de l'octet dans la trame.
   *  \return La valeur obtenue � [pos] (MSB) et [pos+1] (LSB)
   */
   qint32 getSignedWord(quint8 pos) const;


private:

};
#endif // TRAME_H
