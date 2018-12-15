#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPlainTextEdit"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //显示工具栏


//槽函数
private slots:
    void open_path();
    void save_file();
    void separation_file();
    void new_open_file();
    void on_tabWigdget_tabCloseRequestsed(int index);
    void on_tabWigdget_currentChanged(int index);
private:
    Ui::MainWindow *ui;
    //以下是工具栏按钮
    QAction *open;
    QAction *separation;
    QAction *save;
    QAction *new_file;
    //以上是工具栏按钮
private:
    void show_form_doc();//别看了*****此函数无用
    void connect_SLOT_SIGNAL();//信号槽函数
    void set_tab_Widget();
    void show_tool_bar();
    void paintEvent(QPaintEvent *event);
    void independent_dialog();
};
#endif // MAINWINDOW_H
