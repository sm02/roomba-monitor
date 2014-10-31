/*! \file mesurage.h
\brief Définition de la classe mesurage

Accès à tous les mesures faites sur le Roomba.

*/

#ifndef MESURAGE_H
#define MESURAGE_H

#include <QTimer>
#include <QFile>
#include <QDataStream>
#include "capteur.h"
#include "liaison.h"

#define VERSION_STRUCT_FICHIER 2

/*! \enum eCapt
    \brief Enumération des capteurs

*/
enum eCapt {
    soulevRoueG=1,  //!< Whell Drop Left ID=7 bit 3
    eMin=soulevRoueG,
    //! \brief 1=Roue soulevée
    soulevRoueD=2,  //!< Whell Drop Right ID=7 bit 2
    //! \brief 1=Roue soulevée
    chocG=3,        //!< Bump Left ID=7 bit 1
    chocD=4,        //!< Bump Right ID=7 bit 0
    mur=5,          //!< Wall ID=8
    videG=6,        //!< Cliff Left State ID=9
    videAvG=7,      //!< Cliff Front Left State ID=10
    videAvD=8,      //!< Cliff Front Right State ID=11
    videD=9,        //!< Cliff Right State ID=12
    murVirtuel=10,  //!< Virtual Wall ID=13
    surIntensRoueG=11, //!< Wheel Overcurrents, Left Whell ID=14 bit 4
    surIntensRoueD=12, //!< Wheel Overcurrents, Right Whell ID=14 bit 3
    surIntensBrossePrinc=13, //!< Wheel Overcurrents, Main Brush ID=14 bit 2
    surIntensBrosseLat=14, //!< Wheel Overcurrents, Side Brush ID=14 bit 0
    nivPoussiere=15, //!< Dirt Detect ID=15
    infrarougeOmnidir=16, //!< Infrared Character Omni ID=17
    infrarougeG=17, //!< Infrared Character Left ID=52
    infrarougeD=18, //!< Infrared Character Right ID=53
    boutonHorloge=19, //!< Buttons Clock ID=18 bit 7
    boutonProg=20, //!< Buttons Schudule ID=18 bit 6
    boutonJour=21, //!< Buttons Day ID=18 bit 5
    boutonHeure=22, //!< Buttons Hour ID=18 bit 4
    boutonMin=23, //!<Buttons Minute ID=18 bit 3
    boutonBase=24, //!<Buttons Dock ID=18 bit 2
    boutonSpot=25, //!<Buttons Spot ID=18 bit 1
    boutonNett=26, //!<Buttons Clean ID=18 bit 0
    distance=27, //!<Distance ID=19
    angle=28, //!<Angle ID=20
    etatCharge=29, //!<Charging State ID=21
    voltage=30, //!<Voltage ID=22
    courant=31, //!<Current ID=23
    temperature=32, //!<Temperature ID=24
    chargeBat=33, //!<Battery Charge ID=25
    capaciteBat=34, //!<Battery Capacity ID=26
    signalMur=35, //!<Wall Signal ID=27
    signalVideG=36, //!<Cliff Left Signal ID=28
    signalVideAvG=37, //!<Cliff Front Left Signal ID=29
    signalVideAvD=38, //!<Cliff Front Right Signal ID=30
    signalVideD=39, //!<Cliff Right Signal ID=31
    chargeurBase=40, //!<Charging Source Available, Home Base ID=34 bit 1
    chargeurInterne=41, //!<Charging Source Available, Internal Charger ID=34 bit 0
    mode=42, //!< OI Mode
    noMusique=43, //!<Song Number ID=36
    musique=44, //!<Song playing ID=37
    nombrePaquets=45, //!<Number of Stream Packets ID=38
    vitesseReq=46, //!<Requested Velocity ID=39
    rayonReq=47, //!<Requested Radius ID=40
    vitesseDReq=48, //!<Requested Right Velocity ID=41
    vitesseGReq=49, //!<Requested Left Velocity ID=42
    encodeurD=50, //!<Right Encoder Counts ID=43
    encodeurG=51, //!<Left Encoder Counts ID=44
    oeilLateralD=52, //!<Light Right Bumber ID=45 bit 5
    oeilAvantD=53, //!<Light Front Right Bumber ID=45 bit 4
    oeilCentreD=54, //!<Light Center Right Bumber ID=45 bit 3
    oeilCentreG=55, //!<Light Center Left Bumber ID=45 bit 2
    oeilAvantG=56, //!<Light Front Left Bumber ID=45 bit 1
    oeilLateralG=57, //!<Light Left Bumber ID=45 bit 0
    signalOeilLateralG=58, //!<Light Bumb Left Signal ID=46
    signalOeilAvantG=59, //!<Light Bumb Front Left Signal ID=47
    signalOeilCentreG=60, //!<Light Bumb Center Left Signal ID=48
    signalOeilCentreD=61, //!<Light Bumb Center Right Signal ID=49
    signalOeilAvantD=62, //!<Light Bumb Front Right Signal ID=50
    signalOeilLateralD=63, //!<Light Bumb Right Signal ID=51
    courantMoteurG=64, //!<Left Motor Current ID=54
    courantMoteurD=65, //!<Right Motor Current ID=55
    courantMoteurBrossePrinc=66, //!<Main Brush Motor Current ID=56
    courantMoteurBrosseLateral=67, //!<Side Brush Motor Current ID=57
    roueFolle=68, //!<Stasis ID=58
    eMax=roueFolle
};

/*! \def PERIODE_ECHANTILLONNAGE
 * \brief durée entre deux acquisitions (en ms)
 */
#define PERIODE_ECHANTILLONNAGE 200 //<! Période entre chaque mesure (en ms)


class Mesurage : public QObject
{
    Q_OBJECT
public:
    explicit Mesurage(QObject *parent = 0);
    /*!
     * \brief Démarre l'acquisition des mesures
     *
     *Si nécessaire, la connexion est réalisée. En cas d'échec, renvoie false.
     *Ensuite, démarre des acquisions de mesures, toutes les PERIODE_ECHANTILLONAGE ms.
     *
     * \return true si la connexion est réalisée.
     */
    bool demarrerAcquisition();


    /*!
     * \brief Arrête l'acquisition des mesures
     */
    void arreterAcquisition();

    /*!
     * \brief Définit la liaison utilisée pour la connexion au Roomba
     * \param l pointeur vers un objet Liaison
     */
    void setLiaison(Liaison* l);


    /*!
     * \brief Renvoie le nombre de mesures effectuées
     */
    quint32 nbMesures() const;

    /*!
     * \brief Renvoie une mesure pour un capteur donné
     * \param capt Le capteur dont on souhaite la valeur
     * \param rang Le numéro de la mesure (de 0 à nbMesures-1); -1 ou absent pour obtenir la dernière mesure.
     * \return La valeur de la mesure
     */
    qint32 mesure(eCapt capt,qint32 rang=-1);

    /*!
     * \brief Enregistre les mesures dans un fichier
     * \param nomFichier Le nom du fichier où enregistrer les mesures
     */
    void sauvegarder(QString nomFichier) const;

    /*!
     * \brief Charge une jeu de mesures préalablement sauvegardées dans un fichier
     * \param nomFichier Le nom du fichier
     * \return false en cas d'échec
     */
    bool charger(QString nomFichier);

    /*!
     * \brief Renvoie le nombre de trames incomplètes reçues
     */
    quint32 nbTramesIncompletes() const;

private:
    Capteur* _capteurs[eMax+1];
    QTimer * _timer;
    Liaison * _liaison;
    quint32 _nbTramesIncompletes;

signals:

    /**
     * @brief Signal envoyé après chaque cycle d'acquisition
     *
     */
    void nouvelleMesure();


private slots:
    /**
     * @brief Slot pour réaliser une acquisition. A la fin de l'acquisition, le signal nouvelleMesure() est émis.
     *
     */

    void faireMesure();
};

#endif
