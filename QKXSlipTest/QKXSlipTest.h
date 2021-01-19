#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QKXSlipTest.h"
#include "QKXSlipCreate.h"
#include <QMessageBox>
class QKXSlipTest : public QMainWindow
{
	Q_OBJECT

public:
	QKXSlipTest(QWidget *parent = Q_NULLPTR);
	public slots:
	void on_pushButton_CreateQR_clicked();
	void on_pushButton_PrePrint_clicked();
	void on_pushButton_Print_clicked();
	void on_pushButton_CreateFQ_clicked();
private:
	Ui::QKXSlipTestClass ui;
	QKXSlipCreate* m_KXSlip;
};
