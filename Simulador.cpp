//
// Created by Enrique Marques on 20/12/2024.
//

#include "Simulador.h"
#include "Comandos.h"
#include "Cidade.h"

bool fileExists(const std::string& filename) {
    return fs::exists(filename);
}

int Simulador::processarComandos(const string& RespostaComando, int &contador) {
    istringstream iss(RespostaComando);
    vector<string> ComandoParaExecutar{
            istream_iterator<string>{iss},
            istream_iterator<string>{}
    };

    if (ComandoParaExecutar.empty()) return 1;

    if (ComandoParaExecutar[0] == "exec") {
        cout << "\nA executar comando exec: Le comandos do ficheiro " << ComandoParaExecutar[1];
        // Implementação para carregar e executar comandos de um ficheiro
    }
    else if (ComandoParaExecutar[0] == "prox") {
        cout << "\nA executar comando prox";
        instantes += stoi(ComandoParaExecutar[1]);
        cout << "\nValor de instantes " << instantes << " Valor de Duracao: " << contador;

        mapa.atualizarItens(stoi(ComandoParaExecutar[1]));

        // Atualizar o estado de todas as caravanas
        for (auto& caravana : mapa.getCaravanas()) {
            caravana->atualizarEstado(mapa);
        }

        if (instantes >= contador) {
            cout << "\nEntrou aqui";
            mapa.gerarItensAleatorios();
            mapa.desenhar(buffer);
            buffer.display();
            contador += Mapa::getDurancaoItem();
            mapa.mostrarItens();
        }
    }

    else if (ComandoParaExecutar[0] == "comprac") {
        cout << "\nA executar comando comprac na cidade " << ComandoParaExecutar[1]
             << " para adquirir uma caravana do tipo " << ComandoParaExecutar[2];
        // Implementação para comprar uma caravana do tipo indicado
    }
    else if (ComandoParaExecutar[0] == "precos") {
        cout << "\nA executar comando precos: Listando os preços das mercadorias.";
        mapa.MostraPrecos();
    }

    else if (ComandoParaExecutar[0] == "cidade") {
        cout << "\nA executar comando 'cidade' para a cidade: " << ComandoParaExecutar[1] << "\n\n";

        string nomeCidade = ComandoParaExecutar[1]; // Nome completo da cidade
        bool cidadeEncontrada = false;

        for (const auto& cidade : mapa.getCidades()) {
            if (cidade.getNome() == nomeCidade) {
                cidade.listarCaravanas();
                cidadeEncontrada = true;
                break;
            }
        }

        if (!cidadeEncontrada) {
            std::cout << "Cidade com nome \"" << nomeCidade << "\" não encontrada.\n";
        }
    }


    else if (ComandoParaExecutar[0] == "caravana") {
        cout << "\nA executar comando caravana: Mostrando descrição da caravana " << ComandoParaExecutar[1];
        // Implementação para mostrar detalhes da caravana
        mapa.MostraCaravanaById(stoi(ComandoParaExecutar[1]));
    }


    else if (ComandoParaExecutar[0] == "compra") {
        cout << "\nA executar comando compra: Comprando " << ComandoParaExecutar[2]
             << " toneladas para a caravana " << ComandoParaExecutar[1];
        // Implementação para comprar mercadorias

        mapa.CompraMercadoria(stoi(ComandoParaExecutar[1]),stoi(ComandoParaExecutar[2]));
    }
    else if (ComandoParaExecutar[0] == "vende") {
        cout << "\nA executar comando vende: Vendendo toda a mercadoria da caravana " << ComandoParaExecutar[1];
        mapa.VendeMercadorias(stoi(ComandoParaExecutar[1]));
    }

    else if (ComandoParaExecutar[0] == "move") {
        cout << "\nA executar comando move: Movendo a caravana " << ComandoParaExecutar[1]
             << " para a direção " << ComandoParaExecutar[2];

        int idCaravana = stoi(ComandoParaExecutar[1]);

        // Mover a caravana
        mapa.moverCaravana(idCaravana, ComandoParaExecutar[2]);

        // Atualizar os caracteres ao redor da caravana após o movimento
        Caravana* caravanaMovida = mapa.obterCaravanaPorId(idCaravana);
        if (caravanaMovida) {
            caravanaMovida->atualizarCaracteresAoRedor(mapa);

            // Verificar se a caravana está próxima de uma cidade

            // Exibir estado da caravana e proximidade de cidades
            cout << "\nEstado da caravana após o movimento:\n";
            caravanaMovida->exibir();

            if (mapa.verificarProximidadeCidade(idCaravana)) {
                cout << "A caravana está próxima de uma cidade!" << endl;
            }

            // Verificar se há caravanas próximas
            if (mapa.verificarCaravanaProxima(idCaravana)) {
                std::cout << "A caravana " << idCaravana << " está próxima de outra caravana.\n";
            }

            // Verificar se há bárbaros próximos
            if (mapa.verificarBarbarosProximos(idCaravana)) {
                std::cout << "A caravana " << idCaravana << " está próxima de bárbaros.\n";

                mapa.resolverCombates();

            }


            bool itemProximo = false;
            for (const auto& item : mapa.getItens()) {
                int dx = abs(caravanaMovida->GetLinha() - item->GetLinha());
                int dy = abs(caravanaMovida->GetColuna() - item->GetColuna());

                // Verifica se o item está diretamente acima, abaixo, à esquerda ou à direita
                if ((dx == 0 && abs(dy) == 1) || (abs(dx) == 1 && dy == 0)) {
                    itemProximo = true;
                    cout << "A caravana está proxima de um item: " << item->GetTipo() << " na posição ("
                         << item->GetLinha() << ", " << item->GetColuna() << ").\n";
                    item->aplicarEfeito(*caravanaMovida,&mapa);
                    mapa.alterarGrid(item->GetLinha(),item->GetColuna(),'.');
                    break;
                }
            }

            if (itemProximo) {
                cout << "A caravana está próxima de um item!" << endl;
            }

        } else {
            cout << "\nErro: Caravana com ID " << idCaravana << " não encontrada.\n";
        }

        // Atualizar o buffer e exibição
        mapa.desenhar(buffer);
        buffer.display();
    }

    else if (ComandoParaExecutar[0] == "auto") {
        cout << "\nA executar comando auto: Ativando auto-gestão para a caravana " << ComandoParaExecutar[1];
        int idCaravana = stoi(ComandoParaExecutar[1]);
        Caravana* caravana = mapa.obterCaravanaPorId(idCaravana);

        if (caravana) {
            caravana->moverAutonomo(mapa);
            mapa.desenhar(buffer);
            buffer.display();
            cout << "\nMovimentação autônoma realizada para a caravana " << idCaravana;
        } else {
            cout << "\nErro: Caravana com ID " << idCaravana << " não encontrada.";
        }
    }

    else if (ComandoParaExecutar[0] == "stop") {
        cout << "\nA executar comando stop: Parando auto-gestão para a caravana " << ComandoParaExecutar[1];
        // Implementação para parar auto-gestão
    }
    else if (ComandoParaExecutar[0] == "barbaro") {
        cout << "\nA executar comando barbaro: Criando caravana bárbara em ("
             << ComandoParaExecutar[1] << ", " << ComandoParaExecutar[2] << ")";
        mapa.ColocaBarbaro(stoi(ComandoParaExecutar[1]), stoi(ComandoParaExecutar[2]));
        mapa.desenhar(buffer);
        buffer.display();
    }

    else if (ComandoParaExecutar[0] == "areia") {
        cout << "\nA executar comando areia: Criando tempestade em ("
             << ComandoParaExecutar[1] << ", " << ComandoParaExecutar[2]
             << ") com raio " << ComandoParaExecutar[3];

        int centroLinha = stoi(ComandoParaExecutar[1]);
        int centroColuna = stoi(ComandoParaExecutar[2]);
        int raio = stoi(ComandoParaExecutar[3]);

        for (auto& caravana : mapa.getCaravanas()) {
            int distancia = abs(caravana->GetLinha() - centroLinha) + abs(caravana->GetColuna() - centroColuna);
            if (distancia <= raio) {
                caravana->aplicarTempestadeDeAreia();
            }
        }

        cout << "\nTempestade de areia aplicada!";
        mapa.desenhar(buffer);
        buffer.display();
    }

    else if (ComandoParaExecutar[0] == "moedas") {
        cout << "\nA executar comando moedas: Adicionando " << ComandoParaExecutar[1] << " moedas.";
        int m = mapa.AdicionaMoedas(stoi(ComandoParaExecutar[1]));

        if(stoi(ComandoParaExecutar[1]) > 0)
            cout << "\nMoedas adicionadas ";
        else
            cout << "\nMoedas retiradas ";

        cout << "\nMoedas atuais: " << m;
    }
    else if (ComandoParaExecutar[0] == "tripul") {
        cout << "\nA executar comando tripul: Adicionando " << ComandoParaExecutar[2]
             << " tripulantes à caravana " << ComandoParaExecutar[1];

        mapa.compraTripula(stoi(ComandoParaExecutar[1]),stoi(ComandoParaExecutar[2]));
    }
    else if (ComandoParaExecutar[0] == "saves") {
        cout << "\nA executar comando saves: Salvando estado do buffer com o nome " << ComandoParaExecutar[1];
        this->saveBuffer(ComandoParaExecutar[1]);
    }
    else if (ComandoParaExecutar[0] == "loads") {
        cout << "\nA executar comando loads: Recuperando estado do buffer com o nome " << ComandoParaExecutar[1];
        this->loadBuffer(ComandoParaExecutar[1]);
        buffer.display();
    }
    else if (ComandoParaExecutar[0] == "lists") {
        cout << "\nA executar comando lists: Listando cópias do buffer.";
        // Implementação para listar os nomes das cópias
        this->listBuffers();
    }
    else if (ComandoParaExecutar[0] == "dels") {
        cout << "\nA executar comando dels: Apagando cópia do buffer com o nome " << ComandoParaExecutar[1];
        // Implementação para apagar cópia do buffer
        this->deleteBuffer(ComandoParaExecutar[1]);
    }
    else if (ComandoParaExecutar[0] == "terminar") {
        cout << "\nA executar comando terminar: Finalizando a simulacao.";
        cout << "\nNumero de instantes decorrido :" << instantes;
        cout << "\nNumero total de combates vencidos :";                // Falta mostrar isto quando terminar a simulação e dar delete de todas as classes
        cout << "\nNumero de moedas :" << mapa.AdicionaMoedas(0);
        fase = 1;
        return 0;
    }
    else {
        cout << "\nComando errado: " << RespostaComando;
        // Mensagem de erro para comando inválido
    }
    return 1;
}


void Simulador::iniciar() {

    cout << "\nBem vindo ao programa";
    string input,nome_fich,cmd;

    map<std::string, Comandos> ListaDeComandos;
    InicializarComandos(ListaDeComandos);
    string RespostaComando;
    int contador = 0;

    while (true) {
        cout << "\n>";
        getline(cin, input); // Lê a linha inteira
        stringstream ss(input);
        ss >> cmd >> nome_fich;

        if (cmd == "sair") {
            cout << "\nSaindo do programa...";
            break;
        }

        if (fase == 1) { // Fase de carregar mapa
            if (cmd == "config" && !nome_fich.empty()) {
                if (mapa.carregarMapa(nome_fich)) {
                    cout << "\n Mapa carregado com sucesso!" << endl;
                    cout << "Dimensoes do mapa: " << mapa.getLinhas() << "x" << mapa.getColunas() << endl;

                    buffer.resize(mapa.getLinhas(), mapa.getColunas());
                    cout << "Buffer criado com sucesso!" << endl;

                    mapa.desenhar(buffer);
                    cout << "Mapa desenhado no buffer." << endl;

                    buffer.display();
                    cout << "Buffer exibido na consola." << endl;

                    fase = 2; // Avança para a próxima fase
                    contador = Mapa::getDurancaoItem();
                } else {
                    cout << "Erro ao carregar o mapa. Verifique o ficheiro e tente novamente." << endl;
                }
            } else {
                cout << "\nComando invalido na fase 1. Use 'config <nome_ficheiro>' ou 'sair'." << endl;
            }
        }
        else { // Fase de execução de comandos
            if (!input.empty())
                RespostaComando = VerificarComandos(input, ListaDeComandos);

            if (!RespostaComando.empty())
                processarComandos(RespostaComando, contador); // Process the command
            else
                cout << "\nComando nao encontrado, ou invalido. Tente novamente.";

        }
        input.clear();
        RespostaComando.clear();
    }
}

Simulador::Simulador():instantes(0), fase(1) {

}

Simulador::~Simulador() {

}

void Simulador::saveBuffer(const string &name) {
        ofstream outFile(BUFFER_FILE, ios::app);
        if (!outFile) {
            cerr << "Erro ao abrir o ficheiro para escrita.\n";
            return;
        }
        string serialized = buffer.serialize();
        outFile << name << ":" << serialized << "\n";
        outFile.close();
        cout << "Buffer salvo como '" << name << "'.\n";
}

void Simulador::loadBuffer(const string &name) {
    if (!fileExists(BUFFER_FILE)) {
        cerr << "Ficheiro de buffers não existe.\n";
        return;
    }

    ifstream inFile(BUFFER_FILE);
    if (!inFile) {
        cerr << "Erro ao abrir o ficheiro para leitura.\n";
        return;
    }

    string line;
    bool isTargetBuffer = false;
    string bufferData;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue; // Ignora linhas vazias
        }

        if (line.back() == ':') { // Nome do buffer (e.g., "estado1:")
            string bufferName = line.substr(0, line.size() - 1);

            if (bufferName == name) {
                isTargetBuffer = true; // Encontrou o buffer desejado
                bufferData.clear();    // Prepara para coletar as linhas do buffer
            } else if (isTargetBuffer) {
                break; // Se já estava coletando, encontrou outro buffer, então para
            }
        } else if (isTargetBuffer) {
            bufferData += line + '\n'; // Adiciona a linha ao buffer com quebra de linha
        }
    }

    inFile.close();

    if (!bufferData.empty()) {
        buffer.deserialize(bufferData);
        cout << "Buffer '" << name << "' carregado com sucesso.\n";
    } else {
        cerr << "Buffer com nome '" << name << "' não encontrado ou está vazio.\n";
    }
}

void Simulador::listBuffers() const {
    if (!fileExists(BUFFER_FILE)) {
        cout << "Nenhum buffer salvo.\n";
        return;
    }

    ifstream inFile(BUFFER_FILE);
    if (!inFile) {
        cerr << "Erro ao abrir o ficheiro para leitura.\n";
        return;
    }

    string line;
    cout << "Buffers salvos:\n";
    while (getline(inFile, line)) {
        size_t delimPos = line.find(':');
        if (delimPos != string::npos) {
            string bufferName = line.substr(0, delimPos);
            cout << "- " << bufferName << "\n";
        }
    }
    inFile.close();
}

void Simulador::deleteBuffer(const string &name) {
    if (!fileExists(BUFFER_FILE)) {
        cerr << "Ficheiro de buffers não existe.\n";
        return;
    }

    ifstream inFile(BUFFER_FILE);
    if (!inFile) {
        cerr << "Erro ao abrir o ficheiro para leitura.\n";
        return;
    }

    stringstream tempBuffer;
    string line;
    bool found = false;
    bool isDeleting = false;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue; // Ignorar linhas vazias
        }

        if (line.back() == ':') { // Linha de nome do buffer
            string bufferName = line.substr(0, line.size() - 1);

            if (bufferName == name) {
                found = true;
                isDeleting = true; // Ativar a exclusão de linhas
                continue;          // Ignorar esta linha (nome do buffer)
            }

            if (isDeleting) {
                isDeleting = false; // Encontrou outro buffer, parar exclusão
            }
        }

        if (!isDeleting) {
            tempBuffer << line << "\n"; // Manter as linhas não relacionadas ao buffer a ser apagado
        }
    }
    inFile.close();

    if (!found) {
        cerr << "Buffer com nome '" << name << "' não encontrado.\n";
        return;
    }

    ofstream outFile(BUFFER_FILE, ios::trunc);
    outFile << tempBuffer.str();
    outFile.close();

    cout << "Buffer '" << name << "' deletado com sucesso.\n";
}

bool Simulador::fileExists(const string &filename) const {
    return fs::exists(filename);
}

int main(){
    Simulador simulador;
    simulador.iniciar();
    return 0;
}
