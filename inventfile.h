#ifndef INVENTFILE_H
#define INVENTFILE_H
#include <group.h>
#include <host.h>
//#include <QVector>

class InventFile{
public:
    InventFile();
    void addOneGroup(Group& group);
    void addListGroups(QVector<Group>& list_groups);

    void addOneHost(Host& host, Group& group);
    void addOneHost(Host& host, QVector<QString>& names_groups);

private:
    QMap<Group, QVector<Host>> structFile;
};

#endif // INVENTFILE_H
