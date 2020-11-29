/*
 * \file testeurCirconscription.cpp
 *
 *  Created on: Oct 28, 2020
 * \author Pascal Charpentier
 */

#include "Circonscription.h"
#include "Electeur.h"
#include "Candidat.h"
#include "ContratException.h"
#include "PersonneException.h"
#include <gtest/gtest.h>
#include <vector>

using namespace elections;

/**
 * Dispositif de test pour la classe Circonscription
 *
 * Contient une circonscription test et trois électeurs à inscrire sur la liste
 */

class CirconscriptionTest : public::testing :: Test
{
public:

	CirconscriptionTest() : deputeSortant("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL),
	                        circonscription1("Circonscription Test 1", deputeSortant),
	p1(new Electeur("111 111 118", "Arryn", "Jon", util::Date(3, 1, 2007), util::Adresse(1, "The Eyrie", "Riverlands", "X3X 3X3", "Westeros"))),
	p2(new Electeur("222 222 226", "Targaryen", "Dany", util::Date(23, 12, 2000), util::Adresse(1, "The Eyrie", "Riverlands", "X3X 3X3", "Westeros"))),
	p3(new Candidat("333 333 334", "Snow", "Jon", util::Date(2, 2, 2002), util::Adresse(1, "The Eyrie", "Riverlands", "X3X 3X3", "Westeros"), CONSERVATEUR))
{}
	~CirconscriptionTest() {delete p1; delete p2; delete p3;}

	Candidat deputeSortant;
	Circonscription circonscription1 ;

	Personne* p1;
	Personne* p2;
	Personne* p3;
};

/**
 * Méthode testée: pointeurEstNul
 *
 * Cas testé: pointeur nul
 *
 * Comportement attendu: retourne true
 */

TEST(Circonscription, pointeurEstNul)
{
	Personne* pnul = nullptr;
	EXPECT_TRUE(Circonscription::pointeurEstNul(pnul)) ;
}

/**
 * Méthode testée: pointeurEstNul
 *
 * Cas testé: pointeur non-nul
 *
 * Comportement attendu: retourne false
 */

TEST(Circonscription, pointeurEstNulNonNul)
{
	Personne* p = new Electeur("111 111 118", "Arryn", "Jon", util::Date(3, 1, 2007), util::Adresse(1, "The Eyrie", "Riverlands", "X3X 3X3", "Westeros"));
	EXPECT_FALSE(Circonscription::pointeurEstNul(p));
}

/**
 * Méthode testée: reqDeputeElu
 *
 * Cas testé: objet valide
 *
 * Comportement attendu: retourne l'objet Candidat représentant le député sortant
 */


TEST_F(CirconscriptionTest, reqDeputeElu)
{
	EXPECT_EQ(circonscription1.reqDeputeElu(), deputeSortant);
}

/**
 * Méthode testée: reqNomCirconscription
 *
 * Cas testé: objet valide
 *
 * Comportement attendu: retourne le nom de la circonscription
 */

TEST_F(CirconscriptionTest, reqNomCirconscription)
{
	EXPECT_EQ(circonscription1.reqNomCirconscription(), "Circonscription Test 1") ;
}

/**
 * Méthode testée: constructeur
 *
 * Cas testé: paramètres non-valides
 *
 * Comportement attendu: soulève une exception de contrat
 */

TEST(Circonscription, neConstruitPasUnObjetInvalide)
{
	EXPECT_THROW( Circonscription("111 111 118", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 335", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(65, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 38, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(29, 2, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(0, "du Finfin", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, " ", "Alma", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "", "X3X 3X3", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "    ", "Québec"), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "  "), LIBERAL)), PreconditionException ) ;
	EXPECT_THROW( Circonscription("Lagardère", Candidat("333 333 334", "Cash", "Johnny", util::Date(3, 3, 2003), util::Adresse(2020, "du Finfin", "Alma", "X3X 3X3", "Québec"), (PartisPolitiques) 999)), PreconditionException ) ;
}

/**
 * Méthode testée: reqCirconscriptionFormate
 *
 * Cas testé: dispositif de test vide
 *
 * Comportement attendu: retourne une représentation textuelle de la circonscription et la mention liste vide
 */

TEST_F(CirconscriptionTest, reqCirconscriptionFormate)
{
	std::string resultat("Circonscription: Circonscription Test 1\nDéputé sortant: \n" + deputeSortant.reqPersonneFormate() + "\n\nListe des inscrits: \nListe vide");
	EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat);
}


/**
 * Méthode testée: listeEstValide
 *
 * Cas testé: dispositif de test
 *
 * Comportement attendu: retourne true
 */

TEST_F(CirconscriptionTest, ListeVideEstValide)
{
	EXPECT_TRUE(circonscription1.validerVecteurDesInscrits()) ;
}

/**
 * Méthode testée: inscrire
 *
 * Cas testé: dispositif de test valide
 *
 * Comportement attendu: annexe trois électeurs à la liste électorale.  À chaque inscription le nouvel
 * électeur apparait sur l'affichage de la liste électorale
 */

TEST_F(CirconscriptionTest, InscrireElecteurValide)
{
    circonscription1.inscrire(*p1);
    std::string resultat("Circonscription: Circonscription Test 1\nDéputé sortant: \n" + deputeSortant.reqPersonneFormate() + "\n\nListe des inscrits: \n" + p1->reqPersonneFormate() + "\n\n");
    EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat);

    circonscription1.inscrire(*p2);
    resultat += p2->reqPersonneFormate() + "\n\n" ;
    EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat);

    circonscription1.inscrire(*p3);
    resultat += p3->reqPersonneFormate() + "\n\n" ;
    EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat);

    EXPECT_TRUE(circonscription1.validerVecteurDesInscrits()) ;
}

/**
 * Méthode testée: inscrire
 *
 * Cas testé: tentative d'inscription d'un NAS déjà existant
 *
 * Comportement attendu: Lance une exception PersonneDejaPresenteException
 */

TEST_F(CirconscriptionTest, nePasInscrireDoublon)
{
    circonscription1.inscrire(*p1);
    circonscription1.inscrire(*p2);
    circonscription1.inscrire(*p3);

    Electeur doublon("111 111 118", "Piotr", "Trotsky", util::Date(1, 1, 1999), util::Adresse(6, "Pouet", "Alma", "GHT 1Q9", "On"));
    EXPECT_THROW(circonscription1.inscrire(doublon), PersonneDejaPresenteException);

}

/**
 * Méthode testée: désinscrire
 *
 * Cas testé: tentative de désinscrire de la liste vide
 *
 * Comportement attendu: Lance une exception PersonneAbsenteException
 */

TEST_F(CirconscriptionTest, nePasDesinscrireDansListeVide)
{
	EXPECT_THROW(circonscription1.desinscrire("111 111 118"), PersonneAbsenteException);
}

/**
 * Méthode testée: désinscrire
 *
 * Cas testé: tentative de désinscrire un NAS inexistant dans la liste non-vide
 *
 * Comportement attendu: Lance une exception PersonneAbsenteException
 */

TEST_F(CirconscriptionTest, nePasDesinscrireElecteurInexistant)
{
	circonscription1.inscrire(*p1);
	circonscription1.inscrire(*p2);
	circonscription1.inscrire(*p3);

	EXPECT_THROW(circonscription1.desinscrire("260 139 241"), PersonneAbsenteException);
}

TEST_F(CirconscriptionTest, desinscrireElecteurExistant)
{
	circonscription1.inscrire(*p1);
	circonscription1.inscrire(*p2);
	circonscription1.inscrire(*p3);

	circonscription1.desinscrire("222 222 226");

	std::string resultat("Circonscription: Circonscription Test 1\nDéputé sortant: \n" + deputeSortant.reqPersonneFormate()
				+ "\n\nListe des inscrits: \n" + p1->reqPersonneFormate() + "\n\n" + p3->reqPersonneFormate() + "\n\n");

	EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat);

	circonscription1.desinscrire("111 111 118");

	std::string resultat2("Circonscription: Circonscription Test 1\nDéputé sortant: \n" + deputeSortant.reqPersonneFormate()
			+ "\n\nListe des inscrits: \n" + p3->reqPersonneFormate() + "\n\n");

	EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat2);

	circonscription1.desinscrire("333 333 334");

	std::string resultat3("Circonscription: Circonscription Test 1\nDéputé sortant: \n" + deputeSortant.reqPersonneFormate()
			+ "\n\nListe des inscrits: \n" + "Liste vide");

	EXPECT_EQ(circonscription1.reqCirconscriptionFormate(), resultat3);
}

/**
 * Méthode testée: opérator=
 *
 * Cas testé: dispositif de test
 *
 * Comportement attendu: la circonscription1 est affectée < la circonscription2.  Cette dernière est identique à
 * la première.
 */

TEST_F(CirconscriptionTest, operateurAffectation)
{
	circonscription1.inscrire(*p1);
	circonscription1.inscrire(*p2);
	circonscription1.inscrire(*p3);

	Circonscription circonscription2 = circonscription1;
	EXPECT_EQ(circonscription2.reqCirconscriptionFormate(), circonscription1.reqCirconscriptionFormate());
}





