#ifndef POOTP20242025_ITEM_H
#define POOTP20242025_ITEM_H

#include <string>
#include <iostream>
#include "Caravana.h"

class Item {
private:
    std::string tipo; // Tipo do item
    int linha, coluna; // Posição no mapa
    int duracao; // Duração do item em turnos

public:
    Item(const std::string& tipo, int linha, int coluna, int duracao);

    virtual std::string exibir() const = 0; // Exibe informações do item

    int GetLinha() const;
    int GetColuna() const;
    int GetDuracao() const;
    string GetTipo() const;
    bool decrementarDuracao(int valor);

    virtual void aplicarEfeito(Caravana& caravana, Mapa* mapa) = 0; // Efeito do item

    virtual ~Item() = default;
};

#endif //POOTP20242025_ITEM_H
