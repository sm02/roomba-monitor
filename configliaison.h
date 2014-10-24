#ifndef CONFIGLIAISON_H
#define CONFIGLIAISON_H

#include <QString>
/*! \brief Paramètrage de la liaison employée.
 *
 * Paramètrage de configuration de la liaison employée pour le dialogue Roomba - moniteur
 */

class ConfigLiaison
{
public:
    ConfigLiaison();
    /*!
     * \brief port
     * \return
     */
    QString port() const;


    /*!
     * \brief setPort
     * \param port
     */
    void setPort(const QString &port);


    /*!
     * \brief debit
     * \return
     */
    unsigned int debit() const;


    /*!
     * \brief setDebit
     * \param debit
     */
    void setDebit(unsigned int debit);

private:
    QString _port;
    unsigned int _debit;
};

#endif // CONFIGLIAISON_H
