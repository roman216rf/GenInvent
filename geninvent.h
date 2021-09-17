#ifndef GENINVENT_H
#define GENINVENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GenInvent; }
QT_END_NAMESPACE

class GenInvent : public QMainWindow
{
    Q_OBJECT

public:
    GenInvent(QWidget *parent = nullptr);
    ~GenInvent();

private:
    Ui::GenInvent *ui;
};
#endif // GENINVENT_H
