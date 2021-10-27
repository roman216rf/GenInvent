#include "inventfile.h"

InventFile::InventFile(){

}

InventFile::InventFile(QMap<Group, QVector<Host> > new_structFile){
    structFile = new_structFile;
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

void InventFile::addOneHost(Host &host, QString &group){
    if (structFile.contains(group)){
        if (!structFile.value(group).contains(host)){
            structFile[group].append(host);
        }
    }
}

void InventFile::addOneHost(Host &host, QVector<QString> &names_groups){
    for (const QString& group_name : names_groups){
        if (structFile.contains(group_name)){
            QMapIterator <Group, QVector<Host>> i(structFile);
            while(i.hasNext()){
                i.next();
                if (i.key()==group_name){
                    if (!structFile.value(group_name).contains(host))
                        structFile[group_name].append(host);
                }
            }
        }
    }
}

void InventFile::addMoreHosts(QVector<Host> &hosts, QString &group){
    for(Host& host : hosts){
        this->addOneHost(host, group);
    }
}

void InventFile::setVars(QString &groupname, QString &var_name, QString &var_value){
    QMapIterator<Group, QVector<Host>> i(structFile);
    while(i.hasNext()){
        i.next();
        if (i.key().getName() == groupname){
            Group new_group(groupname);
            new_group.setOneVar(var_name, var_value);
            QVector<Host>hosts = structFile[i.key()];
            structFile.erase(structFile.find(i.key()));
            structFile[new_group] = hosts;
        }
    }
}

void InventFile::setVars(QString &groupname, QMap<QString, QString> &var_list){
    QMapIterator<Group, QVector<Host>> i(structFile);
    while(i.hasNext()){
        i.next();
        if (i.key().getName() == groupname){
            Group new_group(groupname);
            new_group.setVars(var_list);
            QVector<Host>hosts = structFile[i.key()];
            structFile.erase(structFile.find(i.key()));
            structFile[new_group] = hosts;
        }
    }
}

void InventFile::append(InventFile &invfile){
    QMapIterator<Group, QVector<Host>> i(invfile.getStructFile());
    while(i.hasNext()){
        i.next();
        if (structFile.contains(i.key())){
            QString groupname = i.key().getName();
            QVector<Host> hosts(i.value());
            QString group = i.key().getName();
            this->addMoreHosts(hosts, group);
            QMap<QString, QString>vars = i.key().getVars();
            this->setVars(groupname, vars);
        }
        else{
            structFile[i.key()] = i.value();
        }
    }
}

QMap<Group, QVector<Host> >& InventFile::getStructFile(){
    return structFile;
}
