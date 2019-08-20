#include "win_main.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	win_main w;
	w.show();
	return a.exec();
}
