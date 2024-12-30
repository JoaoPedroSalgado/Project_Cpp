//
// Created by Enrique Marques on 27/12/2024.
//

#include "CBarbaras.h"
#include "Mapa.h"

int CBarbaras::contadorCBarbaras = 0;

void CBarbaras::exibir() const {
    Caravana::exibir();
}

void CBarbaras::comportamentoAutonomo() {

}

void CBarbaras::comportamentoSemTripulante() {

}

void CBarbaras::interagirComCidade() {

}

void CBarbaras::mover(int dx, int dy, int maxLinhas, int maxColunas) {

}
void CBarbaras::atualizarEstado(Mapa& mapa) {
    // Exemplo de lógica de atualização
    if (tripulacao == 0) {
        desaparecimentoTimer--;
        if (desaparecimentoTimer <= 0) {
            mapa.removerCaravana(this);
        }
    }
}
void CBarbaras::aplicarTempestadeDeAreia() {
    if (rand() % 100 < 33) { // 33% de chance de destruição
        tripulacao = 0;
        std::cout << "Caravana bárbara destruída por tempestade de areia!\n";
    } else {
        tripulacao = static_cast<int>(tripulacao * 0.9); // Perde 10% dos tripulantes
        std::cout << "Caravana bárbara perdeu 10% dos tripulantes na tempestade.\n";
    }
}

void CBarbaras::moverAutonomo(Mapa& mapa) {
    int dx = rand() % 3 - 1; // Movimento aleatório
    int dy = rand() % 3 - 1;

    int novaLinha = (GetLinha() + dx + mapa.getLinhas()) % mapa.getLinhas();
    int novaColuna = (GetColuna() + dy + mapa.getColunas()) % mapa.getColunas();

    moverPara(novaLinha, novaColuna, mapa);
}