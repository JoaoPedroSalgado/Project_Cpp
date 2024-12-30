//
// Created by Enrique Marques on 24/12/2024.
//

#ifndef POOTP20242025_CARAVANA_H
#define POOTP20242025_CARAVANA_H

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Mapa; // Forward declaration para evitar dependências circulares

using namespace std;

class Caravana {
private:
    int id;               // Identificador da caravanaprotected:
    string tipo; // Tipo da caravana (ex: "Comércio", "Militar", "Bárbara")
    int linha, coluna;    // Posição no mapa
    int capacidadeCarga;  // Capacidade máxima de carga
    int tripulantes;      // Número de tripulantes
    int capacidadeTripulantes;      // Capacidade de tripulantes
    int agua;             // Quantidade de água disponível
    int capacidadeAgua;   // Capacidade de água
    int cargaAtual;       // Quantidade atual de carga
    bool autoGestao;      // Indicador de auto-gestão

    static int contadorCaravanas;

    // Caracteres ao redor da caravana
    char D, E, C, B, CE, BE, BD, CD;

public:
    Caravana(int id, int linha, int coluna, int capacidadeCarga, int tripulantes, int capacidadeTripulantes, int agua, int capacidadeAgua, bool autoGestao, const string& tipo, const Mapa& mapa);
    virtual ~Caravana() = default;

    // Métodos de acesso
    int GetNumero() const;
    int GetLinha() const;
    int GetColuna() const;
    void setPosicao(int l, int c);

    int GetTripulantes() const { return tripulantes; };
    int GetCapacidadeTripulantes() const { return capacidadeTripulantes; };

    static void atualizarContadorCaravanas(int maiorID); // Método para ajustar o contador
    static int gerarNovoID(); // Método para gerar novos IDs

    int GetAgua() const { return agua; };
    int GetCapacidadeAgua() const { return capacidadeAgua; };
    int GetCargaAtual() const { return cargaAtual; };
    bool GetAutoGestao() const { return autoGestao; };

    int GetCapacidadeCarga() const { return capacidadeCarga; };

    const string& getTipo() const { return tipo; };
    void setTipo(const string& novoTipo) { tipo = novoTipo; };

    // Exibição de informações
    virtual void exibir() const;
    static void exibirTodasAsCaravanas(const vector<std::unique_ptr<Caravana>>& caravanas);

    // Atualiza os caracteres ao redor no mapa
    void atualizarCaracteresAoRedor(const Mapa& mapa);

    // Métodos virtuais puros para comportamento específico
    virtual void mover(int dx, int dy, int maxLinhas, int maxColunas) = 0; // Deslocamento
    virtual void comportamentoAutonomo() = 0;                             // Movimento autônomo
    virtual void comportamentoSemTripulante() = 0;                        // Sem tripulação
    virtual void interagirComCidade() = 0;

    // Métodos estáticos
    static int getTotalCaravanas();
    static int& getContadorCaravanas();

    // Métodos getter para os caracteres ao redor

    char getC() const { return C; }
    char getCE() const { return CE; }
    char getCD() const { return CD; }
    char getB() const { return B; }
    char getBE() const { return BE; }
    char getBD() const { return BD; }
    char getE() const { return E; }
    char getD() const { return D; }

    void setTripulacao(int q);
    void VendeMercadoria();

    int GetTripulacao() const { return tripulantes; }
    void SetTripulacao(int novaTripulacao) { tripulantes = std::max(0, novaTripulacao); }
    void AjustarAgua(int quantidade) { agua = std::max(0, std::min(capacidadeAgua, agua + quantidade)); }

    void moverPara(int novaLinha, int novaColuna, Mapa& mapa);

    void ajustarCarga(int quantidade);

    void setCarga(int q);

    void setAgua(int a);

    bool CompraTripulacao(int q);
    bool VendeCarga();
    bool CompraCarga(int q);

    virtual void atualizarEstado(Mapa& mapa) = 0; // Método virtual puro
    virtual void aplicarTempestadeDeAreia() = 0; // Método virtual puro

    virtual void moverAutonomo(Mapa& mapa) = 0;

};

#endif //POOTP20242025_CARAVANA_H
