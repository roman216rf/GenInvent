#ifndef INVENTFILE_H
#define INVENTFILE_H
#include <QString>
#include <QMap>

//Родительский класс для таких объектов как группа, хост и т.д.
class InventFile{
public:
    void setName(const QString& new_name); //Функция, меняющая имя объекта
    QString getName()const; //Функция, возвращающая имя объекта

    void addVar(const QString& name_var, const QString& value_var); //Функция, добавляющая переменную объекту

    QMap<QString, QString> getAllVars()const; //Функция, возвращающая весь список переменных

    QString getValueOfVar(const QString& name_var)const; //Функция, возвращающая значение указанной переменной

private:
    QString name; //Переменая, хранящая имя объекта
    QMap<QString, QString> vars; //Переменная, хранящая список переменных объекта
};

#endif // INVENTFILE_H
