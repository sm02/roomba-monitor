#include "mesurage.h"

Mesurage::Mesurage(QObject *parent) :
    QObject(parent)
{
    for (int i=eMin;i<=eMax;i++)
        _capteurs[i]=new Capteur;

    _timer = new QTimer(this);
    _timer->setInterval(PERIODE_ECHANTILLONNAGE);
    connect(_timer, SIGNAL(timeout()), this, SLOT(faireMesure()));
    _nbTramesIncompletes = 0;
}

void Mesurage::setLiaison(Liaison* l) {
    _liaison=l;
}

qint32 Mesurage::mesure(eCapt capt, qint32 rang)
{
    return _capteurs[capt]->valeur(rang);
}

void Mesurage::sauvegarder(QString nomFichier) const
{
    QFile fichier(nomFichier);
    fichier.open(QIODevice::WriteOnly);
    QDataStream out(&fichier);

    // Ecrire l'entête avec la signature

    out << (quint32)0x526d6261;  //"Rmba"
    //out << (quint32)0x00;         //version=0

    //out.setVersion(QDataStream::Qt_4_0);

    // Ecrire les données
    for (uint i=0;i<nbMesures();i++) {
        for (int c=eMin;c<=eMax;c++) {
            out << _capteurs[(eCapt)c]->valeur(i);
        }
        //out << (quint32)0x12345678;
    }
    fichier.close();
}


bool Mesurage::charger(QString nomFichier)
{
    QFile fichier(nomFichier);
    fichier.open(QIODevice::ReadOnly);
    QDataStream in(&fichier);

    // Lecture et vérification de l'entête
    quint32 magic;
    in >> magic;
    if (magic != 0x526d6261) {
        qDebug("Le fichier ne commence pas par l'étiquette 0x526d6261 (\"Rmba\")\n");
        return false;
    }

    // Lecture de la version
    quint32 version;
    in >> version;

    if (version != 0) {
        qDebug("Seule la version 0 est supportée.\n");
        return false;
    }
    // Lecture des données

    qint32 valeur;
    while (! in.atEnd()) {
        for (int c=eMin;c<=eMax;c++) {
            in >> valeur;
            _capteurs[(eCapt)c]->ajouterValeur(valeur);
        }
    }
    fichier.close();
    qDebug("Ouverture du fichier : Nb enregistrements lus:%d\n",this->nbMesures());
    return true;
}


bool Mesurage::demarrerAcquisition()
{
    _nbTramesIncompletes = 0;
    if (! _liaison->connexionEtablie()) {
        if (!_liaison->connecter()) return false;
    }
    _timer->start();
    return true;
}

void Mesurage::arreterAcquisition()
{
    _timer->stop();
}

void Mesurage::faireMesure() {

    QByteArray cmdSensors100;
    cmdSensors100.append(142);
    cmdSensors100.append(100);
    /*Sensors
         *Opcode: 142 Data Bytes: 1
         *This command requests the OI to send a packet of sensor data bytes. There are 58 different sensor data
         *packets. Each provides a value of a specific sensor or group of sensors.
    */
    _liaison->envoyerCommande(cmdSensors100);

    Trame tr(_liaison->lireTrame());
    if (tr.size() != 80) {
        _nbTramesIncompletes++;
        return;
    }

    // On extrait de la trame les mesures:
    //pos=0 ID=7
    _capteurs[soulevRoueG]->ajouterValeur(tr.getBit(0,3));
    _capteurs[soulevRoueD]->ajouterValeur(tr.getBit(0,2));
    _capteurs[chocG]->ajouterValeur(tr.getBit(0,1));
    _capteurs[chocD]->ajouterValeur(tr.getBit(0,0));
    //pos=1 ID=8
    _capteurs[mur]->ajouterValeur(tr.getUnsignedByte(1));
    //pos=2 ID=9
    _capteurs[videG]->ajouterValeur(tr.getUnsignedByte(2));
    //pos=3 ID=10
    _capteurs[videAvG]->ajouterValeur(tr.getUnsignedByte(3));
    //pos=4 ID=11
    _capteurs[videAvD]->ajouterValeur(tr.getUnsignedByte(4));
    //pos=5 ID=12
    _capteurs[videD]->ajouterValeur(tr.getUnsignedByte(5));
    //pos=6 ID=13
    _capteurs[murVirtuel]->ajouterValeur(tr.getUnsignedByte(6));
    //pos=7 ID=14
    _capteurs[surIntensRoueG]->ajouterValeur(tr.getBit(7,4));
    _capteurs[surIntensRoueD]->ajouterValeur(tr.getBit(7,3));
    _capteurs[surIntensBrossePrinc]->ajouterValeur(tr.getBit(7,2));
    _capteurs[surIntensBrosseLat]->ajouterValeur(tr.getBit(7,0));
    //pos=8 ID=15
    _capteurs[nivPoussiere]->ajouterValeur(tr.getUnsignedByte(8));
    //pos=9 : ID=16 (unused byte)
    //pos=10 ID=17
    _capteurs[infrarougeOmnidir]->ajouterValeur(tr.getUnsignedByte(10));
    //pos=11 ID=18
    _capteurs[boutonHorloge]->ajouterValeur(tr.getBit(11,7));
    _capteurs[boutonProg]->ajouterValeur(tr.getBit(11,6));
    _capteurs[boutonJour]->ajouterValeur(tr.getBit(11,5));
    _capteurs[boutonHeure]->ajouterValeur(tr.getBit(11,4));
    _capteurs[boutonMin]->ajouterValeur(tr.getBit(11,3));
    _capteurs[boutonBase]->ajouterValeur(tr.getBit(11,2));
    _capteurs[boutonSpot]->ajouterValeur(tr.getBit(11,1));
    _capteurs[boutonNett]->ajouterValeur(tr.getBit(11,0));
    //pos=12/13 ID=19
    _capteurs[distance]->ajouterValeur(tr.getSignedWord(12));
    //pos=14/15 ID=20
    _capteurs[angle]->ajouterValeur(tr.getSignedWord(14));
    //pos=16 ID=21
    _capteurs[etatCharge]->ajouterValeur(tr.getUnsignedByte(16));
    //pos=17/18 ID=22
    _capteurs[voltage]->ajouterValeur(tr.getUnsignedWord(17));
    //pos=19/20 ID=23
    _capteurs[courant]->ajouterValeur(tr.getSignedWord(19));
    //pos=21 ID=24
    _capteurs[temperature]->ajouterValeur(tr.getSignedByte(21));
    //pos=22/23 ID=25
    _capteurs[chargeBat]->ajouterValeur(tr.getUnsignedWord(22));
    //pos=24/25 ID=26
    _capteurs[capaciteBat]->ajouterValeur(tr.getUnsignedWord(24));
    //pos=26/27 ID=27
    _capteurs[signalMur]->ajouterValeur(tr.getUnsignedWord(26));
    //pos=28/29 ID=28
    _capteurs[signalVideG]->ajouterValeur(tr.getUnsignedWord(28));
    //pos=30/31 ID=29
    _capteurs[signalVideAvG]->ajouterValeur(tr.getUnsignedWord(30));
    //pos=32/33 ID=30
    _capteurs[signalVideAvD]->ajouterValeur(tr.getUnsignedWord(32));
    //pos=34/35 ID=31
    _capteurs[signalVideD]->ajouterValeur(tr.getUnsignedWord(34));
    //pos=36 ID=32 (unused)
    //pos=37/38 ID=33 (unused)
    //pos=39 ID=34
    _capteurs[chargeurBase]->ajouterValeur(tr.getBit(39,1));
    _capteurs[chargeurInterne]->ajouterValeur(tr.getBit(39,0));
    //pos=40 ID=35
    _capteurs[mode]->ajouterValeur(tr.getUnsignedByte(40));
    //pos=41 ID=36
    _capteurs[noMusique]->ajouterValeur(tr.getUnsignedByte(41));
    //pos=42 ID=37
    _capteurs[musique]->ajouterValeur(tr.getUnsignedByte(42));
    //pos=43 ID=38
//...
    //pos=69 ID=52
    _capteurs[infrarougeG]->ajouterValeur(tr.getUnsignedByte(69));
    //pos=70 ID=53
    _capteurs[infrarougeD]->ajouterValeur(tr.getUnsignedByte(70));
    //...
    emit nouvelleMesure();
}


quint32 Mesurage::nbTramesIncompletes() const
{
    return _nbTramesIncompletes;
}

quint32 Mesurage::nbMesures() const
{
    return _capteurs[eMin]->size();
}

