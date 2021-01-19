#include "QtBQPrint.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtBQPrint w;
	w.show();
	return a.exec();
}
