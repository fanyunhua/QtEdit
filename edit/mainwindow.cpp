#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QDebug"
#include "QFileDialog"
#include "QIODevice"
#include "string.h"
#include "GBK.h"
#include "QLineEdit"
#include "QPlainTextEdit"
#include "QAction"
#include "QMainWindow"
#include "QToolBar"
#include "QTableWidget"
#include "formdoc.h"
#include "QWidget"
#include "QPainter"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化并显示工具栏
    show_tool_bar();
    //信号槽连接
    connect_SLOT_SIGNAL();
    //tabWidget进行设置
    set_tab_Widget();
}
MainWindow::~MainWindow()
{
//    QMessageBox::information(this,"警告","确定要退出吗");
    delete ui;
}
//绘制窗口
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter pa(this);
    pa.drawPixmap(0,ui->toolBar->height(),this->width(),
                  this->height()-ui->toolBar->height() -ui->statusBar->height(),
                  QPixmap(":/imgs/imgs/bg.jpg"));
}

//对tabWidget进行补充设计
void MainWindow::set_tab_Widget()
{

    ui->tabWidget->clear();//清理项
    ui->tabWidget->setVisible(false);//设置不可见

    ui->tabWidget->setTabsClosable(true);//有关闭按钮   ***但是TM关不了
    ui->tabWidget->tabsClosable();//这个也是关闭    ***但是TM也关不了

    this->setCentralWidget(ui->tabWidget);
//    this->setWindowState(Qt::WindowMaximized);//最大化显示
}

void MainWindow::new_open_file()
{
    FormDoc *formdoc;
    formdoc = new FormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除
    int cur = ui->tabWidget->addTab(
                formdoc,QString::asprintf("New %d",ui->tabWidget->count()+1));
    qDebug()<< "new tab";
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::open_path()
{
    QString curPath = QDir::currentPath();
    //对话框标题
    QString title = "选择文件";
    //过滤文件
    QString filter = "程序文件(*.h *cpp);;文本文件(*.txt);;所有文件(*.*)";
    //获取文件路径
    QString file_path = QFileDialog::getOpenFileName(this,title,curPath,filter);
        if(file_path.length()>0)
        {
            qDebug()<< file_path;
            //转换文件路径编码
            string gbk_name = GBK::FromUnicode(file_path);
            string s = file_path.toStdString();
            QString qstr2 = QString::fromStdString(s);
            FILE *f = fopen(s.c_str(),"rb");
            //文件大小
            fseek(f,0,SEEK_END);
            int file_size = ftell(f);

            //读文件
             fseek(f,0,SEEK_SET);
             char * buff = new char[file_size+1];
             int n = fread(buff,1,file_size,f);
             qDebug()<< n;
             if(n>0)
             {
                 buff[n] = 0;
//                 edit1->setPlainText(GBK::ToUnicode(buff));
//                 ui->textEdit->setText(GBK::ToUnicode(buff));
//                 formdoc->set_text(buff);
//                 new_open_file();
                 FormDoc *fo = new FormDoc(this);
                 int cur = ui->tabWidget->addTab(fo,"新文件");
                 ui->tabWidget->setCurrentIndex(cur);
                 //fo->set_text(buff);
                 ui->tabWidget->setVisible(true);
             }
             delete []buff;
             fclose(f);
        }
}
//弹出独立对话框
void MainWindow::independent_dialog()
{
    FormDoc *ff = new FormDoc;
    ff->setAttribute(Qt::WA_DeleteOnClose);
    ff->setWindowTitle("无父窗口，关闭自动删除");
//    ff->setWindowFlags(Qt::Window,true);
    ff->setWindowOpacity(0.9);
    ff->show();
}

void MainWindow::save_file()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            "文件另存为",
            "",
            tr("Config Files (*.txt)"));
}
 void MainWindow::separation_file()
 {
     FormDoc *ff = new FormDoc;
     ff->setAttribute(Qt::WA_DeleteOnClose);
     ff->setWindowTitle("NEW");
 //    ff->setWindowFlags(Qt::Window,true);
     ff->setWindowOpacity(0.9);
     ff->show();
 }
 //信号槽连接
 void  MainWindow::connect_SLOT_SIGNAL()
 {
     connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(new_open_file()));
     connect(ui->actionOpen_2,SIGNAL(triggered()),this,SLOT(open_path()));
     connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_file()));
     connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(close_file()));

     connect(new_file,SIGNAL(triggered(bool)),this,SLOT(new_open_file()));
     connect(open,SIGNAL(triggered()),this,SLOT(open_path()));
     connect(separation,SIGNAL(triggered()),this,SLOT(separation_file()));
     connect(save,SIGNAL(triggered()),this,SLOT(save_file()));
     //设置快捷键
     new_file->setShortcut(QKeySequence(QLatin1String("Ctrl+Alt+L")));

    //tabbar显示背景槽连接
     connect(
                ui->tabWidget,
                SIGNAL(currentChanged(int)),
                this,
                SLOT(on_tabWigdget_currentChanged(int)));
     //tabbar关闭槽连接
     connect(
                 ui->tabWidget,
                 SIGNAL(tabCloseRequested(int)),
                 this,
                 SLOT(on_tabWigdget_tabCloseRequestsed(int)));

 }
 //添加 和 显示 工具栏选项
 void MainWindow::show_tool_bar()
 {
     QIcon open_img(":/imgs/imgs/open.png");
     QIcon separation_img(":/imgs/imgs/separation.png");
     QIcon save_img(":/imgs/imgs/save.png");
     QIcon new_img(":/imgs/imgs/new.png");

     open = new QAction(this);
     open->setIcon(open_img);

     separation = new QAction(this);
     separation->setIcon(separation_img);

     save = new QAction(this);
     save->setIcon(save_img);

     new_file = new QAction(this);
     new_file->setIcon(new_img);

     ui->toolBar->addAction(new_file);
     ui->toolBar->addAction(open);
     ui->toolBar->addAction(save);
     ui->toolBar->addAction(separation);
 }
 //别看了   *************此函数无用
void MainWindow::show_form_doc()
{/*
    FormDoc *formdoc = new FormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除
    int cur = ui->tabWidget->addTab(formdoc,
                                    QString::asprintf("DOC %d",ui->tabWidget->count()));

    int cur2 = ui->tabWidget->addTab(formdoc,"第一页");
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);*/
}

//关闭tabWigdget槽函数
void  MainWindow::on_tabWigdget_tabCloseRequestsed(int index)
{
    if(index<0)
        return;
    //关闭当前显示的
    QWidget *aFrom = ui->tabWidget->widget(index);
    aFrom->close();
}
//显示背景槽函数
void  MainWindow::on_tabWigdget_currentChanged(int index)
{
    bool en = ui->tabWidget->count()>0;//<0已无分页
    ui->tabWidget->setVisible(en);
}
