#ifndef EXPORTFILE_H
#define EXPORTFILE_H
#include <inventfile.h>
#include <QMessageBox>
#include <QFile>

class ExportFile
{
public:
    ExportFile(const InventFile& invent);
    void saveFile(const QString& path);

private:
    InventFile inventfile;
};

#endif // EXPORTFILE_H
