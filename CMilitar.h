#ifndef CMILITAR_H
#define CMILITAR_H

#include "Caravana.h" // Certifique-se de incluir o cabeçalho da classe base
#include "Mapa.h"     // Inclua o Mapa para referenciar corretamente o tipo

class CMilitar : public Caravana {
public:
    static int contadorCMilitar;
    int instantesSemTripulacao;
    std::string ultimaDirecao;

    CMilitar(int id, int linha, int coluna, const Mapa& mapa)
            : Caravana(id, linha, coluna, 5, 0, 40, 400, 400, false, "Comércio", mapa){
        contadorCMilitar++;
    };

    ~CMilitar() override;

    void mover(int dx, int dy, int maxLinhas, int maxColunas) override;
    void comportamentoAutonomo() override;
    void comportamentoSemTripulante() override;
    void interagirComCidade() override;
    void exibir() const override;

    void moverAutonomo(Mapa& mapa);
    void aplicarTempestadeDeAreia();
    void atualizarEstado(Mapa& mapa);
};

#endif // CMILITAR_H
