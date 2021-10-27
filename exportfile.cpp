#include "exportfile.h"


void ExportFile::saveFile(QByteArray text){
    QFile file(QFileDialog::getSaveFileName(0, "Выберите имя и путь для сохранения файла", "C:/", "Files (*)"));

    if (file.open(QIODevice::WriteOnly)){
        file.write(text);
    }
    file.close();
}
