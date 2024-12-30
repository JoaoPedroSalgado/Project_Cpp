//
// Created by Enrique Marques on 19/12/2024.
//
#ifndef POOTP20242025_COMANDOS_H
#define POOTP20242025_COMANDOS_H


#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

bool eNumero(const string& str);

using namespace std;

class Comandos {
public:
    int nArgsObrigatorios;
    int nArgsOptionais;
    vector<string> TipoDeArgs;
    string nome;
    function<string(const vector<string>&)> CodigoExecutar;
    string Resposta;

    Comandos() : nArgsObrigatorios(0), nArgsOptionais(0), nome(""), CodigoExecutar(nullptr), Resposta("") {}

    Comandos(int nObrigatorios, int nOptionais, const vector<string>& tipos, const string& nomer, function<string(const vector<string>&)> codigoExecutar, const string& resposta)
            : nArgsObrigatorios(nObrigatorios), nArgsOptionais(nOptionais), TipoDeArgs(tipos), nome(nomer), CodigoExecutar(codigoExecutar), Resposta(resposta) {}
};

string VerificarComandos(const string& ComandoRecebido, map<string, Comandos>& ListaDeComandos);
void InicializarComandos(map<string, Comandos>& ListaDeComandos);
#endif //POOTP20242025_COMANDOS_H
