#include "exportfile.h"


ExportFile::ExportFile(const InventFile &invent){
    inventfile = invent;
}

void ExportFile::saveFile(const QString& path){
    QMessageBox msg;
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::YesAll | QMessageBox::Cancel);
    msg.setButtonText(QMessageBox::Yes, "Linux");
    msg.setButtonText(QMessageBox::YesAll, "Windows");
    msg.setText("Выберите операционную систему, под управлением которой находятся все хосты");
    msg.setWindowTitle("Экспорт файла");
    int res = msg.exec();
    if (res == QMessageBox::Yes || res == QMessageBox::YesAll){
        QMapIterator <Group, QVector<Host>> pair(inventfile.getStructFile());
        QString textfile = "";
        while (pair.hasNext()) {
            pair.next();

            textfile.append("[" + pair.key().getName().trimmed() + "]\n");
            for (const Host& host: pair.value()){
                if (res == QMessageBox::Yes){
                    textfile.append(host.getName().trimmed() + " host=" + host.getIp().trimmed() + " ansible_ssh_user=" + host.getLogin().trimmed() + " become=yes ansible_sudo_pass='" + host.getPass().trimmed() + "' ansible_ssh_pass='" + host.getPass().trimmed() + "'\n");
                }
                else{
                    textfile.append(host.getName().trimmed() + " ansible_host=" + host.getIp().trimmed() + " ansible_user=" + host.getLogin().trimmed() + " ansible_password=" + host.getPass().trimmed() + " ansible_connection=ssh ansible_shell_type=cmd\n");
                }
            }
            textfile.append("\n");
            if (!pair.key().getVars().isEmpty()){
                textfile.append("[" + pair.key().getName().trimmed() + ":vars]\n");

                QMapIterator <QString, QString> var(pair.key().getVars());
                while (var.hasNext()) {
                    var.next();

                    textfile.append(var.key() + "=" + var.value() + "\n");
                }
                textfile.append("\n");
            }
        }

        QFile file(path);
        if (file.open(QIODevice::WriteOnly)){
            file.write(textfile.toStdString().c_str());
            file.close();
        }
    }
}
