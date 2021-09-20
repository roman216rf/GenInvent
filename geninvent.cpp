#include "geninvent.h"
#include "ui_geninvent.h"
#include <QFileDialog>
#include <importZabbixFile.cpp>

GenInvent::GenInvent(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GenInvent)
{
    ui->setupUi(this);
    connect(ui->action_Zabbix, SIGNAL(triggered()), this, SLOT(importFromZabbix()));
}

GenInvent::~GenInvent()
{
    delete ui;
}

void GenInvent::importFromZabbix(){
    QFileDialog fd;
    importZabbixFile(fd.getOpenFileName(0,"Выберите файл, экспортированный из Zabbix", "", "*.yaml"));
}
