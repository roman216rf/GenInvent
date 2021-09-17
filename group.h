#ifndef GROUP_H
#define GROUP_H

#include "inventfile.h"

class Group : public InventFile{

public:
    Group(const QString* new_name);

private:
    QString name;
    QMap<QString, QString> vars;
};

#endif // GROUP_H
