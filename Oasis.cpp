//
// Created by Enrique Marques on 30/12/2024.
//

#include "Oasis.h"

#include <iostream>

Oasis::Oasis(const std::string& tipo,int linha, int coluna, int duracao)
        : Item("Oasis", linha, coluna, duracao) {}

void Oasis::aplicarEfeito(Caravana& caravana, Mapa* mapa) {
    const int quantidadeAgua = 50; // Quantidade de água fornecida pelo Oasis
    cout << "\nCaravana encontrou um Oasis Fornecendo " << quantidadeAgua << " unidades de água.\n";

    // Aumenta a água da caravana, respeitando o limite máximo
    caravana.AjustarAgua(quantidadeAgua);
}

std::string Oasis::exibir() const {
    return "Oasis encontrado na posicao (" + std::to_string(GetLinha()) + ", "
           + std::to_string(GetColuna()) + ") com duracao de "
           + std::to_string(GetDuracao()) + " turnos.";
}