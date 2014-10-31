#ifndef LIAISON_H
#define LIAISON_H

#include <QObject>
#include "cserie.h"
#include "trame.h"
#include "configliaison.h"

class Liaison : public QObject
{
    Q_OBJECT
public:
    explicit Liaison(QObject *parent = 0);

    void configurer(ConfigLiaison & cfg);

    /*! \brief Etablir la connexion au Roomba.
     *
     * \return True en cas de réussite.
     */
    bool connecter();

    /*! \brief Terminer la connexion au Roomba.
     *
     * \return True en cas de réussite.
     */
    bool deconnecter();

    void envoyerCommande(QByteArray& commande);
    Trame lireTrame();

    bool connexionEtablie() const;

private:
    ConfigLiaison _cfg;
    CSerie _ls;
    bool _connexionEtablie;


signals:
    
public slots:

};

#endif // LIAISON_H
