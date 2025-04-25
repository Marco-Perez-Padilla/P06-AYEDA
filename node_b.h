/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 6: Implementación del TDA Árbol
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 25/04/2025

** Archivo node_b.h: Declaracion e implementacion de la plantilla para los nodos del arbol
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/04/2025 - Creacion (primera version) del codigo
**/

#ifndef NODE_B_H
#define NODE_B_H

#include "exceptions.h"


template <class Key> class NodeB {
 protected:
  Key data_;
  NodeB<Key>* left_;
  NodeB<Key>* right_;
 public:
  // Constructor
  NodeB(const Key& data, NodeB<Key>* left = nullptr, NodeB<Key>* right = nullptr) : data_(data), left_(left), right_(right) {}
  ~NodeB() {
    delete left_;
    delete right_;
  }
  // Getters
  Key getData() const {return data_;}
  NodeB<Key>* getLeft() const {return left_;}
  NodeB<Key>* getRight() const {return right_;}
  // Setters
  void setLeft(NodeB<Key>* left) {left_ = left;}
  void setRight(NodeB<Key>* right) {right_ = right;}
};

#endif