#include "cserie.h"
#include "stdio.h"

void CSerie::ThrowError( ErrorType error)
{
// r�cup�re les renseignements dur l'erreur mais c'est � l'utilisateur de retourner
     LastError = error;      // interne
     Errno= GetLastError();  // win32
}

int CSerie::LastErr(char * ErrorString)
{
// retourne le num�ro de la derni�re erreur et remplit ErrorString
// c'est � l'utilisateur de pr�voir suffisamment d'espace pour ErrorString
// errorno est la dern erreur d�tect�e par win32 au moment du lancement de
// l'erreur Error

     // AnsiString E;
      char E[120];
      LPVOID lpMsgBuf;
      switch(LastError)
      {
        case WITHOUT_ERROR:         strcpy(E," Sans erreur  ! ");break;
        case  BAD_SERIAL_PORT :     strcpy(E," mauvais nom de port ") ;break;
        case BAD_BAUD_RATE  :       strcpy(E," mauvais BAUD_RATE") ;break;
        case BAD_PORT_NUMBER  :     strcpy(E," mauvais numero de port ") ;break;
        case BAD_STOP_BITS  :       strcpy(E," mauvais bits de stop ") ;break;
        case BAD_PARITY   :         strcpy(E," mauvaise parite ") ;break;
        case BAD_BYTESIZE  :        strcpy(E," mauvais BYTESIZE ") ;break;
        case PORT_ALREADY_OPEN  :   strcpy(E," port deja ouvert ") ;break;
        case PORT_NOT_OPEN :        strcpy(E," port pas ouvert ") ;break;
        case OPEN_ERROR :           strcpy(E," probleme d'ouverture ") ;break;
        case WRITE_ERROR :          strcpy(E," probleme d'emission ") ;break;
        case READ_ERROR  :          strcpy(E," probleme de reception ") ;break;
        case CLOSE_ERROR  :         strcpy(E," probleme de fermeture ") ;break;
        case PURGECOMM :            strcpy(E,"PURGECOMM") ;break;
        case FLUSHFILEBUFFERS :     strcpy(E,"FLUSHFILEBUFFERS" );break;
        case GETCOMMSTATE :         strcpy(E,"GETCOMMSTATE") ;break;
        case SETCOMMSTATE :         strcpy(E,"SETCOMMSTATE") ;break;
        case SETUPCOMM  :           strcpy(E,"SETUPCOMM") ;break;
        case SETCOMMTIMEOUTS :      strcpy(E,"SETCOMMTIMEOUTS") ;break;
        case CLEARCOMMERROR  :      strcpy(E,"CLEARCOMMERROR") ;break;
        case CEBREAK:              strcpy(E," signal BREAK electronique ") ;break;
        case CEFRAME:              strcpy(E," erreur de CADRE ") ;break;
        case CEIOE:                strcpy(E," erreur d'E/S ") ;break;
        case CEOVERRUN:            strcpy(E," plus de place dans buffer reception : caractere perdu ") ;break;
        case CERXOVER:             strcpy(E," overflow ou reception d'un caractere apres EOF") ;break;
        case CERXPARITY:           strcpy(E," erreur de parite ") ;break;
        case CETXFULL:             strcpy(E," buffer emission plein : ") ;break;
        default :                   strcpy(E,"erreur interne "); break;

      }

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            Errno,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
           (LPTSTR) &lpMsgBuf,
            0,
            NULL
            );
    if(ErrorString)
           sprintf(ErrorString,"TCommPort : %s :: Win32 : %s \n",E,(const char *)lpMsgBuf);
    // rend la memoire (tir� de l'exemple de FormatMessage)
    LocalFree( lpMsgBuf );

 return (int) Errno;
}
//------------------------------------------------------------------------------
CSerie::CSerie(void)
  :m_CommOpen(false),
   m_CommPort("COM2"),
   m_hCom(INVALID_HANDLE_VALUE)
{   // initialise le port comm avec des valeurs convenables au cas o� OpenCommPort
    // serait appel� avant l'une des m�thodes SETxxx
    m_dcb.DCBlength = sizeof(DCB);
    m_dcb.BaudRate  =9600;
    m_dcb.ByteSize  =8;
    m_dcb.Parity    =NOPARITY;    //EVENPARITY etc dans windows.h
    m_dcb.StopBits  =ONESTOPBIT;

    SetTimeout(1000);         // 1 seconde de timeout
    ThrowError(WITHOUT_ERROR);     // pour l'instant pas d'erreur !!
}
//--------------------------------------------------------------------------------------
CSerie::~CSerie(void)
{
    if(m_CommOpen) CloseCommPort();
}
//--------------------------------------------------------------------------------------
void CSerie::SetTimeout(unsigned int Millisecondes)
{
    Timeout=Millisecondes;
}
//--------------------------------------------------------------------------------------
bool CSerie::OpenCommPort(void)
{
    bool Retour=true;
    DWORD bufferin=2048,bufferout=1024;
    COMMPROP commprop;
    DCB tempDCB;
    if(m_CommOpen)   return Retour;      // si d�j� fait on retourne

    // on sauvegarde les 4 champs DCB (parmi d'autres) que l'on va modifier
    tempDCB.BaudRate  =  m_dcb.BaudRate;
    tempDCB.ByteSize  =  m_dcb.ByteSize;
    tempDCB.Parity    =  m_dcb.Parity;
    tempDCB.StopBits  =  m_dcb.StopBits;

    // on tente d'ouvrir le port
    m_hCom = CreateFileA(m_CommPort.c_str(),
                        GENERIC_READ | GENERIC_WRITE,    // On veut lire et �crire !
                        0,     // oblig� pour comm
                        NULL, // pas de s�curit�
                        OPEN_EXISTING, // oblig� pour comm
                        0,    // acces synchrone
                        NULL // oblig� pour comm
                        );

   //  si m_hCom = INVALID_HANDLE_VALUE alors lancer une erreur  (voir classe erreur)
       if(m_hCom == INVALID_HANDLE_VALUE)
       {
            ThrowError(OPEN_ERROR);
            Retour=false;
            return Retour;
       }

    // si l'on est ici c'est que le port a pu �tre ouvert
   // on tente de r�cup�rer les propri�t�s DCB du port
    if(!GetCommState(m_hCom,&m_dcb))
    {
        //quelquechose ne va pas : on ferme et on lance une erreur
        CloseHandle(m_hCom);
        ThrowError(GETCOMMSTATE);
        Retour=false;
        return Retour;
    }

     //dcb contient toutes les propri�t�s r�elles du port. On copie les valeurs d�sir�es dedans
    m_dcb.BaudRate  =  tempDCB.BaudRate;
    m_dcb.ByteSize  =  tempDCB.ByteSize;
    m_dcb.Parity    =  tempDCB.Parity;
    m_dcb.StopBits  =  tempDCB.StopBits;

   // on configure maintenant le port
    if(!SetCommState(m_hCom,&m_dcb))
    {
        //quelquechose ne va pas : on ferme et on lance une erreur
        CloseHandle(m_hCom);
        ThrowError(SETCOMMSTATE);
        Retour=false;
        return Retour;
    }

   // fixe les valeurs initiales des files d'�mission et de r�ception
        ::GetCommProperties(m_hCom, &commprop);     // appel � GetCommProperties de Windows
        // GetCommProperties (commprop) pas utilisable puisque pas ouvert officiellement
        // on prend bufferout = bufferin / 2
        // et     1024    < bufferin  < 32 * 1024
        // attention aux drivers idiots qui retourne 0 en capacit�s ou des capacit�s
        // visiblement trop importantes !
        bufferin=commprop.dwMaxRxQueue;
        if (bufferin > 32*1024 ) bufferin =  32*1024;
        if( bufferin  < 1024) bufferin = 1024;
        bufferout = bufferin / 2;

    if(!SetupComm(m_hCom, bufferin,bufferout))
    {
        //quelquechose ne va pas : on ferme et on lance une erreur
        CloseHandle(m_hCom);
        ThrowError(SETUPCOMM);
        Retour=false;
        return Retour;
    }

   // 0 indique : pas utilis�
   // MAXDWORD : constante sp�ciale

   // d�lais maxi pour readfile( ) , si un des d�lais est d�pass�, readfile retourne pr�matur�ment 0:
   // d�lai maxi entre chaque r�ception de caract�re : ReadIntervalTimeout

   ///////////////////////////////////////////////////////////////////////////////////////////////////////////
   // d�lai total pour n caract�res demand�s :   ReadTotalTimeoutConstant +  (n * ReadTotalTimeoutMultiplier)
   // LA FORMULE EST SEMBLABLE EN ECRITURE
   //////////////////////////////////////////////////////////////////////////////////////////////////////////

    m_TimeOuts.ReadIntervalTimeout         = MAXDWORD;
    m_TimeOuts.ReadTotalTimeoutMultiplier  = MAXDWORD;
    m_TimeOuts.ReadTotalTimeoutConstant    = Timeout;
    //ici on prend sans attendre les caracteres du tampon et s'il n'y en a pas, on attend au maximum Timeout millisecondes
  /*
   en effet d'apr�s l'aide win32 :
    Si une application initialise ReadIntervalTimeout et ReadTotalTimeoutMultiplier � MAXDWORD et
    initialise ReadTotalTimeoutConstant � une valeur sup�rieure � z�ro et plus petite que MAXDWORD,
    voil� ce qui arrive quand ReadFile est appel�e :
- s'il y a des caract�res dans le buffer d'entr�e, ReadFile retourne imm�diatement avec ceux-ci
dans la zone de buffer;
- s'il n'y a pas de caract�res dans le buffer d'entr�e, ReadFile attend jusqu'� ce qu'un caract�re
arrive dans le buffer et retourne alors imm�diatement;
- s'il n'y a pas de caract�re qui arrive dans le d�lai sp�cifi� par  ReadTotalTimeoutConstant,
ReadFile termine par timeout.
Remarques sur les timeouts :
Ils ne sont pas trait�s comme une erreur durant les lectures ou �critures : readfile ou writeFile
retourne une valeur de succ�s. Le compte d'octets lu ou �crit est report� par ReadFile ou writeFile
( ou  GetOverlappedResult or FileIOCompletionRoutine en asynchrone).

Une valeur de 0 � la fois pour  WriteTotalTimeoutMultiplier et WriteTotalTimeoutConstant indique que
les timeout totaux ne sont pas utilis�s pour les op�rations d'�criture (ce sont les seuls timeouts
support�s en �criture)
*/


    // normalement pas utile en �criture puisque nous commandons mais on ne sais jamais ...
    m_TimeOuts.WriteTotalTimeoutMultiplier = 0;
    m_TimeOuts.WriteTotalTimeoutConstant   = Timeout;

    //mise en place de ces time-outs
    if(!SetCommTimeouts(m_hCom, &m_TimeOuts))
    {
        //quelquechose ne va pas : on ferme et on lance une erreur
        CloseHandle(m_hCom);
        ThrowError(SETCOMMTIMEOUTS);
        Retour=false;
        return Retour;
    }

    // si on est ici c'est que tout va bien
    ThrowError(WITHOUT_ERROR);
    m_CommOpen = true;
    return Retour;
}
//--------------------------------------------------------------------------------------
bool CSerie::CloseCommPort(void)
{
    bool Retour=true;
    if(!m_CommOpen)       // si d�j� fait, retourne
      return Retour;

    if(CloseHandle(m_hCom) != 0) // CloseHandle est diff�rent de 0 en cas de succ�s
    {
        m_CommOpen = false;
    }
    else
    {
        ThrowError(CLOSE_ERROR);
        Retour=false;
        return Retour;
    }
    return Retour;

}
//--------------------------------------------------------------------------------------
bool CSerie::SetCommDCBProperties(DCB &properties)
{
    // si le port est ouvert, essaye d'ajuster les propri�t�s sinon
    // r�alise juste une affectation
    bool Retour=true;
    if(m_CommOpen)  // port est ouvert
    {
        if(!SetCommState(m_hCom,&properties))
        {
            // n'a pas march�
            ThrowError(SETCOMMSTATE);
            Retour=false;
            return Retour;

        }
        else
        {

            m_dcb = properties;
        }
    }
    else
    {
        m_dcb = properties;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
void CSerie::GetCommDCBProperties(DCB &properties)
{
  properties = m_dcb;
}
//--------------------------------------------------------------------------------------
bool CSerie::SetBaudRate(unsigned int newBaud)
{
    // si le port est ouvert, essaye d'ajuster les propri�t�s sinon
    // r�alise juste une affectation
    bool Retour=true;
    unsigned int oldBaudRate = m_dcb.BaudRate; // sauvegarde
    m_dcb.BaudRate = newBaud;

    if(m_CommOpen)
    {
        if(!SetCommState(m_hCom,&m_dcb))
        {
            m_dcb.BaudRate = oldBaudRate;      // restauration  car probl�me
            ThrowError(BAD_BAUD_RATE);
            Retour=false;
            return Retour;
        }
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
bool CSerie::SetByteSize(BYTE newByteSize)
{
    // si le port est ouvert, essaye d'ajuster les propri�t�s sinon
    // r�alise juste une affectation
    bool Retour=true;
    BYTE oldByteSize = m_dcb.ByteSize; // sauvegarde
    m_dcb.ByteSize = newByteSize;

    if(m_CommOpen)
    {
        if(!SetCommState(m_hCom,&m_dcb))
        {
            m_dcb.ByteSize = oldByteSize;          // restauration  car probl�me
            ThrowError(BAD_BYTESIZE);
            Retour=false;
            return Retour;

        }
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
bool CSerie::SetParity(BYTE newParity)
{
    // si le port est ouvert, essaye d'ajuster les propri�t�s sinon
    // r�alise juste une affectation
    bool Retour=true;
    BYTE oldParity = m_dcb.Parity;        // sauvegarde
    m_dcb.Parity = newParity;

    if(m_CommOpen)
    {
        if(!SetCommState(m_hCom,&m_dcb))
        {
            m_dcb.Parity = oldParity;           // restauration  car probl�me
            ThrowError(BAD_PARITY);
            Retour=false;
            return Retour;
        }
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
bool CSerie::SetStopBits(BYTE newStopBits)
{
    // si le port est ouvert, essaye d'ajuster les propri�t�s sinon
    // r�alise juste une affectation
    bool Retour=true;
    BYTE oldStopBits = m_dcb.StopBits;        // sauvegarde
    m_dcb.StopBits = newStopBits;

    if(m_CommOpen)
    {
        if(!SetCommState(m_hCom,&m_dcb))
        {
            m_dcb.StopBits = oldStopBits;              // restauration  car probl�me
            ThrowError(BAD_STOP_BITS);
            Retour=false;
            return Retour;

        }
    }
    return Retour;
}
//--------------------------------------------------------------------------------------

unsigned int CSerie::GetBaudRate(void)
{
  return m_dcb.BaudRate;
}
//--------------------------------------------------------------------------------------
BYTE CSerie::GetByteSize(void)
{
  return m_dcb.ByteSize;
}
//--------------------------------------------------------------------------------------
BYTE CSerie::GetParity(void)
{
  return m_dcb.Parity;
}
//--------------------------------------------------------------------------------------
BYTE CSerie::GetStopBits(void)
{
  return m_dcb.StopBits;
}
//--------------------------------------------------------------------------------------
/*! \brief
 *
 *\param[in] buffer byte[] � envoyer
 *\param[in] ByteCount Nombre d'octet � envoyer
 *\param[out] Bytes Nombre d'octets effectivement envoy�s
 */
TRetour CSerie::WriteBuffer(BYTE *buffer, unsigned long ByteCount, unsigned long * Bytes)
{
    TRetour Retour=OK;
    bool Resultat;
    Resultat=VerifyOpen();
    if( (ByteCount == 0) || (buffer == NULL) || (Bytes==NULL) || (!Resultat) )
    {
        if(Bytes) *Bytes=0;
        if (buffer) *buffer=0;
        Retour=WARNING;
        return Retour;
    }
    *Bytes=0;
    Resultat=WriteFile(m_hCom,buffer,ByteCount,Bytes,NULL);
    if(!Resultat )
    {       // cas erreur de communication
            ThrowError(WRITE_ERROR);
            Retour=ERREUR;
    }
    if(Resultat && (*Bytes < ByteCount) )
    {
            // timeout
           Retour=TIMEOUT;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::WriteBufferSlowly(BYTE *buffer, unsigned long ByteCount, unsigned long * Bytes)
{
    // attention, le fait de forcer la transmission ne veut pas dire
    // pour autant que celle-ci soit r�alis�e electroniquement
    // le driver consid�re l'octet envoy� quand il est transmis
    // � l'UART

    TRetour Retour=OK;
    unsigned long NombreEcrit=0;
    bool Resultat;
    Resultat=VerifyOpen();
    if( (ByteCount == 0) || (buffer == NULL) || (!Resultat)  || (Bytes==NULL) )
    {
        if(Bytes) *Bytes=0;
        if (buffer) *buffer=0;
        Retour=WARNING;
        return Retour;
    }
    *Bytes=0;
    for (unsigned int j=0; j<ByteCount; j++)
    {
        if(!WriteFile(m_hCom,buffer,1,&NombreEcrit,NULL))
        {
            ThrowError(WRITE_ERROR);
            Retour=ERREUR;
            return Retour;
        }
        *Bytes=*Bytes + NombreEcrit;
        if(NombreEcrit!=1)
        {
            Retour=TIMEOUT;
            return Retour;
        }
        if( (Retour=FlushCommPort())!=OK )
        {
            // FlushCommPort a eu un probl�me
            Retour=ERREUR;
            return Retour;

        }
        ++buffer;
        NombreEcrit=0;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::WriteString(const char *outString, unsigned long * Bytes)
{
// outString ***doit*** �tre une chaine � O terminal
// le 0 terminal est envoy�

   TRetour Retour=OK;
   unsigned long Longueur;
    bool Resultat;
    Resultat=VerifyOpen();
    if( outString==NULL || (!Resultat) || (Bytes==NULL) )
    {
        if(Bytes) *Bytes=0;
        Retour=WARNING;
        return Retour;
    }
    *Bytes=0;
    Longueur=strlen(outString)+1; // + 1 pour le 0 terminal car strlen ne le compte pas
    if(!WriteFile(m_hCom,outString, Longueur,Bytes,NULL))
    {
        ThrowError(WRITE_ERROR);
        Retour=ERREUR;
        return Retour;
    }
    if(*Bytes!=Longueur)
    {
       Retour=TIMEOUT;
       return Retour;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::ReadBytes(BYTE *buffer, unsigned long MaxBytes, unsigned long *Bytes)
{
    // lit des octets
    // c'est � l'utilisateur de pr�voir suffisamment d'espace pour buffer
    TRetour Retour=OK;
    bool Resultat;
    Resultat=VerifyOpen();
    if( (MaxBytes == 0) || (buffer == NULL) || (!Resultat) || (Bytes==NULL) )
    {
        if(Bytes) *Bytes=0;
        Retour=WARNING;
        return Retour;
    }
    *Bytes=0;
    if(!ReadFile(m_hCom,buffer,MaxBytes,Bytes,NULL))
    {
        ThrowError(READ_ERROR);
        Retour=ERREUR;
        return Retour;
    }
    if(*Bytes != MaxBytes)
    {
        Retour=TIMEOUT;
        return Retour;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::ReadString(char *str, unsigned long MaxBytes, unsigned long * Bytes, char * End, unsigned long Length)
{
    // lit une chaine d'au maximum MaxBytes sauf si End est rencontr�
    // str doit faire MaxBytes
    // length repr�sente le nombre de caract�res � prendre en compte pour End

    TRetour Retour=OK;
    unsigned int Compteur=0;
    bool Resultat;
    BYTE Octet;
    Resultat=VerifyOpen();

    // cas triviaux
    if( (MaxBytes == 0) || (str == NULL) || (!Resultat)  || (Bytes==NULL) || ((Length >0) && (End ==NULL))  )
    {
        if(Bytes) *Bytes=0;
        Retour=WARNING;
        return Retour;
    }

    *Bytes=0;

    while(*Bytes < MaxBytes)
    {
        Retour=GetByte(&Octet);
        if(Retour==OK)
        {
              str[*Bytes] =Octet;
              *Bytes = *Bytes +1;
              if(Length >0)
              {
                  if(Octet==End[Compteur])
                  {
                        Compteur++;
                  }
                  else
                  {
                        if(Compteur && (Octet==End[0]))
                        {
                            // ce n'est pas le bon x �me
                            // mais c'est le bon 1er!
                            // (attention au cas XyX)
                            Compteur=1;
                        }
                        else
                        {   //*********************************
                            Compteur=0; //rien ne correspond
                            //*********************************
                        }
                  }
                  if(Compteur==Length)       // on a trouve la fin
                  {
                            return Retour;
                  }
              }
        }
        else
        {
            return Retour;
        }
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::DiscardBytes(unsigned long MaxBytes, unsigned long * Bytes)
{
    TRetour Retour=OK;
    bool Resultat;
    Resultat=VerifyOpen();
    if( (MaxBytes == 0) || (!Resultat)  || (Bytes==NULL))
    {
        if(Bytes) *Bytes=0;
        Retour=WARNING;
        return Retour;
    }
    *Bytes=0;
    BYTE *Poubelle= new BYTE[MaxBytes];
    Retour=ReadBytes(Poubelle, MaxBytes,Bytes);
    delete []Poubelle;
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::PurgeCommPort(void)
{
    //   vider la file de r�ception et d'emission : efface sans lire
    TRetour Retour=OK;
    bool Resultat;

    Resultat=VerifyOpen();
    if( !Resultat )
    {
        Retour=WARNING;
        return Retour;
    }
    if(!PurgeComm(m_hCom,PURGE_RXCLEAR | PURGE_TXCLEAR	))
    {
        ThrowError(PURGECOMM);
        Retour=ERREUR;
        return Retour;
    }

    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::FlushCommPort(void)
{
    TRetour Retour=OK;
    bool Resultat;
    Resultat=VerifyOpen();
    if( !Resultat )
    {
        Retour=WARNING;
        return Retour;
    }
    //pousser la file de transmission seulement (force la transmission)
    if(!FlushFileBuffers(m_hCom))
    {
        ThrowError(FLUSHFILEBUFFERS);
        Retour=ERREUR;
        return Retour;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::PutByte(BYTE value)
{
    TRetour Retour=OK;
    DWORD dummy;
    bool Resultat;
    Resultat=VerifyOpen();
    if( !Resultat  )
    {
        Retour=WARNING;
        return Retour;
    }
    if(!WriteFile(m_hCom,&value,1,&dummy,NULL))
    {
        ThrowError(WRITE_ERROR);
        Retour=ERREUR;
        return Retour;
    }
    if(dummy != 1)
    {
        Retour=TIMEOUT;
        return Retour;
    }
    return Retour;
}
TRetour CSerie::GetByte(BYTE * Octet)
{
    TRetour Retour=OK;
    DWORD Nombrelu;
    bool Resultat;
    Resultat=VerifyOpen();
    if( (!Resultat)  || (Octet==NULL))
    {
        Retour=WARNING;
        return Retour;
    }
    if (! ReadFile(m_hCom,Octet,1,&Nombrelu,NULL))
    {
        ThrowError(READ_ERROR);
        Retour=ERREUR;
        return Retour;
    }
    if(Nombrelu != 1)
    {
        Retour=TIMEOUT;
        return Retour;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
TRetour CSerie::BytesAvailable(unsigned long * Nb)
{
    TRetour Retour=OK;
    COMSTAT comstat;
    DWORD Pasdummy=0;
    bool Resultat;

    Resultat=VerifyOpen();

    if(  (!Resultat ) ||( Nb==NULL) )
    {
        if (Nb) *Nb=0;
        Retour=WARNING;
        return Retour;
    }
    *Nb=0;
    if(!ClearCommError(m_hCom, &Pasdummy, &comstat))
    {
        ThrowError(CLEARCOMMERROR);
        Retour=ERREUR;
        return Retour;
    }

    *Nb=comstat.cbInQue;

    switch(Pasdummy)
    {
        case CE_BREAK:     ThrowError(CEBREAK) ;break;
        case CE_FRAME:      ThrowError(CEFRAME) ;break;
        case CE_IOE:         ThrowError(CEIOE);break;
        case CE_OVERRUN:      ThrowError(CEOVERRUN) ;break;
        case CE_RXOVER:        ThrowError(CERXOVER) ;break;
        case CE_RXPARITY:      ThrowError(CERXPARITY) ;break;
        case CE_TXFULL:        ThrowError(CETXFULL) ;break;
        case 0 :                break;
        default :              ThrowError(CLEARCOMMERROR) ; Retour=ERREUR; break;
    }
    return Retour;
}
//--------------------------------------------------------------------------------------
void CSerie::SetCommPort(const std::string & port)
{
    // on ne fait rien si c'est d�j� ouvert
    if(  (m_CommOpen)  || (port=="") )
    {
        ThrowError(OPEN_ERROR);
        return;
    }
    m_CommPort = port;
}
//--------------------------------------------------------------------------------------
std::string CSerie::GetCommPort(void)
{
    return m_CommPort;
}
//--------------------------------------------------------------------------------------
void CSerie::GetCommProperties(COMMPROP &properties)
{
    ZeroMemory(&properties, sizeof(COMMPROP));    // met � zero la zone m�moire properties
                                                    // moyen de savoir si �a a march�
    // il faut un handle pour avoir les infos
    if( !m_CommOpen  )
    {
       return;
    }
    ::GetCommProperties(m_hCom, &properties);     // appel � GetCommProperties de Windows
}
