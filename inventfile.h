#ifndef INVENTFILE_H
#define INVENTFILE_H
#include <QString>
#include <QMap>

class InventFile{
public:
    void setName(const QString* new_name);
    void addVar(const QString* name_var, const QString* value_var);
    QString getName()const;
    QMap<QString, QString> getAllVars()const;
    QString getValueOfVar(const QString* name_var)const;

private:
    QString name;
    QMap<QString, QString> vars;
};

#endif // INVENTFILE_H
