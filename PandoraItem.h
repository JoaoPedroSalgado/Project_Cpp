#ifndef POOTP20242025_PANDORAITEM_H
#define POOTP20242025_PANDORAITEM_H

#include "Item.h"

class CaixaDePandora : public Item {
public:
    CaixaDePandora(const std::string& tipo, int linha, int coluna, int duracao);

    std::string exibir() const override;

    void aplicarEfeito(Caravana& caravana, Mapa* mapa) override;

};

#endif //POOTP20242025_PANDORAITEM_H
