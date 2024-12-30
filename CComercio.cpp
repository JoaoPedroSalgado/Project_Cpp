//
// Created by Enrique Marques on 29/12/2024.
//

#include "CComercio.h"
#include "Mapa.h"
#include <iostream>
#include <cmath>
#include <random>

int CComercio::contadorCComercio = 0; // Definição da variável estática

void CComercio::mover(int dx, int dy, int maxLinhas, int maxColunas) {

}

void CComercio::comportamentoAutonomo() {

}

void CComercio::comportamentoSemTripulante() {

}

void CComercio::interagirComCidade() {

}

void CComercio::exibir() const {
    Caravana::exibir();
}

void CComercio::moverAutonomo(Mapa& mapa) {
    if (GetTripulacao() == 0) {
        instantesSemTripulacao++;
        if (instantesSemTripulacao >= 5) {
            std::cout << "Caravana de comércio " << GetNumero() << " desapareceu.\n";
            mapa.removerCaravana(this);
            return;
        }

        // Movimento aleatório
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        int dir = rand() % 4;
        int novaLinha = (GetLinha() + dx[dir] + mapa.getLinhas()) % mapa.getLinhas();
        int novaColuna = (GetColuna() + dy[dir] + mapa.getColunas()) % mapa.getColunas();

        if (mapa.validarMovimento(novaLinha, novaColuna)) {
            setPosicao(novaLinha, novaColuna);
        }

        return;
    }

    // Procura por itens próximos
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            int novaLinha = GetLinha() + dx;
            int novaColuna = GetColuna() + dy;
            if (mapa.obterElemento(novaLinha, novaColuna) == '#') {
                moverPara(novaLinha, novaColuna, mapa);
                return;
            }
        }
    }

    // Tenta ficar próximo de outra caravana do utilizador
    for (const auto& outraCaravana : mapa.getCaravanas()) {
        if (outraCaravana->GetNumero() != GetNumero() &&
            std::abs(GetLinha() - outraCaravana->GetLinha()) <= 1 &&
            std::abs(GetColuna() - outraCaravana->GetColuna()) <= 1) {
            return;
        }
    }
}

void CComercio::aplicarTempestadeDeAreia() {
    if (GetCargaAtual() > 0.5 * GetCapacidadeCarga()) {
        if (rand() % 100 < 50) {  // 50% de chance de destruição
            setTripulacao(0);
        }
    } else {
        if (rand() % 100 < 25) {  // 25% de chance de destruição
            setTripulacao(0);
        }
    }

    if (GetTripulacao() > 0) {
        int perdaCarga = 0.25 * GetCargaAtual();
        ajustarCarga(-perdaCarga);
    }
}

void CComercio::atualizarEstado(Mapa& mapa) {
    if (GetTripulacao() == 0) {
        instantesSemTripulacao++;
        if (instantesSemTripulacao >= 5) {
            mapa.removerCaravana(this);
        }
    }
}

