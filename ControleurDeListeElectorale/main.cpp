#include "controleurdelisteelectorale.h"

#include <QtGui>
#include <QApplication>
#include "Personne.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControleurDeListeElectorale w;
    w.show();
    return a.exec();
}
