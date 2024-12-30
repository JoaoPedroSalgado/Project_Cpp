//
// Created by Enrique Marques on 18/12/2024.
//

#include "Buffer.h"

// Aloca memória para a matriz
void Buffer::alocaMatriz() {
    matriz = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new char[colunas];
    }
}

// Libera memória da matriz
void Buffer::desalocaMatriz() {
    if (matriz) {
        for (int i = 0; i < linhas; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz = nullptr;
    }
}

// Construtor
Buffer::Buffer(int linhas, int colunas)
        : linhas(linhas), colunas(colunas), cursorLinha(0), cursorColuna(0) {
    alocaMatriz();
    clear(); // Inicializa com espaços
}

// Destrutor
Buffer::~Buffer() {
    desalocaMatriz(); // Libera a memória
}

// Limpa o buffer
void Buffer::clear() {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = ' '; // Preenche com espaços
        }
    }
    cursorLinha = cursorColuna = 0; // Reseta o cursor
}

// Move o cursor para uma nova posição
void Buffer::moveCursor(int linha, int coluna) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        cursorLinha = linha;
        cursorColuna = coluna;
    }
}

// Escreve um caractere no buffer
void Buffer::write(char c) {
    if (cursorLinha >= 0 && cursorLinha < linhas &&
        cursorColuna >= 0 && cursorColuna < colunas) {
        matriz[cursorLinha][cursorColuna] = c;
        cursorColuna++; // Avança o cursor
        if (cursorColuna >= colunas) {
            cursorColuna = 0;
            cursorLinha++;
        }
    }
}

// Escreve uma string no buffer
void Buffer::write(const string& str) {
    for (char c : str) {
        write(c); // Escreve cada caractere
    }
}

// Escreve um inteiro no buffer
void Buffer::write(int valor) {
    write(to_string(valor)); // Converte para string e escreve
}

// Exibe o conteúdo do buffer na consola
void Buffer::display() const {
    cout << '\n';
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << matriz[i][j];
        }
        cout << '\n'; // Quebra de linha após cada linha do buffer
    }
}

// Getters para as dimensões do buffer
int Buffer::getLinhas() const {
    return linhas;
}

int Buffer::getColunas() const {
    return colunas;
}

// Sobrecarga do operador << para caracteres
Buffer& Buffer::operator<<(const char c) {
    write(c);
    return *this;
}

// Sobrecarga do operador << para strings
Buffer& Buffer::operator<<(const string& str) {
    write(str);
    return *this;
}

// Sobrecarga do operador << para inteiros
Buffer& Buffer::operator<<(int valor) {
    write(valor);
    return *this;
}

void Buffer::resize(int l, int col) {
    // Aloca uma nova matriz com as dimensões desejadas
    char** novaMatriz = new char*[l];
    for (int i = 0; i < l; ++i) {
        novaMatriz[i] = new char[col]; // Cria as colunas para cada linha
    }

    // Copia os dados da matriz original para a nova matriz
    for (int i = 0; i < std::min(linhas, l); ++i) {
        for (int j = 0; j < std::min(colunas, col); ++j) {
            novaMatriz[i][j] = matriz[i][j];
        }
    }

    desalocaMatriz(); // Libera o bloco antigo de memória

    matriz = novaMatriz;
    linhas = l;
    colunas = col;
}

string Buffer::serialize() const {
    stringstream ss;
    ss << "\n";
    for (int i = 0; i < linhas; i++) {
        if (matriz[i]) {
            ss << matriz[i] << "\n";
        }
    }
    return ss.str();
}

void Buffer::deserialize(const string& data) {
    // Vetor para armazenar as linhas do buffer
    vector<string> lines;
    stringstream ss(data);
    string segment;

    // Quebra os dados recebidos em linhas, separadas por '\n'
    while (getline(ss, segment)) {
        lines.push_back(segment);
    }

    // Redimensiona o buffer para acomodar os novos dados
    int novasLinhas = lines.size();
    int novasColunas = novasLinhas > 0 ? lines[0].size() : 0; // Assume largura uniforme
    resize(novasLinhas, novasColunas);

    // Preenche o buffer com os dados
    for (int i = 0; i < novasLinhas; ++i) {
        for (int j = 0; j < novasColunas; ++j) {
            matriz[i][j] = lines[i][j];
        }
    }
}
