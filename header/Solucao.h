#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Alocacao.h"
#include "Semana.h"
#include "Enfermeiro.h"
#include <memory>

using namespace std;

class Solucao
{
private:
    // Atributos da classe Solucao
    string id;
    // nomeEnf -> dia -> turno -> hab -> true/false
    map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> totalAlocacoes;
    Semana semanaDemandas;
    int nota;
    bool viavel;

public:
    // Construtores
    Solucao();                 // Construtor padrão
    Solucao(const string &id); // Construtor com id

    // Getters e Setters
    string getId() const;
    void setId(const string &id);

    map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> getTotalAlocacoes() const;
    void setTotalAlocacoes(const map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> &alocacoes);

    Semana &getSemanaDemandas();
    void setSemanaDemandas(Semana semanaDemandas);

    int getNota();
    void setNota(int nota);

    bool getViavel();
    void setViavel(bool viavel);

    // Métodos para manipular as alocações
    void adicionarAlocacao(shared_ptr<Enfermeiro> &nomesEnfermeiro, const string &dia, const string &turno, const string &hab, const bool &alocSimNao);
    void exibirAlocacoes() const;
};

#endif // SOLUCAO_H
