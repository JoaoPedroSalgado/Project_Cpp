//
// Created by Enrique Marques on 18/12/2024.
//

#include "Mapa.h"
#include "PandoraItem.h"
#include "JaulaItem.h"
#include "ArcaTesouroItem.h"
#include "MinaItem.h"
#include "Cidade.h"
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <random>
#include <algorithm>

int Mapa::instantes_entre_novos_itens = 0;

Mapa::Mapa()
        : linhas(0), colunas(0), grid(nullptr), moedas(0),
          duracao_item(0), max_itens(0), preco_venda_mercadoria(0),
          preco_compra_mercadoria(0), preco_caravana(0),
          instantes_entre_novos_barbaros(0), duracao_barbaros(0) {
    variaveis = {
            {"moedas", &moedas},
            {"instantes_entre_novos_itens", &instantes_entre_novos_itens},
            {"duração_item", &duracao_item},
            {"max_itens", &max_itens},
            {"preço_venda_mercadoria", &preco_venda_mercadoria},
            {"preço_compra_mercadoria", &preco_compra_mercadoria},
            {"preço_caravana", &preco_caravana},
            {"instantes_entre_novos_barbaros", &instantes_entre_novos_barbaros},
            {"duração_barbaros", &duracao_barbaros}
    };
}

Mapa::~Mapa() {
    if (grid) {
        for (int i = 0; i < linhas; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}

int Mapa::getLinhas() const {
    return linhas;
}

int Mapa::getColunas() const {
    return colunas;
}

bool Mapa::carregarMapa(const string& ficheiro) {
    ifstream f(ficheiro);
    if (!f) {
        cerr << "Erro ao abrir o arquivo: " << ficheiro << endl;
        return false;
    }

    string linha;
    f >> linha >> linhas;
    f >> linha >> colunas;
    f.ignore(numeric_limits<streamsize>::max(), '\n');

    if (linhas <= 0 || colunas <= 0) {
        throw runtime_error("Dimensões inválidas para o mapa.");
    }

    redimensionarGrid(linhas, colunas, '.');

    for (int i = 0; i < linhas; ++i) {
        getline(f, linha);
        for (int j = 0; j < colunas; ++j) {
            if (j < linha.size()) {
                grid[i][j] = linha[j];
            }
        }
    }

    int maiorID = 0;

    while (getline(f, linha)) {
        istringstream ss(linha);
        string chave;
        int valor;

        if (ss >> chave >> valor) {
            auto it = variaveis.find(chave);
            if (it != variaveis.end()) {
                *(it->second) = valor;
            }
        }
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            char c = grid[i][j];

            if (isdigit(c)) {
                int id = c - '0';
                caravanas.push_back(make_unique<CComercio>(id, i, j, *this));
                maiorID = max(maiorID, id);
            } else if (c == '!') {
                int id = barbaras.size() + 1;
                barbaras.push_back(make_unique<CBarbaras>(id, i, j, *this));
                maiorID = max(maiorID, id);
            } else if (islower(c)) {
                string nomeCidade = "Cidade_";
                nomeCidade += c;
                cidades.emplace_back(nomeCidade, c, *this);
            }
        }
    }

    Caravana::atualizarContadorCaravanas(maiorID);

    return true;
}

void Mapa::redimensionarGrid(int novasLinhas, int novasColunas, char valorInicial) {
    if (grid) {
        for (int i = 0; i < linhas; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    linhas = novasLinhas;
    colunas = novasColunas;
    grid = new char*[linhas];

    for (int i = 0; i < linhas; ++i) {
        grid[i] = new char[colunas];
        fill(grid[i], grid[i] + colunas, valorInicial);
    }
}


Caravana* Mapa::obterCaravanaPorId(int id) const {
    for (const auto& caravana : caravanas) {
        if (caravana->GetNumero() == id) {
            return caravana.get();
        }
    }

    for (const auto& cidade : cidades) {
        const auto& caravanasNaCidade = cidade.getCaravanas();
        for (const auto& caravana : caravanasNaCidade) {
            if (caravana->GetNumero() == id) {
                return caravana.get();
            }
        }
    }

    return nullptr;
}






void Mapa::moverCaravana(int numero, const string& direcao) {
    for (auto it = caravanas.begin(); it != caravanas.end(); ++it) {
        if ((*it)->GetNumero() == numero) {
            int linhaAtual = (*it)->GetLinha();
            int colunaAtual = (*it)->GetColuna();

            int dx = 0, dy = 0;
            obterDeslocamento(direcao, dx, dy);

            int novaLinha = (linhaAtual + dx + linhas) % linhas;
            int novaColuna = (colunaAtual + dy + colunas) % colunas;
            char elementoDestino = grid[novaLinha][novaColuna];

            if (islower(elementoDestino)) {
                for (auto& cidade : cidades) {
                    if (cidade.getChar() == elementoDestino) {
                        //cidade.adicionarCaravana(std::move(*it));
                        //caravanas.erase(it);
                        grid[linhaAtual][colunaAtual] = '.';
                        return;
                    }
                }
            }

            if (grid[novaLinha][novaColuna] != '.') {
                return;
            }

            grid[linhaAtual][colunaAtual] = '.';
            grid[novaLinha][novaColuna] = (*it)->GetNumero() + '0';
            (*it)->setPosicao(novaLinha, novaColuna);
            return;
        }
    }
}


bool Mapa::verificarProximidadeCidade(int idCaravana) const {
    // Obtém a caravana pelo ID
    Caravana* caravana = obterCaravanaPorId(idCaravana);
    if (!caravana) {
        std::cerr << "Erro: Caravana com ID " << idCaravana << " não encontrada.\n";
        return false;
    }

    // Verifica os caracteres ao redor da caravana
    return (islower(caravana->getC()) || islower(caravana->getCE()) || islower(caravana->getCD()) ||
            islower(caravana->getB()) || islower(caravana->getBE()) || islower(caravana->getBD()) ||
            islower(caravana->getE()) || islower(caravana->getD()));
}



void Mapa::moverCaravanaNoMapa(std::vector<std::unique_ptr<Caravana>>::iterator& it, const std::string& direcao) {
    int linhaAtual = (*it)->GetLinha();
    int colunaAtual = (*it)->GetColuna();

    // Determina o deslocamento com base na direção
    int dx = 0, dy = 0;
    obterDeslocamento(direcao, dx, dy);

    int novaLinha = (linhaAtual + dx + linhas) % linhas;
    int novaColuna = (colunaAtual + dy + colunas) % colunas;

    if (grid[novaLinha][novaColuna] != '.') {
        std::cout << "Movimento inválido: posição ocupada.\n";
        return;
    }

    grid[linhaAtual][colunaAtual] = '.';
    grid[novaLinha][novaColuna] = (*it)->GetNumero() + '0';
    (*it)->setPosicao(novaLinha, novaColuna);
    (*it)->atualizarCaracteresAoRedor(*this);

    std::cout << "Caravana " << (*it)->GetNumero() << " movida para (" << novaLinha << ", " << novaColuna << ").\n";
}

/*
void Mapa::moverCaravanaNaCidade(Cidade& cidade, std::vector<std::unique_ptr<Caravana>>::iterator& it, const std::string& direcao) {
    int linhaAtual = (*it)->GetLinha();
    int colunaAtual = (*it)->GetColuna();

    int dx = 0, dy = 0;
    obterDeslocamento(direcao, dx, dy);

    int novaLinha = (linhaAtual + dx + linhas) % linhas;
    int novaColuna = (colunaAtual + dy + colunas) % colunas;

    if (grid[novaLinha][novaColuna] != '.') {
        std::cout << "Movimento inválido: posição ocupada.\n";
        return;
    }

    // Atualiza o grid e move a caravana para fora da cidade
    grid[novaLinha][novaColuna] = (*it)->GetNumero() + '0';
    (*it)->setPosicao(novaLinha, novaColuna);
    (*it)->atualizarCaracteresAoRedor(*this);

    // Move a caravana de volta para o vetor global de caravanas
    caravanas.push_back(std::move(*it));
    cidade.getCaravanas().erase(it);

    std::cout << "Caravana " << (*it)->GetNumero() << " saiu da cidade " << cidade.getNome() << " e moveu-se para (" << novaLinha << ", " << novaColuna << ").\n";
}

void Mapa::sairDaCidade(int numero, const std::string& direcao) {
    for (auto& cidade : cidades) {
        auto& caravanasNaCidade = cidade.getCaravanas();
        for (auto it = caravanasNaCidade.begin(); it != caravanasNaCidade.end(); ++it) {
            if ((*it)->GetNumero() == numero) {
                int linhaAtual = (*it)->GetLinha();
                int colunaAtual = (*it)->GetColuna();

                int dx = 0, dy = 0;
                obterDeslocamento(direcao, dx, dy);

                int novaLinha = (linhaAtual + dx + linhas) % linhas;
                int novaColuna = (colunaAtual + dy + colunas) % colunas;

                if (grid[novaLinha][novaColuna] != '.') {
                    std::cout << "Movimento inválido: posição ocupada.\n";
                    return;
                }

                grid[novaLinha][novaColuna] = (*it)->GetNumero() + '0';
                (*it)->setPosicao(novaLinha, novaColuna);
                caravanas.push_back(std::move(*it));
                caravanasNaCidade.erase(it);
                std::cout << "Caravana " << numero << " saiu da cidade " << cidade.getNome() << " e moveu-se para (" << novaLinha << ", " << novaColuna << ").\n";
                return;
            }
        }
    }

    std::cout << "Caravana com o número " << numero << " não encontrada em nenhuma cidade.\n";
}

*/


void Mapa::obterDeslocamento(const std::string& direcao, int& dx, int& dy) const {
    if (direcao == "D")      { dy = 1; }
    else if (direcao == "E") { dy = -1; }
    else if (direcao == "C") { dx = -1; }
    else if (direcao == "B") { dx = 1; }
    else if (direcao == "CE") { dx = -1; dy = -1; }
    else if (direcao == "CD") { dx = -1; dy = 1; }
    else if (direcao == "BE") { dx = 1; dy = -1; }
    else if (direcao == "BD") { dx = 1; dy = 1; }
    else {
        std::cout << "Direção inválida.\n";
    }
}


char Mapa::obterElemento(int linha, int coluna) const {
    return grid[linha][coluna];
}

void Mapa::atualizarElemento(int linha, int coluna, char elemento) {
    grid[linha][coluna] = elemento;
}

int Mapa::getDurancaoItem() {
    return instantes_entre_novos_itens;
}

void Mapa::desenhar(Buffer& buffer) const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            buffer.moveCursor(i, j);
            buffer.write(grid[i][j]);
        }
    }
}


// Atualiza a duração dos itens no mapa
void Mapa::atualizarItens(int instantes) {
    auto it = itens.begin();
    while (it != itens.end()) {
        if ((*it)->decrementarDuracao(instantes)) {
            grid[(*it)->GetLinha()][(*it)->GetColuna()] = '.'; // Limpa a posição do item no grid
            it = itens.erase(it);
        } else {
            ++it;
        }
    }
}


// Gera itens aleatórios no mapa
void Mapa::gerarItensAleatorios() {
    int linha, coluna;
    int tentativas = 0;
    int maxTentativas = 100; // Limite para evitar loops infinitos

    if (itens.size() >= max_itens) {
        return; // Já atingiu o limite de itens no mapa
    }

    // Gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd()); // Gerador de números aleatórios
    uniform_int_distribution<> distribLinha(0, linhas - 1);
    uniform_int_distribution<> distribColuna(0, colunas - 1);

    // Tenta encontrar uma posição válida no mapa
    do {
        linha = distribLinha(gen);
        coluna = distribColuna(gen);
        tentativas++;
    } while (tentativas < maxTentativas && grid[linha][coluna] != '.');

    if (tentativas == maxTentativas) {
        cerr << "Erro: Não foi possível encontrar uma posição vazia para um novo item.\n";
        return;
    }

    // Gerar um item aleatório
    unique_ptr<Item> novoItem;
    uniform_int_distribution<> tipoDistrib(0, 4);

    int tipo = tipoDistrib(gen);
    switch (tipo) {
        case 0:
            novoItem = std::make_unique<CaixaDePandora>("CaixaDePandora", linha, coluna, duracao_item);
            break;
        case 1:
            novoItem = std::make_unique<Jaula>("Jaula", linha, coluna, duracao_item);
            break;
        case 2:
            novoItem = std::make_unique<ArcaDoTesouro>("ArcaDoTesouro", linha, coluna, duracao_item);
            break;
        case 3:
            novoItem = std::make_unique<Mina>("Mina", linha, coluna, duracao_item);
            break;
        case 4:
            novoItem = std::make_unique<Oasis>("Oasis", linha, coluna, duracao_item);
            break;
        default:
            cerr << "Erro: Tipo de item inválido gerado.\n";
            return;
    }

    // Adiciona o item ao vetor e atualiza o grid
    itens.push_back(std::move(novoItem));
    grid[linha][coluna] = '#'; // Representação do item no mapa
}



// Mostra os itens existentes no mapa
void Mapa::mostrarItens() const {
    for (const auto& item : itens) {
        std::cout << item->exibir() << std::endl;
    }
}

// Adiciona ou remove moedas do total
int Mapa::AdicionaMoedas(int m) {
    moedas += m;
    return moedas;
}

int Mapa::setMoedas(int v) {
    moedas = v;
    return 0;
}

void Mapa::MostraCaravanaById(int id) {
    Caravana* caravana = obterCaravanaPorId(id);
    if (caravana) {
        std::cout << "Caravana encontrada. Exibindo informações:\n";
        caravana->exibir();
    } else {
        std::cout << "Caravana com ID " << id << " não encontrada.\n";
    }
}


void Mapa::compraTripula(int idCaravana, int quantidade) {
    for (auto& cidade : cidades) {
        auto& caravanasNaCidade = cidade.getCaravanas(); // Obtém o vetor de caravanas da cidade
        for (auto it = caravanasNaCidade.begin(); it != caravanasNaCidade.end(); ++it) {
            if ((*it)->GetNumero() == idCaravana) { // Verifica se o ID da caravana corresponde

                if (getMoedas() >= quantidade) {
                    if ((*it)->CompraTripulacao(quantidade)) { // Adiciona a tripulação à caravana
                        std::cout << "\nAdicionados " << quantidade
                                  << " tripulantes à caravana com ID " << idCaravana
                                  << " na cidade " << cidade.getNome() << ".\n";
                        setMoedas(getMoedas() - quantidade); // Deduz moedas correspondentes
                        return; // Encerra a busca ao encontrar a caravana
                    } else {
                        std::cout << "\nNão foi possível adicionar os tripulantes à caravana com ID "
                                  << idCaravana << " na cidade " << cidade.getNome() << ".\n";
                        return;
                    }
                } else {
                    std::cout << "\nMoedas insuficientes, Moedas atuais: " << getMoedas() << "\n";
                    return;
                }
            }
        }
    }

    // Caso nenhuma caravana com o ID fornecido seja encontrada
    std::cout << "Caravana com ID " << idCaravana << " não encontrada em nenhuma cidade.\n";
}


int Mapa::getPrecoVenda() const {
    return preco_venda_mercadoria;
}

int Mapa::getPrecoCompra() const {
    return preco_compra_mercadoria;
}
const vector<Cidade>& Mapa::getCidades() const {
    return cidades;
}

void Mapa::MostraPrecos() {
    cout << "\n Preco de venda de mercadoria: " << getPrecoVenda();
    cout << "\n Preco de compra de mercadoria: " << getPrecoCompra();
}

void Mapa::VendeMercadorias(int idCaravana) {
    for (auto& cidade : cidades) {
        auto& caravanasNaCidade = cidade.getCaravanas(); // Obtem o vetor de caravanas da cidade
        for (auto it = caravanasNaCidade.begin(); it != caravanasNaCidade.end(); ++it) {
            if ((*it)->GetNumero() == idCaravana) { // Verifica se o ID da caravana corresponde
                // Vender mercadoria: Define a quantidade para 0
                int auxiliar = (*it)->GetCargaAtual();
                if((*it)->VendeCarga()){
                    setMoedas(getMoedas() + auxiliar * 2);
                    std::cout << "Toda a mercadoria da caravana com ID " << idCaravana
                              << " foi vendida na cidade " << cidade.getNome() << ".\n";
                    return; // Encerra a busca ao encontrar a caravana
                }

            }
        }
    }

    // Caso nenhuma caravana com o ID fornecido seja encontrada
    std::cout << "Caravana com ID " << idCaravana << " não encontrada em nenhuma cidade.\n";
}

void Mapa::CompraMercadoria(int idCaravana, int quantidade) {
    for (auto& cidade : cidades) {
        auto& caravanasNaCidade = cidade.getCaravanas(); // Obtem o vetor de caravanas da cidade
        for (auto it = caravanasNaCidade.begin(); it != caravanasNaCidade.end(); ++it) {
            if ((*it)->GetNumero() == idCaravana) { // Verifica se o ID da caravana corresponde

                if(getMoedas() >= quantidade) {
                    if ((*it)->CompraCarga(quantidade)) { // Comprar mercadoria: Adiciona a quantidade à mercadoria atual
                        std::cout << "\nAdicionadas " << quantidade
                                  << " unidades de mercadoria à caravana com ID " << idCaravana
                                  << " na cidade " << cidade.getNome() << ".\n";
                        setMoedas(getMoedas() - quantidade);
                        return; // Encerra a busca ao encontrar a caravana
                    }
                }
                else{
                    cout << "\n Moedas insuficientes, Moedas atuais: " << getMoedas();
                    return;
                }

            }
        }
    }

    // Caso nenhuma caravana com o ID fornecido seja encontrada
    std::cout << "Caravana com ID " << idCaravana << " não encontrada em nenhuma cidade.\n";
}

bool Mapa::verificarCaravanaProxima(int idCaravana) const {
    Caravana* caravana = obterCaravanaPorId(idCaravana);
    if (!caravana) {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
        return false;
    }

    char posicoes[] = {
            caravana->getC(),
            caravana->getCE(),
            caravana->getCD(),
            caravana->getB(),
            caravana->getBE(),
            caravana->getBD(),
            caravana->getE(),
            caravana->getD()
    };

    for (char pos : posicoes) {
        if (isdigit(pos)) {
            std::cout << "Outra caravana detectada ao redor da caravana " << idCaravana << "!\n";
            return true;
        }
    }

    return false;
}


bool Mapa::verificarBarbarosProximos(int idCaravana) const {
    Caravana* caravana = obterCaravanaPorId(idCaravana);
    if (!caravana) {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
        return false;
    }

    // Verificar as posições ao redor da caravana
    char posicoes[] = {
            caravana->getC(),
            caravana->getCE(),
            caravana->getCD(),
            caravana->getB(),
            caravana->getBE(),
            caravana->getBD(),
            caravana->getE(),
            caravana->getD()
    };

    for (char pos : posicoes) {
        if (pos == '!') { // Verifica se é uma caravana bárbara
            std::cout << "Bárbaros detectados ao redor da caravana " << idCaravana << "!\n";
            return true;
        }
    }

    return false;
}

void Mapa::resolverCombates() {
    for (auto itCaravana = caravanas.begin(); itCaravana != caravanas.end();) {
        Caravana* caravana = itCaravana->get();

        // Verificar bárbaros próximos
        bool combateResolvido = false;
        for (auto itBarbaro = barbaras.begin(); itBarbaro != barbaras.end();) {
            CBarbaras* barbaro = itBarbaro->get();

            // Combate ocorre se estão na mesma posição
            if (std::abs(caravana->GetLinha() - barbaro->GetLinha()) <= 1 &&
                std::abs(caravana->GetColuna() - barbaro->GetColuna()) <= 1) {

                // Sorteio dos valores de combate
                int utilizadorSorteio = rand() % (caravana->GetTripulacao() + 1);
                int barbaroSorteio = rand() % (barbaro->GetTripulacao() + 1);

                if (utilizadorSorteio > barbaroSorteio) {
                    // Vitória da caravana do utilizador
                    int perdaBarbaro = 2 * utilizadorSorteio;
                    int perdaUtilizador = static_cast<int>(std::floor(0.2 * caravana->GetTripulacao()));

                    barbaro->SetTripulacao(barbaro->GetTripulacao() - perdaBarbaro);
                    caravana->SetTripulacao(caravana->GetTripulacao() - perdaUtilizador);

                    // Transferir água do bárbaro para o utilizador
                    int aguaTransferida = std::min(barbaro->GetAgua(),
                                                   caravana->GetCapacidadeCarga() - caravana->GetCargaAtual());
                    caravana->AjustarAgua(aguaTransferida);

                    std::cout << "Caravana utilizador venceu o combate! Perdeu " << perdaUtilizador << " tripulantes.\n";

                    // Remove bárbaro se não houver tripulação restante
                    if (barbaro->GetTripulacao() <= 0) {
                        grid[barbaro->GetLinha()][barbaro->GetColuna()] = '.'; // Limpa o grid
                        itBarbaro = barbaras.erase(itBarbaro);
                        std::cout << "Barbaro foi eliminado.\n";
                    } else {
                        ++itBarbaro;
                    }

                } else {
                    // Vitória do bárbaro
                    int perdaUtilizador = 2 * barbaroSorteio;
                    int perdaBarbaro = static_cast<int>(std::floor(0.2 * barbaro->GetTripulacao()));

                    caravana->SetTripulacao(caravana->GetTripulacao() - perdaUtilizador);
                    barbaro->SetTripulacao(barbaro->GetTripulacao() - perdaBarbaro);

                    // Transferir água do utilizador para o bárbaro
                    int aguaTransferida = std::min(caravana->GetAgua(),
                                                   barbaro->GetCapacidadeCarga() - barbaro->GetCargaAtual());
                    barbaro->AjustarAgua(aguaTransferida);

                    std::cout << "Caravana bárbara venceu o combate! Perdeu " << perdaBarbaro << " tripulantes.\n";

                    // Remove caravana do utilizador se não houver tripulação restante
                    if (caravana->GetTripulacao() <= 0) {
                        grid[caravana->GetLinha()][caravana->GetColuna()] = '.'; // Limpa o grid
                        itCaravana = caravanas.erase(itCaravana);
                        std::cout << "Caravana do utilizador foi eliminada.\n";
                        combateResolvido = true;
                        break;
                    } else {
                        ++itBarbaro;
                    }
                }
            } else {
                ++itBarbaro;
            }
        }

        if (!combateResolvido) {
            ++itCaravana;
        }
    }
}

void Mapa::removerCaravana(Caravana* caravana) {
    for (auto it = caravanas.begin(); it != caravanas.end(); ++it) {
        if (it->get() == caravana) {
            caravanas.erase(it);
            return;
        }
    }
}

const vector<unique_ptr<Caravana>>& Mapa::getCaravanas() const {
    return caravanas;
}

const std::vector<std::unique_ptr<CBarbaras>>& Mapa::getBarbaros() const {
    return barbaras;
}


bool Mapa::validarMovimento(int linha, int coluna) const {
    // Verifica se a posição está dentro dos limites do mapa
    if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
        return false;
    }
    // Verifica se a posição no grid está vazia
    return grid[linha][coluna] == '.';
}

int Mapa::getMoedas() const {
    return moedas;
}

const std::vector<std::unique_ptr<Item>> &Mapa::getItens() const {
    return itens; // Onde `itens` é o vetor que armazena os itens no mapa
}

void Mapa::alterarGrid(int l, int col, char c) {
    grid[l][col] = c;
}


void Mapa::ColocaBarbaro(int lin, int col) {

    // Verifica se as coordenadas são válidas (adapte conforme necessário)
    if (lin < 0 || col < 0 || lin >= getLinhas() || col >= getColunas() && grid[lin][col] == '.') {
        std::cerr << "Erro: Coordenadas inválidas (" << lin << ", " << col << ").\n";
        return;
    }

    // Criação da caravana bárbara
    barbaras.push_back(make_unique<CBarbaras>(barbaras.size() + 1, lin, col, *this));

    // Atualiza o mapa (se necessário, marcando a posição da caravana)
    grid[lin][col] = '!';
}