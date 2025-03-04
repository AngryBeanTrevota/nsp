#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "Contrato.h"
#include "Enfermeiro.h"
#include "Semana.h"
#include "Solucao.h"
#include "Candidato.h"
#include "SolucaoCompleta.h"
#include "EnfermeiroProgresso.h"

using namespace std;

class Instancia
{
private:
    // Atributos
    int totalSemanas;
    int semanaAtual;
    vector<string> habilidadesInstancia;
    vector<string> tipoTurnos;
    map<string, vector<string>> sequenciaTurnosImpossivel;
    map<string, Contrato> tiposContratos;
    vector<shared_ptr<Enfermeiro>> enfermeiros;
    vector<Semana> semanas;
    map<string, int> qtdEnfComHabilidade;

public:
    Instancia(); // Construtor padrão
    Instancia(
        int totalSemanas,
        const vector<string> &habilidades,
        const vector<string> &turnos,
        const map<string, vector<string>> &sequenciaTurnosImpossivel,
        const map<string, Contrato> &contratos,
        const vector<shared_ptr<Enfermeiro>> &enfermeiros,
        const vector<Semana> &semanas);

    // Getters
    int getTotalSemanas() const;
    int getSemanaAtual() const;
    vector<string> getHabilidadesInstancia() const;
    vector<string> getTipoTurnos() const;
    map<string, vector<string>> getSequenciaTurnosImpossivel() const;
    map<string, Contrato> getTiposContratos() const;
    vector<shared_ptr<Enfermeiro>> getEnfermeiros() const;
    vector<Semana> getSemanas() const;
    map<string, int> getQtdEnfComHabilidade() const;

    // Setters
    void setTotalSemanas(int totalSemanas);
    void setSemanaAtual(int semanaAtual);
    void setHabilidadesInstancia(const vector<string> &habilidades);
    void setTipoTurnos(const vector<string> &turnos);
    void setSequenciaTurnosImpossivel(const map<string, vector<string>> &matriz);
    void setTiposContratos(const map<string, Contrato> &contratos);
    void setEnfermeiros(const vector<shared_ptr<Enfermeiro>> &enfermeiros);
    void setSemanas(const vector<Semana> &semanas);
    void setQtdEnfComHabilidade(const map<string, int> qtdEnfComHabilidade);

    // Outros Métodos
    void adicionarContrato(const string &nomeContrato, const Contrato &contrato);
    void adicionarEnfermeiro(const shared_ptr<Enfermeiro> enfermeiro);
    void adicionarSemana(const Semana &semana);
    void adicionarTurno(const string &turno);
    void adicionarHabilidade(const string &habilidade);
    void configurarSequenciaTurnosImpossivel(string turnoI, string turnoJ);
    bool sequenciaTurnosEhImpossivel(string turnoI, string turnoJ);

    void print() const;

    // as coisas de verdade

    void ordenaEnfermeiros(map<string, EnfermeiroProgresso> &enfProgresso);
    string getDiaSemana(int i);
    unique_ptr<Solucao> gulosoSemana(int alfa, map<string, EnfermeiroProgresso> &enfProgresso);
    void calculaValorCand(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, EnfermeiroProgresso &enfProg, bool boolFds, const Semana &semana, Solucao &sol);
    void ordenaVetorCand(vector<unique_ptr<Candidato>> &candidatos);
    void alocaCandidato(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, EnfermeiroProgresso &enfProg, Semana &semana, Solucao &sol, vector<unique_ptr<Candidato>> &candidatos, map<string, map<string, map<string, bool>>> &mapBooleans);
    bool avaliaViabilidade(Solucao &sol);
    int avaliaNota(vector<Solucao> &sol, map<string, EnfermeiroProgresso> &enfProgMap);
    void registraSolucao(vector<Solucao> &solucoes, map<string, EnfermeiroProgresso> &enfProgMap, string codigoInstancia, int numeroIteracao);
    shared_ptr<SolucaoCompleta> guloso(int alfa);

    // busca local

    void mudaTurno(Solucao &solSemana, Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, string turnoNovo, string dia, string turnoAntigo, string habilidade);
    int mudaCalculaNotaBuscaLocal(Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, SolucaoCompleta &sol, Solucao &solSemana, string dia, string habilidade, string turnoNovo);
    void buscaLocal(shared_ptr<SolucaoCompleta> solCompleta, int numSemana, int limiteIter);
    void mudaHabilidade(Solucao &solSemana, Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, string turno, string dia, string habilidadeNova, string habilidadeAntiga);
    int mudaHabilidadeCalculaNotaBuscaLocal(Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, SolucaoCompleta &sol, Solucao &solSemana, string dia, string turno, string habilidadeNova);
};

#endif // INSTANCIA_H
