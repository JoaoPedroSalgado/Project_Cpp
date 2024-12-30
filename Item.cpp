#include "Item.h"

Item::Item(const std::string& tipo, int linha, int coluna, int duracao)
        : tipo(tipo), linha(linha), coluna(coluna), duracao(duracao) {}

int Item::GetLinha() const {
    return linha;
}

int Item::GetColuna() const {
    return coluna;
}

int Item::GetDuracao() const {
    return duracao;
}

string Item::GetTipo() const {
    return tipo;
}

bool Item::decrementarDuracao(int valor) {
    duracao -= valor;
    return duracao <= 0; // Retorna true se o item expirou
}
