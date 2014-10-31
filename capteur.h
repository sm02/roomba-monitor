/*!
* \file      capteur.h
* \brief     Class capteur
* \details   Un capteur avec les mesures effectuées
* \author    SM
* \version   0.1
* \date      nov. 2014
* \copyright GNU GPL v3
*/

#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <qglobal.h>
#include <deque>

typedef std::deque<qint32> dqint;

class Capteur
{
public:
    Capteur();
    ~Capteur();


    /*! \brief Valeur enregistrée
     * \param rang un qint32 pour le rang de la valeur (indexé à partir de 0)
     * si rang<0, renvoie la dernière valeur.
    *  \return un qint32
    */
    qint32 valeur(const qint32 rang) const;


    /*! \brief Enregistre une nouvelle valeur
     *  \param value un qint32 pour la valeur du capteur
    */
    void ajouterValeur(const qint32 value);


    /*! \brief Le nombre de valeurs enregistrées
     *  \return qint32
    */
    quint32 size();

private:
    dqint* _valeurs;
};

#endif
