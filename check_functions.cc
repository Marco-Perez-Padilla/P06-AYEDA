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

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/04/2025 - Creacion (primera version) del codigo
**/

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <expected>
#include <string_view>
#include <vector>
#include <limits>

#include "check_functions.h"


// Including libreries for compatibility among operative systems
#ifdef _WIN32
  #include <conio.h>  // _getch() for pressanykey
  #define CLEAR "cls" // Macro for clrscr in Windows
#else
  #define CLEAR "clear" // Macro for clrscr in Linux
#endif


/**
 * @brief Checks if a given string is made out of (only) numbers or not
 * @param string
 * @return bool
 */
bool ValidateNumber (const std::string& line) {
  if (!line.empty()) {
    for (char chr : line) {
      if (!std::isdigit(chr)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./p06_TDA_tree [--help | -h] [-ab <abb|avl>] [-init <i> [s] [f]] [-trace <y|n>]\n"
              << "Usage:                ./p06_TDA_tree [--help | -h] [-ab <abb|avl>] [-init <i> [s] [f]] [-trace <y|n>]\n"
              << "    [--help | -h]:       Optional argument. Prints this help\n"
              << "    [-ab <abb|avl>]:     Optional argument. Indicates the kind of tree we will work with:\n"
              << "                              - abb: Binary Search Tree. Non-balanced binary tree\n"
              << "                              - avl:  AVL tree. Self-balanced binary tree\n"
              << "    [-init <i>]:          Optional argument: Specifies with <i> the way data will be introduced:\n"
              << "                              - manual: Introduces manually an arbitrary number of elements to the tree\n"
              << "                              - random [s]: Introduces randomly the [s] number of elements to the tree\n"
              << "                              - file [s] [f]: Introduces [s] elements from a file which name is specified with [f], mandatory field\n"
              << "    [-trace <y|n>] Optional argument: If used with <y>, the program will print the trace of the selected sort method. If <n>, this funcitonality will be deactivated\n";

}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./p06_TDA_tree [--help | -h] [-ab <abb|avl>] [-init <i> [s] [f]] [-trace <y|n>]\n"
            << "Try './p06_TDA_tree [--help | -h]' for further information\n";
}


/**
 * @brief Function that processes the arguments given through command line
 * @param argc
 * @param argv
 * @return Program options struct with all the options if no error has occured. Enum parse args error otherwise with the specified error
 */
std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]) {
  bool chosen_size = false;
  bool tree = false;
  bool trace = false;
  bool file = false;
  bool mode = false;

  std::vector<std::string_view> args(argv + 1, argv + argc);
  program_options options;

  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-h" || *it == "--help") {
      options.show_help = true;
    } else if (*it == "-ab") {
      tree = true;
      continue;
    } else if (*it == "-init") {
      mode = true;
      continue;
    } else if (*it == "-trace") {
      trace = true;
      continue;
    } else if (tree == true) {
      tree = false;
      if (std::string(*it) == "abb") {
        options.tree = 0;
        continue;
      } else if (std::string(*it) == "avl") {
        options.tree = 1;
        continue;
      } else {
        return std::unexpected(parse_args_errors::tree_error);
      }
    } else if (mode == true) {
      mode = false;
      if (std::string(*it) == "manual") {
        options.mode = 0;
        continue;
      } else if (std::string(*it) == "random"){
        options.mode = 1;
        chosen_size = true;
        continue;
      } else if (std::string(*it) == "file"){
        options.mode = 2;
        chosen_size = true;
        file = true;
        continue;
      } else {
        return std::unexpected(parse_args_errors::mode_error);
      }
    } else if (!it->starts_with("-") && chosen_size == true) {
      chosen_size = false;
      if (ValidateNumber(std::string(*it)) && std::stoi(std::string(*it)) > 0) {
        options.chosen_size = std::stoi(std::string(*it));
        continue;
      } else {
        return std::unexpected(parse_args_errors::chosen_size_error);
      }
    } else if (!it->starts_with("-") && file == true) {
      file = false;
      std::string file_name = std::string(*it);
      if (file_name.empty()) {
        return std::unexpected(parse_args_errors::file_error);
      } else {
        options.file = file_name;
        continue;
      }
    } else if (trace == true) {
      trace = false;
      if (std::string(*it) == "y") {
        options.trace = 1;
      } else if (std::string(*it) == "n"){
        options.trace = 0;
      } else {
        return std::unexpected(parse_args_errors::trace_error);
      }
    } else {
      return std::unexpected(parse_args_errors::unknown_option); 
    }
  }

  if ((file == true && options.file.empty()) || (chosen_size == true && options.chosen_size == -1)) {
    return std::unexpected(parse_args_errors::missing_argument);
  }

  return options; 
}


/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  #ifdef _WIN32
    _getch(); // Windows
  #else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Linux
    std::cin.get(); 
  #endif
}


/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system(CLEAR);
}


/**
* @brief Start menu to choose an option of the following
* @param char option to be used
*/
void menu (char &opcion) {
 std::cout << "[0]. Exit" << std::endl;     
 std::cout << "[1]. Insert key" << std::endl;
 std::cout << "[2]. Search key" << std::endl;        
 std::cout << "[3]. Show inorder tree" << std::endl;        
 std::cout << "Introduce the action to execute  > ";
 std::cin >> opcion;
};


/**
 * @brief Function that processes error messages from std::unexpected
 * @param expected options after command line
 * @return 0 if an error occurred
 */
bool ProcessArgsErrors(const std::expected<program_options, parse_args_errors>& options) {
  if (!options.has_value()) {
    if (options.error() == parse_args_errors::unknown_option) {
      std::cerr << "fatal error: Unknown option" << std::endl;;
    } else if (options.error() == parse_args_errors::chosen_size_error) {
      std::cerr << "fatal error: Table size, it must be a non negative number superior than 0" << std::endl;
    } else if (options.error() == parse_args_errors::mode_error) {
      std::cerr << "fatal error: Specified insertion mode must be 'manual' or 'random' or 'file'" << std::endl;
    } else if (options.error() == parse_args_errors::file_error) {
      std::cerr << "fatal error: Insertion mode file selected. It must be followed by a file name not empty" << std::endl; 
    } else if (options.error() == parse_args_errors::trace_error) {
      std::cerr << "fatal error: Trace must be specified with 'y' or 'n'" << std::endl;
    } else if (options.error() == parse_args_errors::missing_argument) {
      std::cerr << "fatal error. Missing argument after file insertions mode selected" << std::endl;
    } else if (options.error() == parse_args_errors::tree_error) {
      std::cerr << "fatal error. Tree specification must be either 'abb' or 'avl'" << std::endl;
    }
    Usage();
    return 0;
  }
  return 1;
}