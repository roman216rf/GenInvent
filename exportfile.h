#ifndef EXPORTFILE_H
#define EXPORTFILE_H
#include <QByteArray>
#include <QFileDialog>

class ExportFile
{
public:
    static void saveFile(QByteArray text);
};

#endif // EXPORTFILE_H
