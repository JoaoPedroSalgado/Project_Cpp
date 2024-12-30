#ifndef CIDADE_H
#define CIDADE_H

#include <string>
#include <vector>
#include <memory>
#include "Caravana.h"

using namespace std;

class Mapa;

class Cidade {
private:
    string nome;
    char identificador; // Letra associada à cidade no mapa
    vector<unique_ptr<Caravana>> caravanas; // Caravanas estacionadas na cidade

public:
    Cidade(const string& nome, char identificador, const Mapa& mapa);

    const vector<unique_ptr<Caravana>>& getCaravanas() const;

    const string& getNome() const;
    char getChar() const;

    void exibir() const;

    void adicionarCaravana(std::unique_ptr<Caravana> caravana); // Adiciona uma caravana
    void listarCaravanas() const;
    void removerCaravana(int numero); // Adicionando um método para remover caravanas
    void inicializarCaravanas(const Mapa& mapa); // Novo método para criar caravanas iniciais

    // TripulacaoCaravana
    void fornecerTripulantes(int idCaravana, int quantidade);
};

#endif // CIDADE_H
