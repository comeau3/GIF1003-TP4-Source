/**
 * \file PersonneException.cpp
 *
 * Hiérarchie d'exceptions pour la classe Circonscription
 *
 *  Created on: 2020-11-26
 * \author Pascal Charpentier
 * \author Samuel St-Pierre
 */
#include <stdexcept>

/**
 * \class PersonneException
 *
 * Classe générique d'exceptions associées à la gestion de la liste d'une Circonscription
 */

class PersonneException : public std::runtime_error
{
public:
	PersonneException(const std::string& p_raison) : runtime_error(p_raison) {}

};

/**
 * \class PersonneDejaPresenteException
 *
 * Classe dérivée de PersonneException.  Lancée lorsque la méthode inscrire() est appelée avec un NAS déja
 * présent dans la liste électorale.  Le NAS est unique et ne peut être dupliqué.
 *
 */

class PersonneDejaPresenteException : public PersonneException
{
public:
	PersonneDejaPresenteException(const std::string& p_raison) : PersonneException(p_raison) {}
};

/**
 * \class PersonneAbsenteException
 *
 * Classe dérivée de PersonneException. Lancée lorsque la méthode désinscrire() de Circonscription est appelée
 * avec un NAS absent de la liste.
 *
 */

class PersonneAbsenteException : public PersonneException
{
public:
	PersonneAbsenteException(const std::string& p_raison) : PersonneException(p_raison) {}
 };




