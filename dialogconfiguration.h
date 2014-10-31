/*! \file dialogconfiguration.harderr
* \brief     Fenêtre de configuration des paramètres de la liaison Roomba <-> PC
* \author    SM
* \version   0.1
* \date      nov. 2014
* \copyright GNU GPL v3
*/
#ifndef DIALOGCONFIGURATION_H
#define DIALOGCONFIGURATION_H

#include <QDialog>

namespace Ui {
class DialogConfiguration;
}

class DialogConfiguration : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConfiguration(QWidget *parent = 0);
    ~DialogConfiguration();

    QString port() const;
    qint32 debit() const;

private slots:
    void DialogConfiguration_accepted();

private:
    Ui::DialogConfiguration *ui;
    QString _port;
    qint32 _debit;

    void obtenirValeurs();
};

#endif // DIALOGCONFIGURATION_H
