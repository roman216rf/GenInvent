#ifndef IMPORTZABBIXFILE_H
#define IMPORTZABBIXFILE_H
#include <inventfile.h>
#include <QFile>

//Функция, возвращающая список групп с включенными в них хостами, на основе файла, путь которого передается в качестве аргумента
InventFile importZabbixFile(const QString &file_path){
    //QVector<Group> resultFile; //Объявление списка групп с включенными в них хостами
    InventFile invFile;

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
                        //resultFile.append(tmp);
                        invFile.addOneGroup(tmp);
                    }

                    line = file.readLine();
                }
            }
            else if (line.startsWith("  hosts:")){
                while (!file.atEnd()){
                    QString hostname;
                    QVector<QString> groupList;
                    QString ip;
                    if (line.startsWith("      name:")){
                        line.remove(0, 12);
                        line.chop(1);
                        hostname = line;

                        //line = file.readLine();
                        while (!line.startsWith("      name:") && line!=""){
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
                                while(!line.startsWith("      inventory_mode:")){
                                    if (line.startsWith("          ip:")){
                                        line.remove(0, 14);
                                        line.chop(1);

                                        ip = line;
                                    }
                                    line = file.readLine();
                                }
                            }
                            else{
                                line = file.readLine();
                            }
                        }
                        Host tmp_host(hostname, ip);

                        invFile.addOneHost(tmp_host, groupList);
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
    return invFile;
}

#endif //IMPORTZABBIXFILE_H
