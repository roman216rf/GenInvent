#ifndef IMPORTZABBIXFILE_H
#define IMPORTZABBIXFILE_H
#include <group.h>
#include <host.h>
#include <QFile>

//Функция, возвращающая список групп с включенными в них хостами, на основе файла, путь которого передается в качестве аргумента
QVector<Group> importZabbixFile(const QString &file_path){
    QVector<Group> resultFile; //Объявление списка групп с включенными в них хостами

    QFile file(file_path); //
    //bool typeData = false;

    if (file.exists()&&file.open(QIODevice::ReadOnly)){
        QString line = "";
        while(!file.atEnd()){
            //typeData = (line == "  groups:");

            if (line.startsWith("  groups:")){
                while(!line.startsWith("  hosts:")){
                    if (line.startsWith("      name:") /*&& typeData*/){
                        line.remove(0, 12);
                        line.chop(1);
                        Group tmp(line);
                        resultFile.append(tmp);
                    }

                    line = file.readLine();
                }
            }
            else if (line.startsWith("  hosts:")){
                while (!file.atEnd()){
                    if (line.startsWith("      name:")){
                        line.remove(0, 12);
                        line.chop(1);
                        QString hostname = line;
                        QVector<QString> groupList;

                        //line = file.readLine();
                        while (!line.startsWith("      name:")){
                            if (line.startsWith("      groups:")){
                                while(!line.startsWith("      interfaces:")){
                                    if (line.startsWith("          name:")){
                                        line.remove(0, 16);
                                        line.chop(1);

                                        groupList.append(line);
                                    }
                                    line = file.readLine();
                                }
                            }
                            else if (line.startsWith("      interfaces:")){

                            }
                        }
                    }
                    else{
                        line = file.readLine();
                    }
                }
            }
            else{
                line = file.readLine();
            }
        }
        file.close();
    }
    return resultFile;
}

#endif //IMPORTZABBIXFILE_H
