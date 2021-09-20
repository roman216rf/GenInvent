#include "group.h"

Group::Group(const QString &new_name){
    name = new_name;
}

void Group::setHostToGroup(const Host &host){
    hostList.append(host); //Добавление хоста в группу
    host.addGroupToHost(this); //Добавление имени группы в хост
}

QVector<Host> Group::getHostFromGroup()const{
    return hostList;
}
