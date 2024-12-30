//
// Created by Enrique Marques on 24/12/2024.
//

#include "Caravana.h"
#include "Mapa.h"

// Inicializa o contador de caravanas
int Caravana::contadorCaravanas = 0;

void Caravana::atualizarContadorCaravanas(int maiorID) {
    if (maiorID >= contadorCaravanas) {
        contadorCaravanas = maiorID + 1; // Atualiza o contador para começar após o maior ID
    }
}

int Caravana::gerarNovoID() {
    return contadorCaravanas++;
}
// Construtor
Caravana::Caravana(int id, int linha, int coluna, int capacidadeCarga, int tripulantes, int capacidadeTripulantes, int agua, int capacidadeAgua, bool autoGestao, const string& tipo, const Mapa& mapa)
        : id(id), linha(linha), coluna(coluna), capacidadeCarga(capacidadeCarga),
          tripulantes(tripulantes), capacidadeTripulantes(capacidadeTripulantes), agua(agua), capacidadeAgua(capacidadeAgua),cargaAtual(0), autoGestao(autoGestao), tipo(tipo) {
    contadorCaravanas++;
    atualizarCaracteresAoRedor(mapa); // Configurar os caracteres ao redor no momento da criação
}

// Exibe informações da caravana
void Caravana::exibir() const {
    cout << "ID: " << GetNumero()
         << ", Tipo: " << getTipo()
         << ", Linha: " << GetLinha()
         << ", Coluna: " << GetColuna()
         << ", Capacidade de Carga: " << GetCapacidadeCarga()
         << ", Tripulantes: " << GetTripulantes()
         << ", Agua: " << GetAgua()
         << ", Carga Atual: " << GetCargaAtual()
         << ", AutoGestao: " << (GetAutoGestao() ? "Sim" : "Nao")
         << endl;

    // Exibir as posições ao redor da caravana (se aplicável)
    cout << "\n\nPosições ao redor da caravana:" << endl;
    cout << "\nC: " << getC() << " (Linha: " << GetLinha() - 1 << ", Coluna: " << GetColuna() << ")";
    cout << "\nCE: " << getCE() << " (Linha: " << GetLinha() - 1 << ", Coluna: " << GetColuna() - 1 << ")"
         << "\nCD: " << getCD() << " (Linha: " << GetLinha() - 1 << ", Coluna: " << GetColuna() + 1 << ")"
         << "\nD: " << getD() << " (Linha: " << GetLinha() << ", Coluna: " << GetColuna() + 1 << ")";
    cout << "\nE: " << getE() << " (Linha: " << GetLinha() << ", Coluna: " << GetColuna() - 1 << ")"
         << "\nB: " << getB() << " (Linha: " << GetLinha() + 1 << ", Coluna: " << GetColuna() << ")"
         << "\nBE: " << getBE() << " (Linha: " << GetLinha() + 1 << ", Coluna: " << GetColuna() - 1 << ")"
         << "\nBD: " << getBD() << " (Linha: " << GetLinha() + 1 << ", Coluna: " << GetColuna() + 1 << ")\n";
    cout << endl;
}



// Retorna o número total de caravanas
int Caravana::getTotalCaravanas() {
    return contadorCaravanas;
}

// Retorna a referência ao contador de caravanas
int& Caravana::getContadorCaravanas() {
    return contadorCaravanas;
}

// Exibe todas as caravanas
void Caravana::exibirTodasAsCaravanas(const vector<std::unique_ptr<Caravana>>& caravanas) {
    cout << "\nExibindo todas as caravanas: \n";
    for (const auto& caravana : caravanas) {
        caravana->exibir(); // Usa o operador -> para chamar o método exibir
    }
}

// Retorna o ID da caravana
int Caravana::GetNumero() const {
    return id;
}

// Retorna a linha atual da caravana
int Caravana::GetLinha() const {
    return linha;
}

// Retorna a coluna atual da caravana
int Caravana::GetColuna() const {
    return coluna;
}

// Atualiza a posição da caravana
void Caravana::setPosicao(int l, int c) {
    linha = l;
    coluna = c;
}


// Atualiza os caracteres ao redor da caravana no mapa
void Caravana::atualizarCaracteresAoRedor(const Mapa& mapa) {
    int maxLinhas = mapa.getLinhas();
    int maxColunas = mapa.getColunas();

    // Função para calcular a posição normalizada (mapa rotativo/esférico)
    auto normalizar = [](int posicao, int maximo) {
        return (posicao + maximo) % maximo;
    };

    // Atualiza os caracteres ao redor com coordenadas normalizadas
    D  = mapa.obterElemento(GetLinha(), normalizar(GetColuna() + 1, maxColunas)); // Direita
    E  = mapa.obterElemento(GetLinha(), normalizar(GetColuna() - 1, maxColunas)); // Esquerda
    C  = mapa.obterElemento(normalizar(GetLinha() - 1, maxLinhas), GetColuna());  // Cima
    B  = mapa.obterElemento(normalizar(GetLinha() + 1, maxLinhas), GetColuna());  // Baixo
    CE = mapa.obterElemento(normalizar(GetLinha() - 1, maxLinhas), normalizar(GetColuna() - 1, maxColunas)); // Cima-Esquerda
    CD = mapa.obterElemento(normalizar(GetLinha() - 1, maxLinhas), normalizar(GetColuna() + 1, maxColunas)); // Cima-Direita
    BE = mapa.obterElemento(normalizar(GetLinha() + 1, maxLinhas), normalizar(GetColuna() - 1, maxColunas)); // Baixo-Esquerda
    BD = mapa.obterElemento(normalizar(GetLinha() + 1, maxLinhas), normalizar(GetColuna() + 1, maxColunas)); // Baixo-Direita
}


void Caravana::setTripulacao(int q) {
    if (q > 0) {
        tripulantes += q;
        std::cout << "Adicionados " << q << " tripulantes. Total agora: " << tripulantes << "\n";
    } else {
        std::cout << "Quantidade inválida para adicionar tripulantes.\n";
    }
}

void Caravana::VendeMercadoria() {

}

bool Caravana::CompraTripulacao(int q) {

    if (q > 0 && GetTripulantes() + q > GetCapacidadeTripulantes()) {
        cout << "\n Valor excedido " << GetTripulantes() + q << "/" << GetCapacidadeTripulantes()  << " compra invalida ";
        return false;
    }
    setTripulacao(GetTripulantes() + q);
    cout << "Adicionados " << q << " tripulantes. Total agora: " << GetTripulantes() << "\n";
    return true;
}

bool Caravana::VendeCarga() {
    if (GetCargaAtual() <= 0) {
        cout << "\nOperação inválida: a carga já está em 0.\n";
        return false;
    }

    // Zera a carga atual, representando a venda de toda a mercadoria
    ajustarCarga(0);
    cout << "\nMercadoria vendida com sucesso. Carga atual: " << cargaAtual << "\n";
    return true;
}

bool Caravana::CompraCarga(int q) {

    if(q > 0 && GetCargaAtual() + q > GetCapacidadeCarga()) {
        cout << "\n Valor excedido " << GetCargaAtual() + q << "/" << GetCapacidadeCarga()  << " compra invalida ";
        return false;
    }

    setCarga(GetCargaAtual() + q);
    return true;
}

void Caravana::setCarga(int q) {
    cargaAtual = q;
}


void Caravana::moverPara(int novaLinha, int novaColuna, Mapa& mapa) {
    // Atualiza o grid no mapa
    mapa.atualizarElemento(GetLinha(), GetColuna(), '.');
    mapa.atualizarElemento(novaLinha, novaColuna, GetNumero() + '0');

    // Atualiza a posição da caravana
    setPosicao(novaLinha, novaColuna);
}

void Caravana::ajustarCarga(int quantidade) {
    cargaAtual = std::max(0, std::min(cargaAtual + quantidade, capacidadeCarga));
}


void Caravana::setAgua(int a) {
    agua = a;
    if(agua > GetCapacidadeTripulantes())
        agua = GetCapacidadeTripulantes();
}