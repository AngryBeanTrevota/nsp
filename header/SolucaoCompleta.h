#ifndef SOLUCAOCOMPLETA_H
#define SOLUCAOCOMPLETA_H

#include <vector>
#include <memory>
#include <map>
#include "Solucao.h"
#include "EnfermeiroProgresso.h"
#include "Enfermeiro.h"

using namespace std;

class SolucaoCompleta
{
public:
    vector<Solucao> solucoesSemana;
    map<string, EnfermeiroProgresso> enfProg;

    // Construtor que recebe vector<Enfermeiro>& e inicializa o vetor enfProg
    SolucaoCompleta(vector<shared_ptr<Enfermeiro>> &enfermeiros);

    void adicionaSolucaoSemana(Solucao &sol);

    // Getters e Setters para solucoesSemana
    const vector<Solucao> &getSolucoesSemana() const;
    vector<Solucao> &getSolucoesSemana();
    void setSolucoesSemana(vector<Solucao> solucoes);

    // Getters e Setters para enfProg
    map<string, EnfermeiroProgresso> &getEnfProg();
    void setEnfProg(const map<string, EnfermeiroProgresso> &enfermeiroProgs);

    void imprimirProgressoEnfermeiros() const;
};

#endif // SOLUCAOCOMPLETA_H
