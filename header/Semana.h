#ifndef SEMANA_H
#define SEMANA_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

// Estrutura para armazenar a demanda mínima e ótima
struct Demanda
{
    int minimo;
    int otima;
};

class Semana
{
private:
    // Estrutura para demandas: dia -> turno -> habilidade -> Demanda
    map<string, map<string, map<string, Demanda>>> demandas;

    // Estrutura para preferências de folga: nome -> dia -> turno
    map<string, map<string, string>> preferenciasFolga;

public:
    // Métodos para gerenciar demandas
    map<string, map<string, map<string, Demanda>>> getDemandas();
    void adicionarDemanda(const string dia, const string turno, const string habilidade, int minimo, int maximo);
    void setDemandaMinima(const string dia, const string turno, const string habilidade, int minimo);
    void setDemandaOtima(const string dia, const string turno, const string habilidade, int otima);
    int getDemandaMinima(const string dia, const string turno, const string habilidade);
    int getDemandaOtima(const string dia, const string turno, const string habilidade);
    void reduzDemandaMinima(const string dia, const string turno, const string habilidade, int reducao);
    void reduzDemandaOtima(const string dia, const string turno, const string habilidade, int reducao);
    void incrementaDemandaMinima(const string dia, const string turno, const string habilidade, int incremento);
    void incrementaDemandaOtima(const string dia, const string turno, const string habilidade, int incremento);
    void imprimirDemandas() const;

    // Métodos para gerenciar preferências de folga
    void adicionarPreferenciaFolga(const string nome, const string dia, const string turno);
    bool prefereFolgaTurno(const string nome, const string dia, const string turno) const;
    void imprimirPreferencias() const;

    // Metodos viabilidade e qualidade

    int somaDemandasMinimas();
    int somaDemandasOtimas();
};

#endif // SEMANA_H
