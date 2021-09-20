#include "inventfile.h"

void InventFile::setName(const QString& new_name){
    name = new_name;
}

void InventFile::addVar(const QString& name_var, const QString& value_var){
    vars[name_var] = value_var;
}

QString InventFile::getName()const{
    return name;
}

QMap<QString, QString> InventFile::getAllVars()const{
    return vars;
}

QString InventFile::getValueOfVar(const QString& name_var)const{
    return vars.value(name_var);
}
