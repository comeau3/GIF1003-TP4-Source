#include "controleurdelisteelectorale.h"

#include <QtGui>
#include <QApplication>
#include "Personne.h"
#include <clocale>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("ISO-8859-1"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("ISO-8859-1"));
    QApplication a(argc, argv);
    ControleurDeListeElectorale w;
    w.show();
    return a.exec();
}
