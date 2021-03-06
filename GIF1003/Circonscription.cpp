/****************************************************************************//**
 * \file Circonscription.cpp
 *
 *  Created on: 2020-10-20
 *  \author: Pascal charpentier
 *//*****************************************************************************/

#define CIRCONSCRIPTION
#ifdef CIRCONSCRIPTION

#include "Circonscription.h"
#include "validationFormat.h"
#include "ContratException.h"
#include "PersonneException.h"

#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace elections {

/****************************************************************************//**
 * Construit un objet Circonscription à partir du nom de celle-ci et d'un objet
 * Candidat valide représentant le député sortant.
 *
 * \param[in]  p_nom Nom de la circonscription
 * \param[in] p_depute Objet Candidat représentant le député sortant de la circonscription
 *
 * \pre p_nom est non-vide
 * \pre p_depute est un objet valide
 * \post Les membres correspondent aux paramètres correspondants
 * \post La liste électorale est vide
 *
 * \exception PreconditionException Le champ nom est non-vide
 * \exception InvariantException Un des membres est non-valide
 * \exception PostconditionException Les membres ne correspondent pas aux paramètres
 * \exception PostconditionException La liste électorale est non-vide
 *
 *//*****************************************************************************/

Circonscription::Circonscription(const std::string& p_nom, const Candidat& p_depute) :

		m_nomCirconscription(p_nom),
		m_deputeElu         (p_depute),
		m_vInscrits         ()
{
	PRECONDITION(util::estUnNom(p_nom)) ;
	PRECONDITION(p_depute.valider());

	INVARIANTS();

	POSTCONDITION(p_nom == m_nomCirconscription);
	POSTCONDITION(m_deputeElu == p_depute);
	POSTCONDITION(m_vInscrits.empty());

}

/****************************************************************************//**
 * Constructeur de recopie
 *
 * \param[in] p_circonscription l'objet à recopier
 *
 * \pre l'objet à recopier est valide
 *
 * \exception PreconditionException si l'objet en paramètre est non-valide
 * \exception InvariantException si un des membres est non-valide
 *
 *//*****************************************************************************/

Circonscription::Circonscription(const Circonscription& p_circonscription) :

		m_nomCirconscription(p_circonscription.m_nomCirconscription) ,
		m_deputeElu         (p_circonscription.m_deputeElu) ,
		m_vInscrits         ()
{
	PRECONDITION(p_circonscription.validerCirconscription()) ;

	for (Personne* personne: p_circonscription.m_vInscrits)
	{
		inscrire(*personne);
	}

	INVARIANTS() ;
	POSTCONDITION(reqCirconscriptionFormate() == p_circonscription.reqCirconscriptionFormate());
}

/****************************************************************************//**
 * Teste un pointeur à un objet personne
 *
 * \param[in] p un pointeur < u objet Personne
 * \return true si le pointeur est nul
 *
 *//****************************************************************************/

bool Circonscription::pointeurEstNul(Personne* p)
{
	return p == nullptr ;
}

/****************************************************************************//**
 * Détecte la présence d'une personne dans la liste électorale
 *
 * \return true si une personne inscrite a le nas passé en argument
 * \precondition le nas est valide
 *//*****************************************************************************/

bool Circonscription::personneEstDejaPresente(const std::string& p_nas) const
{
	return trouver(p_nas) != m_vInscrits.end();
}

/****************************************************************************//**
 * Localise un nas donné dans la liste électorale.
 *
 * \param[in] p_nas le numéro d'assurance sociale à localiser, au format 888 888 888
 *
 * \return un itérateur à l'inscription contenant le nas cherché.  m_vInscrits.end()
 * si le nas cherché est absent de la liste.
 *
 *//*****************************************************************************/

Circonscription::Iterateur_t Circonscription::trouver(const std::string& p_nas) const
{
	Iterateur_t iter = m_vInscrits.begin();
	bool trouve = false;

	while ( (!trouve) and (iter != m_vInscrits.end()) )
	{
		if ( (*iter)->reqNas() == p_nas )
			trouve = true;
		else
			++iter;
	}
   return iter;
}

/****************************************************************************//**
 * Vérifie qu'il n'y a aucun pointeur nul dans la liste électorale
 *
 * \return true si aucun pointeur de la liste n'est nul
 *
 *//****************************************************************************/

bool Circonscription::validerVecteurDesInscrits() const
{
	bool valide = true;
	if (m_vInscrits.empty())
	{
		valide = true;
	}
	else
	{
		for (auto it = m_vInscrits.begin(); valide and it != m_vInscrits.end(); ++it)
		{
			valide = !pointeurEstNul(*it);
		}
	}
	return valide ;
}

/****************************************************************************//**
 * Vérifie la validité interne de l'objet courant
 *
 * \return false si le nom est vide, si le candidat est invalide ou si un des
 * pointeurs de la liste électorale est invalide.
 *
 *//*****************************************************************************/

bool Circonscription::validerCirconscription() const
{
	return m_deputeElu.valider() and util::estUnNom(m_nomCirconscription) and validerVecteurDesInscrits();
}

/****************************************************************************//**
 * Appelé par la macro INVARIANTS()
 * Appelle à son tour une macro qui vérifie la validité interne de l'objet courant
 *
 * \exception InvariantException si l'objet Courant est jugé invalide.
 *
 *//****************************************************************************/

void Circonscription::verifieInvariant() const
{
    INVARIANT(validerCirconscription());
}

/****************************************************************************//**
 * Accesseur du nom de la circonscription
 *
 * \return chaîne de caractères contenant le nom de la circonscription
 *
 *//*****************************************************************************/

const std::string& Circonscription::reqNomCirconscription() const
{
	return m_nomCirconscription ;
}

/****************************************************************************//**
 * Accesseur de l'objet député élu
 *
 * \return L'objet député élu
 *
 *//****************************************************************************/

const Candidat& Circonscription::reqDeputeElu() const
{
	return m_deputeElu ;
}

/****************************************************************************//**
 * Rajoute un nouvel électeur ou candidat à la liste électorale
 *
 * \param p_nouveau Nouvelle personne à inscrire, soit un objet Candidat ou Electeur
 *
 * \pre L'objet est valide
 *
 * \post Le dernier élément de la liste est le nouvel inscrit
 * \post La liste est allongée d'un élément
 *
 * \exception PreconditionException si on tente d'inscrire une personne invalide
 * \exception InvariantException si l'objet courant est corrompu
 * \exception PostconditionException si le dernier élément n'est pas le nouvel inscrit
 * \exception PostconditionException si la liste ne s'est pas allongée d'un élément
 * \exception PersonneDejaPresenteException si une personne avec le même NAS est dans la liste
 *
 *//****************************************************************************/

void Circonscription::inscrire(const Personne& p_nouveau)
{
	std::vector<Personne*>::size_type precedent = m_vInscrits.size() ;

	PRECONDITION(p_nouveau.valider()) ;

	if (personneEstDejaPresente(p_nouveau.reqNas()))
		throw (PersonneDejaPresenteException(p_nouveau.reqNas()));
	m_vInscrits.push_back(p_nouveau.clone()) ;

	INVARIANTS() ;

	POSTCONDITION(*(m_vInscrits.back()) == p_nouveau);
	POSTCONDITION(m_vInscrits.size() == (precedent + 1));
}

/****************************************************************************//**
 * Retire une inscription de la liste électorale
 *
 * Fait deux actions: désalloue le pointeur à la personne inscrite.  Efface ce
 * pointeur de la liste.
 *
 * \param[in] p_nas Numéro d'assurance sociale de la personne à retirer
 *
 * \pre Le nas est valide
 *
 * \post La liste est raccourcie d'un élément
 *
 * \exception PersonneAbsenteException si le nas n'est pas localisé dans la liste
 *
 *//*****************************************************************************/

void Circonscription::desinscrire(const std::string& p_nas)
{
	size_t precedent = m_vInscrits.size();
	PRECONDITION(util::validerNas(p_nas));

	Iterateur_t localise = trouver(p_nas);

	if (localise == m_vInscrits.end()) throw PersonneAbsenteException(p_nas);
	delete *localise;
	m_vInscrits.erase(localise);


	POSTCONDITION(m_vInscrits.size() == (precedent - 1) );
	INVARIANTS();
}

/****************************************************************************//**
 * Échanger les attributs de lhs avec les attributs de rhs
 *
 * \param[in] lhs Objet de gauche
 * \param[in] rhs Objet de droite
 *
 * \pre Les deux objets sont valides
 * \post Les deux objets sont valides
 *
 *//*****************************************************************************/

void swap(Circonscription& lhs, Circonscription& rhs)
{
	PRECONDITION(lhs.validerCirconscription());
	PRECONDITION(rhs.validerCirconscription());

	using std::swap;
	swap(lhs.m_nomCirconscription, rhs.m_nomCirconscription) ;
	swap(lhs.m_deputeElu, rhs.m_deputeElu) ;
	swap(lhs.m_vInscrits, rhs.m_vInscrits) ;

	POSTCONDITION(lhs.validerCirconscription());
	POSTCONDITION(rhs.validerCirconscription());
}

/****************************************************************************//**
 * Opérateur d'affectation
 *
 * \pre L'objet de droite est valide
 *
 * \return une copie de l'opérande de droite
 *
 *//*****************************************************************************/

Circonscription& Circonscription::operator = (Circonscription rhs)
{
	PRECONDITION(rhs.validerCirconscription());
    swap(rhs, *this);
    INVARIANTS();
	return *this ;
}

/****************************************************************************//**
* Retourne une version imprimable de l'objet Circoncription comprenant:
* Le nom de la circonscription
* Les infos du député sortant
* Les infos de chaque Personne, candidat ou électeur, sur la liste électorale
*
* \return Le texte contenant ces informations
*
*//******************************************************************************/

std::string Circonscription::reqCirconscriptionFormate() const
{
	static std::string circonscriptionStr("Circonscription: ");
	static std::string deputeStr("Député sortant: ");
	static std::string listeStr("Liste des inscrits: ");
	static char ret = '\n';
	std::ostringstream os;


	os <<  circonscriptionStr << m_nomCirconscription << ret;
	os << deputeStr << ret << m_deputeElu.reqPersonneFormate() << ret << ret;

	os << listeStr << ret;
	if (m_vInscrits.empty())
	{
		os << "Liste vide";
	}
	else
	{
		for (Personne* inscrit: m_vInscrits)
		{
			os << inscrit->reqPersonneFormate() << ret << ret;
		}
	}
	return os.str();
}

/****************************************************************************//**
 * Destructeur: avant de détruire l'objet il faut désallouer chaque item de la liste
 * électorale.
 *//*****************************************************************************/

Circonscription::~Circonscription()
{
	for (auto it = m_vInscrits.begin(); it != m_vInscrits.end(); ++it)
		delete (*it);
}

} /* namespace elections */

#endif
