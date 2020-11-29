/********************************************************************************
** Form generated from reading UI file 'creerelecteur.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREERELECTEUR_H
#define UI_CREERELECTEUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CreerElecteurClass
{
public:

    void setupUi(QDialog *CreerElecteurClass)
    {
        if (CreerElecteurClass->objectName().isEmpty())
            CreerElecteurClass->setObjectName(QString::fromUtf8("CreerElecteurClass"));
        CreerElecteurClass->resize(400, 300);

        retranslateUi(CreerElecteurClass);

        QMetaObject::connectSlotsByName(CreerElecteurClass);
    } // setupUi

    void retranslateUi(QDialog *CreerElecteurClass)
    {
        CreerElecteurClass->setWindowTitle(QApplication::translate("CreerElecteurClass", "CreerElecteur", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreerElecteurClass: public Ui_CreerElecteurClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREERELECTEUR_H
