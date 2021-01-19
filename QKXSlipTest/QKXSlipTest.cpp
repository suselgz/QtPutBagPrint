#include "QKXSlipTest.h"
#pragma execution_character_set("utf-8")
QKXSlipTest::QKXSlipTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_KXSlip = QKXSlipCreateInstance();
	if (m_KXSlip == nullptr)
	{
		QMessageBox::information(nullptr,"info", "dll load error");
	}
	else
	{
		if (m_KXSlip->GetPrintStatus() != 0)
		{
			QMessageBox::information(nullptr, "info", "Printer is not ready!");
		}
	}
	ui.dateEdit_date->setDisplayFormat("yyyy-MM-dd");
	ui.dateEdit_date->setDateTime(QDateTime::currentDateTime());
	ui.dateEdit_date->setCalendarPopup(true);
	ui.lineEdit_QRcode->setText("中国人abc123");
	ui.lineEdit_QBInfo->setText("100");
	ui.lineEdit_FHInfo->setText("张三三");
	ui.lineEdit_FQInfo->setText("李四四");
	int ret = m_KXSlip->GetPrintStatus();
	ret = ret;
}

void QKXSlipTest::on_pushButton_CreateQR_clicked()
{
	QString tempStr = ui.lineEdit_QRcode->text();
	cv::Mat img;
	if (m_KXSlip->GenerateQRcode(tempStr, img))
	{
		cv::imshow("二维码", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "GenerateQRcode Failed");
	}
}

void QKXSlipTest::on_pushButton_PrePrint_clicked()
{
	cv::Mat img;
	if (m_KXSlip->PrePrint(img))
	{
		cv::imshow("打印预览", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "PrePrint Failed");
	}
}

void QKXSlipTest::on_pushButton_Print_clicked()
{
	if (m_KXSlip->Print())
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is OK!");
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is NOT!");
	}
}

void QKXSlipTest::on_pushButton_CreateFQ_clicked()
{
	SLIP_PRINT_INFO print_info;
	print_info.QRStr = ui.lineEdit_QRcode->text();
	print_info.QBInfo = ui.lineEdit_QBInfo->text();
	QString str = ui.dateEdit_date->text();
	QString date = QString("%1年%2月%3日").arg(str.mid(0, 4)).arg(str.mid(5, 2)).arg(str.mid(8, 2));
	print_info.date = date;
	print_info.FHInfo = ui.lineEdit_FHInfo->text();
	print_info.FHInfo2 = ui.lineEdit_FHInfo2->text();
	print_info.FQInfo = ui.lineEdit_FQInfo->text();

	QString modelPath = "../params/model.bmp";
	QString printPath = "../params/print.bmp";
	m_KXSlip->SetPath(modelPath, printPath);
	cv::Mat img;
	int bRet = m_KXSlip->GenerateSlipInfo(print_info, img);
	if (bRet < 0)
	{
		QString msg;
		m_KXSlip->GetLastMsg(bRet, msg);
	}
	else
	{
		cv::imshow("SlipImg", img);
	}

}