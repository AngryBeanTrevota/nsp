#include "SolucaoCompleta.h"

using namespace std;

SolucaoCompleta::SolucaoCompleta(vector<shared_ptr<Enfermeiro>> &enfermeiros)
{

    // Para cada enfermeiro, cria um objeto EnfermeiroProgresso com o código obtido e adiciona ao vetor enfProg
    for (auto &enfermeiro : enfermeiros)
    {
        enfProg[enfermeiro->getCodigo()] = EnfermeiroProgresso(enfermeiro->getCodigo());
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

map<string, EnfermeiroProgresso> &SolucaoCompleta::getEnfProg()
{
    return enfProg;
}

void SolucaoCompleta::setEnfProg(const map<string, EnfermeiroProgresso> &enfermeiroProgs)
{
    enfProg = enfermeiroProgs;
}

void SolucaoCompleta::imprimirProgressoEnfermeiros() const
{
    cout << "=== Progresso dos Enfermeiros ===" << endl;
    for (const auto &par : enfProg)
    {
        // O primeiro elemento (par.first) é a chave (código do enfermeiro)
        // e o segundo (par.second) é o objeto EnfermeiroProgresso.
        cout << "Código: " << par.first << "\n"
             << "Total Alocações: " << par.second.getTotalAloc() << "\n"
             << "Total Alocações Fim de Semana: " << par.second.getTotalAlocFimSemana() << "\n"
             << "Total Turnos Contra Preferência: " << par.second.getTotalTurnosContraPref() << "\n"
             << "Total Finais de Semana Incompletos: " << par.second.getTotalFdsIncompleto() << "\n"
             << "----------------------------------" << endl;
    }
}