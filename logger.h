#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <stdio.h>

class Log

{
public:
    Log();
    ~Log();
    static void log(const QString& message);
    static FILE* fichierLog;

}; //end class Logger

#endif // LOGGER_H
