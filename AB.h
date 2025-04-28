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
**      26/04/2025 - Adicion de especializacion ABB
**      28/04/2025 - Finalizacion version funcional AVL
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
  AB() : root_(nullptr) {}
  // Destructor
  virtual ~AB() {delete root_;}
  // Getter
  NodeB<Key>*& getRoot() {return root_;}
  const NodeB<Key>* getRoot() const {return root_;}
  // Search and insertion virtual methods
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&, bool trace) = 0;
  // Print the inorder path
  void InorderNode(NodeB<Key>*) const;
  void inorder() const;
};


/**
 * @brief Prints the tree with inorder trace
 * @param NodeB nodes of the tree
 */
template <class Key> void AB<Key>::InorderNode(NodeB<Key>* node) const {
  if (node) {
    InorderNode(node->getLeft());
    std::cout << node->getData() << " ";
    InorderNode(node->getRight());
  } else {
    return;
  }
}


/**
 * @brief void inorder method to be called in the menu
 */
template <class Key> void AB<Key>::inorder() const {
  InorderNode(root_);
  std::cout << std::endl;
}


/**
 * @brief Overload of << operator for trees, printing them in levels
 * @param ostream os
 * @param AB tree
 * @return ostream
 */
template <typename Key> std::ostream& operator<<(std::ostream& os, const AB<Key>& tree) {
  std::queue<const NodeB<Key>*> qeueu;
  qeueu.push(tree.getRoot());

  int level = 0;
  while (!qeueu.empty()) {
    int size = qeueu.size();
    os << "Level " << level << ": ";
    while (size >= 1) {
      const NodeB<Key>* node = qeueu.front();
      qeueu.pop();
      if (node) {
        os << node->getData() << " ";
        qeueu.push(node->getLeft());
        qeueu.push(node->getRight());
      } else {
        os << "[.] ";
      }
      --size;
    }
    os << std::endl;
    level++;
  }
  return os;
}


template <class Key> class ABB : public AB<Key> {
 public:
  bool search(const Key&) const override;
  bool insert(const Key&, bool trace) override;
};

/**
 * @brief Method for ABB to search a key in it
 * @param Key key to be searched
 * @return True if the Key has been found, false otherwise
 */
template<class Key> bool ABB<Key>::search(const Key& key) const {
  NodeB<Key>* current = this->root_;
  while (current) {
    if (key < current->getData()) {
      current = current->getLeft();
    } else if (key > current->getData()) {
      current = current->getRight();
    } else {
      return true;
    }
  }
  return false;
}


/**
 * @brief Method for ABB to insert a key in it
 * @param Key key to be inserted
 * @return True if the Key has been correctly inserted, false otherwise
 */
template<class Key> bool ABB<Key>::insert(const Key& key, bool trace) {
  NodeB<Key>** current = &(this->root_);

  while (*current) {
    if (key < (*current)->getData()) {
      current = &((*current)->getLeft());
    } else if (key > (*current)->getData()) {
      current = &((*current)->getRight());
    } else {
      return false;
    }
  }

  *current = new NodeB<Key>(key);
  return true;
}


template <class Key> class AVL : public ABB<Key> {
 private:
  void rotacion_II(NodeAVL<Key>* &node, bool trace);
  void rotacion_DD(NodeAVL<Key>* &node, bool trace);
  void rotacion_ID(NodeAVL<Key>* &node, bool trace);
  void rotacion_DI(NodeAVL<Key>* &node, bool trace);
  void insert_bal(NodeAVL<Key>* &node, const Key& key, bool& grow, bool trace);

 public:
  bool insert(const Key& key, bool trace) override;
};


/**
 * @brief method that considers left-left rotations
 * @param NodeAVL node to be rotated
 * @param bool trace, prints the trace if its value is true
 */
template <class Key> void AVL<Key>::rotacion_II(NodeAVL<Key>* &node, bool trace) {
  if (trace) {
    std::cout << "Desbalanceo:" << std::endl;
    std::cout << *this << std::endl;
  }

  if (trace) std::cout << "Rotacion II en [" << node->getData() << "(" << node->getBal() << ")]:" << "\n";
  
  NodeAVL<Key>* node1 = dynamic_cast<NodeAVL<Key>*>(node->getLeft());
  node->setLeft(node1->getRight());
  node1->setRight(node);
  
  if (node1->getBal() == 1) {
      node->setBal(0);
      node1->setBal(0);
  } else {
      node->setBal(1);
      node1->setBal(-1);
  }
  node = node1;
}


/**
 * @brief method that considers right-right rotations
 * @param NodeAVL node to be rotated
 * @param bool trace, prints the trace if its value is true
 */
template <class Key> void AVL<Key>::rotacion_DD(NodeAVL<Key>* &node, bool trace) {
  if (trace) {
    std::cout << "Desbalanceo:" << std::endl;
    std::cout << *this << std::endl;
  }

  if (trace) std::cout << "Rotacion DD en [" << node->getData() << "(" << node->getBal() << ")]:" << "\n";
  
  NodeAVL<Key>* node1 = dynamic_cast<NodeAVL<Key>*>(node->getRight());
  node->setRight(node1->getLeft());
  node1->setLeft(node);
  
  if (node1->getBal() == -1) {
      node->setBal(0);
      node1->setBal(0);
  } else {
      node->setBal(-1);
      node1->setBal(1);
  }
  node = node1;
}


/**
 * @brief method that considers left-right rotations
 * @param NodeAVL node to be rotated
 * @param bool trace, prints the trace if its value is true
 */
template <class Key> void AVL<Key>::rotacion_ID(NodeAVL<Key>* &node, bool trace) {
  if (trace) {
    std::cout << "Desbalanceo:" << std::endl;
    std::cout << *this << std::endl;
  }

  if (trace) std::cout << "Rotacion ID en [" << node->getData() << "(" << node->getBal() << ")]:" << "\n";
  
  NodeAVL<Key>* node1 = dynamic_cast<NodeAVL<Key>*>(node->getLeft());
  NodeAVL<Key>* node2 = dynamic_cast<NodeAVL<Key>*>(node1->getRight());
  
  node->setLeft(node2->getRight());
  node2->setRight(node);
  node1->setRight(node2->getLeft());
  node2->setLeft(node1);
  
  if (node2->getBal() == -1) node1->setBal(1);
  else node1->setBal(0);
  
  if (node2->getBal() == 1) node->setBal(-1);
  else node->setBal(0);
  
  node2->setBal(0);
  node = node2;
}


/**
 * @brief method that considers right-left rotations
 * @param NodeAVL node to be rotated
 * @param bool trace, prints the trace if its value is true
 */
template <class Key> void AVL<Key>::rotacion_DI(NodeAVL<Key>* &node, bool trace) {
  if (trace) {
    std::cout << "Desbalanceo:" << std::endl;
    std::cout << *this << std::endl;
  }

  if (trace) std::cout << "Rotacion DI en [" << node->getData() << "(" << node->getBal() << ")]:" << "\n";
  
  NodeAVL<Key>* node1 = dynamic_cast<NodeAVL<Key>*>(node->getRight());
  NodeAVL<Key>* node2 = dynamic_cast<NodeAVL<Key>*>(node1->getLeft());
  
  node->setRight(node2->getLeft());
  node2->setLeft(node);
  node1->setLeft(node2->getRight());
  node2->setRight(node1);
  
  if (node2->getBal() == 1) node1->setBal(-1);
  else node1->setBal(0);
  
  if (node2->getBal() == -1) node->setBal(1);
  else node->setBal(0);
  
  node2->setBal(0);
  node = node2;
}


/**
 * @brief private method that inserts a node balanced in the tree recursively
 * @param NodeAVL node to be inserted
 * @param Key key to be inserted
 * @param bool to track if the tree has grown or not
 * @param bool to print the trace if it's true
 */
template <class Key> void AVL<Key>::insert_bal(NodeAVL<Key>* &node, const Key& key, bool& grow, bool trace) {
  if (!node) {
    node = new NodeAVL<Key>(key);
    grow = true;
    return;
  }

  if (key < node->getData()) {
    NodeB<Key>*& left_ref = node->getLeft();
    
    NodeAVL<Key>*& left = reinterpret_cast<NodeAVL<Key>*&>(left_ref);
    if (!left) {
      left_ref = new NodeAVL<Key>(key);
      left = static_cast<NodeAVL<Key>*>(left_ref);
      grow = true;
    } else {
      insert_bal(left, key, grow, trace);
    }

    if (grow) {
      node->setBal(node->getBal() + 1);
      if (node->getBal() == 2) {
        if (left->getBal() == 1) {
          rotacion_II(node, trace);
        } else {
          rotacion_ID(node, trace);
        }
        grow = false;
      } else if (node->getBal() == 0) {
        grow = false;
      }
    }
  } 
  else if (key > node->getData()) {
    NodeB<Key>*& right_ref = node->getRight();
    NodeAVL<Key>*& right = reinterpret_cast<NodeAVL<Key>*&>(right_ref);
    
    if (!right) {
      right_ref = new NodeAVL<Key>(key);
      right = static_cast<NodeAVL<Key>*>(right_ref);
      grow = true;
    } else {
      insert_bal(right, key, grow, trace);
    }

    if (grow) {
      node->setBal(node->getBal() - 1);
      if (node->getBal() == -2) {
        if (right->getBal() == -1) {
          rotacion_DD(node, trace);
        } else {
          rotacion_DI(node, trace);
        }
        grow = false;
      } else if (node->getBal() == 0) {
        grow = false;
      }
    }
  } else {
    grow = false;
  }
}


/**
 * @brief method that inserts a node in a tree
 * @param Key key to be inserted
 * @param bool to print the trace if it's true
 */
template <class Key> bool AVL<Key>::insert(const Key& key, bool trace) {
  if (this->search(key)) {
    return false;
  }

  bool grow = false;
  NodeB<Key>* root = this->getRoot();
  
  if (!root) {
    this->root_ = new NodeAVL<Key>(key);
    return true;
  }
  
  NodeAVL<Key>* avl_root = dynamic_cast<NodeAVL<Key>*>(root);
  if (!avl_root) {
    avl_root = new NodeAVL<Key>(root->getData());
    for (NodeB<Key>* child : {root->getLeft(), root->getRight()}) {
      if (child) {
        if (child->getData() < root->getData())
          avl_root->setLeft(child);
        else
          avl_root->setRight(child);
      }
    }
    root->setLeft(nullptr);
    root->setRight(nullptr);
    delete root;
    this->root_ = avl_root;
  }
  
  insert_bal(avl_root, key, grow, trace);
  this->root_ = avl_root;
  return true;
}


#endif