#ifndef QHTTPDOWNLOADTHREAD_H
#define QHTTPDOWNLOADTHREAD_H

#include <QObject>
#include<QThread>
#include "chttpdownload.h"

class QHttpDownloadThread : public QThread
{
    Q_OBJECT
public:
    explicit QHttpDownloadThread(QObject *parent = 0);
    ChttpDownload *downloader;
    QString userName;
    QString pwd;
    QString url;
    void run();
    bool systemInit(QString userName, QString pwd, QString url);
signals:
    void finish(int t);

public slots:
    void downloadFinished(int t);
};

#endif // QHTTPDOWNLOADTHREAD_H
