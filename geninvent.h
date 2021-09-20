#ifndef GENINVENT_H
#define GENINVENT_H

#include <QMainWindow>
#include <group.h>
#include <host.h>

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

private:
    Ui::GenInvent *ui;
};
#endif // GENINVENT_H
