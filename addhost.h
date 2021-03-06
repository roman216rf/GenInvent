#ifndef ADDHOST_H
#define ADDHOST_H

#include <QDialog>
#include <inventfile.h>
#include <QMessageBox>
#include <host.h>

namespace Ui {
class AddHost;
}

class AddHost : public QDialog
{
    Q_OBJECT

public:
    explicit AddHost(QWidget *parent = nullptr);
    ~AddHost();

    void setPropList(InventFile& invfile);
    void setPropList(InventFile& invfile, const QString& hostname, const QString& groupname);

private slots:
    void on_ip_textChanged(const QString &arg1);
    void click_save();

    void on_pushButton_pressed();

    void on_pushButton_released();

private:
    Ui::AddHost *ui;
    void drawListGroup();
    QVector<QString>getGroupsNames(const QMap<Group, QVector<Host>>& structFile);
    QVector<QString>groups;
    InventFile* inventFile = new InventFile();
    Host editHost = Host("", "");
};

#endif // ADDHOST_H
