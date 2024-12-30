#include "MinaItem.h"

Mina::Mina(const std::string& tipo, int linha, int coluna, int duracao)
        : Item(tipo, linha, coluna, duracao) {}


std::string Mina::exibir() const {
    return GetTipo() + " - Explode e destrói (" + std::to_string(GetLinha()) + ", " + std::to_string(GetColuna()) + ")";
}

void Mina::aplicarEfeito(Caravana& caravana, Mapa* mapa){};