//
// Created by Enrique Marques on 18/12/2024.
//

#ifndef POOTP20242025_BUFFER_H
#define POOTP20242025_BUFFER_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Buffer {
private:
    int linhas, colunas;           // Dimensões do buffer
    char** matriz;                 // Representação bidimensional do buffer
    int cursorLinha, cursorColuna; // Posição atual do cursor

    void alocaMatriz();            // Aloca memória para a matriz
    void desalocaMatriz();         // Libera memória da matriz

public:
    Buffer(int linhas = 0, int colunas = 0);
    ~Buffer();

    string serialize() const;
    void deserialize(const std::string& data);
    int getRows() const;

    void resize(int l, int col);

    void clear(); // Limpa o buffer (preenche com espaços)
    void moveCursor(int linha, int coluna); // Move o cursor para uma posição
    void write(char c); // Escreve um caractere no buffer
    void write(const string& str); // Escreve uma string no buffer
    void write(int valor); // Escreve um inteiro no buffer
    void display() const; // Exibe o conteúdo do buffer na consola

    // Getters para as dimensões do buffer
    int getLinhas() const;
    int getColunas() const;

    // Sobrecarga do operador << para facilitar o uso
    Buffer& operator<<(const char c);
    Buffer& operator<<(const std::string& str);
    Buffer& operator<<(int valor);
};

#endif //POOTP20242025_BUFFER_H
