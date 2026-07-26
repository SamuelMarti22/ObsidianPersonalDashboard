
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#define CHARMATERIA '#'
#define CHARTAREA '+'
#define CHARSEPARADOR '-'

void limpiarTarea(string& linea) {
  linea.erase(remove(linea.begin(), linea.end(), CHARTAREA), linea.end());
  linea.erase(remove(linea.begin(), linea.end(), '['), linea.end());
  linea.erase(remove(linea.begin(), linea.end(), ']'), linea.end());
}

void limpiarMateria(string& linea) {
  linea.erase(remove(linea.begin(), linea.end(), CHARMATERIA), linea.end());
  if (linea.back() == '\n') {
    linea.pop_back();
  }
  if (linea.front() == ' ') {
    linea.erase(0, 1);
  }
}

void insertarTareas(const vector<string>& tareas, ofstream& outputFile) {
  for (size_t i = 0; i < tareas.size(); i++) {
    outputFile << "\"" << tareas[i] << "\"";

    if (i + 1 != tareas.size())
      outputFile << ",";
  }
}

int main() {
  const char *originPath = "/home/jamu/Obsidian/Uni/PENDIENTES.md";
  const char *destinyPath = "./pendientes.json";

  // open the file in read mode
  ifstream archivoObsidian(originPath);

  if (!archivoObsidian.is_open()) {
    printf("Error opening file!\n");
    archivoObsidian.close();
    return 1;
  }

  ofstream outputFile(destinyPath);

  if (!outputFile.is_open()) {
    printf("Error opening output file!\n");
    outputFile.close();
    return 1;
  }

  outputFile << "{ \n";

  string linea;
  vector<string> tareas;
  bool primeraMateria = true;
  
  while (getline(archivoObsidian, linea)) {
    if (linea[0] == CHARMATERIA) {
      limpiarMateria(linea);
      tareas.clear();
      if (!primeraMateria){
        outputFile << "],\n";
      }
      primeraMateria = false;
      outputFile << "\"" << linea << "\" : [";
    }
    if (linea[0] == CHARTAREA) {
      limpiarTarea(linea);
      tareas.push_back(linea);
    }
    if (linea[0] == CHARSEPARADOR) {
      insertarTareas(tareas, outputFile);
    }
  }

  outputFile << "]\n}";

  archivoObsidian.close();
  outputFile.close();

  return 0;
}