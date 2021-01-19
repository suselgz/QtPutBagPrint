#pragma once
//#include <QObject>
#include "qrcode/qrencode.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QRectF>
#include <QImage>
#include <QPixmap>
#include <QLibrary>
#include "QKXSlipCreate.h"
#pragma comment(lib,"winmm.lib")
#include <windows.h>
#include<fstream>
#include<iostream>


class QSlipCreate : public QKXSlipCreate
{
	Q_OBJECT

public:
	QSlipCreate();
	~QSlipCreate();
	void GetLastMsg(int type, QString& Msg);
	void SetPath(QString model_path, QString print_path);
	void GetPath(QString& model_path, QString& print_path);
	bool GenerateQRcode(QString QRtempstr,cv::Mat& img);
	int GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img);
	bool PrePrint(cv::Mat& img);
	bool Print();
	int GetPrintStatus(void);
	bool LoadDllStatus(void);
private:
	void putTextZH(cv::Mat &dst, const char* str, cv::Point org, cv::Scalar color, int fontSize,
		const char *fn = "Arial", bool italic = false, bool underline = false);
	bool save_bmp_image(const  cv::Mat img, std::string dst);
	int  mat_to_binary(const  cv::Mat img, int  line_byte, char * data);
	QString m_modelPath;
	QString m_printPath;
	cv::Mat m_modelImg;
	cv::Mat m_QRmat;
	cv::Mat m_SlipImg;
	QLibrary *m_tscdll;
	bool m_bDllIsLoad;
};
