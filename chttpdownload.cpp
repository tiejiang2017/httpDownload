#include "chttpdownload.h"


ChttpDownload::ChttpDownload(QObject *parent)
    : QObject(parent)
{


	threadNum = 0;
	FreCont = 0;
	startFre = 30000;
	TempFre = 5000;

//	testFunc();
}

ChttpDownload::~ChttpDownload()
{
	if ( m_nTimerId != 0 )
		killTimer(m_nTimerId);
}
bool ChttpDownload::systemInit(QString userName,QString pwd,QString url)
{
    use_name = userName;
    pass_key = pwd;
    company_url = url;
    land_module( use_name, pass_key);
    author_module();
    landFlag = true;
    authorFlag = true;
    mSingleWayDown = true;
    downloadFinished = false;
    //m_nTimerId = startTimer(TempFre);
    int ret = get_download_filepath_module();
    int m = download_request_module();
    //......
    return true;
}
void ChttpDownload::runDownload()
{
    downloading_module();
}

void ChttpDownload::testFunc()
{
	use_name = "vt_down1";
	pass_key = "123456";
	company_url = "https://test.mgt.built-in.net";
	land_module( use_name, pass_key);
	author_module();
	landFlag = true;
	authorFlag = true;
	mSingleWayDown = true;
	//m_nTimerId = startTimer(TempFre);
	get_download_filepath_module();
	download_request_module();
	downloading_module();
}

int ChttpDownload::land_module( QString use_name, QString pass_key)
{
	QString total_url = company_url + QString("/oauth/token?username=") + use_name + QString("&password=") + pass_key + QString("&grant_type=password&scope=all&client_id=adminClient&client_secret=adminClientSecret");
	QUrl url1(total_url);
	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(url1);
	QNetworkReply *pReplay0 = manager->post(*request, QByteArray());
	QEventLoop loop;
	connect(pReplay0, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	int tnum = land_respond_finished(pReplay0);
	return tnum;
}

int ChttpDownload::land_respond_finished(QNetworkReply *reply)
{
	int tt = -1;
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			vector<QString> paraInput,paraOutput;
			paraInput.push_back( "access" );
			paraInput.push_back( "token_type" );
			paraOutput = GetMessageFromReplay(reply, paraInput, false);
			authorCode = paraOutput[1] + " " + paraOutput[0];
			tt = 0;
		}
		else
		{
			//error
			;
		}
	}
	else
	{
		//error
		;
	}
	reply->deleteLater();
	return tt;
}

int ChttpDownload::author_module()
{
	QString total_url = company_url + QString("/rest/yun/ali/baseInfo?vendor=V_VT");
	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(QUrl(total_url));
	QByteArray dataArray;
	dataArray.append(authorCode);
	request->setRawHeader("Authorization",dataArray);
	QNetworkReply *pReplay0 = manager->get(*request);
	QEventLoop loop;
	connect(pReplay0, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	int tnum = author_respond_finished(pReplay0);
	return tnum;
}

int ChttpDownload::author_respond_finished(QNetworkReply *reply)
{
	int tt = -1;
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			vector<QString> paraInput,paraOutput;
			paraInput.push_back( "privateBucketName" );
			paraOutput = GetMessageFromReplay(reply, paraInput, false);
			bucknetName = paraOutput[0];
			tt = 0;
		}
		else
		{
			//error
			;
		}
	}
	else
	{
		//error
		;
	}
	reply->deleteLater();
	return tt;
}

int ChttpDownload::get_download_filepath_module()
{
	QString total_url = company_url + QString("/rest/modelAssign/getAssignTask");
	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(QUrl(total_url));
	QByteArray dataArray;
	dataArray.append(authorCode);
	request->setRawHeader("Authorization",dataArray);
	QNetworkReply *pReplay0 = manager->get(*request);
	QEventLoop loop;
	connect(pReplay0, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	int messageNum = get_download_filepath_respond_finished(pReplay0);
	return messageNum;
}

int ChttpDownload::get_download_filepath_respond_finished(QNetworkReply *reply)
{
	int tout = -1;
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			vector<QString> paraInput,paraOutput;
			paraInput.push_back( "modelFilePath" );
			paraInput.push_back( "modelFileName" );
			paraInput.push_back( "modelId" );
			paraOutput = GetMessageFromReplay(reply, paraInput, false);
			modelId = paraOutput[0];
			mModelFilePath = paraOutput[1];
			mModelFileName = paraOutput[2];
			tout = 0;
		}
		else
		{
			//error
			;
		}
	}
	else
	{
		//error
		;
	}
	reply->deleteLater();
	return tout;
}

int ChttpDownload::download_request_module()
{
	QString total_url = company_url + QString("/rest/yun/ali/oss/signedurl/get");
	QUrl url1(total_url);
	QUrlQuery tQuery;
	tQuery.addQueryItem("bucketName",bucknetName);
	tQuery.addQueryItem("filePath",mModelFilePath);
	url1.setQuery(tQuery);
	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(url1);
	QByteArray dataArray;
	dataArray.append(authorCode);
	request->setRawHeader("Authorization",dataArray);
	QNetworkReply *pReplay0 = manager->get(*request);
	QEventLoop loop;
	connect(pReplay0, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	int tnum = download_request_respond_finished(pReplay0);
	return tnum;
}

int ChttpDownload::download_request_respond_finished(QNetworkReply *reply)
{
	int tt = -1;
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			vector<QString> paraInput,paraOutput;
			paraInput.push_back( "signedGetUrl" );
			paraOutput = GetMessageFromReplay(reply, paraInput, true);
			mFinalPath = paraOutput[0];
			tt = 0;
		}
		else
		{
			//error
			;
		}
	}
	else
	{
		//error
		;
	}
	reply->deleteLater();
	return tt;
}

int ChttpDownload::downloading_module()
{
	QDir files;//文件夹
	QString fileStr=QString("text/");
	QString fileName=QString("text/")+mModelFileName;
	if(!files.exists(fileStr)){
		files.mkpath(fileStr);
	}

	mfile=new QFile(fileName);
	if(!mfile->open(QIODevice::WriteOnly)){
		delete mfile;
		mfile=0;
		return 5;
	}
	QNetworkRequest tRequest;
	QUrl url1(mFinalPath);
	qDebug()<< mFinalPath;
	manager = new QNetworkAccessManager(this);
	tRequest.setUrl(url1);
	QSslCertificate certificate;
	QSslKey key;
	QList<QSslCertificate> importedCerts;
	QSslConfiguration config = tRequest.sslConfiguration();
	config.setCaCertificates(importedCerts);
	config.setLocalCertificate(certificate);
	config.setPrivateKey(key);
	config.setProtocol(QSsl::AnyProtocol);
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	tRequest.setSslConfiguration(config);

	QByteArray dataArray;
	dataArray.append(authorCode);
	tRequest.setRawHeader("Authorization",dataArray);
	mReply = manager->get(tRequest);
	connect(mReply, SIGNAL(finished()), this, SLOT(downloading_finished()));
	connect(mReply , SIGNAL(error(QNetworkReply::NetworkError)) , this , SLOT(onError(QNetworkReply::NetworkError)));
	connect((QObject *)mReply, SIGNAL(readyRead()),this, SLOT(downloading_read()));
	respond_process_status( "Downing" );
	return 0;
}

void ChttpDownload::downloading_read()
{
	if(mfile){
		mfile->write(mReply->readAll());
        mfile->flush();
	}
//    if(mfile->size()==0)
        qDebug()<<"downloading_reading ...";
//    else
//    {
//        printf(".");
//        fflush(stdout);
//    }
}

void ChttpDownload::onError(QNetworkReply::NetworkError errorCode)
{
	 qDebug()<< errorCode;
	 respond_process_status( "DownFail" );
}

int ChttpDownload::downloading_finished()
{
	int tt = -1;
    qDebug()<<"downloading_finished...";
	QVariant statusCodeV = mReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if(mReply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			QByteArray bytes = mReply->readAll();  //获取字节
			QString result(bytes);  //转化为字符串
			tt = 0;
		}
		else
		{
			//error
			;
		}

	}
	else
	{
		;
	}
	mfile->flush();
	mfile->close();
	delete mfile;
	mfile = 0;
	mReply->deleteLater();
	respond_process_status( "DownSuccess" );
    downloadFinished = true;
    emit fileDownloadDoneSignal(tt);
	return tt;
}

vector<QString> ChttpDownload::GetMessageFromReplay( QNetworkReply *reply, vector<QString> srcName, bool httpFlag )
{
	vector<QString> outData;
	if ( srcName.size() < 1 || reply == NULL )
		return outData;

	//读取服务器返回响应数据
	QString replyText = reply->readAll();
	replyText.replace(QString("{"), QString(""));
	replyText.replace(QString("}"), QString(""));
	QStringList strlist = replyText.split(","); 

	for ( int i = 0; i < strlist.size(); ++i )
	{
		QStringList strlist2 = strlist[i].split(":");   
		if ( strlist2.size() < 2 )
			continue;
		for ( int z = 0; z < srcName.size(); ++z )
		{
			for ( int j = 0; j < strlist2.size() - 1; ++j )
			{
				if (strlist2[j].contains(srcName[z],Qt::CaseSensitive))
				{
					if ( httpFlag )
					{
						if ( strlist2[j+1].contains("http",Qt::CaseSensitive) )
						{						
							strlist2[j+1].replace(QString("\""), QString(""));
							strlist2[j+2].replace(QString("\""), QString(""));
							outData.push_back(strlist2[j+1]+":"+strlist2[j+2]);
							return outData;
						}			
					}
					else
					{
						strlist2[j+1].replace(QString("\""), QString(""));
						outData.push_back(strlist2[j+1]);
					}
				}
			}
		}
	}
	return outData;
}

void ChttpDownload::timerEvent( QTimerEvent *event )
{
	//获取链接、下载、授权失败时将重新进行token获取landFlag = false;
	if ( !landFlag )
		int landNum = land_module( use_name, pass_key);

	//获取链接、下载失败时重新获取bucketname，authorFlag = false；
	if ( !authorFlag )
		int authorNum = author_module();

	for ( int i = 0; i < 1; ++i )
	{
		if ( mSingleWayDown )
		{
			int getPathNum = get_download_filepath_module();
			int downRequestNum = download_request_module();
			if ( downRequestNum == 0 && getPathNum == 0 )
			{
				mSingleWayDown = false;
				vector<QString> DownloadParams;
				DownloadParams.push_back(authorCode);
				DownloadParams.push_back(mFinalPath);
//				downloadTh.setParameter(this, DownloadParams, i);
//				downloadTh.start();
			}
			else if ( downRequestNum != 0 )
			{
				FreCont++;
				cout << "FreCont:" << FreCont << endl;
				TempFre = TempFre + FreCont * startFre;
				if (TempFre > 30*60*1000)
				{
					killTimer(m_nTimerId);
				}

				if (m_nTimerId != 0)
				{
					killTimer(m_nTimerId);
					m_nTimerId = startTimer(TempFre);
				}
			}
			else 
			{
				//获取下载链接错误须进行重新登陆授权
				landFlag = false;
				authorFlag = false;
				return;
			}
		}
	}
}

//void ChttpDownload::timerEvent( QTimerEvent *event )
//{
//	//获取链接、下载、授权失败时将重新进行token获取landFlag = false;
//	if ( !landFlag )
//		int landNum = land_module( use_name, pass_key);
//
//	//获取链接、下载失败时重新获取bucketname，authorFlag = false；
//	if ( !authorFlag )
//		int authorNum = author_module();
//
//	for ( int i = 0; i < sizeDown; ++i )
//	{
//		if ( !downLoad[i].isRunning() )
//		{
//			int getPathNum = get_download_filepath_module();
//			int downRequestNum = download_request_module();
//			if ( downRequestNum == 0 && getPathNum == 0 )
//			{
//				vector<QString> DownloadParams;
//				DownloadParams.push_back(authorCode);
//				DownloadParams.push_back(mFinalPath);
//				downLoad[i].setParameter(this, DownloadParams, i);
//				threadNum++;
//				cout << "threadNum:" << threadNum << endl;
//				downLoad[i].start();
//			}
//			else if ( downRequestNum != 0 )
//			{
//				FreCont++;
//				cout << "FreCont:" << FreCont << endl;
//				TempFre = TempFre + FreCont * startFre;
//				if (m_nTimerId != 0)
//				{
//					killTimer(m_nTimerId);
//					m_nTimerId = startTimer(TempFre);
//				}
//			}
//			else 
//			{
//				//获取下载链接错误须进行重新登陆授权
//				landFlag = false;
//				authorFlag = false;
//				return;
//			}
//		}
//	}
//}






void ChttpDownload::isDownloading_DoneSlot( bool doneFlag, int tnum)
{
//	downLoad[tnum].quit();
//	downLoad[tnum].wait();

//	if ( doneFlag )
//		threadNum--;
//	else
		return;
}

void ChttpDownload::isSingleDownloading_DoneSlot( bool doneFlag)
{
//	downloadTh.quit();
//	downloadTh.wait();
	if ( doneFlag )
	{
		mSingleWayDown = true;//整个进程下载完成并停止，而后继续进入timerEvent函数
	}
}

int ChttpDownload::respond_process_status( QString statusName )
{
	QString total_url = company_url + QString("/rest/modelAssign/setModelStatus/") + modelId + "-" + statusName;
	QUrl url1(total_url);
	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(url1);
	QByteArray dataArray;
	dataArray.append(authorCode);
	request->setRawHeader("Authorization",dataArray);
	QNetworkReply *pReplay0 = manager->post(*request, QByteArray());
	QEventLoop loop;
	connect(pReplay0, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	int tnum = respond_process_status_finished(pReplay0);
	return tnum;
}

int ChttpDownload::respond_process_status_finished(QNetworkReply *reply)
{
	int tt = -1;
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	QString replyText = reply->readAll();
	if (reply->error() == QNetworkReply::NoError)
	{
		if ( statusCodeV == 200 )
		{
			tt = 0;
		}
		else
		{
			//error
			;
		}
	}
	else
	{
		//error
		;
	}
	reply->deleteLater();
	return tt;
}
