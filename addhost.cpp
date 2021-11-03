#include "addhost.h"
#include "ui_addhost.h"

AddHost::AddHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddHost)
{
    ui->setupUi(this);
}

AddHost::~AddHost()
{
    delete ui;
}
