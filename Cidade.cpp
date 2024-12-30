#include "Cidade.h"
#include <iostream>
#include <algorithm>
#include "CComercio.h"
#include "CMilitar.h"

using namespace std;

Cidade::Cidade(const string& nome, char identificador, const Mapa& mapa)
        : nome(nome), identificador(identificador) {
    inicializarCaravanas(mapa);
}

const string& Cidade::getNome() const {
    return nome;
}

char Cidade::getChar() const {
    return identificador;
}

void Cidade::adicionarCaravana(std::unique_ptr<Caravana> caravana) {
    caravanas.push_back(std::move(caravana));
}

void Cidade::listarCaravanas() const {
    cout << "Caravanas na cidade " << nome << ":\n";
    for (const auto& caravana : caravanas) {
        caravana->exibir();
    }
}

const vector<unique_ptr<Caravana>>& Cidade::getCaravanas() const {
    return caravanas;
}


void Cidade::exibir() const {
    cout << "\nCidade: " << getNome() << " com o Identificador: " << getChar() << "\n";;
    listarCaravanas(); // Exibe as caravanas estacionadas na cidade
}

void Cidade::removerCaravana(int numero) {
    auto it = std::remove_if(caravanas.begin(), caravanas.end(),
                             [numero](const unique_ptr<Caravana>& caravana) {
                                 return caravana->GetNumero() == numero;
                             });

    if (it != caravanas.end()) {
        caravanas.erase(it, caravanas.end());
    }
}

void Cidade::inicializarCaravanas(const Mapa& mapa) {
    caravanas.push_back(make_unique<CComercio>(Caravana::gerarNovoID(), 0, 0, mapa));
    caravanas.push_back(make_unique<CMilitar>(Caravana::gerarNovoID(), 0, 0, mapa));
}

void Cidade::fornecerTripulantes(int idCaravana, int quantidade) {
    for (auto& caravana : caravanas) {
        if (caravana->GetNumero() == idCaravana) {
            caravana->setTripulacao(quantidade);
            return;
        }
    }
    std::cout << "Caravana com ID " << idCaravana << " não encontrada nesta cidade.\n";
}