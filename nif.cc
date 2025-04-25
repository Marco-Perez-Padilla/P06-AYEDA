/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 6: Implementación del TDA Árbol
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 22/04/2025

** Archivo nif.cc: Implementación de la clase NIF 
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/04/2025 - Creacion (primera version) del codigo
**/


#include "nif.h"
#include "exceptions.h"
#include "check_functions.h" // ValidateNumber()

/**
 * @brief Default constructor for NIF class. It inizialtes a random NIF with 8 digits
 */
NIF::NIF() {
  // If the seed has already been initialized, don't initialize it again
  static bool initialized = false;
  if (!initialized) {
    // Create the seed in terms of the time
    srand(time(nullptr));
    initialized = true;
  }
  // Generate the random number between 0 and 99999999
  int random_number = rand() % 100000000;
  // Convert it to string
  nif_ = std::to_string(random_number);
  // If the result has less than 8 digits, add 0's
  nif_.insert(nif_.begin(), 8 - nif_.size(), '0');
}


/**
 * @brief NIF constructor given a string
 */
NIF::NIF (const std::string& nif) {
  if (nif == "-1") {
    nif_ = nif;
    return;
  }
  // If it doesn't have 8 digits or it's not  number, throw an exception
  if (nif.size() != 8 || !ValidateNumber(nif)) {
    throw NifStringException();
  }
  nif_ = nif;
}


/**
 * @brief NIF constuctor fiven a long number. It checks if the number is valid
 */
NIF::NIF (long nif_number) {
  if (nif_number == -1) {
    nif_ = std::to_string(nif_number);
    return;
  }
  // If negative number or more than 8 digits, throw an exception
  if (nif_number < 0 || nif_number > 99999999) {
    throw NifLongException();
  }
  // Convert it to string
  nif_ = std::to_string(nif_number);
  // Add 0's if it has less than 8 digits
  nif_.insert(nif_.begin(), 8 - nif_.size(), '0');
}


/**
 * @brief Overload of == operator for NIF class
 * @param NIF to be compared
 * @return true if both NIF's are equal. False otherwise
 */
bool NIF::operator==(const NIF& other_nif) const {
  return getNif() == other_nif.getNif();
}


/**
 * @brief Overload of != operator for NIF class
 * @param NIF to be compared
 * @return false if both NIF's are equal. True otherwise
 */
bool NIF::operator!=(const NIF& other_nif) const {
  return getNif() != other_nif.getNif();
}


/**
 * @brief Overload of < operator for NIF class
 * @param NIF to be compared
 * @return true if the first NIF is lesser than the second one. False otherwise
 */
bool NIF::operator<(const NIF& other_nif) const {
  return getNif() < other_nif.getNif();
}


/**
 * @brief Overload of > operator for NIF class
 * @param NIF to be compared
 * @return false if the first NIF is lesser or equal than the second one. True otherwise
 */
bool NIF::operator>(const NIF& other_nif) const {
  return getNif() > other_nif.getNif();
}


/**
 * @brief Overload of <= operator for NIF class
 * @param NIF to be compared
 * @return true if the first NIF is lesser or equal than the second one. False otherwise
 */
bool NIF::operator<=(const NIF& other_nif) const {
  return getNif() <= other_nif.getNif();
}


/**
 * @brief Overload of == operator for NIF class
 * @param NIF to be compared
 * @return false if the first NIF is minor than the second one. True otherwise
 */
bool NIF::operator>=(const NIF& other_nif) const {
  return getNif() >= other_nif.getNif();
}


/**
 * @brief operator to change type from NIF to long
 */
NIF::operator long() const {return std::stol(nif_);}


/**
 * @brief Method that checks if a nif is empty
 * @return true is nif = -1, false otherwise
 */
bool NIF::isEmpty() const {return (nif_ == "-1");}


/**
 * @brief overload of operator << for NIF class
 * @param ostream
 * @param NIF
 * @return os
 */
std::ostream& operator<< (std::ostream& os, const NIF& nif) {
  os << nif.getNif();
  return os;
}
