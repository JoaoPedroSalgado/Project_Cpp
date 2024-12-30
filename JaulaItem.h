#ifndef POOTP20242025_JAULAITEM_H
#define POOTP20242025_JAULAITEM_H

#include "Item.h"

class Jaula : public Item {
public:
    Jaula(const std::string& tipo, int linha, int coluna, int duracao);

    void aplicarEfeito(Caravana& caravana, Mapa* mapa) override;

    std::string exibir() const override;
};

#endif //POOTP20242025_JAULAITEM_H
