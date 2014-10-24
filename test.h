#ifndef TEST_H
#define TEST_H

#include "roomba.h"
#include "configliaison.h"

class Test : public QObject

{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);

private:
    Roomba rmb;
    ConfigLiaison cfg;

public slots:
    void test1();
    void test2();
    void afficher();
};

#endif // TEST_H
