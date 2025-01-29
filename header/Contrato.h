#ifndef CONTRATO_H
#define CONTRATO_H

class Contrato
{
private:
    int minAlocacoes;
    int maxAlocacoes;
    int minTrabSeguido;
    int maxTrabSeguido;
    int minFolgaSeguida;
    int maxFolgaSeguida;
    int maxAlocacoesFimSemana;
    bool precisaFimSemanaCompleto;

public:
    // Construtor padrão
    Contrato();

    // Construtor com parâmetros
    Contrato(int minAloc, int maxAloc, int minTrab, int maxTrab,
             int minFolga, int maxFolga, int maxFimSemana, bool precisaFimSemana);

    // Métodos getters
    int getMinAlocacoes() const;
    int getMaxAlocacoes() const;
    int getMinTrabSeguido() const;
    int getMaxTrabSeguido() const;
    int getMinFolgaSeguida() const;
    int getMaxFolgaSeguida() const;
    int getMaxAlocacoesFimSemana() const;
    bool getPrecisaFimSemanaCompleto() const;

    // Métodos setters
    void setMinAlocacoes(int value);
    void setMaxAlocacoes(int value);
    void setMinTrabSeguido(int value);
    void setMaxTrabSeguido(int value);
    void setMinFolgaSeguida(int value);
    void setMaxFolgaSeguida(int value);
    void setMaxAlocacoesFimSemana(int value);
    void setPrecisaFimSemanaCompleto(bool value);

    void imprimirContrato();
};

#endif // CONTRATO_H