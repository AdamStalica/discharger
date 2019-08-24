#include "win_main.h"
#include <QtWidgets/QApplication>


/*
	GUI TODO:

		- widget new speedway
		- widget new race
		- widget new log info
		- widget add new logs
		- widget log in 
		- widget start simulation

	LOG TODO:
		- connection to the api
		- 
*/



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	win_main w;
	w.show();
	return a.exec();
}