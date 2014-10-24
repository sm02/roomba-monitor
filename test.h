#ifndef TEST_H
#define TEST_H

#include <QtGlobal>

class Test
{
public:
    Test();
    bool connecter();

    quint64 nbEchant() const;
    void setNbEchant(const quint64 &nbEchant);

private:
    quint64 _nbEchant;
};

extern Test t;

#endif // TEST_H
