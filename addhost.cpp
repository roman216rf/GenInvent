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
    QMapIterator <Group, QVector<Host>> group(invfile.getStructFile());
    while(group.hasNext()){
        group.next();
        groups.append(group.key().getName());
    }
    inventFile = &invfile;
    drawListGroup();
}

void AddHost::click_save(){
    if (!ui->hostname->text().isEmpty()){
        if (!ui->ip1->text().isEmpty() && !ui->ip2->text().isEmpty() && !ui->ip3->text().isEmpty() && !ui->ip4->text().isEmpty()){
            if (!ui->login->text().isEmpty()){
                if (!ui->pass->text().isEmpty()){
                    Host host(ui->hostname->text(), QString(ui->ip1->text() + "." + ui->ip2->text() + "." + ui->ip3->text() + "." + ui->ip4->text()));
                    host.setLogin(ui->login->text());
                    host.setPass(ui->pass->text());

                    QVector<QString>selectedGroups;
                    for (QListWidgetItem* item : ui->listWidget->selectedItems()){
                        selectedGroups.append(item->text());
                    }

                    inventFile->addOneHost(host, selectedGroups);
                    this->close();
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
