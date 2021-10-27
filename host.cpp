#include "host.h"



Host::Host(){
    name = "NO_NAME";
    ip = "0.0.0.0";
}

Host::Host(const QString &hostname, const QString &ip_host){
    name = hostname;
    ip = ip_host;
}

QString Host::getIp() const{
    return ip;
}

void Host::setIp(const QString &ip_host){
    ip = ip_host;
}

QString Host::getLogin() const{
    return login;
}

void Host::setLogin(const QString &login_host){
    login = login_host;
}

QString Host::getPass() const{
    return pass;
}

void Host::setPass(const QString &pass_host){
    pass = pass_host;
}

QString Host::getName() const{
    return name;
}

void Host::setName(const QString &value){
    name = value;
}

/*QMap<QString, QString> Host::getVars() const{
    return vars;
}

void Host::setVars(const QMap<QString, QString> &value){
    vars = value;
}

void Host::setOneVar(const QString &var_name, const QString &value){
    vars[var_name] = value;
}*/

bool Host::operator==(const Host &host) const{
    return ((this->getName() == host.getName()) || (this->getIp() == host.getIp()));
}


