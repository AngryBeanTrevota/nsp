#include "SolucaoCompleta.h"

using namespace std;

SolucaoCompleta::SolucaoCompleta(vector<shared_ptr<Enfermeiro>> &enfermeiros)
{

    // Para cada enfermeiro, cria um objeto EnfermeiroProgresso com o código obtido e adiciona ao vetor enfProg
    for (auto &enfermeiro : enfermeiros)
    {
        enfProg.push_back(EnfermeiroProgresso(enfermeiro->getCodigo()));
    }
}

void SolucaoCompleta::adicionaSolucaoSemana(Solucao &sol)
{
    this->solucoesSemana.push_back(sol);
}

// Getters e Setters para solucoesSemana
const vector<Solucao> &SolucaoCompleta::getSolucoesSemana() const
{
    return solucoesSemana;
}

vector<Solucao> &SolucaoCompleta::getSolucoesSemana()
{
    return solucoesSemana;
}

void SolucaoCompleta::setSolucoesSemana(vector<Solucao> solucoes)
{
    solucoesSemana = std::move(solucoes);
}

// Getters e Setters para enfProg
const vector<EnfermeiroProgresso> &SolucaoCompleta::getEnfProg() const
{
    return enfProg;
}

vector<EnfermeiroProgresso> &SolucaoCompleta::getEnfProg()
{
    return enfProg;
}

void SolucaoCompleta::setEnfProg(const vector<EnfermeiroProgresso> &enfermeiroProgs)
{
    enfProg = enfermeiroProgs;
}