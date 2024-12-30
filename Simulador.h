//
// Created by Enrique Marques on 20/12/2024.
//

#ifndef POOTP20242025_SIMULADOR_H
#define POOTP20242025_SIMULADOR_H

#include <string>
#include <sstream>
#include "Mapa.h"
#include "Buffer.h"
#include <numeric>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <sstream>

using namespace std;
namespace fs = filesystem;

class Simulador {
private:
    // Divisão Simulador -> Buffer + Mapa + Jogador -> Cidades + Caravanas + Itens
    Mapa mapa;
    Buffer buffer;
    int instantes;
    int fase;

    const string BUFFER_FILE = "buffers.txt";

    bool fileExists(const string& filename) const;
public:
    Simulador();
    ~Simulador();
    void iniciar();

    // Manipulação de buffers
    void saveBuffer(const string& name);
    void loadBuffer(const string& name);
    void listBuffers() const;
    void deleteBuffer(const string& name);

    int processarComandos(const string& RespostaComando, int &contador);
};

#endif //POOTP20242025_SIMULADOR_H
