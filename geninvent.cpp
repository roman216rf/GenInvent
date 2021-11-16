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
    connect(ui->action_del, SIGNAL(triggered()), this, SLOT(del()));
    connect(ui->action_edit, SIGNAL(triggered()), this, SLOT(edit()));
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

void GenInvent::del(){
    if (ui->treeWidget->selectedItems().at(0)->parent() == NULL){
        QMessageBox msg;
        msg.setWindowTitle("Удаление группы");
        msg.setText("Вы действительно хотите удалить группу " + ui->treeWidget->selectedItems().at(0)->text(0) + " со всеми её хостами?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setButtonText(QMessageBox::Yes, "Удалить");

        int res = msg.exec();
        if (res == QMessageBox::Yes){
            inventfile.delGroup(ui->treeWidget->selectedItems().at(0)->text(0));
            drawStruct(inventfile);
        }
    }
    else{
        QMessageBox msg;
        msg.setWindowTitle("Удаление хоста");
        msg.setText("Вы действительно хотите удалить хост " + ui->treeWidget->selectedItems().at(0)->text(0) + "?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setButtonText(QMessageBox::Yes, "Удалить");

        int res = msg.exec();
        if (res == QMessageBox::Yes){
            inventfile.delHost(ui->treeWidget->selectedItems().at(0)->text(0));
            drawStruct(inventfile);
        }
    }
}

void GenInvent::edit(){
    AddGroup w(this);
    w.setPropList(inventfile, ui->treeWidget->selectedItems().at(0)->text(0));
    w.exec();
    drawStruct(inventfile);
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

                ui->listWidget->addItem("Логин хоста");
                QListWidgetItem *login = new QListWidgetItem(ui->listWidget);
                login->setText(host.getLogin());
                ui->listWidget->addItem(login);

                ui->listWidget->addItem("Пароль хоста");
                QListWidgetItem *pass = new QListWidgetItem(ui->listWidget);
                pass->setText(host.getPass());
                ui->listWidget->addItem(pass);
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

void GenInvent::on_treeWidget_customContextMenuRequested(const QPoint &pos){
    QMenu menu(this);
    menu.addAction(ui->action_add_group);
    ui->action_add_group->setData(QVariant(pos));

    menu.addAction(ui->action_add_host);
    ui->action_add_host->setData(QVariant(pos));

    if (ui->treeWidget->selectedItems().count() > 0){
        menu.addAction(ui->action_del);
        ui->action_del->setData(QVariant(pos));

        menu.addAction(ui->action_edit);
        ui->action_edit->setData(QVariant(pos));
    }

    menu.exec(ui->treeWidget->mapToGlobal(pos));
}

void GenInvent::drawStruct(const InventFile &inventFile) const{
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
