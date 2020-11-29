/**
 * \filetesteurCandidat.cpp
 *
 *  Created on: Oct 19, 2020
 * \author Pascal Charpentier
 */

#include "Candidat.h"
#include "ContratException.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

using namespace elections;

/**
 * Méthode testée: validerPartiPolitique (STATIQUE)
 *
 * Cas testés: partis valides
 *
 * Comportement attendu: retourne true
 */
TEST(Candidat, validerPartiPolitiqueValide)
{
	EXPECT_TRUE(Candidat::validerPartiPolitique(BLOC_QUEBECOIS));
	EXPECT_TRUE(Candidat::validerPartiPolitique(LIBERAL));
	EXPECT_TRUE(Candidat::validerPartiPolitique(CONSERVATEUR));
	EXPECT_TRUE(Candidat::validerPartiPolitique(INDEPENDANT));
	EXPECT_TRUE(Candidat::validerPartiPolitique(NOUVEAU_PARTI_DEMOCRATIQUE));
}

/**
 * Méthode testée: validerPartiPolitique
 *
 * Cas testés: partis non-valides
 *
 * Comportement attendu: retourne false
 */

TEST(Candidat, validerPartiPolitiqueInvalide)
{
	EXPECT_FALSE(Candidat::validerPartiPolitique((PartisPolitiques) 56));
	EXPECT_FALSE(Candidat::validerPartiPolitique((PartisPolitiques) -45));

}

/**
 * Méthode testée: formatterPartiPolitique
 *
 * Cas testés: partis valides
 *
 * Comportement attendu: retourne la forme affichable du parti
 */
TEST(Candidat, formatterPartiPolitiqueValide)
{
	EXPECT_EQ(Candidat::formatterPartiPolitique(BLOC_QUEBECOIS), "Bloc québécois");
	EXPECT_EQ(Candidat::formatterPartiPolitique(LIBERAL), "Libéral");
	EXPECT_EQ(Candidat::formatterPartiPolitique(INDEPENDANT), "Indépendant");
	EXPECT_EQ(Candidat::formatterPartiPolitique(CONSERVATEUR), "Conservateur");
	EXPECT_EQ(Candidat::formatterPartiPolitique(NOUVEAU_PARTI_DEMOCRATIQUE), "Nouveau parti démocratique");
}

/**
 * Méthode testée: constructeur
 *
 * Cas testés: partis valides
 *
 * Comportement attendu: construit un objet sans exception
 */

TEST(Candidat, constructeurValide)
{
	EXPECT_NO_THROW(Candidat test("111 111 118", "Pascal", "Charpentier",
			util::Date(8, 4, 1990),
			util::Adresse(3040, "Rifle Range Road", "Sudbury", "M7T 5R5", "Ontario"),
			NOUVEAU_PARTI_DEMOCRATIQUE));
}

/**
 * Méthode testée: constructeur
 *
 * Cas testés: paramètres non-valides
 *
 * Comportement attendu: soulève une exception
 */

TEST(candidat, constructeurNonValide)
{

		util::Adresse adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec");
		util::Date date(8, 4, 1990);
		EXPECT_THROW(Candidat test("111 111 117", "Pascal", "Charpentier", date, adresse, NOUVEAU_PARTI_DEMOCRATIQUE), PreconditionException);
		EXPECT_THROW(Candidat test("111 111 118", "", "Charpentier", date, adresse, NOUVEAU_PARTI_DEMOCRATIQUE), PreconditionException);
		EXPECT_THROW(Candidat test("111 111 118", "Pascal", "", date, adresse, NOUVEAU_PARTI_DEMOCRATIQUE), PreconditionException);
		EXPECT_THROW(Candidat test("111 111 118", "Pascal", "Charpentier", date, adresse, (PartisPolitiques) 23), PreconditionException);
}

/**
 * class Candidat
 *
 * Dispositif de test pour la classe Candidat
 * Contient un objet Candidat
 */

class CandidatTest : public::testing::Test
{
public:
	CandidatTest() : test("111 111 118", "Charpentier", "Pascal",
			              util::Date(8, 4, 1990),
						  util::Adresse(2020, "du Finfin", "Alma", "G8Z 3S3", "Québec"),
						  NOUVEAU_PARTI_DEMOCRATIQUE) {}

	Candidat test;
};

/**
 * Méthode testée: reqPartiPolitique
 *
 * Cas testé: parti valide
 *
 * Comportement attendu: retourne le parti politique
 */

TEST_F(CandidatTest, reqPartiPolitique)
{
	EXPECT_EQ(test.reqPartiPolitique(), NOUVEAU_PARTI_DEMOCRATIQUE);
}

/**
 * Méthode testée:reqPersonneFormate
 *
 * Cas testés: personne valide
 *
 * Comportement attendu: retourne la forme affichable du candidat
 */

TEST_F(CandidatTest, reqPersonneFormate)
{
	EXPECT_EQ(test.reqPersonneFormate(), "Candidat\n"
			                             "-------------------------------\n"
			                             "NAS               : 111 111 118\n"
			                             "Nom               : Charpentier\n"
			                             "Prénom            : Pascal\n"
			                             "Date de naissance : Dimanche le 08 avril 1990\n"
			                             "Adresse           : 2020, du Finfin, Alma, G8Z 3S3, Québec\n"
			                             "Parti             : Nouveau parti démocratique" );

}

/**
 * Méthode testée:  clone
 *
 * Cas testé:
 *
 * Comportement attendu: retourne un pointeur non-nul et de la taille appropriée
 */

TEST_F(CandidatTest, pointeurEstValide)
{
	Personne* c = test.clone();
	EXPECT_NE(c, nullptr);
	delete c;
}

/**
 * Méthode testée:  clone
 *
 * Cas testé:
 *
 * Comportement attendu: le pointeur pointe une copie exacte de l'objet original
 */

TEST_F(CandidatTest, objetOriginalestCopie)
{
	Personne* cloneCandidat = test.clone();

	EXPECT_NE(&test, cloneCandidat);
	EXPECT_EQ(test.reqPersonneFormate(), cloneCandidat->reqPersonneFormate());

	delete cloneCandidat;
}





