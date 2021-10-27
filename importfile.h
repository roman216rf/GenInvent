#ifndef IMPORTFILE_H
#define IMPORTFILE_H
#include <inventfile.h>
#include <QFile>
#include <exportfile.h>


class ImportFile
{
public:
    static InventFile importZabbixFile(const QString &file_path);

    static InventFile importAnsibleFile(const QString &file_path);
};

#endif // IMPORTFILE_H
