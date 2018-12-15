#include "formdoc.h"
#include "ui_formdoc.h"
#include "QPlainTextEdit"
#include "QDebug"
#include "QFileDialog"
#include "string.h"
#include "GBK.h"
FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
    //添加工具栏
    show_toolbar();
    //添加信号槽连接
    connect_SLOT_SIGNAL();
    //设置快捷键
    set_shot_cut();

}

FormDoc::~FormDoc()
{
    delete ui;
}
//设置快捷键
void FormDoc::set_shot_cut()
{
    this->save->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
    this->open->setShortcut(QKeySequence(QLatin1String("Ctrl+O")));
}

//信号槽函数
void FormDoc::connect_SLOT_SIGNAL()
{
    connect(this->save,SIGNAL(triggered()),this,SLOT(save_data()));
    connect(this->open,SIGNAL(triggered()),this,SLOT(open_data()));
}

//添加 和 显示 工具栏选项
void FormDoc::add_toolbar()
{
    QIcon open_img(":/imgs/imgs/open.png");
    QIcon close_img(":/imgs/imgs/close.png");
    QIcon save_img(":/imgs/imgs/save.png");

    open = new QAction(this);
    open->setIcon(open_img);

    close = new QAction(this);
    close->setIcon(close_img);

    save = new QAction(this);
    save->setIcon(save_img);

    local_toolbar->addAction(open);
    local_toolbar->addAction(save);
//    local_toolbar->addAction(close);
}
void FormDoc::show_toolbar()
{
    //此处请注意 工具栏初始化之后默认会添加到面板
    local_toolbar = new QToolBar("文档",this);
//    open = new QAction("open",this);
//    local_toolbar->addAction(open);
//    local_toolbar->addAction(open);
    add_toolbar();

    //设置字体
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(20);
    ui->plainTextEdit->setFont(font);//非指针变量

    ui->verticalLayout->setContentsMargins(0,0,0,0);
    ui->verticalLayout->addWidget(local_toolbar);
    ui->verticalLayout->addWidget(ui->plainTextEdit);
    //未知bug QWidget::insertAction: Attempt to insert null action
    //如果不添加任何东西会报以上错误，暂时未知，，未知。。。。。。
    //具体操作 bug 异常退出
}
void FormDoc::save_data()
{
    QString file_path = QFileDialog::getSaveFileName(this,
            "文件另存为",
            "",
            tr("Config Files (*.txt)"));
    if(file_path.length()>0)
    {
        //获取文本内容
        QString text = this->ui->plainTextEdit->toPlainText();
        string gbk_text = GBK::FromUnicode(text);

        //转换文件路径编码
        string gbk_file_name = GBK::FromUnicode(file_path);
//        string s = file_path.toStdString();
//        QString qstr2 = QString::fromStdString(s);
        FILE *f = fopen(gbk_file_name.c_str(),"wb");
        fwrite(gbk_text.c_str(),1,gbk_text.length(),f);
        fclose(f);
    }
}
void FormDoc::open_data()
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
                 this->ui->plainTextEdit->setPlainText(buff);
             }
             delete []buff;
             fclose(f);
        }
}
