/********************************************************************************
** Form generated from reading UI file 'desinscrireelecteur.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESINSCRIREELECTEUR_H
#define UI_DESINSCRIREELECTEUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DesinscrireElecteurClass
{
public:

    void setupUi(QDialog *DesinscrireElecteurClass)
    {
        if (DesinscrireElecteurClass->objectName().isEmpty())
            DesinscrireElecteurClass->setObjectName(QString::fromUtf8("DesinscrireElecteurClass"));
        DesinscrireElecteurClass->resize(400, 300);

        retranslateUi(DesinscrireElecteurClass);

        QMetaObject::connectSlotsByName(DesinscrireElecteurClass);
    } // setupUi

    void retranslateUi(QDialog *DesinscrireElecteurClass)
    {
        DesinscrireElecteurClass->setWindowTitle(QApplication::translate("DesinscrireElecteurClass", "DesinscrireElecteur", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DesinscrireElecteurClass: public Ui_DesinscrireElecteurClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESINSCRIREELECTEUR_H
