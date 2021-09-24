#include "geninvent.h"
#include <importZabbixFile.cpp>

InventFile inventfile;

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
    inventfile = importZabbixFile(fd.getOpenFileName(0,"Выберите файл, экспортированный из Zabbix", "", "*.yaml"));

    QMapIterator <Group, QVector<Host>> group(inventfile.getStructFile());
    while (group.hasNext()){
        group.next();
        QTreeWidgetItem *group_item = new QTreeWidgetItem(ui->treeWidget);
        group_item->setText(0, group.key().getName());
        ui->treeWidget->addTopLevelItem(group_item);
        for (const Host& host : group.value()){
            QTreeWidgetItem *host_item = new QTreeWidgetItem(group_item);
            host_item->setText(0, host.getName());
            group_item->addChild(host_item);
        }
    }
}

void GenInvent::on_treeWidget_itemActivated(QTreeWidgetItem *item){
    ui->listWidget->clear();
    if (item->parent() != NULL){
        int i = 0;
        for (const Host& host : inventfile.getStructFile().value(item->parent()->text(0))){
            if (host.getName() == item->text(0)){

                ui->listWidget->addItem("Имя хоста");
                QListWidgetItem *hostname = new QListWidgetItem(ui->listWidget);
                hostname->setText(host.getName());
                ui->listWidget->addItem(hostname);

                ui->listWidget->addItem("IP адрес хоста");
                QListWidgetItem *ip = new QListWidgetItem(ui->listWidget);
                ip->setText(host.getIp());
                ui->listWidget->addItem(ip);

                ui->listWidget->addItem("Логин хоста");
                QListWidgetItem *login = new QListWidgetItem(ui->listWidget);
                login->setText(host.getLogin());
                ui->listWidget->addItem(login);

                ui->listWidget->addItem("Пароль хоста");
                QListWidgetItem *pass = new QListWidgetItem(ui->listWidget);
                pass->setText(host.getPass());
                ui->listWidget->addItem(pass);

                QMapIterator<QString, QString> vars(inventfile.getStructFile().value(item->parent()->text(0)).value(i).getVars());
                while(vars.hasNext()){
                    vars.next();

                    ui->listWidget->addItem(vars.key());
                    QListWidgetItem *var = new QListWidgetItem(ui->listWidget);
                    var->setText(vars.value());
                    ui->listWidget->addItem(var);
                }
            }
            i++;
        }
    }
}

void GenInvent::on_listWidget_itemClicked(QListWidgetItem *item){
}
