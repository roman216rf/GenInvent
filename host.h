#ifndef HOST_H
#define HOST_H
#include <QString>
#include <QMap>

class Host{

public:
    Host();
    Host(const QString &hostname, const QString &ip_host);

    //Функции, изменяющие и возвращающие ия хоста, ip адрес хоста, логин, переменные и пароль
    QString getIp() const;
    void setIp(const QString &value);

    QString getLogin() const;
    void setLogin(const QString &value);

    QString getPass() const;
    void setPass(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QMap<QString, QString> getVars() const;
    //void setVars(const QMap<QString, QString> &value);
    //void setOneVar(const QString &var_name, const QString &value);

    bool operator==(const Host &host)const;

private:
    QString name; //Переменая, хранящая имя объекта
    //QMap<QString, QString> vars; //Переменная, хранящая список переменных объекта
    QString ip;
    QString login;
    QString pass;
};

#endif // HOST_H
