#include "inventObject.h"

void InventObject::setName(const QString& new_name){
    name = new_name;
}

void InventObject::addVar(const QString& name_var, const QString& value_var){
    vars[name_var] = value_var;
}

QString InventObject::getName()const{
    return name;
}

QMap<QString, QString> InventObject::getAllVars()const{
    return vars;
}

QString InventObject::getValueOfVar(const QString& name_var)const{
    return vars.value(name_var);
}
