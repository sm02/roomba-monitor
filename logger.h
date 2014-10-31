/*!
* \file      logger.h
* \brief     Class Log
* \author    SM
* \version   0.1
* \date      nov. 2014
* \copyright GNU GPL v3
*/
#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <stdio.h>

/*! \brief Journalisation des messages de l'application
*/
class Log

{
public:
    Log();
    ~Log();
    static void log(const QString& message);
    static FILE* fichierLog;

}; //end class Logger

#endif // LOGGER_H
