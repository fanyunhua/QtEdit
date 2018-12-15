#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>
#include "QToolBar"
#include "QAction"
#include "QPlainTextEdit"
namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit FormDoc(QWidget *parent = 0);
    ~FormDoc();
private:
    void connect_SLOT_SIGNAL();//信号槽函数
private slots:
    void open_data();
    void save_data();
private:
    Ui::FormDoc *ui;
    QAction *open;
    QAction *close;
    QAction *save;
    void show_toolbar();
    void add_toolbar();
    QToolBar *local_toolbar;
    void set_shot_cut();
};
#endif // FORMDOC_H
