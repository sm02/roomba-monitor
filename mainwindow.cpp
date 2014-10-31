#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconfiguration.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rmb(new Roomba)
{
    ctrlIndic =new ControleurIndicateurs(NULL,rmb);
    ui->setupUi(this);

    //connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(fermerApplication()));
    ui->selectionMesure->init(rmb);
    connect(this, SIGNAL(fichierCharge()), ui->selectionMesure, SLOT(mesureAjoutee()));
    connect(rmb, SIGNAL(nouvelleMesure()), ui->selectionMesure, SLOT(mesureAjoutee()));
    connect(ui->selectionMesure,SIGNAL(mesureSelectionnee(qint32)),ctrlIndic,SLOT(selectionnerMesure(qint32)));

    ctrlIndic->ouvrirIndicateurs();
}

MainWindow::~MainWindow()
{
    delete ctrlIndic;
    delete rmb;
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

    rmb->charger(nomFichier);

    emit fichierCharge();  // envoyé vers controleurIndicateurs pour mettre à jour les nouvelles données
}

void MainWindow::on_actionEnregistrer_triggered()
{
    QStringList listeNomFichier;
    QString nomFichier;

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);       // Commenter
    dialog.setNameFilter(tr("Données Roomba (*.rmbdata)")); // Commenter
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix("rmbdata");

    if ( dialog.exec() == QDialog::Rejected)
        return;  // Aucun fichier n'a été choisi, donc on arrête là.

    listeNomFichier=dialog.selectedFiles();
    nomFichier=listeNomFichier[0];

    //qDebug() << "Nom du fichier :" << nomFichier;

    //Sauvegarde des mesures dans le fichier
    rmb->sauvegarder(nomFichier);
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    ctrlIndic->close();
    event->accept();
}

void MainWindow::sauvegarderConfiguration(QString port, qint32 debit)
{
    FILE *f;
    f=fopen("configRmb.txt","w");
    fprintf(f,"debit=%d\n",debit);
    fprintf(f,"port=%s\n",port.toStdString().c_str());
    fclose(f);
}

void MainWindow::on_actionConnecter_triggered()
{
    if (rmb->connecter()) {
        ui->actionConnecter->setEnabled(false);
        ui->actionDeconnecter->setEnabled(true);
        ui->actionAcquerir_les_mesures->setEnabled(true);
    }
}


void MainWindow::on_actionDeconnecter_triggered()
{
    rmb->deconnecter();
    ui->actionConnecter->setEnabled(true);
    ui->actionDeconnecter->setEnabled(false);

    //TODO
    //à compléter pour forcer Arrêt des mesures

    ui->actionAcquerir_les_mesures->setEnabled(false);
    ui->actionArreter_l_acquisition->setEnabled(false);
}


void MainWindow::on_actionAcquerir_les_mesures_triggered()
{
    if (rmb->estConnecte()) {
        ui->actionAcquerir_les_mesures->setEnabled(false);
        ui->actionArreter_l_acquisition->setEnabled(true);
        rmb->debuterEnregistrement();
    }
}

void MainWindow::on_actionArreter_l_acquisition_triggered()
{
    ui->actionAcquerir_les_mesures->setEnabled(true);
    ui->actionArreter_l_acquisition->setEnabled(false);
    rmb->finirEnregistrement();

}
