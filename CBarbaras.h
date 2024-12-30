//
// Created by Enrique Marques on 27/12/2024.
//

#ifndef POOTP20242025_CBARBARAS_H
#define POOTP20242025_CBARBARAS_H

#include "Caravana.h"

class CBarbaras : public Caravana {
private:
    static int contadorCBarbaras;
    int desaparecimentoTimer; // Temporizador para desaparecimento
    int tripulacao; // Número de tripulantes
public:
    CBarbaras(int id, int linha, int coluna, const Mapa& mapa)
            : Caravana(id, linha, coluna, 0, 0, 40,0, 0, true, "Bárbara", mapa), desaparecimentoTimer(7), tripulacao(10) {
        contadorCBarbaras++;
    }

    void atualizarEstado(Mapa& mapa) override;

    void aplicarTempestadeDeAreia() override;
    void moverAutonomo(Mapa& mapa) override;
    void exibir() const override;
    void comportamentoAutonomo() override; // Movimento autônomo
    void comportamentoSemTripulante() override; // Sem tripulação
    void interagirComCidade() override;
    void mover(int dx, int dy, int maxLinhas, int maxColunas) override;
};

#endif //POOTP20242025_CBARBARAS_H
