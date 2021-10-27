#ifndef INVENTFILE_H
#define INVENTFILE_H
#include <group.h>
#include <host.h>
//#include <QVector>

class InventFile{
public:
    InventFile();
    InventFile(QMap<Group, QVector<Host>> structFile);
    void addOneGroup(Group& group);
    void addListGroups(QVector<Group>& list_groups);

    void addOneHost(Host& host, QString& group);
    void addOneHost(Host& host, QVector<QString>& names_groups);
    void addMoreHosts(QVector<Host>&hosts, QString& group);

    void setVars(QString& groupname, QString& var_name, QString& var_value);
    void setVars(QString& groupname, QMap<QString, QString>& var_list);

    void append(InventFile& invfile);

    QMap <Group, QVector<Host>>& getStructFile();

private:
    QMap<Group, QVector<Host>> structFile;
};

#endif // INVENTFILE_H
