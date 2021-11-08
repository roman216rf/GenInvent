#include "geninvent.h"

InventFile inventfile, old_inventfile;
QString old_value;

GenInvent::GenInvent(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GenInvent){
    ui->setupUi(this);
    connect(ui->action_Zabbix, SIGNAL(triggered()), this, SLOT(importFromZabbix()));
    connect(ui->action_Ansible, SIGNAL(triggered()), this, SLOT(importFromAnsible()));
    connect(ui->action_add_group, SIGNAL(triggered()), this, SLOT(addGroup()));
    connect(ui->action_add_host, SIGNAL(triggered()), this, SLOT(addHost()));
    connect(ui->action_del_groups, SIGNAL(triggered()), this, SLOT(delGroups()));
    connect(ui->action_del_hosts, SIGNAL(triggered()), this, SLOT(delHosts()));
}

GenInvent::~GenInvent(){
    delete ui;
}

void GenInvent::importFromZabbix(){
    old_inventfile = inventfile;
    QFileDialog fd;
    inventfile = ImportFile::importZabbixFile(fd.getOpenFileName(0,"Выберите файл, экспортированный из Zabbix", "", "*.yaml"));
    fd.close();
    inventfile.append(old_inventfile);
    drawStruct(inventfile);
}

void GenInvent::importFromAnsible(){
    old_inventfile = inventfile;
    QFileDialog fd;
    inventfile = ImportFile::importAnsibleFile(fd.getOpenFileName(0,"Выберите файл, экспортированный из Ansible", "", "*"));
    fd.close();
    inventfile.append(old_inventfile);

    drawStruct(inventfile);
}

void GenInvent::addGroup(){
    AddGroup w(this);
    w.setPropList(inventfile);
    w.exec();
    drawStruct(inventfile);
}

void GenInvent::addHost(){
    AddHost w(this);
    w.setPropList(inventfile);
    w.exec();
    drawStruct(inventfile);
}

void GenInvent::delGroups(){

}

void GenInvent::delHosts(){

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

                /*QMapIterator<QString, QString> vars(inventfile.getStructFile().value(item->parent()->text(0)).value(i).getVars());
                while(vars.hasNext()){
                    vars.next();

                    ui->listWidget->addItem(vars.key());
                    QListWidgetItem *var = new QListWidgetItem(ui->listWidget);
                    var->setText(vars.value());
                    ui->listWidget->addItem(var);
                    var->setFlags(var->flags() | Qt::ItemIsEditable);
                }*/
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
                    //inventfile.getStructFile()[group.key()][i].setVars(var);
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

void GenInvent::on_treeWidget_customContextMenuRequested(const QPoint &pos){
    QMenu menu(this);
    menu.addAction(ui->action_add_group);
    menu.addAction(ui->action_add_host);
    menu.addAction(ui->action_del_groups);
    menu.addAction(ui->action_del_hosts);
    ui->action_add_group->setData(QVariant(pos));
    ui->action_add_host->setData(QVariant(pos));
    ui->action_del_groups->setData(QVariant(pos));
    ui->action_del_hosts->setData(QVariant(pos));
    menu.exec(ui->treeWidget->mapToGlobal(pos));
}

void GenInvent::drawStruct(InventFile &inventFile) const{
    ui->treeWidget->clear();
    QMapIterator <Group, QVector<Host>> group(inventFile.getStructFile());
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
