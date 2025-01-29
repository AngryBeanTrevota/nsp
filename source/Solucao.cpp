#include "..\header\Solucao.h"
#include "..\header\Alocacao.h"

// Construtor padrão
Solucao::Solucao() : id("") {}

// Construtor com id
Solucao::Solucao(const string &id) : id(id), totalAlocacoes() {}

// Getter para o id
string Solucao::getId() const
{
    return id;
}

// Setter para o id
void Solucao::setId(const string &id)
{
    this->id = id;
}

// Getter para totalAlocacoes
const map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> &Solucao::getTotalAlocacoes() const
{
    return totalAlocacoes;
}

// Setter para totalAlocacoes
void Solucao::setTotalAlocacoes(const map<shared_ptr<Enfermeiro>, map<string, map<string, map<string, bool>>>> &alocacoes)
{
    this->totalAlocacoes = alocacoes;
}

// Adicionar alocação ao enfermeiro
void Solucao::adicionarAlocacao(shared_ptr<Enfermeiro> &enfermeiro, const string &dia, const string &turno, const string &hab, const bool &alocSimNao)
{
    totalAlocacoes[enfermeiro][dia][turno][hab] = alocSimNao;
}

Semana &Solucao::getSemanaDemandas()
{
    return semanaDemandas;
}

void Solucao::setSemanaDemandas(Semana semanaDemandas)
{
    this->semanaDemandas = semanaDemandas;
}

int Solucao::getNota()
{
    return nota;
}

void Solucao::setNota(int nota)
{
    this->nota = nota;
}

bool Solucao::getViavel()
{
    return viavel;
}
void Solucao::setViavel(bool viavel)
{
    this->viavel = viavel;
}

// Exibir todas as alocações
void Solucao::exibirAlocacoes() const
{
    for (const auto &enfermeiro : totalAlocacoes)
    {
        const string &nomeEnfermeiro = enfermeiro.first->getCodigo();
        for (const auto &dia : enfermeiro.second)
        {
            const string &nomeDia = dia.first;
            for (const auto &turno : dia.second)
            {
                const string &nomeTurno = turno.first;
                for (const auto &hab : turno.second)
                {
                    const string &habilidade = hab.first;
                    bool alocacao = hab.second;

                    if (alocacao)
                    { // Apenas imprime se for true
                        cout << nomeEnfermeiro << " " << nomeDia << " " << nomeTurno << " " << habilidade << endl;
                    }
                }
            }
        }
    }

    cout << endl
         << "Viavel: " << (viavel ? "Sim" : "Nao") << endl;
    cout << "Penalidade: " << nota << endl;
}
