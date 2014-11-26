#include "wdgselectionmesure.h"
#include "ui_wdgselectionmesure.h"

WdgSelectionMesure::WdgSelectionMesure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgSelectionMesure)
{
    ui->setupUi(this);
    connect(ui->spinBoxEchantillon,SIGNAL(valueChanged(int)),this,SLOT(_mesureSelectionnee(int)));
    connect(ui->horizontalSliderEchantillon,SIGNAL(valueChanged(int)),this,SLOT(_mesureSelectionnee(int)));
}

WdgSelectionMesure::~WdgSelectionMesure()
{
    delete ui;
}

void WdgSelectionMesure::init(Roomba *r)
{
    _rmb = r;
}

void WdgSelectionMesure::setNbMesures(int nbMesures)
{
    ui->labelNoMaxEchantillon->setText(QString("%1").arg(nbMesures-1));
    ui->spinBoxEchantillon->setMaximum(nbMesures-1);
    ui->horizontalSliderEchantillon->setMaximum(nbMesures-1);
}

void WdgSelectionMesure::mesureAjoutee()
{
    qint32 n = _rmb->nbMesures();
    setNbMesures(n);

    ui->spinBoxEchantillon->setValue(n-1);
    ui->horizontalSliderEchantillon->setValue(n-1);

    emit mesureSelectionnee(n-1);
}

void WdgSelectionMesure::_mesureSelectionnee(int numMesure)
{
    emit mesureSelectionnee(numMesure);
}
