#ifndef ALOCACAO_H
#define ALOCACAO_H

#include <string>
#include <iostream>
using namespace std;

class Alocacao
{
public:
    int semana;
    string dia;
    string turno;
    string habilidade;

    // Construtor
    Alocacao(int semana, string dia, string turno, string habilidade)
        : semana(semana), dia(dia), turno(turno), habilidade(habilidade) {}

    // Método para exibir a alocação
    void exibir() const
    {
        cout << "Semana: " << semana << " Dia: " << dia << ", Turno: " << turno << ", Habilidade: " << habilidade << endl;
    }
};

#endif // ALOCACAO_H
