#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QDialog>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <group.h>
#include <inventfile.h>
#include <QMessageBox>

namespace Ui {
class AddGroup;
}

class AddGroup : public QDialog
{
    Q_OBJECT

public:
    //explicit
    AddGroup(QWidget *parent = nullptr);
    ~AddGroup();

    void setPropList(InventFile& invfile);
    void setPropList(InventFile& invfile, const QString& groupname);

private slots:
    void addVar();
    void delVar();

    void click_save();

private:
    QVector<QString> getUsingVars()const;
    void delUsingVarFromCmb(const QString& varname);
    QVector<QString> getVarList(const QMap<Group, QVector<Host>>& structFile);
    void createOldVars(const QMap<QString, QString>& vars);
    Ui::AddGroup *ui;
    QVector<QString> varList;
    InventFile* inventFile = new InventFile();
    Group editGroup = Group("");
};

#endif // ADDGROUP_H
