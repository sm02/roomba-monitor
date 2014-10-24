#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconfiguration.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOuvrir_triggered()
{
    QStringList listeNomFichier;
    QString nomFichier;

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);       // Commenter
    dialog.setNameFilter(tr("Données Roomba (*.rmbdata)")); // Commenter
    dialog.setViewMode(QFileDialog::Detail);

    if ( dialog.exec() == QDialog::Rejected)
        return;  // Aucun fichier n'a été choisi, donc on arrête là.

    listeNomFichier=dialog.selectedFiles();
    nomFichier=listeNomFichier[0];

//    qDebug() << "Nom du fichier :" << nomFichier;

    rmb.charger(nomFichier);
    this->adapterMaxSurSelecteurs(rmb.nbMesures());
}

void MainWindow::on_actionEnregistrer_triggered()
{
    QStringList listeNomFichier;
    QString nomFichier;

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);       // Commenter
    dialog.setNameFilter(tr("Données Roomba (*.drmb)")); // Commenter
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix("drmb");

    if ( dialog.exec() == QDialog::Rejected)
        return;  // Aucun fichier n'a été choisi, donc on arrête là.

    listeNomFichier=dialog.selectedFiles();
    nomFichier=listeNomFichier[0];

    //qDebug() << "Nom du fichier :" << nomFichier;

    //Sauvegarde des mesures dans le fichier
    rmb.sauvegarder(nomFichier);
}


void MainWindow::on_actionConfigurer_triggered()
{
    DialogConfiguration *dialogConf;
    dialogConf=new DialogConfiguration;

    dialogConf->exec();

    qDebug() << "Port: " << dialogConf->port();
    qDebug() << "Débit: " << dialogConf->debit();
    sauvegarderConfiguration(dialogConf->port(),dialogConf->debit());
    delete(dialogConf);
}

void MainWindow::on_actionAcquerir_les_mesures_triggered()
{
    if (rmb.connecter()) {
        ui->actionAcquerir_les_mesures->setEnabled(false);
        ui->actionArreter_l_acquisition->setEnabled(true);
    }
}

void MainWindow::adapterMaxSurSelecteurs(int nbEchant)
{
    ui->labelNoMaxEchantillon->setText(QString("%1").arg(nbEchant));
    ui->spinBoxEchantillon->setMaximum(nbEchant);
    ui->horizontalSliderEchantillon->setMaximum(nbEchant);
}

void MainWindow::sauvegarderConfiguration(QString port, qint32 debit)
{
    FILE *f;
    f=fopen("configRmb.txt","w");
    fprintf(f,"debit=%d\n",debit);
    fprintf(f,"port=%s\n",port.toStdString().c_str());
    fclose(f);
}

