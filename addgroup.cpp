#include "addgroup.h"
#include "ui_addgroup.h"

int id_count = 0;

AddGroup::AddGroup(QWidget *parent):QDialog(parent), ui(new Ui::AddGroup){

    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(click_save()));
    QWidget* wgt = new QWidget;
    QLayout* l = new QHBoxLayout;
    QPushButton* add_item = new QPushButton("Добавить переменную");
    add_item->setIcon(QIcon(":/pushbutton_icon/resourses/icons/add_icon.ico"));
    connect(add_item, SIGNAL(clicked()), SLOT(addVar()));
    l->addWidget(add_item);

    wgt->setLayout(l);

    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);

    item->setSizeHint(wgt->sizeHint());
    ui->listWidget->setItemWidget(item, wgt);
}

AddGroup::~AddGroup(){
    delete ui;
}

void AddGroup::addVar(){
    QWidget* wgt = new QWidget;
    QLayout* l = new QHBoxLayout;
    QLineEdit* edit = new QLineEdit;
    QSizePolicy sp = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sp.setHorizontalStretch(2);
    edit->setSizePolicy(sp);
    QComboBox* cmbbox = new QComboBox;
    cmbbox->setEditable(true);

    for (QString varname : varList){
        if (!getUsingVars().contains(varname))
            cmbbox->addItem(varname);
    }

    sp.setHorizontalStretch(1);
    cmbbox->setSizePolicy(sp);
    QLabel* id = new QLabel(QString::number(id_count++));
    id->setHidden(true);
    l->addWidget(id);
    l->addWidget(cmbbox);
    l->addWidget(edit);
    QPushButton* del_item = new QPushButton("");
    del_item->setIcon(QIcon(":/pushbutton_icon/resourses/icons/del_icon.ico"));
    del_item->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    connect(del_item, SIGNAL(clicked()), SLOT(delVar()));
    l->addWidget(del_item);

    wgt->setLayout(l);

    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);

    item->setSizeHint(wgt->sizeHint());
    ui->listWidget->setItemWidget(item, wgt);
}

void AddGroup::delVar(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QLabel* id = btn->parent()->findChild<QLabel*>();
    QComboBox* cmb = btn->parent()->findChild<QComboBox*>();
    delUsingVarFromCmb(cmb->currentText());
    for (int i = 1; i<ui->listWidget->count(); i++){
        QLabel* getId = ui->listWidget->itemWidget(ui->listWidget->item(i))->findChild<QLabel*>();
        if (getId->text() == id->text()){
            ui->listWidget->takeItem(i);
        }
    }
}

QVector<QString> AddGroup::getUsingVars() const{
    QVector<QString>usingVars;

    for (int i = 1; i<ui->listWidget->count(); i++){
        QComboBox* cmb = ui->listWidget->itemWidget(ui->listWidget->item(i))->findChild<QComboBox*>();
        usingVars.append(cmb->currentText());
    }
    return usingVars;
}

void AddGroup::delUsingVarFromCmb(const QString& varname){
    for (int i = 1; i<ui->listWidget->count(); i++){
        QComboBox* getcmb = ui->listWidget->itemWidget(ui->listWidget->item(i))->findChild<QComboBox*>();
        for(int i = 0; i<getcmb->count(); i++){
            if (getcmb->itemText(i) == varname)
                getcmb->removeItem(i);
        }
    }
}

void AddGroup::setPropList(const QVector<QString> &newvarList, InventFile& invfile){
    varList = newvarList;
    inventFile = &invfile;

}

void AddGroup::click_save(){
    if (!ui->new_groupname->text().isEmpty()){
        Group group(ui->new_groupname->text());
        QMap<QString, QString> vars;
        bool ok_vars = true;
        for (int i = 1; i<ui->listWidget->count(); i++){
            QComboBox* varname = ui->listWidget->itemWidget(ui->listWidget->item(i))->findChild<QComboBox*>();
            QLineEdit* varvalue = ui->listWidget->itemWidget(ui->listWidget->item(i))->findChild<QLineEdit*>();

            if(!varname->currentText().isEmpty() && !varvalue->text().isEmpty()){
                if (!vars.contains(varname->currentText())){
                    vars.insert(varname->currentText(), varvalue->text());
                }
                else{
                    QMessageBox msg;
                    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msg.setText("Уже существует переменная " + varname->currentText() + " со значением " + vars.value(varname->currentText()) + ". Вы хотите заменить значение на " + varvalue->text() + "?");
                    int ret = msg.exec();
                    if (ret == QMessageBox::Yes)
                        vars.insert(varname->currentText(), varvalue->text());
                }
            }
            else{
                QMessageBox msg;
                msg.setText("Имя и/или значение переменной не могут быть пустыми!");
                msg.exec();
                ok_vars = false;
            }
        }
        if (ok_vars){
            group.setVars(vars);
            inventFile->addOneGroup(group);
            this->close();
        }
    }
    else{
        QMessageBox msg;
        msg.setText("Имя группы не может быть пустым!");
        msg.exec();
    }
}
