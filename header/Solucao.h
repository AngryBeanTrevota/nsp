#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Alocacao.h"
#include "Semana.h"
#include "Enfermeiro.h"
#include "EnfermeiroProgresso.h"
#include <memory>

using namespace std;

class Solucao
{
private:
    // Atributos da classe Solucao
    string id;
    // nomeEnf -> dia -> turno -> hab -> true/false
    map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> totalAlocacoes;
    Semana semanaDemandas;
    map<string, map<string, map<string, int>>> demandasSupridas;
    map<string, EnfermeiroProgresso> progressoEnfermeiros;
    int nota;
    bool viavel;
    int grauInviabilidade;

public:
    // Construtores
    Solucao();                 // Construtor padrão
    Solucao(const string &id); // Construtor com id

    // Getters e Setters
    string getId() const;
    void setId(const string &id);

    const std::map<std::shared_ptr<Enfermeiro>,
                   std::map<std::string,
                            std::map<std::string,
                                     std::map<std::string, bool>>>> &
    getTotalAlocacoes() const;
    void setTotalAlocacoes(const map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> &alocacoes);

    Semana &getSemanaDemandas();
    void setSemanaDemandas(Semana semanaDemandas);

    int getNota();
    void setNota(int nota);

    int getGrauInviabilidade();

    bool getViavel();
    void setViavel(bool viavel);

    map<string, map<string, map<string, int>>> getDemandasSupridas();
    void setDemandasSupridas(map<string, map<string, map<string, int>>> demandasSupridas);

    // Métodos para manipular as alocações
    void adicionarAlocacao(shared_ptr<Enfermeiro> &nomesEnfermeiro, const string &dia, const string &turno, const string &hab, const bool &alocSimNao);
    void exibirAlocacoes() const;
    void adicionarDemandaSuprida(const string dia, const string turno, const string habilidade, int val);
    void incrementaDemandaSuprida(const string dia, const string turno, const string habilidade, int val);
    void decrementaDemandaSuprida(const string dia, const string turno, const string habilidade, int val);
    void imprimirDemandasSupridas() const;

    // Avalia soluca

    bool avaliaViabilidade();
    int somaDemandasOtimasFaltando();
};

#endif // SOLUCAO_H
