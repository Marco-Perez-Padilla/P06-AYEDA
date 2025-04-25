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

** Archivo check_functions.h: Declaracion de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/04/2025 - Creacion (primera version) del codigo
**/

#ifndef CHECK_FUNCTIONS_H
#define CHECK_FUNCTIONS_H


#include <iostream>
#include <string>
#include <expected>


// Enum of errors in arguments
enum class parse_args_errors {
 missing_argument,
 chosen_size_error,
 mode_error,
 trace_error,
 file_error,
 tree_error,
 unknown_option,
};


// Struct that storages the values given in command line
struct program_options {
 bool show_help = false;
 int chosen_size = -1; // chosen size -1 as default
 int mode = 0; // Manual mode as default
 int trace = 0; // No trace as default
 int tree = 0; // ABB as default
 std::string file;
};
 
bool ValidateNumber (const std::string& line);
void Help ();
void Usage();
void pressanykey();
void clrscr();
void menu(char &option);
bool ProcessArgsErrors(const std::expected<program_options, parse_args_errors>& options);
std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]);

#endif