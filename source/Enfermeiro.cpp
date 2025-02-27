#include "..\header\Enfermeiro.h"
#include <iostream>

// Construtor
Enfermeiro::Enfermeiro(
    const string &codigo,
    Contrato &contrato,
    vector<string> &habilidades,
    string &ultimoTurnoTrabalhado,
    int &seguidosUltimoTurnoTrabalhado,
    int &turnosSeguidos,
    int &folgasSeguidas)
{
    this->codigo = codigo;
    this->contrato = contrato;
    this->habilidades = habilidades;
    this->ultimoTurnoTrabalhado = ultimoTurnoTrabalhado;
    this->seguidosUltimoTurnoTrabalhado = seguidosUltimoTurnoTrabalhado;
    this->turnosSeguidos = turnosSeguidos;
    this->folgasSeguidas = folgasSeguidas;
}

// Construtor padrão
Enfermeiro::Enfermeiro()
    : codigo(""), contrato(*(new Contrato())), habilidades({}),
      ultimoTurnoTrabalhado("None"), seguidosUltimoTurnoTrabalhado(0),
      turnosSeguidos(0), folgasSeguidas(0) {}

// Getters
string Enfermeiro::getCodigo()
{
    return codigo;
}

Contrato Enfermeiro::getContrato()
{
    return contrato;
}

vector<string> Enfermeiro::getHabilidades()
{
    return habilidades;
}

string Enfermeiro::getUltimoTurnoTrabalhado()
{
    return ultimoTurnoTrabalhado;
}

int Enfermeiro::getSeguidosUltimoTurnoTrabalhado()
{
    return seguidosUltimoTurnoTrabalhado;
}

int Enfermeiro::getTurnosSeguidos()
{
    return turnosSeguidos;
}

int Enfermeiro::getFolgasSeguidas()
{
    return folgasSeguidas;
}

// Setters
void Enfermeiro::setCodigo(string codigo)
{
    this->codigo = codigo;
}

void Enfermeiro::setContrato(Contrato contrato)
{
    this->contrato = contrato;
}

void Enfermeiro::setHabilidades(vector<string> habilidades)
{
    this->habilidades = habilidades;
}

void Enfermeiro::setUltimoTurnoTrabalhado(string ultimoTurnoTrabalhado)
{
    this->ultimoTurnoTrabalhado = ultimoTurnoTrabalhado;
}

void Enfermeiro::setSeguidosUltimoTurnoTrabalhado(int seguidosUltimoTurnoTrabalhado)
{
    this->seguidosUltimoTurnoTrabalhado = seguidosUltimoTurnoTrabalhado;
}

void Enfermeiro::setTurnosSeguidos(int turnosSeguidos)
{
    this->turnosSeguidos = turnosSeguidos;
}

void Enfermeiro::setFolgasSeguidas(int folgasSeguidas)
{
    this->folgasSeguidas = folgasSeguidas;
}

// Adicionar habilidade
void Enfermeiro::adicionarHabilidade(string habilidade)
{
    habilidades.push_back(habilidade);
}

void Enfermeiro::print() const
{
    cout << "=== Enfermeiro ===" << endl;
    cout << "Código: " << codigo << endl;

    cout << "\nContrato:" << endl;
    // Supondo que Contrato tenha um método print().

    Contrato cont = contrato;
    cont.imprimirContrato();

    cout
        << "\nHabilidades:" << endl;
    for (const auto &habilidade : habilidades)
    {
        cout << " - " << habilidade << endl;
    }
    cout << "===================" << endl;
}
