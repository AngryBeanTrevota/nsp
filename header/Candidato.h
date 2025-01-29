#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
#include <iostream>
using namespace std;

class Candidato
{
public:
    // Construtor padrão
    Candidato() : dia(""), turno(""), habilidade(""), demandaMin(0), demandaOpt(0), outroFdsAloc(false), valor(0) {}

    // Construtor parametrizado
    Candidato(string dia, string turno, string habilidade, int demandaMin, int demandaOpt, float valor)
        : dia(dia), turno(turno), habilidade(habilidade), demandaMin(demandaMin), demandaOpt(demandaOpt), outroFdsAloc(false), valor(valor) {}

    // Getters
    string getDia() const { return dia; }
    string getTurno() const { return turno; }
    string getHabilidade() const { return habilidade; }
    int getDemandaMin() const { return demandaMin; }
    int getDemandaOpt() const { return demandaOpt; }
    bool getOutroFdsAloc() const { return outroFdsAloc; }
    float getValor() const { return valor; }

    // Setters
    void setDia(const string &dia) { this->dia = dia; }
    void setTurno(const string &turno) { this->turno = turno; }
    void setHabilidade(const string &habilidade) { this->habilidade = habilidade; }
    void setDemandaMin(int demandaMin) { this->demandaMin = demandaMin; }
    void setDemandaOpt(int demandaOpt) { this->demandaOpt = demandaOpt; }
    void setOutroFdsAloc(bool outroFdsAloc) { this->outroFdsAloc = outroFdsAloc; }
    void setValor(float valor) { this->valor = valor; }

    // Função para imprimir o candidato
    void imprimir() const
    {
        cout << "Candidato:" << endl;
        cout << "  Dia: " << dia << endl;
        cout << "  Turno: " << turno << endl;
        cout << "  Habilidade: " << habilidade << endl;
        cout << "  Demanda Minima: " << demandaMin << endl;
        cout << "  Demanda Opcional: " << demandaOpt << endl;
        cout << "  Outro fds aloc:  " << outroFdsAloc << endl;
        cout << "  Valor: " << valor << endl;
    }

private:
    string dia;
    string turno;
    string habilidade;
    int demandaMin;
    int demandaOpt;
    bool outroFdsAloc;
    float valor;
};

#endif // CANDIDATO_H
