#include "geninvent.h"
#include "ui_geninvent.h"

GenInvent::GenInvent(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GenInvent)
{
    ui->setupUi(this);

}

GenInvent::~GenInvent()
{
    delete ui;
}

