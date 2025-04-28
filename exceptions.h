/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 5: Algoritmos de ordenación
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 22/03/2025

** Archivo exceptions.h: Declaracion de la clase que maneja los errores 
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Adicion errores block size y no insercion
**/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


/**
 * @brief Class Exceptions that inheritages from std:exception, it has a protected member which is the message to be thrown if an error occurs
 */
class Exceptions : public std::exception {
 protected:
  std::string error_message_;
 public:
  explicit Exceptions (const std::string& error_message) : error_message_(error_message) {}
  const char* what() const throw() {return error_message_.c_str();}
};


/**
 * @brief Class NifStringException. Throws an exception if size is not 8
 */
class NifStringException : public Exceptions {
 public:
  NifStringException() : Exceptions("Error: NIF size is different than 8") {}
};


/**
 * @brief Class NifLongException. Throws an exception if size is greater than 8, or negative number
 */
class NifLongException : public Exceptions {
 public:
  NifLongException() : Exceptions("Error: NIF cannot be negative nor superior than 99999999") {}
};


/**
 * @brief Class BlockSizeZeroException. Throws an exception if the given block size is 0
 */
class BlockSizeZeroException : public Exceptions {
 public:
  BlockSizeZeroException() : Exceptions("Error: Block size can't be 0") {}
};


/**
 * @brief Class ClosedInsertException. Throws an exception if a key couldn't be inserted on a hash table
 */
class ClosedInsertException : public Exceptions {
 public:
  ClosedInsertException() : Exceptions("Error: Key couldn't be inserted, block full") {}
};



/**
 * @brief Class ClosedInsertException. Throws an exception if a key couldn't be inserted on a hash table
 */
class WrongPosition : public Exceptions {
 public:
 WrongPosition() : Exceptions("Error: Position can't be greater or equal than the block size") {}
};


#endif