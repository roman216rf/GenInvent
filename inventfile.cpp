#include "inventfile.h"

InventFile::InventFile(){

}

void InventFile::addOneGroup(Group &group){
    if (!structFile.contains(group)){
        QVector<Host> tmp;
        structFile.insert(group, tmp);
    }
}

void InventFile::addListGroups(QVector<Group> &list_groups){
    for (Group& group : list_groups){
        if (!structFile.contains(group)){
            QVector<Host> tmp;
            structFile.insert(group, tmp);
        }
    }
}

void InventFile::addOneHost(Host &host, Group &group){
    if (!structFile.value(group).contains(host)){
        QVector<Host> tmp = structFile.value(group);
        tmp.append(host);
        structFile.insert(group, tmp);
    }
}

void InventFile::addOneHost(Host &host, QVector<QString> &names_groups){
    for (const QString& group_name : names_groups){
        QMapIterator <Group, QVector<Host>> i(structFile);
        while(i.hasNext()){
            i.next();
            if (i.key().getName()==group_name){
                QVector<Host> tmp = i.value();
                tmp.append(host);
                structFile.insert(i.key(), tmp);
            }
        }
    }
}
