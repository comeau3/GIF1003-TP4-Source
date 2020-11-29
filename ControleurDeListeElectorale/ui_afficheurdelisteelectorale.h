/********************************************************************************
** Form generated from reading UI file 'afficheurdelisteelectorale.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AFFICHEURDELISTEELECTORALE_H
#define UI_AFFICHEURDELISTEELECTORALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_afficheurDeListeElectoraleClass
{
public:

    void setupUi(QWidget *afficheurDeListeElectoraleClass)
    {
        if (afficheurDeListeElectoraleClass->objectName().isEmpty())
            afficheurDeListeElectoraleClass->setObjectName(QString::fromUtf8("afficheurDeListeElectoraleClass"));
        afficheurDeListeElectoraleClass->resize(400, 300);

        retranslateUi(afficheurDeListeElectoraleClass);

        QMetaObject::connectSlotsByName(afficheurDeListeElectoraleClass);
    } // setupUi

    void retranslateUi(QWidget *afficheurDeListeElectoraleClass)
    {
        afficheurDeListeElectoraleClass->setWindowTitle(QApplication::translate("afficheurDeListeElectoraleClass", "afficheurDeListeElectorale", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class afficheurDeListeElectoraleClass: public Ui_afficheurDeListeElectoraleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AFFICHEURDELISTEELECTORALE_H
