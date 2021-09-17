#ifndef HOST_H
#define HOST_H

#include "inventfile.h"

class Host : public InventFile{

public:
    Host(const QString* hostname);

private:
    QString name;
    QMap<QString, QString> vars;
};

#endif // HOST_H
