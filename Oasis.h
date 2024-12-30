//
// Created by Enrique Marques on 30/12/2024.
//

#ifndef POOTP20242025_OASIS_H
#define POOTP20242025_OASIS_H

#include "Item.h"

class Oasis : public Item {
public:
    Oasis(const std::string& tipo,int linha, int coluna, int duracao);

    void aplicarEfeito(Caravana& caravana, Mapa* mapa) override;
    string exibir() const override;
};
#endif //POOTP20242025_OASIS_H`