/********************************************************************************
** Form generated from reading UI file 'controleurdelisteelectorale.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLEURDELISTEELECTORALE_H
#define UI_CONTROLEURDELISTEELECTORALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControleurDeListeElectoraleClass
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ControleurDeListeElectoraleClass)
    {
        if (ControleurDeListeElectoraleClass->objectName().isEmpty())
            ControleurDeListeElectoraleClass->setObjectName(QString::fromUtf8("ControleurDeListeElectoraleClass"));
        ControleurDeListeElectoraleClass->resize(800, 600);
        centralwidget = new QWidget(ControleurDeListeElectoraleClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ControleurDeListeElectoraleClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ControleurDeListeElectoraleClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ControleurDeListeElectoraleClass->setMenuBar(menubar);
        statusbar = new QStatusBar(ControleurDeListeElectoraleClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ControleurDeListeElectoraleClass->setStatusBar(statusbar);

        retranslateUi(ControleurDeListeElectoraleClass);

        QMetaObject::connectSlotsByName(ControleurDeListeElectoraleClass);
    } // setupUi

    void retranslateUi(QMainWindow *ControleurDeListeElectoraleClass)
    {
        ControleurDeListeElectoraleClass->setWindowTitle(QApplication::translate("ControleurDeListeElectoraleClass", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControleurDeListeElectoraleClass: public Ui_ControleurDeListeElectoraleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLEURDELISTEELECTORALE_H
