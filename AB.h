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

** Archivo AB.h: Declaracion e implementacion de los arboles binarios mediante polimorfismo
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/04/2025 - Creacion (primera version) del codigo
**/

#ifndef AB_H
#define AB_H

#include <iostream>
#include <queue>

#include "node_b.h"
#include "exceptions.h"


template <class Key> class AB {
 protected:
  NodeB<Key>* root_;
 public:
  // Constructor
  virtual AB() : root_(nullptr) {}
  // Destructor
  virtual ~AB() {delete root_;}
  // Getter
  NodeB<Key>* getRoot() {return root_;}
  // Search and insertion virtual methods
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  // Print the inorder path
  void InorderNode (NodeB<Key>*) const;
  void inorder() const;
};


template <class Key> void AB<Key>::InorderNode (NodeB<Key>* node) const {
  if (node) {
    InorderNode(node->getLeft());
    std::cout << node->getData() << " ";
    InorderNode(node->getRight());
  }
}


template <class Key> void AB<Key>::inorder () const {
  InorderNode(root_);
  std::cout << std::endl;
}


template <typename Key> std::ostream& operator<<(std::ostream& os, const AB<Key>& tree) {
  std::queue<NodeB<Key>*> qeueu;
  qeueu.push(tree.getRoot());

  int level = 0;
  while (!qeueu.empty()) {
    int size = qeueu.size();
    os << "Level " << level << ": ";
    while (size >= 1) {
      NodeB<Key>* node = qeueu.front();
      qeueu.pop();
      if (node) {
        os << nodo->get_dato() << " ";
        q.push(nodo->get_izdo());
        q.push(nodo->get_dcho());
      } else {
        os << "[.] ";
      }
      --size;
    }
    os << std::endl;    
  }
  return os;
}

#endif