#ifndef CHTTPDOWNLOAD_H
#define CHTTPDOWNLOAD_H

#include <QObject>

#include <ostream>


#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QFile>
#include <QFileInfo>
#include <QUrlQuery>
#include <QThread>
#include <QDir>
#include <QtNetwork/QSslKey>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslCertificateExtension>
#include <QtNetwork/QSslConfiguration>
#include <iostream>
#include<QEventLoop>
using namespace std;

class ChttpDownload : public QObject
{
	Q_OBJECT

public:
    ChttpDownload(QObject *parent = 0);
	~ChttpDownload();

	//自动下载初始化变量点击登陆按钮后，这些数据无法更改
	int startFre;//timerEvent初始循环频率,同时也是递增单位
	int FreCont;//timerEvent中未获取连接次数 
	int TempFre;//timerEvent当前循环频率
	int threadNum;//线程正在运行的个数
	//获取下载返回信息
	vector<QString> GetMessageFromReplay( QNetworkReply *reply, vector<QString> srcName, bool httpFlag );
	//登陆获取授权码
	int land_module( QString use_name, QString pass_key);
	QString authorCode;
	//授权登陆获取bucknetName
	int author_module();
	QString bucknetName;
	//获取下载链接
	int get_download_filepath_module();
	//下载请求校验
	int download_request_module();
	//下载
	int downloading_module();
	//调用测试函数
	void testFunc();
	//回写状态信息
	int respond_process_status( QString statusName );
	//公司网址
	QString company_url;
	QString mModelFilePath, mModelFileName;
	QString mFinalPath;
	QString downLocalFilePath;//文件下载到本地的路径
	QString use_name,pass_key;
	//modelId
	QString modelId;
	//单线程下载完成标志
	bool mSingleWayDown;

	bool landFlag;//登陆授权成功标志
	bool authorFlag;//登陆授权成功标志

    bool downloadFinished;
    bool systemInit(QString userName, QString pwd, QString url);

    void runDownload();
public slots:
		void isDownloading_DoneSlot( bool doneFlag, int tnum);
		void isSingleDownloading_DoneSlot( bool doneFlag);

	private slots:
		//读取服务器返回响应数据
		int land_respond_finished(QNetworkReply *reply);
		int author_respond_finished(QNetworkReply *reply);
		int get_download_filepath_respond_finished(QNetworkReply *reply);
		int download_request_respond_finished(QNetworkReply *reply);
		int downloading_finished();
		void downloading_read();
		void onError(QNetworkReply::NetworkError errorCode);
		int respond_process_status_finished(QNetworkReply *reply);

protected:
	void timerEvent( QTimerEvent *event );
	int m_nTimerId;

private:

	QNetworkAccessManager *manager;//管理Http请求和响应
	QNetworkRequest* request;//请求
	QNetworkReply* mReply;//响应
	QUrl currentUrl;//保存当前网页的URL地址，网中每个文件都有一个独立的URL
	QFile *mfile;//保存下载的文件
signals:
	void fileDownloadDoneSignal(int doneFlag);
};



#endif // CHTTPDOWNLOAD_H
