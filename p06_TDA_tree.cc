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

** Archivo p04_hash_program.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las templates para crear una tabla hash, y hacer busquedas e inserciones en la misma
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Primera version funcional. Instanciacion de las plantillas
**      23/03/2025 - Creacion del menu
**      24/03/2025 - Adicion manejo de errores
**      05/04/2025 - Adaptacion del programa cliente a metodos de ordenacion
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

   // Crear árbol AVL
   AVL<NIF> arbol;
   bool trace = options.value().trace;

   std::cout << "=== PRUEBA DE ARBOL AVL CON TRAZA ===" << std::endl;
   
   // Caso 1: Árbol vacío
   std::cout << "\nÁrbol vacío:" << std::endl;
   std::cout << arbol << std::endl;

   // Caso 2: Insertar elementos
   std::cout << "\nInsertando 30:" << std::endl;
   arbol.insert(NIF(30), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 25:" << std::endl;
   arbol.insert(NIF(25), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 15 (debería causar rotación II):" << std::endl;
   arbol.insert(NIF(15), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 40:" << std::endl;
   arbol.insert(NIF(40), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 50 (debería causar rotación DD):" << std::endl;
   arbol.insert(NIF(50), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 35 (debería causar rotación DI):" << std::endl;
   arbol.insert(NIF(35), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 10:" << std::endl;
   arbol.insert(NIF(10), trace);
   std::cout << arbol << std::endl;

   std::cout << "\nInsertando 5 (debería causar rotación II):" << std::endl;
   arbol.insert(NIF(5), trace);
   std::cout << arbol << std::endl;

   // Caso 3: Mostrar recorrido inorden
   std::cout << "\nRecorrido inorden:" << std::endl;
   arbol.inorder();

   // Prueba con modo traza desactivado
   AVL<NIF> arbol_sin_traza;
   trace = false;
   
   std::cout << "\n\n=== PRUEBA SIN TRAZA ===" << std::endl;
   std::cout << "Insertando 100, 90, 80:" << std::endl;
   arbol_sin_traza.insert(NIF(100), trace);
   arbol_sin_traza.insert(NIF(90), trace);
   arbol_sin_traza.insert(NIF(80), trace);
   std::cout << arbol_sin_traza << std::endl;

  return 0;
}