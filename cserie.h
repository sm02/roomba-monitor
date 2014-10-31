#ifndef CSERIE_H
#define CSERIE_H

#include <windows.h>
#include <string>
#include <string.h>

// Attention � OPEN_ERROR car dans ce cas le port s�rie n'a pu �tre ouvert quand,
// par exemple, une autre application utilise d�j� ce port ou que l'on cr�e 2 objets
// identiques

//--------------------------------------------------------------------------------------
 typedef enum ErrorType
        {WITHOUT_ERROR,BAD_SERIAL_PORT, BAD_BAUD_RATE, BAD_PORT_NUMBER, BAD_STOP_BITS, BAD_PARITY,
        BAD_BYTESIZE, PORT_ALREADY_OPEN, PORT_NOT_OPEN, OPEN_ERROR, WRITE_ERROR, READ_ERROR,
        CLOSE_ERROR, PURGECOMM, FLUSHFILEBUFFERS, GETCOMMSTATE, SETCOMMSTATE, SETUPCOMM,
        SETCOMMTIMEOUTS, CLEARCOMMERROR, CEBREAK, CEFRAME,CEIOE,CEOVERRUN,CERXOVER,CERXPARITY,CETXFULL}  TError;
 typedef enum RetourType {ERREUR,WARNING,TIMEOUT,OK} TRetour;

class CSerie
{
  public:
    CSerie(void);
    ~CSerie(void);
    bool OpenCommPort(void);                        // Tente d'ouvrir le port
    bool CloseCommPort(void);                       // Ferme le port
    void SetCommPort(const std::string & port);     // Notification du nom du port (COM1,COM2 ...)
    std::string GetCommPort(void);                  // Quel est le nom du port ?
    bool SetBaudRate(unsigned int newBaud);         // Configurer la vitesse
    unsigned int GetBaudRate(void);                 // Quelle vitesse ?
    bool SetParity(BYTE newParity);                 // Configurer la parit�
    BYTE GetParity(void);                           // Quelle parit� ?
    bool SetByteSize(BYTE newByteSize);             // Configurer le nombre de bits
    BYTE GetByteSize(void);                         // Obtenir le nombre de bits
    bool SetStopBits(BYTE newStopBits);             // Configurer le nombre de bits de stops
    BYTE GetStopBits(void);                         // Obtenir le nombre de bits de stops
    bool SetCommDCBProperties(DCB &properties);     // utilisation � �viter
    void GetCommDCBProperties(DCB &properties);     // utilisation � �viter
    void GetCommProperties(COMMPROP &properties);   // Obtenir les possibilit�s maximales du port
    TRetour WriteString(const char *outString, unsigned long * Bytes);        // Envoyer une chaine avec son 0 terminal
    TRetour WriteBuffer(BYTE  *buffer, unsigned long ByteCount, unsigned long * Bytes);        // Envoyer ByteCount octets d'un seul coup
    TRetour WriteBufferSlowly(BYTE *buffer, unsigned long ByteCount, unsigned long * Bytes);   // Envoyer ByteCount octets octet par octet
    TRetour ReadString(char *string, unsigned long MaxBytes, unsigned long * Bytes, char * End, unsigned long Length);  // Lire une chaine (voir m�thode)
    TRetour ReadBytes(BYTE *bytes, unsigned long byteCount, unsigned long *Bytes);  // Lire des octets  (voir m�thode)
    TRetour DiscardBytes(unsigned long MaxBytes, unsigned long * Bytes);                       // Ecarter Maxbytes octets
    TRetour PurgeCommPort(void);                       // Effacer la file de r�ception et d'emission (sans envoyer)
    TRetour FlushCommPort(void);                       // Pousser la file d'emission  (en envoyant)
    TRetour PutByte(BYTE value);                      // Envoyer 1 octet
    TRetour GetByte(BYTE * Octet);                    // Obtenir un octet
    TRetour BytesAvailable( unsigned long * Nb);        // Pour obtenir le nombre d'octets dans le buffer en attente de lecture
    bool GetConnected() { return m_CommOpen; }      // Le port est-il ouvert ?
    HANDLE GetHandle()  { return m_hCom;   }        // utilisation � �viter
    int LastErr(char * ErrorString);                // retourne le num�ro de la derni�re erreur et remplit ErrorString
    void SetTimeout(unsigned int Millisecondes);    // initialiser le  timeout

  protected:


    void ThrowError( TError error);                 // Met � jour les indicateurs d'erreur.
    bool VerifyOpen(void) {
        if(!m_CommOpen)
        {
            ThrowError(PORT_NOT_OPEN);
            return false;
        }
        else return true;
    }
    bool VerifyClosed(void)
    {
        if(m_CommOpen)
         {
            ThrowError(PORT_ALREADY_OPEN);
            return false;
        }
        else return true;
    }
    bool          m_CommOpen;
    COMMTIMEOUTS  m_TimeOuts;   // structure windows
    std::string   m_CommPort;         // chaine COMx ...
    DCB           m_dcb;        // DCB est une structure utilis�e par win pour configurer le port
    HANDLE        m_hCom;       // handle du port COMx
    DWORD         Errno;        // derni�re erreur d�tect�e par win32 au moment ou l'on a lev� une erreur
    unsigned int   Timeout;     // timeout en r�ception et emission
    TError  LastError;        // derni�re erreur lev�e par la classe  (m�thode ThrowError )


};

#endif // CSERIE_H



