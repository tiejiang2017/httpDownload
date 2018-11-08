#include "qhttpdownloadthread.h"

QHttpDownloadThread::QHttpDownloadThread(QObject *parent) : QThread(parent)
{

}
bool QHttpDownloadThread::systemInit(QString userName,QString pwd,QString url)
{
    this->userName = userName;
    this->pwd=pwd;
    this->url=url;
}

void QHttpDownloadThread::downloadFinished(int t)
{
    qDebug()<<"QHttpDownloadThread finished...";
    emit finish(t);
}

void QHttpDownloadThread::run()
{
    downloader = new ChttpDownload(this);
    downloader->systemInit(userName, pwd, url);
    downloader->runDownload();
    connect(downloader,SIGNAL(fileDownloadDoneSignal(int)),this,SLOT(downloadFinished(int)));
    exec();


}
