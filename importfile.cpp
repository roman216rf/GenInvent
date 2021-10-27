#include "importfile.h"

InventFile ImportFile::importZabbixFile(const QString &file_path){
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

QString clearValue(QString& raw_string, const QString& substr_true, const QString& substr_false){
    if (raw_string.startsWith(substr_true)){
        raw_string.remove(0, substr_true.length());
    }
    else{
        raw_string.remove(0, substr_false.length());
    }
    return raw_string;
}

InventFile ImportFile::importAnsibleFile(const QString &file_path){
    InventFile invFile;

    QFile file(file_path);

    if(file.exists()&&file.open(QIODevice::ReadOnly)){
        QString line = "";
        Group group("temp");
        while(!file.atEnd()){
            if (line.startsWith("[") && !line.startsWith("[all:vars]")){
                if (!line.endsWith(":vars]") && !line.endsWith(":vars]\n")){
                    line.remove(0,1);
                    line.chop(2);
                    group = Group(line);
                    invFile.addOneGroup(group);
                    line = file.readLine();

                    while(line != "" && line != "\n"){
                        QStringList hostString = line.split(QRegExp(" "), QString::SkipEmptyParts);
                        QString  ip, login, pass;
                        for(int i = 1; i < hostString.length(); i++){
                            if (hostString[i].startsWith("ansible_host=") || hostString[i].startsWith("host="))
                                ip = clearValue(hostString[i], "ansible_host=", "host=");
                            else if (hostString[i].startsWith("ansible_user=") || hostString[i].startsWith("ansible_ssh_user="))
                                login = clearValue(hostString[i], "ansible_user=", "ansible_ssh_user=");
                            else if (hostString[i].startsWith("ansible_password=") || hostString[i].startsWith("ansible_sudo_pass='")){
                                pass = clearValue(hostString[i], "ansible_password=", "ansible_sudo_pass='");
                                if (pass.endsWith("'"))
                                    pass.chop(1);
                            }
                        }

                        Host host(hostString[0], ip);
                        QString groupname = group.getName();
                        host.setLogin(login);
                        host.setPass(pass);

                        invFile.addOneHost(host, groupname);
                        line = file.readLine();
                    }
                }
                else{
                    line.remove(0, 1);
                    line.chop(7);
                    QString current_group = line;
                    line = file.readLine();
                    QMap<QString, QString>vars;
                    while (line != "" && line != "\n"){
                        QStringList varString = line.split(QRegExp("="), QString::SkipEmptyParts);
                        if (varString[1].endsWith('\n'))
                            varString[1].chop(1);
                        vars[varString[0]] = varString[1];
                        line = file.readLine();
                    }
                    invFile.setVars(current_group, vars);
                }
            }
            line = file.readLine();
        }
        file.close();
    }
    return invFile;
}
