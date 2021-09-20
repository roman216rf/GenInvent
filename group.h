#ifndef GROUP_H
#define GROUP_H

#include "inventObject.h"
#include "host.h"

//Класс предоставляющий функции для работы с группами хостов
class Host;
class Group : InventObject{

public:
    Group(const QString &new_name);

    void setHostToGroup(Host &host); //Функция, для добавления хоста в группу

    QVector<Host> getHostFromGroup()const; //Функция, для возвращения списка хостов в группе
private:
    QString name;
    QMap<QString, QString> vars;
    QVector<Host> hostList; //Переменная, хранящая список хостов в этой группе
};

#endif // GROUP_H
