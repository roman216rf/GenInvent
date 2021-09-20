#ifndef HOST_H
#define HOST_H

#include "inventfile.h"
#include "group.h"

class Host : public InventFile{

public:
    Host(const QString &hostname, const QString &ip_host, const QString &login_host, const QString &pass_host);

    //Функции, изменяющие и возвращающие ip адрес хоста, логин и пароль
    QString getIp() const;
    void setIp(const QString &value);

    QString getLogin() const;
    void setLogin(const QString &value);

    QString getPass() const;
    void setPass(const QString &value);

    void addGroupToHost(const Group &group); //Функция, добавляющая объект группы в список групп хоста
    QVector<Group> getGroupList()const; //Функция, возвращающая список групп хоста

private:
    QString name;
    QString ip;
    QString login;
    QString pass;
    QMap<QString, QString> vars;
    QVector<Group> groupList;
};

#endif // HOST_H
