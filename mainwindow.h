#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "roomba.h"
#include "controleurindicateurs.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void closeEvent(QCloseEvent *event);
signals:
    void fichierCharge();

private slots:
    void on_actionOuvrir_triggered();

    void on_actionEnregistrer_triggered();

    void on_actionConfigurer_triggered();

    void on_actionAcquerir_les_mesures_triggered();

    void on_actionConnecter_triggered();

    void on_actionDeconnecter_triggered();

    void on_actionArreter_l_acquisition_triggered();

private:
    Ui::MainWindow *ui;

    void sauvegarderConfiguration(QString port,qint32 debit);

    Roomba *rmb;
    ControleurIndicateurs *ctrlIndic;
};

#endif // MAINWINDOW_H
