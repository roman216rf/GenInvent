#include "group.h"

Group::Group(const QString &new_name){
    name = new_name;
}

QString Group::getName() const{
    return name;
}

void Group::setName(const QString &value){
    name = value;
}

QMap<QString, QString> Group::getVars() const{
    return vars;
}

void Group::setVars(const QMap<QString, QString> &value){
    vars = value;
}

void Group::setOneVar(const QString &var_name, const QString &value){
    vars[var_name] = value;
}

bool Group::operator==(const Group &group1)const{
    return group1.getName() == this->getName();
}

bool Group::operator<(const Group &group) const{
    return this->getName() < group.getName();
}
