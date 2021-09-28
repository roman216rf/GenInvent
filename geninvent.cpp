#include "geninvent.h"
#include <importZabbixFile.cpp>

InventFile inventfile;
QString old_value;

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
    fd.close();
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
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    old_value = item->text(0);
    ui->treeWidget->editItem(item);
}

void GenInvent::on_treeWidget_itemClicked(QTreeWidgetItem *item){
    old_value = item->text(0);
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
                ip->setFlags(ip->flags() | Qt::ItemIsEditable);

                ui->listWidget->addItem("Логин хоста");
                QListWidgetItem *login = new QListWidgetItem(ui->listWidget);
                login->setText(host.getLogin());
                ui->listWidget->addItem(login);
                login->setFlags(login->flags() | Qt::ItemIsEditable);

                ui->listWidget->addItem("Пароль хоста");
                QListWidgetItem *pass = new QListWidgetItem(ui->listWidget);
                pass->setText(host.getPass());
                ui->listWidget->addItem(pass);
                pass->setFlags(pass->flags() | Qt::ItemIsEditable);

                QMapIterator<QString, QString> vars(inventfile.getStructFile().value(item->parent()->text(0)).value(i).getVars());
                while(vars.hasNext()){
                    vars.next();

                    ui->listWidget->addItem(vars.key());
                    QListWidgetItem *var = new QListWidgetItem(ui->listWidget);
                    var->setText(vars.value());
                    ui->listWidget->addItem(var);
                    var->setFlags(var->flags() | Qt::ItemIsEditable);
                }
            }
            i++;
        }
    }
    else {
        QMapIterator<Group, QVector<Host>> group(inventfile.getStructFile());
        while(group.hasNext()){
            group.next();

            if (group.key().getName() == item->text(0)){
                ui->listWidget->addItem("Имя группы");
                QListWidgetItem *groupname = new QListWidgetItem(ui->listWidget);
                groupname->setText(group.key().getName());
                ui->listWidget->addItem(groupname);

                QMapIterator<QString, QString> vars(group.key().getVars());
                while(vars.hasNext()){
                    vars.next();

                    ui->listWidget->addItem(vars.key());
                    QListWidgetItem *var = new QListWidgetItem(ui->listWidget);
                    var->setText(vars.value());
                    ui->listWidget->addItem(var);
                    var->setFlags(var->flags() | Qt::ItemIsEditable);
                }
            }
        }
    }
}

void GenInvent::on_treeWidget_itemChanged(QTreeWidgetItem *item){
    QMapIterator <Group, QVector<Host>> group(inventfile.getStructFile());
    if (item->parent() != NULL){
        while (group.hasNext()){
            group.next();
            int i = 0;
            for (const Host& host : group.value()){
                if (host.getName() == old_value){
                    inventfile.getStructFile()[group.key()][i].setName(item->text(0));
                }
                i++;
            }
        }

        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
            for(int j = 0; j < ui->treeWidget->topLevelItem(i)->childCount(); j++){
                if (ui->treeWidget->topLevelItem(i)->child(j)->text(0) == old_value){
                    ui->treeWidget->topLevelItem(i)->child(j)->setText(0, item->text(0));
                }
            }
        }
    }
    else {
        while (group.hasNext()){
            group.next();

            if (group.key().getName() == old_value){
                QVector<Host>hosts = inventfile.getStructFile()[group.key()];
                inventfile.getStructFile().remove(group.key());
                inventfile.getStructFile().insert(item->text(0), hosts);
            }
        }
    }
}

void GenInvent::on_listWidget_itemDoubleClicked(QListWidgetItem *item){
    ui->listWidget->editItem(item);
}

void GenInvent::on_listWidget_itemSelectionChanged(){
    QMapIterator <Group, QVector<Host>> group(inventfile.getStructFile());
    if (ui->treeWidget->selectedItems().at(0)->parent() != NULL){
        while(group.hasNext()){
            group.next();

            for (int i = 0; i < inventfile.getStructFile()[group.key()].length(); i++){
                if (inventfile.getStructFile()[group.key()][i].getName() == ui->listWidget->item(1)->text()){
                    inventfile.getStructFile()[group.key()][i].setIp(ui->listWidget->item(3)->text());
                    inventfile.getStructFile()[group.key()][i].setLogin(ui->listWidget->item(5)->text());
                    inventfile.getStructFile()[group.key()][i].setPass(ui->listWidget->item(7)->text());

                    QMap<QString, QString>var;
                    for (int i = 9; i < ui->listWidget->count(); i=+2){
                        var.insert(ui->listWidget->item(i-1)->text(), ui->listWidget->item(i)->text());
                    }
                    inventfile.getStructFile()[group.key()][i].setVars(var);
                }
            }
        }
    }
    else{
        while(group.hasNext()){
            group.next();

            if (group.key().getName() == ui->listWidget->item(1)->text()){
                QMap<QString, QString>var;
                for (int i = 3; i <= ui->listWidget->count(); i=+2){
                    var.insert(ui->listWidget->item(i-1)->text(), ui->listWidget->item(i)->text());
                }

                Group gr(group.key().getName());
                gr.setVars(var);
                inventfile.getStructFile().insert(gr, group.value());
                inventfile.getStructFile().remove(group.key());
            }
        }
    }
}
