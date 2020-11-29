/**
 * \file testeurPersonne.cpp
 *
 * Tests unitaires de la classe Personne.  Comme c'est une classe abstraite
 * nous allons créer une classe dérivée pour fin de testage, qui ne contiendra pas
 * d'implémentation supplémentaire:
 *
 * clone() retournera nullptr
 * reqPersonneFormatee() retournera la chaîne formattée de la version précédente
 *
 *  Created on: 2020-10-17
 *  \author Pascal Charpentier
 */

#define TEST

#include "Personne.h"
#include "Date.h"
#include "Adresse.h"
#include "ContratException.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

using namespace elections;

/**
 * \class PersonneConcrete
 *
 * Classe de testage pour la classe Personne: cell-ci est abstraite.  On crée donc cette classe dérivée qui
 * n'a aucune implémentation additionnelle.
 *
 * clone() retourne nullptr
 * reqPersonneFormatee() retourne une chaîne avec les infos demandées
 */

class PersonneConcrete : public Personne
{
public:

	/* Constructeur */

	PersonneConcrete(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom,
		             const util::Date& p_date, const util::Adresse& p_adresse);


	/* Méthodes virtuelles pures à supplanter */

	Personne* clone() const override // Ne fait rien
	{
		return nullptr;
	}

	std::string reqPersonneFormate() const override // Aucune augmentation
	{
		return Personne::reqPersonneFormate();
	}

	~PersonneConcrete() {}

};

// Ce constructeur ne fait qu'appeler le constructeur Personne(...)

PersonneConcrete::PersonneConcrete(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom,
		             const util::Date& p_date, const util::Adresse& p_adresse) :

		             Personne(p_nas, p_nom, p_prenom, p_date, p_adresse) {}


/**************************************************************************//**
 * TESTS DES MÉTHODES STATIQUES DE VALIDATION:
 *
 * Personne::validerIdentitePersonne()
 * Personne::validerPersonne()
 *
 *//****************************************************************************/

/**
 * Méthode testée: validerIdentitePersonne (STATIQUE)
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne true
 */

TEST(validerIdentitePersonne, identitesValides)
{
	std::string ligne1, ligne2, ligne3;
	std::ifstream fichier("identitesValides.testdata");

	if (!fichier.is_open())
	{
		std::cout << "Le fichier de données n'a pu être ouvert." << std::endl;
		std::exit(1);
	}

	while (std::getline(fichier, ligne1))
	{
		std::getline(fichier, ligne2);
		std::getline(fichier, ligne3);
		EXPECT_TRUE(Personne::validerIdentitePersonne(ligne1, ligne2, ligne3));
	}
}

/**
 * Méthode testée: validerIdentitePersonne (STATIQUE)
 *
 * Cas testés: données non-valides
 *
 * Comportement attendu: retourne false
 */

TEST(testValiderIdentitePersonne, identitesInvalides)
{
	std::string ligne1, ligne2, ligne3;
	std::ifstream fichier("identitesInvalides.testdata");

	if (!fichier.is_open())
	{
		std::cout << "Le fichier de données n'a pu être ouvert." << std::endl;
		std::exit(1);
	}

	while (std::getline(fichier, ligne1))
	{
		std::getline(fichier, ligne2);
		std::getline(fichier, ligne3);
		EXPECT_FALSE(Personne::validerIdentitePersonne(ligne1, ligne2, ligne3));
	}
}

/******************************************************************************
 * TESTS DU CONSTRUCTEUR
 *
 ******************************************************************************/

/**
 * Méthode testée: constructeur
 *
 * Cas testés: données valides
 *
 * Comportement attendu: construit l'objet sans exception
 */

TEST(PersonneConcrete, constructeurValide)
{
	std::string ligne1, ligne2, ligne3;
	std::ifstream fichier("identitesValides.testdata");

	if (!fichier.is_open())
	{
		std::cout << "Le fichier de données n'a pu être ouvert." << std::endl;
		std::exit(1);
	}


	while (std::getline(fichier, ligne1))
	{

		std::getline(fichier, ligne2);
		std::getline(fichier, ligne3);
		util::Date date(8, 4, 1986);
		util::Adresse adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");

		EXPECT_NO_THROW(PersonneConcrete personne(ligne1, ligne2, ligne3, date, adresse));
	}
}

/**
 * Méthode testée: constructeur
 *
 * Cas testés: données non-valides
 *
 * Comportement attendu: soulève une exception de contrat
 */

TEST(PersonneConcrete, constructeurNonValide)
{
	std::string ligne1, ligne2, ligne3;
	std::ifstream fichier("identitesInvalides.testdata");

	if (!fichier.is_open())
	{
		std::cout << "Le fichier de données n'a pu être ouvert." << std::endl;
		std::exit(1);
	}


	while (std::getline(fichier, ligne1))
	{

		std::getline(fichier, ligne2);
		std::getline(fichier, ligne3);
		util::Date date(8, 4, 1986);
		util::Adresse adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");


		EXPECT_THROW(PersonneConcrete personne(ligne1, ligne2, ligne3, date, adresse), PreconditionException);
	}
}

/**
 * \class PersonneTest
 *
 * Dispositif de test pour la réutilisation d'instances de PersonneConcrete
 * Contient des instances de 3 personnes valides distinctes et une personne identique à
 * la PersonneConcrete 1 pour tester l.opérateur d'égalité...
 */

class PersonneTest : public::testing::Test
{
public:

	PersonneTest() : personneValide1("111 111 118", "Targaryen", "Daenerys", util::Date(8, 5, 1990), util::Adresse(2020, "du Dragon", "Dragonstone", "X0X 4E4", "Westeros")),
	                 personneValide2("260 139 241", "Arryn", "Jon", util::Date(9, 9, 2009), util::Adresse(666, "du Sommet", "The Eyrie", "I9I 9I9", "VeryHigh")),
	                 personneValide4(personneValide1) {}

	PersonneConcrete personneValide1;
	PersonneConcrete personneValide2;
	PersonneConcrete personneValide4;

};

/**
 * Méthode testée: reqNas
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne le nas correct
 */

TEST_F(PersonneTest, reqNas)
{
	EXPECT_EQ(personneValide1.reqNas(), "111 111 118");
}

/**
 * Méthode testée: reqNom
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne le nom correct
 */

TEST_F(PersonneTest, reqNom)
{
	EXPECT_EQ(personneValide1.reqNom(), "Targaryen");
}

/**
 * Méthode testée: reqPrenom
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne le prénom correct
 */

TEST_F(PersonneTest, reqPrenom)
{
	EXPECT_EQ(personneValide1.reqPrenom(), "Daenerys");
}

/**
 * Méthode testée:reqDateNaissance
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne l'objet Date correct
 */

TEST_F(PersonneTest, reqDateNaissance)
{
	EXPECT_EQ(personneValide1.reqDateNaissance().reqJour(), 8);
	EXPECT_EQ(personneValide1.reqDateNaissance().reqMois(), 5);
	EXPECT_EQ(personneValide1.reqDateNaissance().reqAnnee(), 1990);
}

/**
 * Méthode testée: reqAdresse
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne l'objet Adresse correct
 */

TEST_F(PersonneTest, reqAdresse)
{
	EXPECT_EQ(personneValide1.reqAdresse().reqNumeroCivic(), 2020);
	EXPECT_EQ(personneValide1.reqAdresse().reqNomRue(), "du Dragon");
	EXPECT_EQ(personneValide1.reqAdresse().reqVille(), "Dragonstone");
	EXPECT_EQ(personneValide1.reqAdresse().reqCodePostal(), "X0X 4E4");
	EXPECT_EQ(personneValide1.reqAdresse().reqProvince(), "Westeros");
}

/**
 * Méthode testée: validerIdentitePersonne (STATIQUE)
 *
 * Cas testés: données valides
 *
 * Comportement attendu: assigne une nouvelle adresse valide
 */

TEST_F(PersonneTest, mutateurValide)
{
	util::Adresse nouvelleAdresse(1, "Rack", "Dreadfort", "T5T 5T5", "The North");

	personneValide1.asgAdresse(nouvelleAdresse);

	EXPECT_EQ(personneValide1.reqAdresse().reqNumeroCivic(), 1);
	EXPECT_EQ(personneValide1.reqAdresse().reqNomRue(), "Rack");
	EXPECT_EQ(personneValide1.reqAdresse().reqVille(), "Dreadfort");
	EXPECT_EQ(personneValide1.reqAdresse().reqCodePostal(), "T5T 5T5");
	EXPECT_EQ(personneValide1.reqAdresse().reqProvince(), "The North");
}

/**
 * Méthode testée: opérateur ==
 *
 * Cas testés: personnes identiques
 *
 * Comportement attendu: retourne true
 */

TEST_F(PersonneTest, testOperateurs)
{
	EXPECT_TRUE(personneValide1 == personneValide4);
	EXPECT_EQ(personneValide1, personneValide4);
}

/**
 * Méthode testée: opérateur !=
 *
 * Cas testés: personnes distinctes
 *
 * Comportement attendu: retourne false
 */

TEST_F(PersonneTest, testOperateurInegal)
{
	EXPECT_TRUE(personneValide1 != personneValide2);
	EXPECT_NE(personneValide1, personneValide2);
}

/**
 * Méthode testée: reqPersonneFormate
 *
 * Cas testés: données valides
 *
 * Comportement attendu: retourne une chaîne avec les informations correctes
 */

TEST_F(PersonneTest, testFormattage)
{
	EXPECT_EQ(personneValide1.reqPersonneFormate(), "NAS               : 111 111 118\n"
			"Nom               : Targaryen\n"
			"Prénom            : Daenerys\n"
			"Date de naissance : Mardi le 08 mai 1990\n"
			"Adresse           : 2020, du Dragon, Dragonstone, X0X 4E4, Westeros");

}













