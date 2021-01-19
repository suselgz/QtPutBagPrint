#define KX_KXSLIP_CREATE_MAIN_VERSION 1
#define KX_KXSLIP_CREATE_SUB_VERSION 1
#define KX_KXSLIP_CREATE_VERSION ((KX_KXSLIP_CREATE_MAIN_VERSION << 16) + KX_KXSLIP_CREATE_SUB_VERSION)
#pragma once
#include <QObject>
#include "opencv2/opencv.hpp"
enum PRODECT_COUPONS_
{
	One_yuan = 1,
	Five_yuan = 5,
	Ten_yuan = 10,
	Twenty_yuan = 20,
	Fifty_yuan = 50,
	One_hundred_yuan = 100
};
enum GENERATE_ERR_
{
	GenerateSlip_OK = 0,           //创建成功
	GenerateQRcode_failed = -1,    //生成二维码失败
	CreateSlipInfo_failed = -2,    //生成封签的信息失败
	Save_image_failed = -3,        //生成的封签保存到本地失败
	Load_ModelImg_failed = -4,      //加载模板图像失败
	Create_FQimg_failed = -5        //生成封签图像失败
};
struct SLIP_PRINT_INFO
{
	QString QRStr;//QR码内容
	QString QBInfo;//券别
	QString date;  //日期
	QString FHInfo;//复核人员
	QString FHInfo2;//复核人员2
	QString FQInfo;//封签人员
};
#define CODE_LIB_SOLUTION
#ifdef CODE_LIB_SOLUTION
#define CODE_LIB_EXPORT __declspec(dllexport)
#else
#define CODE_LIB_EXPORT __declspec(dllimport)
#endif

class   QKXSlipCreate : public QObject
{
	Q_OBJECT
public:
	virtual void GetLastMsg(int type, QString& Msg) = 0;
	virtual void SetPath(QString model_path,QString print_path)=0;
	virtual void GetPath(QString& model_path, QString& print_path)=0;
	virtual bool GenerateQRcode(QString QRtempstr, cv::Mat& img)=0;
	virtual int GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img)=0;
	virtual bool PrePrint(cv::Mat& img)=0;
	virtual bool Print()=0;
	virtual int GetPrintStatus(void) = 0;
};
CODE_LIB_EXPORT QKXSlipCreate * _stdcall QKXSlipCreateInstance(int version = KX_KXSLIP_CREATE_VERSION);