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

    // Setters
    void setTotalSemanas(int totalSemanas);
    void setSemanaAtual(int semanaAtual);
    void setHabilidadesInstancia(const vector<string> &habilidades);
    void setTipoTurnos(const vector<string> &turnos);
    void setSequenciaTurnosImpossivel(const map<string, vector<string>> &matriz);
    void setTiposContratos(const map<string, Contrato> &contratos);
    void setEnfermeiros(const vector<shared_ptr<Enfermeiro>> &enfermeiros);
    void setSemanas(const vector<Semana> &semanas);

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

    void ordenaEnfermeiros();
    string getDiaSemana(int i);
    unique_ptr<Solucao> gulosoSemana();
    void calculaValorCand(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, bool boolFds, const Semana &semana);
    void ordenaVetorCand(vector<unique_ptr<Candidato>> &candidatos);
    void alocaCandidato(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol, vector<unique_ptr<Candidato>> &candidatos, map<string, map<string, map<string, bool>>> &mapBooleans);
    void desalocaBuscaLocal(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol);
    void alocaBuscaLocal(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol);
    bool avaliaViabilidade(Solucao &sol);
    int avaliaNota(Solucao &sol, int semanaAtual);
    void buscaLocal(unique_ptr<Solucao> &sol);
    vector<unique_ptr<Solucao>> guloso();
};

#endif // INSTANCIA_H
