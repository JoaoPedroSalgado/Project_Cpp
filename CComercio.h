//
// Created by Enrique Marques on 27/12/2024.
//

#ifndef POOTP20242025_CCOMERCIO_H
#define POOTP20242025_CCOMERCIO_H

#include "Caravana.h"

class CComercio : public Caravana {
private:
    static int contadorCComercio;
    int instantesSemTripulacao;

public:
    CComercio(int id, int linha, int coluna, const Mapa& mapa)
            : Caravana(id, linha, coluna,40, 20, 100, 200, 200, false, "Comércio", mapa), instantesSemTripulacao(0) {
        contadorCComercio++;
    }

    void exibir() const override;
    void comportamentoAutonomo() override; // Movimento autônomo
    void comportamentoSemTripulante() override; // Sem tripulação
    void interagirComCidade() override;
    void mover(int dx, int dy, int maxLinhas, int maxColunas) override;

    void moverAutonomo(Mapa& mapa);  // Movimento autônomo
    void aplicarTempestadeDeAreia();
    void atualizarEstado(Mapa& mapa);
};

#endif //POOTP20242025_CCOMERCIO_H
