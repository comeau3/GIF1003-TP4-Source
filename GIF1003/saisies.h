/**
 * \file saisies.h
 *
 *  \brief Déclaration des fonctions utilitaires permettant la validation de saisies à la console.
 *
 *  Created on: Oct 6, 2020
 * \author Pascal Charpentier
 * \version 0.1
 */

#ifndef SAISIES_H_
#define SAISIES_H_

#include <string>
#include "Adresse.h"
#include "Date.h"
#include "Personne.h"
#include "Electeur.h"
#include "Candidat.h"

std::string saisirAvecInvite(const std::string& invite);

unsigned int saisirNumeroCivic();
std::string saisirLigneNonVideAvecInvite(const std::string& invite);
long saisirEntierValideAvecInvite(const std::string& p_invite);
std::string mettreEnMajuscules(std::string p_saisie);
std::string saisirCodePostal();
util::Adresse saisirAdresseValide();

bool estUnMoisValide(long p_mois);
bool estUneAnneeValide(long p_annee);
bool estUnJourValide(long p_jour);
long saisirJourValide();
long saisirMoisValide();
long saisirAnneeValide();
util::Date saisirDateValide();
util::Date saisirDateFormatteeValide();

std::string saisirNasValide();
elections::Electeur saisirPersonneValide();
elections::Candidat saisirCandidatValide();


#endif /* SAISIES_H_ */
