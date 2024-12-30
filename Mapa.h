#ifndef POOTP20242025_MAPA_H
#define POOTP20242025_MAPA_H

#include <string>
#include <random>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Buffer.h"
#include "Caravana.h"
#include "CBarbaras.h"
#include "CComercio.h"
#include "CMilitar.h"
#include "Item.h"

#include "Oasis.h"

class Cidade;

using namespace std;

class Mapa {
private:
    int linhas, colunas;               // Dimensões do mapa
    char** grid;                       // Representação da grelha do deserto
    vector<unique_ptr<Caravana>> caravanas;
    vector<unique_ptr<CBarbaras>> barbaras;
    vector<Cidade> cidades;
    vector<unique_ptr<Item>> itens;

    // Variáveis lidas do arquivo de configuração
    int moedas;
    static int instantes_entre_novos_itens;
    int duracao_item;
    int max_itens;
    int preco_venda_mercadoria;
    int preco_compra_mercadoria;
    int preco_caravana;
    int instantes_entre_novos_barbaros;
    int duracao_barbaros;

    unordered_map<string, int*> variaveis;

    // Métodos auxiliares
    void moverCaravanaNoMapa(std::vector<std::unique_ptr<Caravana>>::iterator& it, const std::string& direcao);
    void moverCaravanaNaCidade(Cidade& cidade, std::vector<std::unique_ptr<Caravana>>::iterator& it, const std::string& direcao);
    void obterDeslocamento(const std::string& direcao, int& dx, int& dy) const;

public:
    Mapa();                                   // Construtor padrão
    ~Mapa();                                  // Destrutor

    // Gerenciamento do mapa
    int getLinhas() const;
    int getColunas() const;
    bool carregarMapa(const string& ficheiro); // Carrega o mapa de um ficheiro
    void redimensionarGrid(int novasLinhas, int novasColunas, char valorInicial);
    void desenhar(Buffer& buffer) const;

    void alterarGrid(int l, int col, char c);
    void ColocaBarbaro(int lin, int col);

    // Métodos estáticos
    static int getDurancaoItem();

    const vector<unique_ptr<Caravana>>& getCaravanas() const;

    // Operações no grid
    bool validarMovimento(int linha, int coluna) const;
    char obterElemento(int linha, int coluna) const;
    void atualizarElemento(int linha, int coluna, char elemento);

    // Gerenciamento de itens
    void gerarItensAleatorios();
    void mostrarItens() const;
    void atualizarItens(int instantes);

    // Gerenciamento de caravanas
    void moverCaravana(int numero, const string& direcao);
    void sairDaCidade(int numero, const string& direcao);
    Caravana* obterCaravanaPorId(int id) const;

    void MostraCaravanaById(int id);

    // Gerenciamento de moedas
    int AdicionaMoedas(int m);
    int setMoedas(int v);
    int getMoedas() const;

    // Gerenciamento de cidades
    const vector<Cidade>& getCidades() const;
    void compraTripula(int idCaravana, int quantidade);
    void VendeMercadorias(int idCaravana);
    void MostraPrecos();

    bool verificarProximidadeCidade(int idCaravana) const;
    bool verificarCaravanaProxima(int idCaravana) const;
    bool verificarBarbarosProximos(int idCaravana) const;

    void resolverCombates();

    int getPrecoVenda() const;

    int getPrecoCompra() const;

    void removerCaravana(Caravana* caravana);

    const std::vector<std::unique_ptr<CBarbaras>>& getBarbaros() const;

    const std::vector<std::unique_ptr<Item>>&getItens() const;

    void CompraMercadoria(int idCaravana, int quantidade);

};

#endif //POOTP20242025_MAPA_H
