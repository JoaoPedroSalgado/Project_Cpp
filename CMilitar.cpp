#include "CMilitar.h"
#include "Mapa.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

int CMilitar::contadorCMilitar = 0;

CMilitar::~CMilitar() = default;

void CMilitar::mover(int dx, int dy, int maxLinhas, int maxColunas) {
    cout << "Movendo caravana militar...\n";
}

void CMilitar::comportamentoAutonomo() {
    cout << "Comportamento autônomo para caravana militar.\n";
}

void CMilitar::comportamentoSemTripulante() {
    cout << "Caravana militar sem tripulação.\n";
}

void CMilitar::interagirComCidade() {
    cout << "Caravana militar interagindo com a cidade.\n";
}

void CMilitar::exibir() const {
    Caravana::exibir();
}


void CMilitar::aplicarTempestadeDeAreia() {
    if (rand() % 100 < 33) {  // 33% de chance de destruição
        setTripulacao(0);
    }

    int perdaTripulacao = 0.1 * GetTripulacao();
    setTripulacao(GetTripulacao() - perdaTripulacao);
}

void CMilitar::atualizarEstado(Mapa& mapa) {
    if (GetTripulacao() == 0) {
        instantesSemTripulacao++;
        if (instantesSemTripulacao >= 7) {
            mapa.removerCaravana(this);
        }
    }
}

void CMilitar::moverAutonomo(Mapa& mapa) {
    // Fica parado se não houver bárbaros próximos
    for (const auto& barbaro : mapa.getBarbaros()) {
        int distancia = abs(barbaro->GetLinha() - GetLinha()) + abs(barbaro->GetColuna() - GetColuna());
        if (distancia <= 6) {
            int dx = (barbaro->GetLinha() > GetLinha()) ? 1 : -1;
            int dy = (barbaro->GetColuna() > GetColuna()) ? 1 : -1;
            moverPara(GetLinha() + dx, GetColuna() + dy, mapa);
            return;
        }
    }
}
