#include "host.h"



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

void Host::addGroupToHost(const Group &group){
    groupList.append(group);
}

QVector<Group> Host::getGroupList()const{
    return groupList;
}
