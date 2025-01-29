#include "..\header\Semana.h"

void Semana::adicionarDemanda(const string dia, const string turno, const string habilidade, int minimo, int maximo)
{
    demandas[dia][turno][habilidade] = {minimo, maximo};
}

void Semana::adicionarPreferenciaFolga(const string nome, const string dia, const string turno)
{
    preferenciasFolga[nome][dia] = turno;
}

bool Semana::prefereFolgaTurno(const string nome, const string dia, const string turno) const
{
    auto itNome = preferenciasFolga.find(nome);
    if (itNome == preferenciasFolga.end())
        return false;

    auto itDia = itNome->second.find(dia);
    if (itDia == itNome->second.end())
        return false;

    return itDia->second == turno || itDia->second == "Any";
}

void Semana::imprimirDemandas() const
{
    // Map para armazenar demandas: dia -> turno -> habilidade -> Demanda
    for (const auto iteradorDia : demandas)
    {
        cout << iteradorDia.first << ":\n";
        for (const auto iteradorTurnos : iteradorDia.second)
        {
            cout << "  " << iteradorTurnos.first << ":\n";
            for (const auto iteradorDemanda : iteradorTurnos.second)
            {
                cout << "    " << iteradorDemanda.first << " -> Min: " << iteradorDemanda.second.minimo << ", Opt: " << iteradorDemanda.second.otima << "\n";
            }
        }
    }
}

void Semana::imprimirPreferencias() const
{
    for (const auto iteradorNome : preferenciasFolga)
    {
        cout << iteradorNome.first << ":\n";
        for (const auto iteradorDia : iteradorNome.second)
        {
            cout << "  " << iteradorDia.first << " -> " << iteradorDia.second << "\n";
        }
    }
}

void Semana::setDemandaMinima(const string dia, const string turno, const string habilidade, int minimo)
{
    demandas[dia][turno][habilidade].minimo = minimo;
}

void Semana::setDemandaOtima(const string dia, const string turno, const string habilidade, int otima)
{
    demandas[dia][turno][habilidade].otima = otima;
}

int Semana::getDemandaMinima(const string dia, const string turno, const string habilidade)
{
    return demandas[dia][turno][habilidade].minimo;
}

int Semana::getDemandaOtima(const string dia, const string turno, const string habilidade)
{
    return demandas[dia][turno][habilidade].otima;
}

void Semana::reduzDemandaMinima(const string dia, const string turno, const string habilidade, int reducao)
{
    demandas[dia][turno][habilidade].minimo -= reducao;
}
void Semana::reduzDemandaOtima(const string dia, const string turno, const string habilidade, int reducao)
{
    demandas[dia][turno][habilidade].otima -= reducao;
}

void Semana::incrementaDemandaMinima(const string dia, const string turno, const string habilidade, int incremento)
{
    demandas[dia][turno][habilidade].minimo += incremento;
}
void Semana::incrementaDemandaOtima(const string dia, const string turno, const string habilidade, int incremento)
{
    demandas[dia][turno][habilidade].otima += incremento;
}

int Semana::somaDemandasMinimas()
{
    int contador = 0;

    for (const auto iteradorDia : demandas)
    {
        cout << iteradorDia.first << ":\n";
        for (const auto iteradorTurnos : iteradorDia.second)
        {
            cout << "  " << iteradorTurnos.first << ":\n";
            for (const auto iteradorDemanda : iteradorTurnos.second)
            {
                if (iteradorDemanda.second.minimo >= 0)
                {
                    contador = contador + iteradorDemanda.second.minimo;
                }
            }
        }
    }

    return contador;
}

int Semana::somaDemandasOtimas()
{
    int contador = 0;

    for (const auto iteradorDia : demandas)
    {
        cout << iteradorDia.first << ":\n";
        for (const auto iteradorTurnos : iteradorDia.second)
        {
            cout << "  " << iteradorTurnos.first << ":\n";
            for (const auto iteradorDemanda : iteradorTurnos.second)
            {
                if (iteradorDemanda.second.otima >= 0)
                {
                    contador = contador + iteradorDemanda.second.otima;
                }
            }
        }
    }

    return contador;
}