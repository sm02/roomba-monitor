#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"

#include <QDebug>

DialogConfiguration::DialogConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);

    //Remplir ComboPort avec COM1 à COM15
    QStringList l;
    QString s;
    for (int i=1;i<=15;i++) {
        s=QString("COM%1").arg(i);
        l.append(s);
    }
    ui->comboPort->addItems(l);

    connect(this,SIGNAL(accepted()),this,SLOT(DialogConfiguration_accepted()));
}

qint32 DialogConfiguration::debit() const
    {
         return _debit;
}

QString DialogConfiguration::port() const
    {
         return _port;
}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::obtenirValeurs()
{
    if ( ui->radio4800->isChecked() ) {
        _debit=4800;
    }
    if ( ui->radio9600->isChecked() ) {
        _debit=9600;
    }
    if ( ui->radio19200->isChecked() ) {
        _debit=19200;
    }
    if ( ui->radio28800->isChecked() ) {
        _debit=28800;
    }
    if ( ui->radio38400->isChecked() ) {
        _debit=38400;
    }
    if ( ui->radio57600->isChecked() ) {
        _debit=57600;
    }
    if ( ui->radio115200->isChecked() ) {
        _debit=115200;
    }

    _port= ui->comboPort->currentText();

}




void DialogConfiguration::DialogConfiguration_accepted()
{
    obtenirValeurs();
}
