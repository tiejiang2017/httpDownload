#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::threadFinish(int t)
{
    thread.quit();
    thread.wait();
    qDebug()<<" MainWindow::threadFinish"<<t;
    ui->label->setText("download finished...");
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    QString use_name = "vt_down1";
    QString pass_key = "123456";
    QString company_url = "https://test.mgt.built-in.net";
    connect(&thread,SIGNAL(finish(int)),this,SLOT(threadFinish(int)));
    thread.systemInit(use_name,pass_key,company_url);
    thread.start();
    ui->label->setText("downloading...");
    ui->pushButton->setEnabled(false);
}
