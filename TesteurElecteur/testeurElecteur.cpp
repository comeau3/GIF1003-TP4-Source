/**
 * \file testeurElecteur.cpp
 *
 *  Created on: Oct 19, 2020
 * \author: Pascal Charpentier
 */

#include "Electeur.h"
#include "ContratException.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

using namespace elections;

/**
 * Méthode testée: constructeur
 *
 * Cas testé: paramètres valides
 *
 * Comportement attendu: construit l'objet sans exception
 */

TEST(Electeur, constructeurValide)
{

		util::Adresse adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");
		util::Date date(8, 4, 1990);
		EXPECT_NO_THROW(Electeur test("111 111 118", "Pascal", "Charpentier", date, adresse));
}

/**
 * Méthode testée: constructeur
 *
 * Cas testé: paramètres non valides
 *
 * Comportement attendu: soulève une exception de contrat
 */

TEST(Electeur, constructeurInvalide)
{
	util::Adresse adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");
	util::Date date(8, 4, 1990);

	EXPECT_THROW(Electeur test("111 111 117", "Pascal", "Charpentier", date, adresse), PreconditionException);
	EXPECT_THROW(Electeur test("111 111 118", "", "Charpentier", date, adresse), PreconditionException);
	EXPECT_THROW(Electeur test("111 111 118", "Pascal", "", date, adresse), PreconditionException);
}

/**
 * Dispositif de test pour la classe Electeur
 *
 * Contient un objet Electeur
 */


class ElecteurTest : public::testing::Test
{
public:
	ElecteurTest() : electeurValide( "111 111 118", "Charpentier", "Pascal",
			                         util::Date(8, 4, 1990),
			                         util::Adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec") ) {}

	Electeur electeurValide;
};

/**
 * Méthode testée: reqPersonneFormate
 *
 * Cas testé: paramètres valides
 *
 * Comportement attendu: construit la chaîne avec les infos adéquates
 */

TEST_F(ElecteurTest, ElecteurEstValide)
{

	EXPECT_EQ(electeurValide.reqPersonneFormate(), "Électeur\n"
			                             "------------------------------\n"
			                             "NAS               : 111 111 118\n"
			                             "Nom               : Charpentier\n"
			                             "Prénom            : Pascal\n"
			                             "Date de naissance : Dimanche le 08 avril 1990\n"
			                             "Adresse           : 2020, du Finfin, Alma, G8Z 3S3, Québec" );

}

/**
 * Méthode testée: clone
 *
 * Cas testé: paramètres valides
 *
 * Comportement attendu: le pointeur retourné est non-nul et de la taille adéquate
 */

TEST_F(ElecteurTest, pointeurEstValide)
{
	Personne* c = electeurValide.clone();
	EXPECT_NE(c, nullptr);
	EXPECT_EQ(sizeof(*c), sizeof(Electeur));
	delete c;
}

/**
 * Méthode testée: clone
 *
 * Cas testé: paramètres valides
 *
 * Comportement attendu: l'objet pointé est identique à l'original
 */

TEST_F(ElecteurTest, objetOriginalestCopie)
{
	Personne* c = electeurValide.clone();
	EXPECT_NE(&electeurValide, c);
	EXPECT_EQ(electeurValide.reqPersonneFormate(), c->reqPersonneFormate());
	delete c;
}





