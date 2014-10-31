#include "logger.h"

#include "stdio.h"
#include <QString>
#include <QDir>

FILE *Log::fichierLog=NULL;

Log::Log()
{
    QString n;
    n=QDir::homePath() + "/moniteurRoomba.log";

    fichierLog = fopen(n.toStdString().c_str(),"a");
}


Log::~Log()
{
    fclose(fichierLog);
}


void Log::log(const QString &message)
{
    fprintf(fichierLog,message.toStdString().c_str());
    fflush(fichierLog);
}



