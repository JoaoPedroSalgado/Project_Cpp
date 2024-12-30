#include "PandoraItem.h"

CaixaDePandora::CaixaDePandora(const std::string& tipo, int linha, int coluna, int duracao)
        : Item(tipo, linha, coluna, duracao) {}


std::string CaixaDePandora::exibir() const {
    return GetTipo() + " - Reduz tripulação (" + std::to_string(GetLinha()) + ", " + std::to_string(GetColuna()) + ")";
}

void CaixaDePandora::aplicarEfeito(Caravana &caravana, Mapa *mapa) {
    double aux = caravana.GetTripulantes();
    caravana.setTripulacao(aux * 0.8);
}