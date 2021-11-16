#include "addhost.h"
#include "ui_addhost.h"

AddHost::AddHost(QWidget *parent) :QDialog(parent), ui(new Ui::AddHost){
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(click_save()));
    connect(ui->ip1, SIGNAL(textChanged(const QString&)), SLOT(on_ip_textChanged(const QString&)));
    connect(ui->ip2, SIGNAL(textChanged(const QString&)), SLOT(on_ip_textChanged(const QString&)));
    connect(ui->ip3, SIGNAL(textChanged(const QString&)), SLOT(on_ip_textChanged(const QString&)));
    connect(ui->ip4, SIGNAL(textChanged(const QString&)), SLOT(on_ip_textChanged(const QString&)));
}

AddHost::~AddHost(){
    delete ui;
}

void AddHost::setPropList(InventFile &invfile){
    groups = getGroupsNames(invfile.getStructFile());
    inventFile = &invfile;
    drawListGroup();
}

void AddHost::setPropList(InventFile &invfile, const QString &hostname, const QString& groupname){
    groups = getGroupsNames(invfile.getStructFile());
    inventFile = &invfile;
    drawListGroup();
    editHost = inventFile->getStructFile().find(Group(groupname)).value().at(inventFile->getStructFile().find(Group(groupname)).value().indexOf(Host(hostname, "")));
    ui->hostname->setText(editHost.getName());
    ui->ip1->setText(editHost.getIp().section('.', 0,0));
    ui->ip2->setText(editHost.getIp().section('.', 1,1));
    ui->ip3->setText(editHost.getIp().section('.', 2,2));
    ui->ip4->setText(editHost.getIp().section('.', 3,3));
    ui->login->setText(editHost.getLogin());
    ui->pass->setText(editHost.getPass());
    QMapIterator <Group, QVector<Host>> group(inventFile->getStructFile());
    while (group.hasNext()) {
        group.next();
        if (group.value().contains(editHost)){
            ui->listWidget->findItems(group.key().getName(), Qt::MatchExactly).at(0)->setSelected(true);
        }
    }
}

void AddHost::click_save(){
    if (!ui->hostname->text().isEmpty()){
        if (!ui->ip1->text().isEmpty() && !ui->ip2->text().isEmpty() && !ui->ip3->text().isEmpty() && !ui->ip4->text().isEmpty()){
            if (!ui->login->text().isEmpty()){
                if (!ui->pass->text().isEmpty()){
                    Host host(ui->hostname->text(), QString(ui->ip1->text() + "." + ui->ip2->text() + "." + ui->ip3->text() + "." + ui->ip4->text()));
                    host.setLogin(ui->login->text());
                    host.setPass(ui->pass->text());

                    int count = 0;
                    QMapIterator <Group, QVector<Host>> group(inventFile->getStructFile());
                    while (group.hasNext()) {
                        group.next();
                        if (group.value().contains(host))
                            count++;
                    }
                    if (count == 0 || editHost.getName() == host.getName()){
                        QVector<QString>selectedGroups;
                        if (ui->listWidget->selectedItems().count() > 0){
                            for (QListWidgetItem* item : ui->listWidget->selectedItems()){
                                selectedGroups.append(item->text());
                            }

                            if (editHost.getName() == ""){
                                inventFile->addOneHost(host, selectedGroups);
                                this->close();
                            }
                            else{
                                QMessageBox msg;
                                msg.setText("Вы уверены, что хотите внести изменения в хост " + editHost.getName() + "?");
                                msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
                                int res = msg.exec();
                                if (res == QMessageBox::Yes){
                                    inventFile->delHost(editHost.getName());
                                    inventFile->addOneHost(host, selectedGroups);
                                    this->close();
                                }
                                else{
                                    this->close();
                                }
                            }
                        }
                        else {
                            QMessageBox msg;
                            msg.setText("Не выбрано ни одной группы.");
                            msg.exec();
                        }
                    }
                    else{
                        QMessageBox msg;
                        msg.setText("Хост с таким именем и/или IP адресом уже существует.");
                        msg.exec();
                    }
                }
                else{
                    QMessageBox msg;
                    msg.setText("Пароль пользователя хоста не может быть пустым.");
                    msg.exec();
                }
            }
            else{
                QMessageBox msg;
                msg.setText("Имя пользователя хоста не может быть пустым. Учетная запись должна быть локальной и иметь права администратора.");
                msg.exec();
            }
        }
        else{
            QMessageBox msg;
            msg.setText("Введен не корректный ip адрес хоста. Адрес должен соответствовать следующему шаблону: Х.Х.Х.Х, где Х - это значение, в диапазоне от 0 до 255.");
            msg.exec();
        }
    }
    else{
        QMessageBox msg;
        msg.setText("Имя хоста не может быть пустым.");
        msg.exec();
    }
}

void AddHost::drawListGroup(){
    for(QString group: groups){
       ui->listWidget->addItem(group);
    }
}

QVector<QString> AddHost::getGroupsNames(const QMap<Group, QVector<Host> > &structFile){
    QVector<QString> groupList;
    QMapIterator <Group, QVector<Host>> group(structFile);
    while(group.hasNext()){
        group.next();
        groupList.append(group.key().getName());
    }
    return groupList;
}

void AddHost::on_ip_textChanged(const QString &arg1){
    if(int(arg1.toInt()) > 255 ||int(arg1.toInt()) < 0){
        QLineEdit* ip = qobject_cast<QLineEdit*>(sender());
        ip->setText("255");

        QString text = "Недопустимое значение " + arg1 + ". Значение должно быть в диапазоне от 0 до 255.";
        QMessageBox msg;
        msg.setText(text);
        msg.exec();
    }
}

void AddHost::on_pushButton_pressed(){
    ui->pass->setEchoMode(QLineEdit::Normal);
}

void AddHost::on_pushButton_released(){
    ui->pass->setEchoMode(QLineEdit::Password);
}
