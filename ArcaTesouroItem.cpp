#include "ArcaTesouroItem.h"
#include "Mapa.h"

ArcaDoTesouro::ArcaDoTesouro(const std::string& tipo, int linha, int coluna, int duracao)
        : Item(tipo, linha, coluna, duracao) {}

std::string ArcaDoTesouro::exibir() const {
    return GetTipo() + " - Contém riqueza (" + std::to_string(GetLinha()) + ", " + std::to_string(GetColuna()) + ")";
}

void ArcaDoTesouro::aplicarEfeito(Caravana &caravana, Mapa* mapa) {
    int auxiliar = mapa->getMoedas();
    mapa->setMoedas(auxiliar * 1.1);
}