#ifndef ENFERMEIRO_H
#define ENFERMEIRO_H

#include <string>
#include <vector>
#include <utility>
#include "Contrato.h"

using namespace std;

class Enfermeiro
{
private:
    string codigo;
    Contrato contrato;
    vector<string> habilidades;

    // Valores de progresso do enfermeiro

    int totalAloc;
    int totalAlocFimSemana;
    int totalTurnosContraPref;
    int totalFdsIncompleto;
    string ultimoTurnoTrabalhado;
    int seguidosUltimoTurnoTrabalhado;
    int turnosSeguidos;
    int folgasSeguidas;

public:
    Enfermeiro();
    Enfermeiro(
        const string &codigo,
        Contrato &contrato,
        vector<string> &habilidades,
        int &totalAloc,
        int &totalAlocFimSemana,
        int &totalTurnosContraPref,
        int &totalFdsIncompleto,
        string &ultimoTurnoTrabalhado,
        int &seguidosUltimoTurnoTrabalhado,
        int &turnosSeguidos,
        int &folgasSeguidas);

    // Getters
    string getCodigo();
    Contrato getContrato();
    vector<string> getHabilidades();
    int getTotalAloc();
    int getTotalAlocFimSemana();
    int getTotalTurnosContraPref();
    int getTotalFdsIncompleto();
    string getUltimoTurnoTrabalhado();
    int getSeguidosUltimoTurnoTrabalhado();
    int getTurnosSeguidos();
    int getFolgasSeguidas();

    // Setters
    void setCodigo(string codigo);
    void setContrato(Contrato contrato);
    void setHabilidades(vector<string> habilidades);
    void setTotalAloc(int totalAloc);
    void setTotalAlocFimSemana(int totalAlocFimSemana);
    void setTotalTurnosContraPref(int totalTurnosContraPref);
    void setTotalFdsIncompleto(int totalFdsIncompleto);
    void setUltimoTurnoTrabalhado(string ultimoTurnoTrabalhado);
    void setSeguidosUltimoTurnoTrabalhado(int seguidosUltimoTurnoTrabalhado);
    void setTurnosSeguidos(int turnosSeguidos);
    void setFolgasSeguidas(int folgasSeguidas);

    // Adicionar habilidade
    void adicionarHabilidade(string habilidade);

    void print() const;
};

#endif // ENFERMEIRO_H
