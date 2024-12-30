#ifndef POOTP20242025_MINAITEM_H
#define POOTP20242025_MINAITEM_H

#include "Item.h"

class Mina : public Item {
public:
    Mina(const std::string& tipo, int linha, int coluna, int duracao);

    void aplicarEfeito(Caravana& caravana, Mapa* mapa) override;

    std::string exibir() const override;
};

#endif //POOTP20242025_MINAITEM_H
