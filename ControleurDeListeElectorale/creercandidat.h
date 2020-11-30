#ifndef CREERCANDIDAT_H
#define CREERCANDIDAT_H

#include <QtGui>
#include "Candidat.h"
#include "creerpersonne.h"



class CreerCandidat : public CreerPersonne
{



public:

    CreerCandidat(QWidget *parent = 0);
    ~CreerCandidat();

    void actualiserSaisies();
    void clicBoutonSoumettre();

    elections::Personne* reqPersonne(); // Cette méthode permet à l'appelant de récupérer l'objet créé

    elections::PartisPolitiques partiAccepte;

    QLabel* partiBanniere;
    QComboBox* partiSaisie;


};



#endif // CREERCANDIDAT_H
