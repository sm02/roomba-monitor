#ifndef CONFIGLIAISON_H
#define CONFIGLIAISON_H

#include <QString>
/*! \brief Param�trage de la liaison employ�e.
 *
 * Param�trage de configuration de la liaison employ�e pour le dialogue Roomba - moniteur
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
