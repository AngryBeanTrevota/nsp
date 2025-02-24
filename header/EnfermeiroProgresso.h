#ifndef ENFERMEIROPROGRESSO_H
#define ENFERMEIROPROGRESSO_H

#include <string>

using namespace std;

class EnfermeiroProgresso
{
private:
    string codigo;
    int totalAloc;
    int totalAlocFimSemana;
    int totalTurnosContraPref;
    int totalFdsIncompleto;

public:
    // Construtor
    EnfermeiroProgresso(string codigo) : codigo(codigo),
                                         totalAloc(0),
                                         totalAlocFimSemana(0),
                                         totalTurnosContraPref(0),
                                         totalFdsIncompleto(0) {}

    // Getters
    string getCodigo() const { return codigo; }
    int getTotalAloc() const { return totalAloc; }
    int getTotalAlocFimSemana() const { return totalAlocFimSemana; }
    int getTotalTurnosContraPref() const { return totalTurnosContraPref; }
    int getTotalFdsIncompleto() const { return totalFdsIncompleto; }

    // Setters
    void setTotalAloc(int valor) { totalAloc = valor; }
    void setTotalAlocFimSemana(int valor) { totalAlocFimSemana = valor; }
    void setTotalTurnosContraPref(int valor) { totalTurnosContraPref = valor; }
    void setTotalFdsIncompleto(int valor) { totalFdsIncompleto = valor; }

    // Método para atualizar todos os valores de progresso de uma vez
    void atualizarProgresso(int aloc, int alocFds, int contraPref, int fdsIncompleto)
    {
        totalAloc = aloc;
        totalAlocFimSemana = alocFds;
        totalTurnosContraPref = contraPref;
        totalFdsIncompleto = fdsIncompleto;
    }
};

#endif