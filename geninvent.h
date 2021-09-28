#ifndef GENINVENT_H
#define GENINVENT_H

#include <QMainWindow>
#include <QTreeWidget>
#include "ui_geninvent.h"
#include <QFileDialog>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GenInvent; }
QT_END_NAMESPACE

class GenInvent : public QMainWindow
{
    Q_OBJECT

public:
    GenInvent(QWidget *parent = nullptr);
    ~GenInvent();

private slots:
    void importFromZabbix();

    void on_treeWidget_itemActivated(QTreeWidgetItem *item);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

private:
    Ui::GenInvent *ui;
};
#endif // GENINVENT_H
