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

** Archivo nif.h: Declaracion de la clase NIF 
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/04/2025 - Creacion (primera version) del codigo
**/

#ifndef NIF_H
#define NIF_H


#include <iostream>
#include <iomanip>
#include <string>
#include <ctime> // time()
#include <cstdlib> //rand(), srand()


class NIF {
 private:
  std::string nif_;
 public:
  // Constructors
  NIF();
  explicit NIF (const std::string&);
  explicit NIF (long);
  // Getter
  const std::string& getNif() const {return nif_;}
  // Comparation operators
  bool operator==(const NIF&) const;
  bool operator!=(const NIF&) const;
  bool operator<(const NIF&) const;
  bool operator>(const NIF&) const;
  bool operator<=(const NIF&) const;
  bool operator>=(const NIF&) const;
  // Change type operator
  operator long() const;
  // Empty method
  bool isEmpty() const;
};
std::ostream& operator<< (std::ostream&, const NIF&);


#endif