#include "JaulaItem.h"

Jaula::Jaula(const std::string& tipo, int linha, int coluna, int duracao)
        : Item(tipo, linha, coluna, duracao) {}

std::string Jaula::exibir() const {
    return GetTipo() + " - Aumenta tripulação (" + std::to_string(GetLinha()) + ", " + std::to_string(GetColuna()) + ")";
}

void Jaula::aplicarEfeito(Caravana &caravana, Mapa *mapa) {
    // Implementar o aumento da tripulação
    int max = caravana.GetTripulantes();
    caravana.setTripulacao(max + max/2);
}