#include "configliaison.h"

ConfigLiaison::ConfigLiaison()
{
}

QString ConfigLiaison::port() const
{
    return _port;
}

unsigned int ConfigLiaison::debit() const
{
    return _debit;
}

void ConfigLiaison::setDebit(unsigned int debit)
{
    _debit = debit;
}
void ConfigLiaison::setPort(const QString &port)
{
    _port = port;
}
