/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 6: Implementación del TDA Árbol
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 25/05/2025

** Archivo p04_hash_program.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las templates para crear un arbol binario y permite trabajar con el mismo
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/04/2025 - Creacion (primera version) del codigo
**      28/04/2025 - Adaptacion menu para arboles
**/

#include <iostream>
#include <fstream>

#include "check_functions.h"
#include "nif.h"
#include "AB.h"


int main(int argc, char* argv[]) {
  auto options = parse_args(argc,argv);

  bool errors = ProcessArgsErrors(options);
  if (errors == 0) {
    exit(EXIT_FAILURE);
  }

  if (options.value().show_help) {
    Help(); 
    return 0;
  }

  AVL<NIF> arbol;
  int chosen_size = options.value().chosen_size; 
  int mode = options.value().mode; 
  int tree_option = options.value().tree; 
  bool trace = options.value().trace;
  std::string file = options.value().file;

  AB<NIF>* tree = nullptr;
  if (tree_option == 0) {
    tree = new ABB<NIF>();
  } else if (tree_option == 1) {
    tree = new AVL<NIF>();
  } 


  if (mode == 0) {
  } else if (mode == 1) {
    for (int i = 0; i < chosen_size; ++i) {
      NIF key = NIF();  
      tree->insert(key, trace);
    }
    std::cout << *tree << std::endl;
    std::cout << "Initial tree (Random):" << *tree << std::endl;
    pressanykey();
  } else if (mode == 2) {
    std::ifstream input_file(file);
    if (!input_file) {
      std::cerr << "Error opening the file: " << file << std::endl;
      exit(EXIT_FAILURE);
    }
    long key;
    for (int i = 0; i < chosen_size && (input_file >> key); ++i) {
      NIF nif (key);
      tree->insert(nif, trace);
    }
    std::cout << "Initial tree (File):" << *tree;
    pressanykey();
  }

  char option;

  do {
    clrscr();
    NIF random_nif;
    menu(option);
    switch (option) {
      case '1': {
        std::cout << "Introduce NIF to be inserted: ";
        long key;
        std::cin >> key;
        NIF nif (key);
        bool inserted = tree->insert(nif, trace);
        if (!inserted) {
          std::cout << "Given key is already in the tree, not inserted" << std::endl;
        }
        std::cout << *tree;  // mostrar por niveles
        pressanykey();
        break;
      }
        
      case '2': {
        std::cout << "Introduce NIF to be searched: ";
        long key;
        std::cin >> key;
        NIF nif (key);
        bool found = tree->search(nif);
        std::cout << (found ? "Key found\n" : "Key not found\n");
        pressanykey();
        break;
      }

      case '3': {
        std::cout << "Inorder trace:\n";
        tree->inorder();
        pressanykey();
        break;
      }
    }
  } while (option != '0');

  delete tree;
  clrscr();

  return 0;
}