/**
 * \file validationFormat.cpp
 *
 * \brief Contient des fonctions auxiliaires servant à valider certaines entrées.
 *
 * Les fonctions destinées à être utilisées par des modules externes sont:
 *
 * validerNas: Accepte un argument de type const string, et retourne un bool.
 *             Il s'agit d'un validateur de numéro d'assurance sociale.
 *             Retourne true si l'argument est de la forme "xxx xxx xxx" où
 *             x est un chiffre de 0 à 9.
 *
 * validerFormatFichier: Accepte un argument de type istream, et retourne bool.
 *             Il s'agit d'un validateur de format pour un flux d'entrée.
 *             Ce flux doit être formé de lignes successives séparées par des
 *             '\n'.  Voir la description détaillée de la fonction.
 *
 *
 *
 *  Created on: 29 août 2020
 *  \version 0.1
 *  \author: Pascal Charpentier NI: 111283256
 */

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>

#include "validationFormat.h"

using namespace std;

/**
 * \namespace util
 *
 * Espace de noms contenant des fonctions de validations de saisies et les
 * classes permettant de représenter une date valide et une adresse valide canadienne.\n
 *
 * classe Adresse
 *
 * classe Date
 *
 * bool validerFormatFichier(istream& p_is): Validateur de fichier de données
 * électorales
 *
 * bool validerNas(const std::string& p_nas): Validateur de numéro d'assurance sociale
 *
 */

namespace util
{

/****************************************************************************//**
 * Constantes pour la validation des adresses
 *
 *//****************************************************************************/

static const std::string::size_type LONGUEUR_CODE_POSTAL = 7;

static const std::size_t NB_PROVINCES_TERRITOIRES = 13;

static const std::string PROVINCES_TERRITOIRES_FR[NB_PROVINCES_TERRITOIRES] = { "Colombie-Britannique", "Alberta", "Saskatchewan", "Manitoba",
		"Ontario", "Québec", "Nouveau-Brunswick", "Nouvelle-Écosse", "Ile du Prince Édouard", "Terre-Neuve", "Nunavut", "Yukon",
		"Territoires du Nord-Ouest" };

/***************************************************************************//**
 * Constantes pour la validation des partis politiques
 *//****************************************************************************/



/****************************************************************************//**
 * Constantes pour la validation des numéros d'assurance sociale
 *//****************************************************************************/

static const string::size_type LONGUEUR_CHAINE_NAS = 11;
static const unsigned int      NB_CHIFFRES_NAS = 9;
static const string::size_type INDEX_PREMIER_SEPARATEUR_NAS = 3;
static const string::size_type INDEX_SECOND_SEPARATEUR_NAS = 7;

/****************************************************************************//**
 * Constantes pour la validation des dates
 *//****************************************************************************/

static const size_t            INDEX_JOUR = 0;
static const size_t            INDEX_MOIS = 1;
static const size_t            INDEX_ANNEE = 2;

static const int               JOUR_MIN = 1;
static const int               JOUR_MAX = 31;
static const int               MOIS_MIN = 1;
static const int               MOIS_MAX = 12;
static const int               ANNEE_MIN = 1900;
static const int               ANNEE_MAX = 2020;

/****************************************************************************//**
 * Constantes pour la validation des blocs de données personnelles
 *//****************************************************************************/

static const size_t MAX_CHAR = 100;
static const size_t NB_LIGNES_BLOC = 4;
static const size_t INDEX_DATE = 2;

/******************************************************************************
 * Liste des fonctions et leurs déclarations
 *****************************************************************************/

// ** Validation d'un flux d'entrée

bool validerFormatFichier(istream& p_is); // **** POUR CORRECTION: LIGNE 148 ****

// Validation des lignes et sections d'un flux d'entrée

bool validerProchaineLigneEstUnNom(istream& p_is);
bool validerProchaineLigneEstUnParti(istream& p_is);
bool validerProchaineLigneEstUnNas(istream& p_is);
bool validerProchainBlocEstComplet(istream& p_is);

// Identification du format d'une ligne donnée


bool estUnNom(const string& p_ligne);

// Validation d'une ligne individuelle pour un format donné

bool validerNas(const string& p_nas);  // **** POUR CORRECTION: LIGNE 410 ****

bool validerProvinceOuTerritoire(const std::string& p_province);
bool validerDate(const string& p_ligne);

// Analyse et validation d'un numéro d'assurance sociale

bool validerLeFormatDuNas(const string& p_nas);
void extraireLesChiffresDuNas(const string& p_nas, unsigned int p_chiffres[NB_CHIFFRES_NAS]);
bool validerLesChiffresDuNas(const unsigned int p_chiffres[NB_CHIFFRES_NAS]);

// Analyse et validation d'une date



bool validerLesChampsDeLaDate(const int champs[NB_CHAMPS_DATE]);

// Validation d'un caractère séparateur

bool estUnSeparateurPermis(const char caractere);

/****************************************************************************//**
* \brief Vérifie un flux de données pour voir s'il se conforme au format suivant:
*
*        ligne 1: Nom de circonscription non-vide
*        ligne 2: Parti politique valide
*        ligne 3: Numéro d'assurance sociale valide
*        ligne 4: Nom non-vide
*        ligne 5: Prénom non-vide
*        ligne 6: Date de naissance valide
*        ligne 7: adresse non-vide
*        + blocs subséquents
*
*        Les blocs subséquents peuvent être de type électeur ou candidat:
*        Les blocs électeurs comprennent les lignes de 3 à 7
*        Les blocs candidats comprennent les lignes de 2 à 7
*
*        Un bloc doit être présent en intégralité pour que le fichier soit valide.
*
* \param[in] p_is flux d'entrée
*
* \return true si le flux est conforme, false autrement.
*
*//******************************************************************************/

bool validerFormatFichier(istream& p_is)
{
	bool valide = true;
	char tampon[MAX_CHAR];
	string ligneCourante;

	valide = validerProchaineLigneEstUnNom(p_is) && validerProchaineLigneEstUnParti(p_is) &&
			 validerProchaineLigneEstUnNas(p_is) && validerProchainBlocEstComplet(p_is);

	while ( valide && p_is.getline(tampon, MAX_CHAR) )
	{
		ligneCourante = tampon;
		if (estUnPartiPolitique(ligneCourante))
		{
			valide = ( validerProchaineLigneEstUnNas(p_is) && validerProchainBlocEstComplet(p_is) );
		}
		else if (validerNas(ligneCourante))
		{
			valide = validerProchainBlocEstComplet(p_is);
		}
		else
		{
			valide = false;
		}
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie si la prochaine ligne d'un flux d'entrée contient des données.
 *
 * \param[in] p_is flux d'entrée
 *
 * \return true si la prochaine ligne saisie du flux est non-vide et n'est ni
 *         un numéro d'assurance sociale, ni un parti politique
 *
 *//*****************************************************************************/

bool validerProchaineLigneEstUnNom(istream& p_is)
{
	bool valide = true;
	char tampon[MAX_CHAR];
	string ligneCourante;

	if (!p_is.getline(tampon, MAX_CHAR))
	{
		valide = false;
	}
	else
	{
		ligneCourante = tampon;
		valide = estUnNom(ligneCourante);
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie que la prochaine ligne d'un flux d'entrée représente un des
 *        partis politiques prédéfinis.
 *
 * \param[in] p_is flux d'entrée
 *
 * \return true si la prochaine ligne du flux est un parti.
 *
 *//*****************************************************************************/

bool validerProchaineLigneEstUnParti(istream& p_is)
{
	bool valide = true;
	char tampon[MAX_CHAR];
	string ligneCourante;

	if (!p_is.getline(tampon, MAX_CHAR))
	{
		valide = false;
	}
	else
	{
		ligneCourante = tampon;
		valide = estUnPartiPolitique(ligneCourante);
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie si la prochaine ligne disponible d'un flux d'entrée contient
 *        un numéro d'assurance sociale valide.
 *
 * \param[in] p_is flux d'entrée
 *
 * \return true si la prochaine ligne est un numéro d'assurance sociale.
 *
 *//*****************************************************************************/

bool validerProchaineLigneEstUnNas(istream& p_is)
{
	bool valide = true;
	char tampon[MAX_CHAR];
	string ligneCourante;

	if (!p_is.getline(tampon, MAX_CHAR))
	{
		valide = false;
	}
	else
	{
		ligneCourante = tampon;
		valide = validerNas(ligneCourante);
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie que les quatre prochaines lignes d'un flux d'entrée sont
 *        non-vides, et que la troisième contient une date valide.
 *
 * \param[in] p_is flux d'entrée
 *
 * \return true si les quatres lignes sont non-vides et la troisième une date
 *
 *//*****************************************************************************/

bool validerProchainBlocEstComplet(istream& p_is)
{
	bool valide = true;
	char tampon[MAX_CHAR];
	string ligneCourante = "";

	for (size_t i = 0; valide && (i < NB_LIGNES_BLOC); ++i)
	{
		if (!p_is.getline(tampon, MAX_CHAR))
		{
			valide = false;
		}
		if (valide)
		{
			ligneCourante = tampon;
			if (i == INDEX_DATE)
			{
				valide = validerDate(ligneCourante);
			}
			else
			{
				valide = estUnNom(ligneCourante);
			}
		}
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie si une chaîne de caractère est vide, ou ne contient que des espaces
 *
 * \param [in] p_ligne: Chaîne de caractères à vérifier
 *
 * \return bool: true si la chaîne est vide ou ne contient que des espaces ou des tabs.
 *
 *//*****************************************************************************/

bool estUneLigneVide(const string& p_ligne)
{
	bool vide = true;
	string::size_type longueur = p_ligne.size();

	if (longueur != 0)
	{
		for (string::size_type i = 0; vide and (i < longueur); ++i)
		{
			vide = isspace(p_ligne[i]);
		}
	}
	return vide;
}

/****************************************************************************//**
 *
 * \brief Vérifie si une chaîne de caractères contient un des noms de partis politiques.
 *
 *  Les partis politiques fédéraux sont les chaînes prédéfinies suivantes:
 *  BLOC_QUEBECOIS
 *  LIBERAL
 *  CONSERVATEUR
 *  INDEPENDANT
 *  NOUVEAU_PARTI_DEMOCRATIQUE
 *
 *  \return bool true si la chaîne correspond à une des chaînes prédéfinies
 *
 *//****************************************************************************/

bool estUnPartiPolitique(const string& p_ligne)
{
	bool estUnParti = false;

	for (size_t i = 0; !estUnParti && (i < NB_PARTIS); ++i)
	{
		estUnParti = (p_ligne == PARTIS_POLITIQUES_FEDERAUX[i]);
	}
	return estUnParti;
}

/****************************************************************************//**
 *
 * \brief Vérifie si une ligne contient un nom de famille
 *
 * Pour l'instant, ne fait que vérifier que la ligne soit non-vide, et ne soit pas constituée d'une NAS
 * ou d'un nom de parti.
 *
 * \param[in] p_ligne Chaîne de caractères à tester
 *
 * \return bool true si la chaîne peut représenter un nom
 *
 *//*****************************************************************************/

bool estUnNom(const string& p_ligne)
{
	return !estUneLigneVide(p_ligne) and
		   !estUnPartiPolitique(p_ligne) and
		   !validerNas(p_ligne) and
		   !validerDate(p_ligne);
}

/****************************************************************************//**
 *
 * \brief Vérifie si une chaîne contient un numéro valide d'assurance sociale.
 *
 * Pour être valide, la chaîne doit contenir exactement 9 chiffres, par groupes de 3, séparés par un
 * espace ou un tiret.  Elle doit donc contenir 11 caractères exactement.
 * Aucun autre caractère n'est toléré.
 * \n
 * Exemples de chaînes valides:\n
 * ---------------------------\n
 * \n
 * 245 367 996\n
 * 245-367-996\n
 * 245 367-996\n
 * \n
 * Exemples de chaînes invalides:\n
 * -----------------------------\n
 * \n
 * 245367996\n
 * 245.367.996\n
 * -----245-367-996-\n
 * 2   45 3    67 9   9  6\n
 * 245 367 99 -> Seulement 8 chiffres\n
 * 245 367 996a -> Présence d'une lettre\n
 * 245r367 996 -> Présence d'une lettre\n
 * 245 367 9965 -> 10 chiffres.\n
 * \n
 * Les 9 chiffres doivent vérifier l'algorithme de validation suivant:
 * \n
 *
 * \param[in] p_nas (string) Chaîne de caractères à valider.
 * \return (bool) true si la chaîne est un NAS valide. Sinon false.
 *
 *//*****************************************************************************/

bool validerNas(const string& p_nas)
{
    bool valide = false;
	unsigned int chiffres[NB_CHIFFRES_NAS];

    if (validerLeFormatDuNas(p_nas))
    {
    	extraireLesChiffresDuNas(p_nas, chiffres);
    	valide = validerLesChiffresDuNas(chiffres);
    }
    return valide;
}

/****************************************************************************//**
 * Vérifier si un objet string est au format d'un code postal canadien.
 *
 * \param[in] p_code un objet string à tester.
 *
 * \return true si la chaîne contient 7 caractères de la forme suivante:
 * LDL DLD ou D est un chiffre et L est une lettre majuscule.
 *
 *//****************************************************************************/

bool validerCodePostal(const std::string& p_code)
{
    bool valide = (p_code.size() == LONGUEUR_CODE_POSTAL);

    for (std::string::size_type i = 0; valide and i < LONGUEUR_CODE_POSTAL; ++i)
    {
    	if (i == 3)
    	{
    		valide = (p_code[i] == ' ');
    	}
    	else if ((i == 1) or (i == 4) or (i == 6))
    	{
    		valide = isdigit(p_code[i]);
    	}
    	else
    	{
    		valide = estUneLettreMajuscule(p_code[i]);
    	}
    }
   return valide;
}

/****************************************************************************//**
 * Vérifier si un objet string contient le nom d'une province ou d'un territoire
 * canadien, en version française.
 *
 * \param[in] p_province un objet string à tester.
 *
 * \return true si la chaîne contient un des noms définis dans la constante
 * PROVINCES_TERRITOIRES_FR.
 *
 *//****************************************************************************/

bool validerProvinceOuTerritoire(const std::string& p_province)
{
	bool valide = false;

	for (size_t i = 0; !valide and (i < NB_PROVINCES_TERRITOIRES); ++i)
	{
		valide = (p_province == PROVINCES_TERRITOIRES_FR[i]);
	}
	return valide;
}


/****************************************************************************//**
 *
 * \brief Vérifie qu'une chaîne de caractère soit une date plausible au format
 * JJ MM AAAA.
 *
 * Chaînes valides:\n
 * ---------------\n
 * \n
 * 01 01 1921\n
 * 03 04 2019\n
 * 28 11 1978\n
 * \n
 * Chaînes non-valides:\n
 * -------------------\n
 * \n
 * a01 01 1921 (Présence de caractères alphabétiques)\n
 * 32 11 1922 (date du jour invraisemblable)\n
 * 01 15 1932 (mois invraisemblable)\n
 * 01 02 2845 (année invraisemblable)\n
 * 1 2 1923 (format non respecté, il faut 2 chiffres pour chaque champs)\n
 * 01  03 1965 (format non-respecté, trop d'espaces)\n
 *
 * \param[in] p_ligne Chaîne de caractères à tester
 *
 * \return bool true si c'est une date au format attendu avec des valeurs admissibles
 *
 *//***************************************************************************/

bool validerDate(const string& p_ligne)
{
	bool valide = false;
	int champs[NB_CHAMPS_DATE];

	if (validerLeFormatDeLaDate(p_ligne))
	{
		extraireLesChampsDeLaDate(p_ligne, champs);
		valide = validerLesChampsDeLaDate(champs);
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Vérifie que la chaîne p_nas est formée de 3 groupes de 3 chiffres séparées d'un seul espace ou tiret.
 *
 * Conditions de validation:\n
 * ========================\n
 * La chaîne doit avoir exactement 11 caractères\n
 * Elle ne peut contenir que des chiffres, des espaces ou des tirets.\n
 * Les espaces ou les tirets ne peuvent occuper que les positions 3 et 6.  Il y en a donc exactement 2.  Tous les
 * autres caractères sont des chiffres.\n
 * \n
 * Les chaînes suivantes sont donc valides:\n
 * ---------------------------------------\n
 * 123 456 789\n
 * 000 000 000\n
 * 333-444-555\n
 * \n
 * Les chaînes suivantes ne sont pas valides:\n
 * -----------------------------------------\n
 * 1 23 456 789\n
 * 123456789\n
 *        123 456 789\n
 * 123e456t789\n
 *
 * \param[in] p_nas:  Chaîne de caractères à tester
 *
 * \return    bool: true si la chaîne est au format voulu, sinon false.
 *
 *//*****************************************************************************/

bool validerLeFormatDuNas(const string& p_nas)
{
	bool valide = true;
	string::size_type longueur = p_nas.size();

	if (longueur != LONGUEUR_CHAINE_NAS)
		valide = false;

	for (string::size_type i = 0; valide && (i < longueur); ++i )
	{
		if ( (i == INDEX_PREMIER_SEPARATEUR_NAS) or (i == INDEX_SECOND_SEPARATEUR_NAS) )
		{
			valide = estUnSeparateurPermis(p_nas[i]);
		}
		else
		{
			valide = isdigit(p_nas[i]);
		}
	}
	return valide;
}

/****************************************************************************//**
 *
 * \brief Extrait les chiffres d'une chaîne préalablement validée par la fonction valideLeFormatDuNas
 *        et les place dans un tableau.
 *
 * \param[in] p_nas: La chaîne contenant les 9 chiffres du NAS
 *
 * \param[out] p_chiffres: Tableau contenant les 9 chiffres extraits de la chaîne
 *
 * \pre p_nas doit absolument être au format xxx xxx xxx où x est un chiffre
 *
 * \exception runtime_error si on n'a as extrait exactement 9 chiffres de p_nas
 *
 *//*****************************************************************************/

void extraireLesChiffresDuNas(const string& p_nas, unsigned int p_chiffres[NB_CHIFFRES_NAS])
{
	string::size_type longueur = p_nas.size();
	string::size_type index = 0;

	for (string::size_type i = 0; i < longueur; ++i)
	{
		if (isdigit(p_nas[i]))
		{
			p_chiffres[index] = static_cast<unsigned int> (p_nas[i] - '0');
			++index;
		}
	}

	// Le cas suivant ne doit jamais se produire si la chaîne a été préalablement
	// validée avec validerLeFormatDuNas().

	assert (index == NB_CHIFFRES_NAS);
}

/****************************************************************************//**
 *
 * \brief Vérifie si les neuf chiffres d'un NAS obéissent à la formule de validation
 *
 * La formule de validation est donnée [ici](http://fr.wikipedia.org/wiki/Num%C3%A9ro_d%27assurance_sociale)
 *
 * \param p_chiffres: Tableau contenant les chiffres sous forme d'entiers non-signés
 *
 * \return bool: true si les neuf chiffres obéissent à la formule, false sinon.
 *
 *//*****************************************************************************/

bool validerLesChiffresDuNas(const unsigned int p_chiffres[NB_CHIFFRES_NAS])
{
	unsigned int somme = 0;

	for (string::size_type i = 0; i < NB_CHIFFRES_NAS; ++i)
	{
		// Formule de validation de Wikipedia

		somme += ( (i % 2) ?  (2 * p_chiffres[i] - 9 * (p_chiffres[i] / 5)) : p_chiffres[i] );
	}

	// La somme obtenue doit être divisible par 10

	return !(somme % 10);

}

/***************************************************************************//**
 *
 * \brief Vérifie qu'une chaîne de caractères soit constituée d'un jour, un mois et une année
 *
 * La chaîne entrée doit être au format JJ MM AAAA où J, M et A sont des chiffres.
 * Les groupes doivent être séparés par des espaces ou des tirets.
 *
 * Chaînes valides:\n
 * ---------------\n
 *
 * 12-34-5675\n
 * 34-87 1992\n
 * 02 04 5676\n
 *
 * Chaînes non-valides:\n
 * -------------------\n
 *
 * 123 5 6778\n
 * 1 234 2343\n
 * 12 34 54652\n
 * 23  45  6765\n
 * 12w34r5676\n
 *
 * \param p_ligne Chaîne de caractères à contrôler
 *
 * \return bool true si la date est au format JJ MM AAAA
 *
 *//*****************************************************************************/

bool validerLeFormatDeLaDate(const string& p_ligne)
{
	bool valide = true;

	stringstream os(p_ligne);
	string jour;
	string mois;
	string annee;

	valide = getline(os, jour, ' ') and getline(os, mois, ' ') and getline(os, annee) ;

	if (valide)
	{
		valide = estUnEntierPositif(jour) and estUnEntierPositif(mois) and estUnEntierPositif(annee);
	}
	return valide;
}

/***************************************************************************//**
 *
 * \brief Extrait les infos de jour, mois et année d'une chaîne de caractère
 *
 * Convertit une chaîne de caractère en tableau de 3 entiers qui contient les informations
 * suivantes:\n
 * [0]: date du jour\n
 * [1]: numéro du mois\n
 * [2]: année à quatre chiffres\n
 *
 * \param[in]  p_ligne   Chaîne de caractères à convertir
 * \param[out] champs Tableau contenant les informations
 *
 * \pre La chaîne p_ligne doit absolument être au format JJ MM AAAA
 *
 * \exception invalid_argument Si la chaîne n'est pas au format stipulé et contient des
 *            caractères non-numériques
 *//*****************************************************************************/

void extraireLesChampsDeLaDate(const string& p_ligne, int champs[NB_CHAMPS_DATE])
{
	stringstream flux;
	string donneeBrute;

	flux << p_ligne;

	for (size_t i = 0; i < NB_CHAMPS_DATE; ++i)
	{
		flux >> donneeBrute;
		champs[i] = stoi(donneeBrute);
	}
}

/****************************************************************************//**
 *
 * \brief Vérifie que les informations d'une date soient dans des ranges acceptables
 *
 * Le jour doit être compris entre 1 et 31, le mois entre 1 et 12 et l'année entre
 * 1900 et 2020.
 *
 * \param[in] champs Tableau contenant 3 entiers: jour - mois - année
 *
 * \return bool true si le 1<jour<31, 1<mois<12, 1900<année<2020
 *
 * \pre Le tableau champs doit être initialisé et contenir trois entiers.
 *
 *//*****************************************************************************/

bool validerLesChampsDeLaDate(const int champs[NB_CHAMPS_DATE])
{
	bool valide = true;

	if ( (champs[INDEX_JOUR] < JOUR_MIN) or (champs[INDEX_JOUR] > JOUR_MAX) )
	{
		valide = false;
	}
	else if ( (champs[INDEX_MOIS] < MOIS_MIN) or (champs[INDEX_MOIS] > MOIS_MAX) )
	{
			valide = false;
	}
	else if ( (champs[INDEX_ANNEE] < ANNEE_MIN) or (champs[INDEX_ANNEE] > ANNEE_MAX) )
	{
		    valide = false;
	}
	return valide;
}

/****************************************************************************//**
 * Vérifie qu'une chaîne de caractères ne contient que des chiffres
 *
 * \param[in] p_ligne la chaîne de caractères à tester
 *
 * \return true si p_ligne est non-vide et ne contient que des chiffres
 *
 *//****************************************************************************/

bool estUnEntierPositif(const std::string& p_ligne)
{
  return !p_ligne.empty() && std::all_of(p_ligne.begin(), p_ligne.end(), ::isdigit);
}

/****************************************************************************//**
 *
 * \brief vérifie qu'un caractère est un espace ou un tiret
 *
 * \param[in] caractere le caractère à vérifier
 *
 * \return true si le caractère est un espace ou un tiret
 *
 *//****************************************************************************/

bool estUnSeparateurPermis(const char caractere)
{
	return ( (caractere == ' ') or (caractere == '-') );
}

/****************************************************************************//**
 * Vérifie si un caractère représente une lettre majuscule
 *
 * \param[in] caractere Le caractère à vérifier
 *
 * \return true si le caractère est une lettre et majuscule.
 *
 *//*****************************************************************************/

bool estUneLettreMajuscule(const char& caractere)
{
	return isalpha(caractere) and (caractere == toupper(caractere));
}

} // Namespace util









