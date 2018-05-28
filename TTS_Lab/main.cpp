#include "TTS_Lab.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TTS_Lab w;
	w.show();
	return a.exec();
}
