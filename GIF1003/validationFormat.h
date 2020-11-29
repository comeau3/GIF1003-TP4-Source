/**
 * \file validationFormat.h
 *
 * Déclarations pour les fonctions de validationFormat.cpp
 *
 *  Created on: 30 août 2020
 * \author: Pascal Charpentier
 */

#ifndef VALIDATIONFORMAT_H_
#define VALIDATIONFORMAT_H_

#include <string>
#include <vector>

namespace util
{

/**
 * \var NB_CHAMPS_DATE Constante contenant le nombre de champs d'une date valide: 3 pour jour, mois et année
 */
const size_t NB_CHAMPS_DATE = 3;

const size_t      NB_PARTIS = 5;
const std::string PARTIS_POLITIQUES_FEDERAUX[NB_PARTIS]
{
	"Bloc québécois", "Conservateur", "Indépendant", "Libéral",
	"Nouveau parti démocratique"
};

bool estUneLigneVide(const std::string& p_ligne);
bool validerNas(const std::string& p_nas);
bool validerCodePostal(const std::string& p_code);
bool validerFormatFichier(std::istream& p_is);
bool estUnNom(const std::string& p_ligne);
bool estUnPartiPolitique(const std::string& p_ligne);
bool estUneLettreMajuscule(const char& caractere);
bool validerLeFormatDeLaDate(const std::string& p_ligne);
void extraireLesChampsDeLaDate(const std::string& p_ligne, int champs[NB_CHAMPS_DATE]);
bool estUnEntierPositif(const std::string& p_ligne);

} // namespace util

#endif /* VALIDATIONFORMAT_H_ */
