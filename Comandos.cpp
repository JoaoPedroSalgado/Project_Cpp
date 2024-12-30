//
// Created by Enrique Marques on 19/12/2024.
//

#include "Comandos.h"
#include "Simulador.h"

bool eNumero(const string& str) {
    if (str.empty()) {
        return false; // String vazia não é um número
    }

    // Verifica se o primeiro caractere é um dígito ou um sinal '-'
    size_t start = 0;
    if (str[0] == '-') {
        if (str.size() == 1) {
            return false; // Apenas '-' não é um número
        }
        start = 1; // Ignora o sinal para os próximos caracteres
    }

    // Verifica se os caracteres restantes são dígitos
    for (size_t i = start; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

string VerificarComandos(const string& ComandoRecebido, map<string, Comandos>& ListaDeComandos) {

    istringstream iss(ComandoRecebido);  // Separa string em várias strings por espaços
    vector<string> ArgumentosRecebidosSeparado{
            istream_iterator<string>{iss},
            istream_iterator<string>{}
    };
    // Iterador responsavel por tentar encontrar um objecto com mesmo nome que o comando introduzido
    auto ComandoEncontrado = ListaDeComandos.find(ArgumentosRecebidosSeparado[0]);
    int NumeroArgsRemovido0 = ArgumentosRecebidosSeparado.size() - 1;
    // if que verifica que encontrou o comando no array da classe Comandos
    if (ComandoEncontrado != ListaDeComandos.end()) {
        // verificar se os argumentos obrigatórios estão em ordem
        if (NumeroArgsRemovido0 < ComandoEncontrado->second.nArgsObrigatorios){

            string Resultado = "[X] Numero de Argumentos Invalido!"
                               "\nMinimo: " +
                               to_string(ComandoEncontrado->second.nArgsObrigatorios) +
                               "\nIntroduziu: "+
                               to_string(NumeroArgsRemovido0) +
                               "\nComando aceita args do tipo";

            string MostrarArgumentos = "\n{";
            for (size_t i = 0; i < ComandoEncontrado->second.TipoDeArgs.size(); ++i) {
                MostrarArgumentos += "\"" + ComandoEncontrado->second.TipoDeArgs[i] + "\"";
                if (i < ComandoEncontrado->second.TipoDeArgs.size() - 1) {
                    MostrarArgumentos += ", ";
                }
            }
            MostrarArgumentos += "}";

            return Resultado + MostrarArgumentos;
        }

        if (NumeroArgsRemovido0 > (ComandoEncontrado->second.nArgsObrigatorios + ComandoEncontrado->second.nArgsOptionais)){
            string Resultado = "[Y] Argumentos Invalido!"
                               "\nMax: " +
                                to_string(ComandoEncontrado->second.nArgsObrigatorios) +
                                "\nIntroduziu: "+
                                to_string(NumeroArgsRemovido0) +
                                "\nComando aceita args do tipo";

            string MostrarArgumentos = "\n{";
            for (size_t i = 0; i < ComandoEncontrado->second.TipoDeArgs.size(); ++i) {
                MostrarArgumentos += "\"" + ComandoEncontrado->second.TipoDeArgs[i] + "\"";
                if (i < ComandoEncontrado->second.TipoDeArgs.size() - 1) {
                    MostrarArgumentos += ", ";
                }
            }
            MostrarArgumentos += "}";

            return Resultado + MostrarArgumentos;
        }
        string RespostaExecutada = ComandoEncontrado->second.CodigoExecutar(ArgumentosRecebidosSeparado);

        if (!RespostaExecutada.empty()) {
            return RespostaExecutada;

        } else {
            return ComandoEncontrado->second.Resposta;
        }

    } else {
        return "";
    }
}

void InicializarComandos(map<string, Comandos>& ListaDeComandos) {

    // Fase 2 Comandos
    // Comando: exec <nomeFicheiro>
    ListaDeComandos["exec"] = {1, 0,  // 1 obrigatório, 0 opcionais
                               {"string"},
                               "Le comandos do ficheiro indicado e executa-os.",
                               [](const std::vector<std::string>& args) {
                                   std::stringstream ss;
                                   ss << "exec " << args[1];
                                   return ss.str();
                               },
                               "Resposta para o comando exec"};

    // Comando: prox <n>
    ListaDeComandos["prox"] = {0, 1,  // 0 obrigatório, 1 opcional
                               {"int"},
                               "Avança n instantes, ou 1 se n não for especificado.",
                               [](const vector<string>& args) {
                                   stringstream ss;
                                   int n = 1;

                                   // Verificar se há mais de um argumento (além do nome do comando)
                                   if (args.size() > 1) {
                                       if (eNumero(args[1])) {
                                           n = stoi(args[1]);
                                       } else {
                                           ss << "prox " << 1;
                                           return ss.str();
                                       }
                                   }

                                   ss << "prox " << n;
                                   return ss.str();
                               },
                               "Resposta para o comando prox"};

    // Comando: comprac <C> <T>
    ListaDeComandos["comprac"] = {2, 0,  // 2 obrigatórios, 0 opcionais
                                  {"string", "string"},
                                  "Compra uma caravana do tipo T na cidade C.",
                                  [](const std::vector<std::string>& args) {
                                      std::stringstream ss;
                                      ss << "Comando comprac executado. Cidade: " << args[1] << ", Tipo: " << args[2];
                                      return ss.str();
                                  },
                                  "Resposta para o comando comprac"};

    // Comando: precos
    ListaDeComandos["precos"] = {0, 0,  // 0 obrigatório, 0 opcionais
                                 {},
                                 "Lista os preços das mercadorias.",
                                 [](const std::vector<std::string>& args) {
                                     std::stringstream ss;
                                     ss << "precos";
                                     return ss.str();
                                 },
                                 "Resposta para o comando precos"};

    // Comando: cidade <C>
    ListaDeComandos["cidade"] = {1, 0,  // 1 obrigatório, 0 opcionais
                                 {"string"},
                                 "Lista o conteúdo da cidade indicada.",
                                 [](const std::vector<std::string>& args) {
                                     std::stringstream ss;
                                     ss << "cidade " << args[1];
                                     return ss.str();
                                 },
                                 "Resposta para o comando cidade"};

    // Comando: caravana <C>
    ListaDeComandos["caravana"] = {1, 0,  // 1 obrigatório, 0 opcionais
                                   {"string"},
                                   "Mostra os detalhes da caravana indicada.",
                                   [](const std::vector<std::string>& args) {
                                       std::stringstream ss;
                                       ss << "caravana " << args[1];
                                       return ss.str();
                                   },
                                   "Resposta para o comando caravana"};

    // Comando: compra <N> <M>
    ListaDeComandos["compra"] = {2, 0,  // 2 obrigatórios, 0 opcionais
                                 {"int", "int"},
                                 "Compra M toneladas de mercadorias para a caravana N.",
                                 [](const std::vector<std::string>& args) {
                                     std::stringstream ss;
                                     if (!eNumero(args[1]) || !eNumero(args[2])) {
                                         ss << "Erro: Argumentos inválidos.";
                                         return ss.str();
                                     }
                                     ss << "compra " << args[1] << " " << args[2];
                                     return ss.str();
                                 },
                                 "Resposta para o comando compra"};

    // Comando: vende <N>
    ListaDeComandos["vende"] = {1, 0,  // 1 obrigatório, 0 opcionais
                                {"int"},
                                "Vende toda a mercadoria da caravana N.",
                                [](const std::vector<std::string>& args) {
                                    std::stringstream ss;
                                    if (!eNumero(args[1])) {
                                        ss << "Erro: Argumento inválido.";
                                        return ss.str();
                                    }
                                    ss << "vende " << args[1];
                                    return ss.str();
                                },
                                "Resposta para o comando vende"};

    // Comando: move <N> <X>
    ListaDeComandos["move"] = {2, 0,  // 2 obrigatórios, 0 opcionais
                               {"int", "string"},
                               "Move a caravana N na direção X.",
                               [](const std::vector<std::string>& args) {
                                   std::stringstream ss;
                                   if (!eNumero(args[1])) {
                                       ss << "Erro: Número da caravana inválido.";
                                       return ss.str();
                                   }
                                   ss << "move " << args[1] << " " << args[2];
                                   return ss.str();
                               },
                               "Resposta para o comando move"};

    // Command: auto <N>
    ListaDeComandos["auto"] = {1, 0,
                               {"int"},
                               "Coloca a caravana N em auto-gestão.",
                               [](const vector<string>& args) {
                                   stringstream ss;
                                   if (!eNumero(args[1])) {
                                       ss << "Argumento inválido. Introduza um número.";
                                       return ss.str();
                                   }
                                   ss << "auto " << args[1];
                                   return ss.str();
                               },
                               "Resposta para o comando auto"};

    // Command: stop <N>
    ListaDeComandos["stop"] = {1, 0,
                               {"int"},
                               "Pára o comportamento automático da caravana N.",
                               [](const vector<string>& args) {
                                   stringstream ss;
                                   if (!eNumero(args[1])) {
                                       ss << "Argumento inválido. Introduza um número.";
                                       return ss.str();
                                   }
                                   ss << "Comando stop executado para a caravana: " << args[1];
                                   return ss.str();
                               },
                               "Resposta para o comando stop"};

    // Command: barbaro <l> <c>
    ListaDeComandos["barbaro"] = {2, 0,
                                  {"int", "int"},
                                  "Cria uma caravana bárbara nas coordenadas indicadas.",
                                  [](const vector<string>& args) {
                                      stringstream ss;
                                      if (!eNumero(args[1]) || !eNumero(args[2])) {
                                          ss << "barbaro " << args[1] << " " << args[2];
                                          return ss.str();
                                      }
                                      ss << "Comando barbaro executado nas coordenadas (" << args[1] << ", " << args[2] << ")";
                                      return ss.str();
                                  },
                                  "Resposta para o comando barbaro"};

    // Command: areia <l> <c> <r>
    ListaDeComandos["areia"] = {3, 0,
                                {"int", "int", "int"},
                                "Cria uma tempestade de areia na posição indicada com raio r.",
                                [](const vector<string>& args) {
                                    stringstream ss;
                                    if (!eNumero(args[1]) || !eNumero(args[2]) || !eNumero(args[3])) {
                                        ss << "Argumentos inválidos. Introduza três números.";
                                        return ss.str();
                                    }
                                    ss << "areia " << args[1] << " " << args[2] << " " << args[3];
                                    return ss.str();
                                },
                                "Resposta para o comando areia"};

    // Command: moedas <N>
    ListaDeComandos["moedas"] = {1, 0,
                                 {"int"},
                                 "Acrescenta N moedas ao jogador.",
                                 [](const vector<string>& args) {
                                     stringstream ss;
                                     if (!eNumero(args[1])) {
                                         ss << "Argumento inválido. Introduza um número.";
                                         return ss.str();
                                     }
                                     ss << "moedas " << args[1];
                                     return ss.str();
                                 },
                                 "Resposta para o comando moedas"};



    ListaDeComandos["tripul"] = {2, 0,  // 2 argumentos obrigatórios, 0 opcionais
                                 {"int", "int"},  // Espera dois inteiros: <N> e <T>
                                 "Compra T tripulantes para a caravana N desde que essa caravana esteja numa cidade.",
                                 [](const std::vector<std::string>& args) {
                                     std::stringstream ss;

                                     // Verificar se os argumentos são números
                                     if (!eNumero(args[1]) || !eNumero(args[2])) {
                                         ss << "Erro: Argumentos inválidos. Deve introduzir dois números.";
                                         return ss.str();
                                     }

                                     ss << "tripul " << args[1] << " " << args[2];
                                     return ss.str();
                                 },
                                 "Resposta para o comando tripul"};

    // Command: saves <nome>
    ListaDeComandos["saves"] = {1, 0,
                                {"string"},
                                "Faz uma cópia do estado do buffer associado ao nome indicado.",
                                [](const vector<string>& args) {
                                    stringstream ss;
                                    ss << "saves "<< args[1];
                                    return ss.str();
                                },
                                "Resposta para o comando saves"};

    // Command: loads <nome>
    ListaDeComandos["loads"] = {1, 0,
                                {"string"},
                                "Recupera a cópia do buffer associada ao nome indicado.",
                                [](const vector<string>& args) {
                                    stringstream ss;
                                    ss << "loads "<< args[1];
                                    return ss.str();
                                },
                                "Resposta para o comando loads"};

    // Command: lists
    ListaDeComandos["lists"] = {0, 0,
                                {},
                                "Lista os nomes das cópias do buffer existentes.",
                                [](const vector<string>& args) {
                                    stringstream ss;
                                    ss << "lists";
                                    return ss.str();
                                },
                                "Resposta para o comando lists"};

    // Command: dels <nome>
    ListaDeComandos["dels"] = {1, 0,
                               {"string"},
                               "Apaga a cópia do buffer associada ao nome indicado.",
                               [](const vector<string>& args) {
                                   stringstream ss;
                                   ss << "dels " << args[1];
                                   return ss.str();
                               },
                               "Resposta para o comando dels"};

    // Command: terminar
    ListaDeComandos["terminar"] = {0, 0,
                                   {},
                                   "Termina a simsulação, apresentando a pontuação.",
                                   [](const vector<string>& args) {
                                       stringstream ss;
                                       ss << "terminar";
                                       return ss.str();
                                   },
                                   "Resposta para o comando terminar"};
}