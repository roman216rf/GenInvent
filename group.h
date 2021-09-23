#ifndef GROUP_H
#define GROUP_H
#include <QMap>
#include <host.h>
//Класс предоставляющий функции для работы с группами хостов
class Group{

public:
    Group(const QString &new_name);

    QString getName() const;
    void setName(const QString &value);

    QMap<QString, QString> getVars() const;
    void setVars(const QMap<QString, QString> &value);
    void setOneVar(const QString &var_name, const QString &value);
    bool operator==(const Group &group1)const;
    bool operator<(const Group& group)const;
private:
    QString name; //Переменая, хранящая имя объекта
    QMap<QString, QString> vars; //Переменная, хранящая список переменных объекта
};

#endif // GROUP_H
