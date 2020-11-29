/********************************************************************************
** Form generated from reading UI file 'creercandidat.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREERCANDIDAT_H
#define UI_CREERCANDIDAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CreerCandidatClass
{
public:

    void setupUi(QDialog *CreerCandidatClass)
    {
        if (CreerCandidatClass->objectName().isEmpty())
            CreerCandidatClass->setObjectName(QString::fromUtf8("CreerCandidatClass"));
        CreerCandidatClass->resize(400, 300);

        retranslateUi(CreerCandidatClass);

        QMetaObject::connectSlotsByName(CreerCandidatClass);
    } // setupUi

    void retranslateUi(QDialog *CreerCandidatClass)
    {
        CreerCandidatClass->setWindowTitle(QApplication::translate("CreerCandidatClass", "CreerCandidat", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreerCandidatClass: public Ui_CreerCandidatClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREERCANDIDAT_H
