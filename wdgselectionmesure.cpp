#include "wdgselectionmesure.h"
#include "ui_wdgselectionmesure.h"

WdgSelectionMesure::WdgSelectionMesure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgSelectionMesure)
{
    ui->setupUi(this);
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
    ui->labelNoMaxEchantillon->setText(QString("%1").arg(nbMesures));
    ui->spinBoxEchantillon->setMaximum(nbMesures);
    ui->horizontalSliderEchantillon->setMaximum(nbMesures);
}

void WdgSelectionMesure::mesureAjoutee()
{
    setNbMesures(_rmb->nbMesures());
}
