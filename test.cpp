#include "test.h"
#include <QMessageBox>

Test::Test()
{
}

bool Test::connecter() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Simuler l'état de la connexion");
    msgBox.setText("L'ouverture de la connexion a-t-elle réussi ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if (ret==QMessageBox::Yes) return true;
    else return false;
}
quint64 Test::nbEchant() const
{
    return _nbEchant;
}

void Test::setNbEchant(const quint64 &nbEchant)
{
    _nbEchant = nbEchant;
}

Test t;
