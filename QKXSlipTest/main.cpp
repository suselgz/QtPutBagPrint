#include "QKXSlipTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QKXSlipTest w;
	w.show();
	return a.exec();
}
