#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "roomba.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOuvrir_triggered();

    void on_actionEnregistrer_triggered();

    void on_actionConfigurer_triggered();

    void on_actionAcquerir_les_mesures_triggered();

private:
    Ui::MainWindow *ui;

    void adapterMaxSurSelecteurs(int nbEchant);
    void sauvegarderConfiguration(QString port,qint32 debit);

    Roomba rmb;
};


#endif // MAINWINDOW_H
