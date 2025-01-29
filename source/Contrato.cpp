// Contrato.cpp
#include "..\header\Contrato.h"
#include <iostream>
#include <string>

using namespace std;

// Construtor padrão
Contrato::Contrato()
    : minAlocacoes(0), maxAlocacoes(0), minTrabSeguido(0), maxTrabSeguido(0),
      minFolgaSeguida(0), maxFolgaSeguida(0), maxAlocacoesFimSemana(0), precisaFimSemanaCompleto(false) {}

// Construtor com parâmetros
Contrato::Contrato(int minAloc, int maxAloc, int minTrab, int maxTrab,
                   int minFolga, int maxFolga, int maxFimSemana, bool precisaFimSemana)
    : minAlocacoes(minAloc), maxAlocacoes(maxAloc), minTrabSeguido(minTrab), maxTrabSeguido(maxTrab),
      minFolgaSeguida(minFolga), maxFolgaSeguida(maxFolga), maxAlocacoesFimSemana(maxFimSemana),
      precisaFimSemanaCompleto(precisaFimSemana) {}

// Métodos getters
int Contrato::getMinAlocacoes() const { return minAlocacoes; }
int Contrato::getMaxAlocacoes() const { return maxAlocacoes; }
int Contrato::getMinTrabSeguido() const { return minTrabSeguido; }
int Contrato::getMaxTrabSeguido() const { return maxTrabSeguido; }
int Contrato::getMinFolgaSeguida() const { return minFolgaSeguida; }
int Contrato::getMaxFolgaSeguida() const { return maxFolgaSeguida; }
int Contrato::getMaxAlocacoesFimSemana() const { return maxAlocacoesFimSemana; }
bool Contrato::getPrecisaFimSemanaCompleto() const { return precisaFimSemanaCompleto; }

// Métodos setters
void Contrato::setMinAlocacoes(int value) { minAlocacoes = value; }
void Contrato::setMaxAlocacoes(int value) { maxAlocacoes = value; }
void Contrato::setMinTrabSeguido(int value) { minTrabSeguido = value; }
void Contrato::setMaxTrabSeguido(int value) { maxTrabSeguido = value; }
void Contrato::setMinFolgaSeguida(int value) { minFolgaSeguida = value; }
void Contrato::setMaxFolgaSeguida(int value) { maxFolgaSeguida = value; }
void Contrato::setMaxAlocacoesFimSemana(int value) { maxAlocacoesFimSemana = value; }
void Contrato::setPrecisaFimSemanaCompleto(bool value) { precisaFimSemanaCompleto = value; }

void Contrato::imprimirContrato()
{
  cout << "Detalhes do Contrato:" << endl;
  cout << "Min. Alocações: " << minAlocacoes << endl;
  cout << "Max. Alocações: " << maxAlocacoes << endl;
  cout << "Min. Trabalho Seguido: " << minTrabSeguido << endl;
  cout << "Max. Trabalho Seguido: " << maxTrabSeguido << endl;
  cout << "Min. Folga Seguida: " << minFolgaSeguida << endl;
  cout << "Max. Folga Seguida: " << maxFolgaSeguida << endl;
  cout << "Max. Alocações Fim de Semana: " << maxAlocacoesFimSemana << endl;
  cout << "Precisa Fim de Semana: " << (precisaFimSemanaCompleto ? "Sim" : "Não") << endl;
}