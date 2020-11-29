/**
 * \file testeurAdresse.cpp
 *
 * Tests unitaires de la classe Adresse.
 *
 *  Created on: 2020-10-11
 * \author Pascal Charpentier
 */

#include "Adresse.h"
#include "ContratException.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

using namespace util;

/**
 * Méthode testée: Adresse::validerLigneNonVide (STATIQUE)
 *
 * Cas testés: lignes constituées de caractères blancs (espaces, tabulations et retour de chariot)
 *
 * Comportement attendu: retourne false
 */

TEST(validerLigneNonVide, lignesVides)
{
	std::string ligne;
	std::ifstream fichier("lignesVides.testdata");

	EXPECT_TRUE(fichier.is_open());

	while (std::getline(fichier, ligne))
	{
		EXPECT_FALSE(Adresse::validerLigneNonVide(ligne));
	}
}

/**
 * Méthode testée: Adresse::validerLigneNonVide (STATIQUE)
 *
 * Cas testés: lignes comportant au-moins un caractère imprimable
 *
 * Comportement attendu: retourne true
 */

TEST(validerLigneNonVide, lignesNonVides)
{
	std::string ligne;
	std::ifstream fichier("lignesNonVides.testdata");

	EXPECT_TRUE(fichier.is_open());

	while (std::getline(fichier, ligne))
	{
		EXPECT_TRUE(Adresse::validerLigneNonVide(ligne));
	}
}

/**
 * Méthode testée: Adresse::validerNumeroCivic (STATIQUE)
 *
 * Cas testés: entiers nuls ou négatifs
 *
 * Comportement attendu: retourne false
 */

TEST(validerNumeroCivic, numerosInvalides)
{
	std::string ligne;
	std::ifstream fichier("numerosCiviquesInvalides.testdata");

	EXPECT_TRUE(fichier.is_open());

	while (std::getline(fichier, ligne))
	{
		int numero = std::stoi(ligne);
		EXPECT_FALSE(Adresse::validerNumeroCivic(numero));
	}
}

/**
 * Méthode testée: Adresse::validerNumeroCivic (STATIQUE)
 *
 * Cas testés: entiers positifs
 *
 * Comportement attendu: retourne true
 */

TEST(validerNumeroCivic, numerosValides)
{
	std::string ligne;
	std::ifstream fichier("numerosCiviquesValides.testdata");

	EXPECT_TRUE(fichier.is_open());

	while (std::getline(fichier, ligne))
	{
		int numero = std::stoi(ligne);
		EXPECT_TRUE(Adresse::validerNumeroCivic(numero));
	}
}

/**
 * Méthode testée: Adresse::validerAdresse (STATIQUE)
 *
 * Cas testés: Adresses valides
 *
 * Comportement attendu: retourne true
 */

TEST(validerAdresse, adressesValides)
{
	std::ifstream fichier("adressesValides.testdata");

	EXPECT_TRUE(fichier.is_open());

	int numero;
	std::string numstr, rue, ville, cp, province;

	while (std::getline(fichier, numstr))
	{
		numero = stoi(numstr);
		getline(fichier, rue);
		getline(fichier, ville);
		getline(fichier, cp);
		getline(fichier, province);
		EXPECT_TRUE(Adresse::validerAdresse(numero, rue, ville, cp, province));
	}
}

/**
 * Méthode testée: Adresse::validerAdresse (STATIQUE)
 *
 * Cas testés: adresses non-valides
 *
 * Comportement attendu: retourne false
 */

TEST(validerAdresse, adressesInvalides)
{
	std::ifstream fichier("adressesInvalides.testdata");
	EXPECT_TRUE(fichier.is_open());

	int numero;
	std::string numstr, rue, ville, cp, province;

	while (std::getline(fichier, numstr))
	{
		numero = stoi(numstr);
		getline(fichier, rue);
		getline(fichier, ville);
		getline(fichier, cp);
		getline(fichier, province);
		EXPECT_FALSE(Adresse::validerAdresse(numero, rue, ville, cp, province));
	}
}

/**
 * Méthode testée: Constructeur
 *
 * Cas testés: Paramètres valides
 *
 * Comportement attendu: l'objet est construit sans lever d'exception
 */

TEST(Adresse, construitUnObjetValide)
{
	std::ifstream fichier("adressesValides.testdata");
	EXPECT_TRUE(fichier.is_open());

	int numero;
	std::string numstr, rue, ville, cp, province;

	while (std::getline(fichier, numstr))
	{
		numero = stoi(numstr);
		getline(fichier, rue);
		getline(fichier, ville);
		getline(fichier, cp);
		getline(fichier, province);

		EXPECT_NO_THROW(Adresse adresseValide(numero, rue, ville, cp, province));

	}
}

/**
 * Méthode testée: Constructeur
 *
 * Cas testés: Paramètres non-valides
 *
 * Comportement attendu: une exception de contrat est levée et le constructeur arrête
 */

TEST(Adresse, neConstruitPasUnObjetInvalide)
{
	std::ifstream fichier("adressesInvalides.testdata");
	if (!fichier.is_open())
	{
		std::cerr << "Fichier ne peut être ouvert" << std::endl;
		std::exit(1);
	}

	int numero;
	std::string numstr, rue, ville, cp, province;

	while (std::getline(fichier, numstr))
	{
		numero = stoi(numstr);
		getline(fichier, rue);
		getline(fichier, ville);
		getline(fichier, cp);
		getline(fichier, province);

		EXPECT_THROW(Adresse adresseValide(numero, rue, ville, cp, province), PreconditionException);

	}
}

/**
 * \class AdresseTest
 *
 * Dispositif de test pour la classe Adresse.  Contient deux adresses valides distinctes et une adresse
 * qui est la copie de la première, afin de tester l'opérateur d'égalité.
 */

class AdresseTest : public::testing::Test
{


public:

	AdresseTest() : adresseValide1(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec"),
	                adresseValide2(10567, "boulevard de l'Avenir", "Laval", "H7E 1M8", "Québec"),
	                adresseValide4(adresseValide1){}

	Adresse adresseValide1;
	Adresse adresseValide2;
	Adresse adresseValide4;

};

/**
 * Méthode testée: accesseur du numéro civique
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne le numéro
 */

TEST_F(AdresseTest, reqNumeroCivic)
{
	EXPECT_EQ(adresseValide1.reqNumeroCivic(), 2020);
	EXPECT_EQ(adresseValide2.reqNumeroCivic(), 10567);
}

/**
 * Méthode testée: reqNomRue
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne le nom de la rue
 */

TEST_F(AdresseTest, reqNomRue)
{

	EXPECT_EQ(adresseValide1.reqNomRue(), "du Finfin");
	EXPECT_EQ(adresseValide2.reqNomRue(), "boulevard de l'Avenir");
}

/**
 * Méthode testée: reqVille
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne le nom de la ville
 */

TEST_F(AdresseTest, reqVille)
{

	EXPECT_EQ(adresseValide1.reqVille(), "Alma");
	EXPECT_EQ(adresseValide2.reqVille(), "Laval");
}

/**
 * Méthode testée:reqCodePostal
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne le code postal
 */

TEST_F(AdresseTest, reqCodePostal)
{

	EXPECT_EQ(adresseValide1.reqCodePostal(), "G8Z 3S3");
	EXPECT_EQ(adresseValide2.reqCodePostal(), "H7E 1M8");
}

/**
 * Méthode testée: reqProvince
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne la province
 */

TEST_F(AdresseTest, reqProvince)
{

	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");
	EXPECT_EQ(adresseValide2.reqProvince(), "Québec");
}

/**
 * Méthode testée: mutateur
 *
 * Cas testés: assignation d'une adresse valide
 *
 * Comportement attendu: modifie les paramètres de l'adresse aux valeurs demandées
 */

TEST_F(AdresseTest, mutateurValide)
{
	adresseValide1.asg(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");

	EXPECT_EQ(adresseValide1.reqNumeroCivic(), 2020);
	EXPECT_EQ(adresseValide1.reqNomRue(), "du Finfin");
	EXPECT_EQ(adresseValide1.reqVille(), "Alma");
	EXPECT_EQ(adresseValide1.reqCodePostal(), "G8Z 3S3");
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");
}

/**
 * Méthode testée: mutateur
 *
 * Cas testés: tentative d'assignation d'adresses invalides: numéro civique négatif, rue vide, ville vide, code postal vide, province vide.
 *
 * Comportement attendu: soulève une exception de contrat
 */

TEST_F(AdresseTest, mutateurInvalide)
{

	EXPECT_THROW(adresseValide1.asg(-2, "du Bouc", "BoucVille", "BOUCBO", "Bouchon"), PreconditionException);
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");

	EXPECT_THROW(adresseValide1.asg(666, "", "BoucVille", "BOUCBO", "Bouchon"), PreconditionException);
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");


	EXPECT_THROW(adresseValide1.asg(666, "Satan", "  ", "BOUCBO", "Bouchon"), PreconditionException);
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");


	EXPECT_THROW(adresseValide1.asg(666, "Satan", "Lucifer", "\n\n\n", "Bouchon"), PreconditionException);
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");


	EXPECT_THROW(adresseValide1.asg(666, "Satan", "Lucifer", "BOUCBO", ""), PreconditionException);
	EXPECT_EQ(adresseValide1.reqProvince(), "Québec");

}

/**
 * Méthode testée: opérateurs d'égalité
 *
 * Cas testés: Les adresses 1 et 4 sont identiques
 *
 * Comportement attendu: retourne true
 */

TEST_F(AdresseTest, operateurEgaliteEgal)
{
	EXPECT_TRUE(adresseValide1 == adresseValide4);
	EXPECT_EQ(adresseValide1, adresseValide4);
}

/**
 * Méthode testée: opérateur de non-égalité
 *
 * Cas testés: Les adresses 1 et 2 sont distinctes
 *
 * Comportement attendu: retourne false
 */

TEST_F(AdresseTest, operateurEgaliteInegal)
{
	EXPECT_TRUE(adresseValide1 != adresseValide2);
	EXPECT_FALSE(adresseValide1 == adresseValide2);
	EXPECT_NE(adresseValide1, adresseValide2);
}

/**
 * Méthode testée: reqAdresseFormatee
 *
 * Cas testés: dispositif de test
 *
 * Comportement attendu: retourne une chaîne au format voulu
 */

TEST_F(AdresseTest, testFormattage)
{
	EXPECT_EQ(adresseValide1.reqAdresseFormatee(), "2020, du Finfin, Alma, G8Z 3S3, Québec");
	EXPECT_EQ(adresseValide2.reqAdresseFormatee(), "10567, boulevard de l'Avenir, Laval, H7E 1M8, Québec");
}





