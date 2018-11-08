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

	//�Զ����س�ʼ�����������½��ť����Щ�����޷�����
	int startFre;//timerEvent��ʼѭ��Ƶ��,ͬʱҲ�ǵ�����λ
	int FreCont;//timerEvent��δ��ȡ���Ӵ��� 
	int TempFre;//timerEvent��ǰѭ��Ƶ��
	int threadNum;//�߳��������еĸ���
	//��ȡ���ط�����Ϣ
	vector<QString> GetMessageFromReplay( QNetworkReply *reply, vector<QString> srcName, bool httpFlag );
	//��½��ȡ��Ȩ��
	int land_module( QString use_name, QString pass_key);
	QString authorCode;
	//��Ȩ��½��ȡbucknetName
	int author_module();
	QString bucknetName;
	//��ȡ��������
	int get_download_filepath_module();
	//��������У��
	int download_request_module();
	//����
	int downloading_module();
	//���ò��Ժ���
	void testFunc();
	//��д״̬��Ϣ
	int respond_process_status( QString statusName );
	//��˾��ַ
	QString company_url;
	QString mModelFilePath, mModelFileName;
	QString mFinalPath;
	QString downLocalFilePath;//�ļ����ص����ص�·��
	QString use_name,pass_key;
	//modelId
	QString modelId;
	//���߳�������ɱ�־
	bool mSingleWayDown;

	bool landFlag;//��½��Ȩ�ɹ���־
	bool authorFlag;//��½��Ȩ�ɹ���־

    bool downloadFinished;
    bool systemInit(QString userName, QString pwd, QString url);

    void runDownload();
public slots:
		void isDownloading_DoneSlot( bool doneFlag, int tnum);
		void isSingleDownloading_DoneSlot( bool doneFlag);

	private slots:
		//��ȡ������������Ӧ����
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

	QNetworkAccessManager *manager;//����Http�������Ӧ
	QNetworkRequest* request;//����
	QNetworkReply* mReply;//��Ӧ
	QUrl currentUrl;//���浱ǰ��ҳ��URL��ַ������ÿ���ļ�����һ��������URL
	QFile *mfile;//�������ص��ļ�
signals:
	void fileDownloadDoneSignal(int doneFlag);
};



#endif // CHTTPDOWNLOAD_H
