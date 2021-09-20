#ifndef GROUP_H
#define GROUP_H

#include "inventfile.h"
#include "host.h"

//Класс предоставляющий функции для работы с группами хостов
class Group : public InventFile{

public:
    Group(const QString &new_name);

    void setHostToGroup(const Host &host); //Функция, для добавления хоста в группу

    QVector<Host> getHostFromGroup()const; //Функция, для возвращения списка хостов в группе
private:
    QString name;
    QMap<QString, QString> vars;
    QVector<Host> hostList; //Переменная, хранящая список хостов в этой группе
};

#endif // GROUP_H
