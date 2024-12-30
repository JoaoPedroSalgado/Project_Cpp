#ifndef POOTP20242025_ARCATESOUROITEM_H
#define POOTP20242025_ARCATESOUROITEM_H

#include "Item.h"

class ArcaDoTesouro : public Item {
public:
    ArcaDoTesouro(const std::string& tipo, int linha, int coluna, int duracao);
    void aplicarEfeito(Caravana& caravana, Mapa* mapa) override;

    std::string exibir() const override;
};

#endif //POOTP20242025_ARCATESOUROITEM_H
