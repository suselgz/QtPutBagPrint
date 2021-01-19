#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtBQPrint.h"
#include "QKXSlipCreate.h"
#include <QLibrary>
#include <windows.h>
class QtBQPrint : public QMainWindow
{
	Q_OBJECT

public:
	QtBQPrint(QWidget *parent = Q_NULLPTR);
	public slots:
	void on_pushButton_CreateQR_clicked();
	void on_pushButton_PrePrint_clicked();
	void on_pushButton_Print_clicked();
	void on_pushButton_CreateFQ_clicked();
	void on_pushButton_Test_clicked();
private:
	Ui::QtBQPrintClass ui;
	QKXSlipCreate* m_Slip;
	QLibrary *m_tscdll;
};
