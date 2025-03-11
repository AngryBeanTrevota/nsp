#include "..\header\Instancia.h"
#include "..\header\Candidato.h"
#include "..\header\SolucaoCompleta.h"
#include <algorithm>
#include <memory>
#include <random>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>

// Construtor
Instancia::Instancia()
    : totalSemanas(0), semanaAtual(0)
{
}

Instancia::Instancia(
    int totalSemanas,
    const vector<string> &habilidades,
    const vector<string> &turnos,
    const map<string, vector<string>> &sequenciaTurnosImpossivel,
    const map<string, Contrato> &contratos,
    const vector<shared_ptr<Enfermeiro>> &enfermeiros,
    const vector<Semana> &semanas) : totalSemanas(totalSemanas),
                                     semanaAtual(0), // Inicia com zero por padrão
                                     habilidadesInstancia(habilidades),
                                     tipoTurnos(turnos),
                                     sequenciaTurnosImpossivel(sequenciaTurnosImpossivel),
                                     tiposContratos(contratos),
                                     enfermeiros(enfermeiros),
                                     semanas(semanas)
{
}

// Getters
int Instancia::getTotalSemanas() const { return totalSemanas; }
int Instancia::getSemanaAtual() const { return semanaAtual; }
vector<string> Instancia::getHabilidadesInstancia() const { return habilidadesInstancia; }
vector<string> Instancia::getTipoTurnos() const { return tipoTurnos; }
map<string, vector<string>> Instancia::getSequenciaTurnosImpossivel() const { return sequenciaTurnosImpossivel; }
map<string, Contrato> Instancia::getTiposContratos() const { return tiposContratos; }
vector<shared_ptr<Enfermeiro>> Instancia::getEnfermeiros() const { return enfermeiros; }
vector<Semana> Instancia::getSemanas() const { return semanas; }

// Setters
void Instancia::setTotalSemanas(int totalSemanas) { this->totalSemanas = totalSemanas; }
void Instancia::setSemanaAtual(int semanaAtual) { this->semanaAtual = semanaAtual; }
void Instancia::setHabilidadesInstancia(const vector<string> &habilidades) { habilidadesInstancia = habilidades; }
void Instancia::setTipoTurnos(const vector<string> &turnos) { tipoTurnos = turnos; }
void Instancia::setSequenciaTurnosImpossivel(const map<string, vector<string>> &matriz) { sequenciaTurnosImpossivel = matriz; }
void Instancia::setTiposContratos(const map<string, Contrato> &contratos) { tiposContratos = contratos; }
void Instancia::setEnfermeiros(const vector<shared_ptr<Enfermeiro>> &enfermeiros) { this->enfermeiros = enfermeiros; }
void Instancia::setSemanas(const vector<Semana> &semanas) { this->semanas = semanas; }

int random(int min, int max)
{
    int randomNum = rand() % (max - min + 1) + min;
    return randomNum;
}

bool encontraString(const vector<string> &vec, const string &val)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == val)
        {
            return true;
        }
    }
    return false;
}

// Outros Métodos
void Instancia::adicionarContrato(const string &nomeContrato, const Contrato &contrato)
{
    tiposContratos[nomeContrato] = contrato;
}

void Instancia::adicionarEnfermeiro(const shared_ptr<Enfermeiro> enfermeiro)
{
    enfermeiros.push_back(enfermeiro);
    for (int i = 0; i < enfermeiro->getHabilidades().size(); i++)
    {
        qtdEnfComHabilidade[enfermeiro->getHabilidades()[i]] = qtdEnfComHabilidade[enfermeiro->getHabilidades()[i]] + 1;
    }
}

void Instancia::adicionarSemana(const Semana &semana)
{
    semanas.push_back(semana);
}

void Instancia::adicionarHabilidade(const string &habilidade)
{
    habilidadesInstancia.push_back(habilidade);
    qtdEnfComHabilidade[habilidade] = 0;
}

void Instancia::adicionarTurno(const string &turno)
{
    tipoTurnos.push_back(turno);
}

void Instancia::configurarSequenciaTurnosImpossivel(string turnoI, string turnoJ)
{
    string target1 = turnoI;
    bool existsI = find(tipoTurnos.begin(), tipoTurnos.end(), target1) != tipoTurnos.end();
    string target2 = turnoJ;
    bool existsJ = find(tipoTurnos.begin(), tipoTurnos.end(), target2) != tipoTurnos.end();
    if (existsI && existsJ)
    {
        sequenciaTurnosImpossivel[turnoI].push_back(turnoJ);
    }
    else
    {
        cerr << "Índices inválidos para configuração de turnos!" << endl;
    }
}

bool Instancia::sequenciaTurnosEhImpossivel(string turnoI, string turnoJ)
{
    if (turnoI == "None")
    {
        return false;
    }
    else
    {
        string target = turnoJ;
        bool exists = encontraString(sequenciaTurnosImpossivel[turnoI], target);
        return exists;
    }
}

void Instancia::setQtdEnfComHabilidade(const map<string, int> qtdEnfComHabilidade)
{
    this->qtdEnfComHabilidade = qtdEnfComHabilidade;
}

map<string, int> Instancia::getQtdEnfComHabilidade() const
{
    return qtdEnfComHabilidade;
}

void Instancia::print() const
{
    cout << "=== Instância ===" << endl;
    cout << "Total de semanas: " << totalSemanas << endl;
    cout << "Semana atual: " << semanaAtual << endl;

    cout << "\nHabilidades da instância:" << endl;
    for (const auto &par : qtdEnfComHabilidade)
    {
        cout << par.first << " -> " << par.second << endl;
    }

    cout << "\nTipos de turnos:" << endl;
    for (const auto &turno : tipoTurnos)
    {
        cout << " - " << turno << endl;
    }

    cout << "\nSequência de turnos impossíveis:" << endl;
    for (const auto &entry : sequenciaTurnosImpossivel)
    {
        cout << "Turno " << entry.first << " não pode ser seguido por:" << endl;
        for (const auto &turno : entry.second)
        {
            cout << "   - " << turno << endl;
        }
    }

    cout << "\nTipos de contratos:" << endl;
    for (const auto &entry : tiposContratos)
    {
        cout << "Contrato: " << entry.first << endl;
        Contrato cont = entry.second;
        cont.imprimirContrato();
    }

    cout << "\nEnfermeiros:" << endl;
    for (int i = 0; i < enfermeiros.size(); i++)
    {
        enfermeiros[i]->print();
    }

    cout << "=================" << endl;
}

// aqui começa a brincadeira hihihi

void Instancia::ordenaEnfermeiros(map<string, EnfermeiroProgresso> &enfProgresso)
{
    sort(enfermeiros.begin(), enfermeiros.end(),
         [&enfProgresso](shared_ptr<Enfermeiro> a, shared_ptr<Enfermeiro> b)
         {
             /*
 int progressoA = enfProgresso[a->getCodigo()].getTotalAloc();
 int progressoB = enfProgresso[b->getCodigo()].getTotalAloc();
 return (a->getContrato().getMinAlocacoes() - progressoA) >
        (b->getContrato().getMinAlocacoes() - progressoB);

 // Ordenando por mais flexível por ultimo(maior diferença primeiro)
              */

             int flexibilidadeA = a->getHabilidades().size();
             int flexibilidadeB = b->getHabilidades().size();

             return (flexibilidadeA < flexibilidadeB);
         });
}

string Instancia::getDiaSemana(int i)
{
    switch (i)
    {
    case 0:
        return "Mon";
    case 1:
        return "Tue";
    case 2:
        return "Wed";
    case 3:
        return "Thu";
    case 4:
        return "Fri";
    case 5:
        return "Sat";
    case 6:
        return "Sun";
    default:
        return "Invalid"; // Caso o valor de `i` seja inválido
    }
}

void Instancia::calculaValorCand(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, EnfermeiroProgresso &enfProg, bool boolFds, const Semana &semana, Solucao &sol)
{
    /*ordena esse vetor por ordenaVetorAlocacoes: quantoFaltaDemandaMin(se não faltar,
    considera a demanda ótima no segmento a seguir)
    + ((quantoFaltaDemandaOpt + quantoFaltaAlocacoesSeguidas*boolAnteriorSeguinteAloc -
    quantoFaltaDescansoSeguido*boolAnteriorSeguinteFolga - 1*boolPref(calcula aqui) + 1*boolOutroFds +
    quantoFaltaTotalAloc(pode ser negativo) + quantoFaltaFdsLimite(também pode ser negativo))/7)

    3 bool no vetor: anteriorSeguinteAloc, anteriorSeguinteFolga e outroFdsAloc
    */

    // considerar o caso turno sem ser none, turno fds e turno none

    float quantoFaltaDemandaMin = (cand->getTurno() != "None") ? cand->getDemandaMin() : 0;                                                                                                          // h1 check
    float quantoFaltaDemandaOpt = (cand->getTurno() != "None") ? cand->getDemandaOpt() : 0;                                                                                                          // s1 check
    float notaPreferencia = semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()) && (cand->getTurno() == "None") ? 0 : 1;                                                    // s4 check
    float notaFdsCompleto = (cand->getTurno() != "None" && boolFds) ? 1 : 0;                                                                                                                         // s5
    float notaTotalAloc = (cand->getTurno() != "None") ? enf->getContrato().getMinAlocacoes() - enfProg.getTotalAloc() : 0;                                                                          // s6
    float notaTotalFds = (cand->getTurno() != "None" && (cand->getDia() == "Sat" || cand->getDia() == "Sun")) ? enf->getContrato().getMaxAlocacoesFimSemana() - enfProg.getTotalAlocFimSemana() : 0; // s7
    float notaHabilidadeRara = (cand->getTurno() != "None") ? (qtdEnfComHabilidade[cand->getHabilidade()] / habilidadesInstancia.size()) : 0;
    float nota;
    // se não viável

    if (!sol.avaliaViabilidade())
    {
        // if(quantoFaltaDemandaMin > 0) -> nota abaixo
        // else nota = 0
        if (quantoFaltaDemandaMin > 0)
        {
            nota = quantoFaltaDemandaMin + notaHabilidadeRara + ((quantoFaltaDemandaOpt + notaPreferencia + notaFdsCompleto + notaTotalAloc + notaTotalFds) / 5);
        }
        else
        {
            nota = 0;
        }
    }
    else
    {
        // se viável
        // td mundo nota abaixo sem demanda min
        nota = notaHabilidadeRara + quantoFaltaDemandaOpt +
               notaPreferencia + notaFdsCompleto +
               notaTotalAloc + notaTotalFds;
    }

    cand->setValor(nota);
}

void Instancia::alocaCandidato(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, EnfermeiroProgresso &enfProg, Semana &semana, Solucao &sol, vector<unique_ptr<Candidato>> &candidatos, map<string, map<string, map<string, bool>>> &mapBooleans)
{
    // REMOVE CANDS AGORA IMPOSSÍVEIS

    // Faz alocação na solução

    sol.adicionarAlocacao(enf, cand->getDia(), cand->getTurno(), cand->getHabilidade(), true);

    // AJUSTA DEMANDA

    // if(cand->getTurno() != "None"
    // semana.alocacao(dia, turno, hab) que incrementa o supridos em 1

    if (cand->getTurno() != "None")
    {
        sol.incrementaDemandaSuprida(cand->getDia(), cand->getTurno(), cand->getHabilidade(), 1);

        // AJUSTA ENFERMEIRO

        // totais:
        // if(cand->getTurno() != "None") incrementa alocTotal

        enfProg.setTotalAloc(enfProg.getTotalAloc() + 1);
    }

    // pref:
    // if(prefereFolga(<dadosCnd>) incrementa turnosContraPref

    if (semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()))
    {
        enfProg.setTotalTurnosContraPref(enfProg.getTotalTurnosContraPref() + 1);
    }

    // Fds:

    // se sat, altera o map[sun] pra todos os turnos pra true, e o msm pro contrário

    string diaFds = "";
    if (cand->getDia() == "Sat")
    {
        diaFds = "Sun";
    }
    else
    {
        if (cand->getDia() == "Sun")
        {
            diaFds = "Sat";
        }
    }

    for (int i = 0; i < tipoTurnos.size(); i++)
    {
        for (int j = 0; j < enf->getHabilidades().size(); j++)
        {
            mapBooleans[diaFds][tipoTurnos[i]][enf->getHabilidades()[j]] = true;
        }
    }

    // Se sat ou sun, incrementa totalFds

    if (cand->getDia() == "Sat" || cand->getDia() == "Sun")
    {
        enfProg.setTotalAlocFimSemana(enfProg.getTotalAlocFimSemana() + 1);
    }

    // Percorre toda lista de candidatos
    // Remove candidato e os outros no mesmo dia, posso só remover td mundo do dia

    vector<int> candidatosParaApagar; // provavelmente ngm vai ler isso mas eu sou mto idiota pqp, eh por q nn tinha isso q tava dando errado
    for (int i = 0; i < candidatos.size(); i++)
    {
        if (candidatos[i]->getDia() == cand->getDia())
        {
            candidatosParaApagar.push_back(i);
        }
    }

    for (int i = candidatosParaApagar.size() - 1; i >= 0; i--)
    {
        candidatos.erase(candidatos.begin() + candidatosParaApagar[i]);
    }

    // FUNCIONA ATÉ AQUI ---------------------------------------------------------------------------------------
}

void Instancia::mudaTurno(Solucao &solSemana, Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, string turnoNovo, string dia, string turnoAntigo, string habilidade)
{

    if (turnoAntigo == turnoNovo) // não muda nada
    {
        return;
    }

    if (turnoAntigo != "None")
    {
        if (!solSemana.getTotalAlocacoes().at(enf).at(dia).at(turnoAntigo).at(habilidade))
        {
            std::cout << endl
                      << "Não estava alocado antes" << endl;
            return;
        }
    }

    /*

    cout << endl
         << endl
         << "MUDANDO O TURNO: " << enf->getCodigo() << " (" << dia << ", " << turnoAntigo << ", " << habilidade << ") para " << " (" << dia << ", " << turnoNovo << ", " << habilidade << ")" << endl
         << endl;
    cout << endl
         << endl
         << "ANTES:" << endl
         << endl;
    solSemana.exibirAlocacoes();

    */

    // atualiza o map de alocacoes

    if (turnoAntigo == "None" && turnoNovo != "None")
    {
        solSemana.adicionarAlocacao(enf, dia, turnoNovo, habilidade, true);
    }
    else
    {
        if (turnoNovo == "None" && turnoAntigo != "None")
        {
            solSemana.adicionarAlocacao(enf, dia, turnoAntigo, habilidade, false);
        }
        else
        {
            solSemana.adicionarAlocacao(enf, dia, turnoNovo, habilidade, true);
            solSemana.adicionarAlocacao(enf, dia, turnoAntigo, habilidade, false);
        }
    }

    if (turnoNovo == "None")
    {
        // não trabalha no dia/desaloca
        // demanda

        solSemana.decrementaDemandaSuprida(dia, turnoAntigo, habilidade, 1);

        // enfermeiro

        enfProg.setTotalAloc(enfProg.getTotalAloc() - 1);
        if (turnoAntigo == "Sat" || turnoAntigo == "Sun")
        {
            enfProg.setTotalAlocFimSemana(enfProg.getTotalAlocFimSemana() - 1);
        }
    }
    else
    {
        if (turnoAntigo == "None")
        {
            // passa a trabalhar no dia/aloca
            // demanda

            solSemana.incrementaDemandaSuprida(dia, turnoNovo, habilidade, 1);

            // enfermeiro

            enfProg.setTotalAloc(enfProg.getTotalAloc() + 1);
            if (turnoNovo == "Sat" || turnoNovo == "Sun")
            {
                enfProg.setTotalAlocFimSemana(enfProg.getTotalAlocFimSemana() + 1);
            }
        }
        else
        {
            // só muda de turno
            // demanda

            solSemana.decrementaDemandaSuprida(dia, turnoAntigo, habilidade, 1);
            solSemana.incrementaDemandaSuprida(dia, turnoNovo, habilidade, 1);

            // enfermeiro

            if ((turnoNovo == "Sat" || turnoNovo == "Sun") && (turnoAntigo != "Sat" && turnoAntigo != "Sun"))
            {
                enfProg.setTotalAlocFimSemana(enfProg.getTotalAlocFimSemana() + 1);
            }
            if ((turnoAntigo == "Sat" || turnoAntigo == "Sun") && (turnoNovo != "Sat" && turnoNovo != "Sun"))
            {
                enfProg.setTotalAlocFimSemana(enfProg.getTotalAlocFimSemana() - 1);
            }
        }
    }

    /*

    cout << endl
         << endl
         << "DEPOIS:" << endl
         << endl;
    solSemana.exibirAlocacoes();

    */
}

int Instancia::mudaCalculaNotaBuscaLocal(Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, SolucaoCompleta &sol, Solucao &solSemana, string dia, string habilidade, string turnoNovo)
{

    // verifica qual era o turno antigo

    string turnoAntigo = "None";
    for (int turno = 0; turno < tipoTurnos.size(); turno++)
    {
        if (solSemana.getTotalAlocacoes().at(enf).at(dia).at(tipoTurnos[turno]).at(habilidade))
        {
            turnoAntigo = tipoTurnos[turno];
        }
    }

    // salva valores de antes

    int grauInviabilidadeAntes = solSemana.grauViabilidadeTurno(dia, turnoAntigo, habilidade) + solSemana.grauViabilidadeTurno(dia, turnoNovo, habilidade);
    int demandasOptFaltandoAntes = solSemana.demandasOtimasFaltandoTurno(dia, turnoNovo, habilidade) + solSemana.demandasOtimasFaltandoTurno(dia, turnoAntigo, habilidade);
    int alocTotalAntes = enfProg.getTotalAloc();
    int alocFdsAntes = enfProg.getTotalAlocFimSemana();

    // faz mudanca

    mudaTurno(solSemana, semanaInstancia, enfProg, enf, turnoNovo, dia, turnoAntigo, habilidade);

    // calcula com valores depois

    int mudancaDemandaMin = solSemana.grauViabilidadeTurno(dia, turnoAntigo, habilidade) + solSemana.grauViabilidadeTurno(dia, turnoNovo, habilidade) - grauInviabilidadeAntes;
    int mudancaDemandaOpt = solSemana.demandasOtimasFaltandoTurno(dia, turnoNovo, habilidade) + solSemana.demandasOtimasFaltandoTurno(dia, turnoAntigo, habilidade) - demandasOptFaltandoAntes;
    int mudancaAlocTotal = enfProg.getTotalAloc() - alocTotalAntes;
    int mudancaAlocFds = enfProg.getTotalAlocFimSemana() - alocFdsAntes;

    // retorna resultado

    sol.setGrauInviabilidade(sol.getGrauInviabilidade() + mudancaDemandaMin);
    sol.setPenalidade(sol.getPenalidade() + mudancaDemandaOpt + mudancaAlocTotal + mudancaAlocFds);
    return sol.getPenalidade();
}

void Instancia::mudaHabilidade(Solucao &solSemana, Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, string turno, string dia, string habilidadeNova, string habilidadeAntiga)
{
    if (habilidadeAntiga == habilidadeNova) // não muda nada
    {
        return;
    }

    if (habilidadeAntiga != "None")
    {
        if (!solSemana.getTotalAlocacoes().at(enf).at(dia).at(turno).at(habilidadeAntiga))
        {
            std::cout << endl
                      << "Não estava alocado antes" << endl;
            return;
        }
    }

    if (!solSemana.getTotalAlocacoes().at(enf).at(dia).at(turno).at(habilidadeNova))
    {
        std::cout << endl
                  << "Já está alocado" << endl;
        return;
    }

    // atualiza o map de alocacoes

    if (habilidadeAntiga == "None")
    {
        solSemana.adicionarAlocacao(enf, dia, turno, habilidadeNova, true);
        solSemana.incrementaDemandaSuprida(dia, turno, habilidadeNova, 1);
        enfProg.setTotalAloc(enfProg.getTotalAloc() + 1);
        if (dia == "Sat" || dia == "Sun")
        {
            enfProg.setTotalAlocFimSemana(enfProg.getTotalFdsIncompleto() + 1);
        }
    }
    else
    {
        solSemana.adicionarAlocacao(enf, dia, turno, habilidadeNova, true);
        solSemana.adicionarAlocacao(enf, dia, turno, habilidadeAntiga, false);
        solSemana.decrementaDemandaSuprida(dia, turno, habilidadeAntiga, 1);
        solSemana.incrementaDemandaSuprida(dia, turno, habilidadeNova, 1);
    }
}

int Instancia::mudaHabilidadeCalculaNotaBuscaLocal(Semana &semanaInstancia, EnfermeiroProgresso &enfProg, shared_ptr<Enfermeiro> enf, SolucaoCompleta &sol, Solucao &solSemana, string dia, string turno, string habilidadeNova)
{
    if (turno == "None")
    {
        return 0;
    }
    // verifica qual era o turno antigo

    string habilidadeAntiga = "None";
    vector<string> habEnf = enf->getHabilidades();
    for (int hab = 0; hab < habEnf.size(); hab++)
    {
        if (solSemana.getTotalAlocacoes().at(enf).at(dia).at(turno).at(habEnf[hab]))
        {
            habilidadeAntiga = habEnf[hab];
        }
    }

    // salva valores de antes

    int grauInviabilidadeAntes = solSemana.grauViabilidadeTurno(dia, turno, habilidadeAntiga) + solSemana.grauViabilidadeTurno(dia, turno, habilidadeNova);
    int demandasOptFaltandoAntes = solSemana.demandasOtimasFaltandoTurno(dia, turno, habilidadeAntiga) + solSemana.demandasOtimasFaltandoTurno(dia, turno, habilidadeNova);
    int alocTotalAntes = enfProg.getTotalAloc();
    int alocFdsAntes = enfProg.getTotalAlocFimSemana();

    // faz mudanca

    mudaHabilidade(solSemana, semanaInstancia, enfProg, enf, turno, dia, habilidadeNova, habilidadeAntiga);

    // calcula com valores depois

    int mudancaDemandaMin = solSemana.grauViabilidadeTurno(dia, turno, habilidadeAntiga) + solSemana.grauViabilidadeTurno(dia, turno, habilidadeNova) - grauInviabilidadeAntes;
    int mudancaDemandaOpt = solSemana.demandasOtimasFaltandoTurno(dia, turno, habilidadeAntiga) + solSemana.demandasOtimasFaltandoTurno(dia, turno, habilidadeNova) - demandasOptFaltandoAntes;
    int mudancaAlocTotal = enfProg.getTotalAloc() - alocTotalAntes;
    int mudancaAlocFds = enfProg.getTotalAlocFimSemana() - alocFdsAntes;

    // retorna resultado

    sol.setGrauInviabilidade(sol.getGrauInviabilidade() + mudancaDemandaMin);
    sol.setPenalidade(sol.getPenalidade() + mudancaDemandaOpt + mudancaAlocTotal + mudancaAlocFds);
    return sol.getPenalidade();
}

void Instancia::ils(shared_ptr<SolucaoCompleta> solCompleta, int numSemana, int limiteIterILS, int limiteIterBL)
{
    // busca local inicial

    buscaLocal(solCompleta, numSemana, limiteIterBL);

    // cria ponteiro melhorSol pra guardar a melhor até agr

    SolucaoCompleta &solucaoAtual = *solCompleta;

    // while contador < limiteIter
    for (int contador = 0; contador < limiteIterILS; contador++)
    {
        // clona melhorSol
        auto solucaoAtualClone = std::make_shared<SolucaoCompleta>(solucaoAtual);

        // perturba solucao
        perturbacao(solucaoAtualClone, numSemana);

        // busca local no clone
        buscaLocal(solucaoAtualClone, numSemana, limiteIterBL);
        // if (penalidade(melhorSol) > penalidade(solClone))
        //     *melhorSol = clone

        int penalidadeAtual = solucaoAtual.getPenalidade() * solucaoAtual.getGrauInviabilidade() + solucaoAtual.getPenalidade();
        int penalidadeClone = solucaoAtualClone->getPenalidade() * solucaoAtualClone->getGrauInviabilidade() + solucaoAtualClone->getPenalidade();

        if (penalidadeClone < penalidadeAtual)
        {
            solucaoAtual = *solucaoAtualClone;
            cout << "Penalidade atual vs clone: " << penalidadeAtual << " vs " << penalidadeClone;
        }
    }

    // muda solucao pra ser a do ils

    *solCompleta = solucaoAtual;
}

void Instancia::buscaLocal(shared_ptr<SolucaoCompleta> solCompleta, int numSemana, int limiteIter)
{
    // recebe SolucaoCompleta, numeroSemana e qtdIteracoes

    // inicializa melhor solucao + contador + houveMudanca

    bool houveMudanca = true;
    int contador = 0;
    SolucaoCompleta &melhorSolucao = *solCompleta;
    SolucaoCompleta &solucaoAtual = *solCompleta;
    vector<string> diasSemana = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    vector<string> turnosComNone(this->getTipoTurnos());
    turnosComNone.push_back("None");

    // while(tiver melhora)

    while (houveMudanca && contador < limiteIter)
    {
        houveMudanca = false;

        for (int enf = 0; enf < enfermeiros.size(); enf++) // for(todos os enfermeiros)
        {
            vector<string> enfHabilidades = enfermeiros[enf]->getHabilidades();
            for (int dia = 0; dia < 7; dia++) // for(todos os dias)
            {
                for (int hab = 0; hab < enfHabilidades.size(); hab++)
                {
                    for (int turnos = 0; turnos < turnosComNone.size(); turnos++) // for(turnos)
                    {
                        // SolucaoCompleta solucaoAtual = clone da solInicial
                        SolucaoCompleta solucaoAtualClone = SolucaoCompleta(solucaoAtual);

                        // faz mudança

                        mudaCalculaNotaBuscaLocal(semanas[numSemana], solucaoAtualClone.getEnfProg()[enfermeiros[enf]->getCodigo()], enfermeiros[enf], solucaoAtualClone, solucaoAtualClone.getSolucoesSemana()[numSemana], diasSemana[dia], enfHabilidades[hab], turnosComNone[turnos]);
                        //    reavalia penalidade (CONSIDER INVIABILIDADE!! fazer uma func penalidadeComInv)

                        int penalidadeMelhorAtual = melhorSolucao.getGrauInviabilidade() * melhorSolucao.getPenalidade() + melhorSolucao.getPenalidade();
                        int penalidadeNovaSolucao = solucaoAtualClone.getGrauInviabilidade() * solucaoAtualClone.getPenalidade() + solucaoAtualClone.getPenalidade();

                        //      TENHO QUE MUDAR PRA NÃO COLOCAR MAIS ENFERMEIRO DEPOIS QUE CUMPRIU A ÓTIMA
                        //      será que melhora??
                        //      if(solucaoAtual.penalidade < melhorSol->penalidade)
                        //          melhorSol = &solucaoAtual;
                        //          houveMudanca = true;

                        if (penalidadeNovaSolucao < penalidadeMelhorAtual)
                        {
                            melhorSolucao = solucaoAtualClone;
                            houveMudanca = true;
                        }
                    }
                }
            }
        }
        solucaoAtual = melhorSolucao; // muda só depois de passar por tudo e dar uma chance pra todos
    }

    // solucaoFinal = &melhorSol
    *solCompleta = melhorSolucao;
}

void Instancia::ordenaVetorCand(vector<unique_ptr<Candidato>> &candidatos)
{
    // Ordenar o vetor pelas notas em ordem decrescente
    std::sort(candidatos.begin(), candidatos.end(),
              [](const std::unique_ptr<Candidato> &a, const std::unique_ptr<Candidato> &b)
              {
                  return a->getValor() > b->getValor();
              });
}

bool Instancia::avaliaViabilidade(Solucao &sol)
{
    bool viavel = sol.avaliaViabilidade();

    return viavel;
}

int Instancia::avaliaNota(vector<Solucao> &sol, map<string, EnfermeiroProgresso> &enfProgMap)
{
    // demanda otima não cumprida (ver de cada semana)
    int demandaOtimaFalta = 0;
    cout << "qtd semanas: " << sol.size() << endl;

    for (int i = 0; i < sol.size(); i++)
    {
        cout << endl
             << "Semana " << i << " demandas faltando: " << endl;
        // fazer método em solucao que retorne o que falta da demanda ótima
        demandaOtimaFalta += sol[i].somaDemandasOtimasFaltando();
    }
    std::cout << "demandaOtimaFalta: " << demandaOtimaFalta << std::endl;
    if (demandaOtimaFalta < 0)
    {
        demandaOtimaFalta = 0;
    }

    // coisas do enfermeiro

    int preferenciasFalta = 0;
    int fdsIncompleto = 0;
    int alocTotalFaltaMin = 0;
    int alocTotalAcimaMax = 0;
    int fdsTotalAcimaMax = 0;

    for (int i = 0; i < enfermeiros.size(); i++)
    {
        EnfermeiroProgresso &enfProg = enfProgMap[enfermeiros[i]->getCodigo()];
        preferenciasFalta += enfProg.getTotalTurnosContraPref();
        fdsIncompleto += enfProg.getTotalFdsIncompleto();
        if (enfProg.getTotalAloc() <= enfermeiros[i]->getContrato().getMinAlocacoes())
        {
            alocTotalFaltaMin += enfermeiros[i]->getContrato().getMinAlocacoes() - enfProg.getTotalAloc();
        }
        else
        {
            if (enfProg.getTotalAloc() > enfermeiros[i]->getContrato().getMaxAlocacoes())
            {
                alocTotalAcimaMax += enfProg.getTotalAloc() - enfermeiros[i]->getContrato().getMaxAlocacoes();
            }
        }
        if (enfProg.getTotalAlocFimSemana() > enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana())
        {
            fdsTotalAcimaMax += enfProg.getTotalAlocFimSemana() - enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana();
        }
    }

    std::cout << "preferenciasFalta: " << preferenciasFalta << std::endl;
    std::cout << "fdsIncompleto: " << fdsIncompleto << std::endl;
    std::cout << "alocTotalFaltaMin: " << alocTotalFaltaMin << std::endl;
    std::cout << "alocTotalAcimaMax: " << alocTotalAcimaMax << std::endl;
    std::cout << "fdsTotalAcimaMax: " << fdsTotalAcimaMax << std::endl;

    int penalidade = demandaOtimaFalta + preferenciasFalta + fdsIncompleto + (alocTotalFaltaMin + alocTotalAcimaMax) + fdsTotalAcimaMax;
    return penalidade;
}

void Instancia::registraSolucao(vector<Solucao> &solucoes, map<string, EnfermeiroProgresso> &enfProgMap, string codigoInstancia, int numeroIteracao, int duracaoMilissegundos)
{
    ofstream outputFile;
    outputFile.open("resultadosTestes/ILS/" + codigoInstancia + ".txt", ios::app);

    if (!outputFile.is_open())
    {
        cerr << "Erro ao abrir output.txt" << endl;
        return;
    }

    outputFile << "-------Instância " << codigoInstancia << " iteração " << numeroIteracao << "-------\n\n";

    outputFile << "---viabilidade:\n\n";

    int grauInviabilidade = 0;
    for (int i = 0; i < semanas.size(); i++)
    {
        Solucao &solAtual = solucoes[i];

        outputFile << "semana " << i + 1 << ": " << (solAtual.getGrauInviabilidade() > 0 ? "sim" : "não")
                   << " (grau de inviabilidade " << solAtual.getGrauInviabilidade() << ")\n";
        grauInviabilidade += solAtual.getGrauInviabilidade();
    }

    outputFile << "\n---penalidade\n\n";

    int demandaOtimaFalta = 0;

    outputFile << "-falta demanda ótima por semana:\n\n";
    for (int i = 0; i < solucoes.size(); i++)
    {
        Solucao &solAtual = solucoes[i];
        int demandaOtimaFaltaSemana = solAtual.somaDemandasOtimasFaltando();
        outputFile << "semana " << i + 1 << ": " << demandaOtimaFaltaSemana << "\n";
        demandaOtimaFalta += demandaOtimaFaltaSemana;
    }

    // coisas do enfermeiro

    int preferenciasFalta = 0;
    int fdsIncompleto = 0;
    int alocTotalFaltaMin = 0;
    int alocTotalAcimaMax = 0;
    int fdsTotalAcimaMax = 0;

    for (int i = 0; i < enfermeiros.size(); i++)
    {
        EnfermeiroProgresso &enfProg = enfProgMap[enfermeiros[i]->getCodigo()];
        preferenciasFalta += enfProg.getTotalTurnosContraPref();
        fdsIncompleto += enfProg.getTotalFdsIncompleto();
        if (enfProg.getTotalAloc() <= enfermeiros[i]->getContrato().getMinAlocacoes())
        {
            alocTotalFaltaMin += enfermeiros[i]->getContrato().getMinAlocacoes() - enfProg.getTotalAloc();
        }
        else
        {
            if (enfProg.getTotalAloc() > enfermeiros[i]->getContrato().getMaxAlocacoes())
            {
                alocTotalAcimaMax += enfProg.getTotalAloc() - enfermeiros[i]->getContrato().getMaxAlocacoes();
            }
        }
        if (enfProg.getTotalAlocFimSemana() > enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana())
        {
            fdsTotalAcimaMax += enfProg.getTotalAlocFimSemana() - enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana();
        }
    }

    outputFile << "-geral:\n\n";
    outputFile << "demandaOtimaFalta: " << demandaOtimaFalta << "\n";
    outputFile << "preferenciasFalta: " << preferenciasFalta << "\n";
    outputFile << "fdsIncompleto: " << fdsIncompleto << "\n";
    outputFile << "alocTotalFaltaMin: " << alocTotalFaltaMin << "\n";
    outputFile << "alocTotalAcimaMax: " << alocTotalAcimaMax << "\n";
    outputFile << "fdsTotalAcimaMax: " << fdsTotalAcimaMax << "\n\n";

    int penalidade = demandaOtimaFalta + preferenciasFalta + fdsIncompleto + (alocTotalFaltaMin + alocTotalAcimaMax) + fdsTotalAcimaMax;

    outputFile << "\n---conclusão\n\n";
    outputFile << "viável: " << ((grauInviabilidade == 0) ? "sim" : "não") << "\n";
    outputFile << "grau de inviabilidade: " << grauInviabilidade << "\n";
    outputFile << "penalidade: " << penalidade << "\n\n";
    outputFile << "tempo total: " << duracaoMilissegundos << "ms\n\n";
    outputFile << "-------------------------------------------\n\n";

    outputFile.close();
}

void Instancia::perturbacao(shared_ptr<SolucaoCompleta> solCompleta, int numSemana)
{
    vector<string> tipoTurnosComNone(tipoTurnos);
    tipoTurnosComNone.push_back("None");
    setTipoTurnos(tipoTurnosComNone);

    // sorteia os dias a serem trocados

    string dia1 = getDiaSemana(random(0, 6));
    string dia2 = dia1;
    while (dia1 == dia2)
    {
        dia2 = getDiaSemana(random(0, 6));
    }

    cout << "Dias do swap: " << dia1 << "/ " << dia2 << endl;

    Solucao &solucaoSemana = solCompleta->getSolucoesSemana()[numSemana];

    // pega os valores antes da mudança

    // inicializa os de demandaMin e demandaOpt

    int demandaMinDepois = 0;
    int demandaOptDepois = 0;

    // totalAlocFds

    int totalAlocFdsAntes = 0;
    int totalAlocFdsDepois = 0;

    int demandaMinAntes = 0;
    int demandaOptAntes = 0;

    for (int enf = 0; enf < enfermeiros.size(); enf++)
    {
        // pega o total aloc do fds antes de cada enfermeiro
        totalAlocFdsAntes += solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana();
        for (int turno = 0; turno < tipoTurnos.size(); turno++)
        {
            vector<string> enfHabilidades(enfermeiros[enf]->getHabilidades());
            enfHabilidades.push_back("None");
            for (int hab = 0; hab < enfHabilidades.size(); hab++)
            {
                // pega demanda minima e ótima antes
                demandaMinAntes += (solucaoSemana.grauViabilidadeTurno(dia1, tipoTurnos[turno], enfHabilidades[hab]) + solucaoSemana.grauViabilidadeTurno(dia2, tipoTurnos[turno], enfHabilidades[hab]));
                demandaOptAntes += (solucaoSemana.demandasOtimasFaltandoTurno(dia1, tipoTurnos[turno], enfHabilidades[hab]) + solucaoSemana.demandasOtimasFaltandoTurno(dia2, tipoTurnos[turno], enfHabilidades[hab]));
            }
        }
    }

    // realização do swap

    // atualiza demandas

    for (int turno = 0; turno < tipoTurnos.size(); turno++)
    {
        for (int hab = 0; hab < habilidadesInstancia.size(); hab++)
        {
            // atualiza demanda suprida
            int demandaSupridaDia1 = solucaoSemana.getDemandaSupridaEspecifica(dia1, tipoTurnos[turno], habilidadesInstancia[hab]);
            int demandaSupridaDia2 = solucaoSemana.getDemandaSupridaEspecifica(dia2, tipoTurnos[turno], habilidadesInstancia[hab]);
            solucaoSemana.adicionarDemandaSuprida(dia1, tipoTurnos[turno], habilidadesInstancia[hab], demandaSupridaDia2);
            solucaoSemana.adicionarDemandaSuprida(dia2, tipoTurnos[turno], habilidadesInstancia[hab], demandaSupridaDia1);
        }
    }

    for (int enf = 0; enf < enfermeiros.size(); enf++)
    {
        vector<string> enfHabilidades = enfermeiros[enf]->getHabilidades();
        enfHabilidades.push_back("None");
        for (int turno = 0; turno < tipoTurnos.size(); turno++)
        {
            for (int hab = 0; hab < enfHabilidades.size(); hab++)
            {
                // atualiza alocacoes
                bool alocDia1 = solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia1, tipoTurnos[turno], enfHabilidades[hab]);
                bool alocDia2 = solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia2, tipoTurnos[turno], enfHabilidades[hab]);
                solucaoSemana.adicionarAlocacao(enfermeiros[enf], dia1, tipoTurnos[turno], enfHabilidades[hab], alocDia2);
                solucaoSemana.adicionarAlocacao(enfermeiros[enf], dia2, tipoTurnos[turno], enfHabilidades[hab], alocDia1);

                // se o turno era alocado e agora nao é, remove um

                if ((dia1 == "Sat" || dia1 == "Sun") && (alocDia2 == false) && (solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia1, tipoTurnos[turno], enfHabilidades[hab])))
                {
                    solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].setTotalAlocFimSemana(solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana() - 1);
                }
                if ((dia2 == "Sat" || dia2 == "Sun") && (alocDia1 == false) && (solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia2, tipoTurnos[turno], enfHabilidades[hab])))
                {
                    solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].setTotalAlocFimSemana(solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana() - 1);
                }

                // se o turno NAO era alocado e agora É, adiciona 1
                if ((dia1 == "Sat" || dia1 == "Sun") && (alocDia2 == true) && (!solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia1, tipoTurnos[turno], enfHabilidades[hab])))
                {
                    solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].setTotalAlocFimSemana(solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana() + 1);
                }
                if ((dia2 == "Sat" || dia2 == "Sun") && (alocDia1 == true) && (!solucaoSemana.getAlocacaoEspecifica(enfermeiros[enf], dia2, tipoTurnos[turno], enfHabilidades[hab])))
                {
                    solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].setTotalAlocFimSemana(solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana() + 1);
                }
            }
        }
    }

    // pega valores DEPOIS

    for (int enf = 0; enf < enfermeiros.size(); enf++)
    {
        // pega o total aloc do fds Depois de cada enfermeiro
        totalAlocFdsDepois += solCompleta->getEnfProg()[enfermeiros[enf]->getCodigo()].getTotalAlocFimSemana();
        for (int turno = 0; turno < tipoTurnos.size(); turno++)
        {
            vector<string> enfHabilidades = enfermeiros[enf]->getHabilidades();
            enfHabilidades.push_back("None");
            for (int hab = 0; hab < enfHabilidades.size(); hab++)
            {
                // pega demanda minima e ótima Depois

                string turnoAtual = tipoTurnos[turno];

                string habAtual = enfHabilidades[hab];

                demandaMinDepois += (solucaoSemana.grauViabilidadeTurno(dia1, tipoTurnos[turno], enfHabilidades[hab]) + solucaoSemana.grauViabilidadeTurno(dia2, tipoTurnos[turno], enfHabilidades[hab]));
                demandaOptDepois += (solucaoSemana.demandasOtimasFaltandoTurno(dia1, tipoTurnos[turno], enfHabilidades[hab]) + solucaoSemana.demandasOtimasFaltandoTurno(dia2, tipoTurnos[turno], enfHabilidades[hab]));
            }
        }
    }

    int mudancaPenalidade = (totalAlocFdsDepois - totalAlocFdsAntes) + (demandaOptDepois - demandaOptAntes);
    int mudancaGrauInv = (demandaMinDepois - demandaMinAntes);

    // Impressão com quebras de linha antes
    cout << "\n\n\n";

    // Impressão das variáveis utilizadas nos cálculos
    cout << "Total Aloc Fds Antes: " << totalAlocFdsAntes << endl;
    cout << "Total Aloc Fds Depois: " << totalAlocFdsDepois << endl;
    cout << "Demanda Opt Antes: " << demandaOptAntes << endl;
    cout << "Demanda Opt Depois: " << demandaOptDepois << endl;
    cout << "Demanda Min Antes: " << demandaMinAntes << endl;
    cout << "Demanda Min Depois: " << demandaMinDepois << endl;

    cout << "\n"; // Separação entre os valores originais e os cálculos

    // Impressão das mudanças calculadas
    cout << "Mudanca Penalidade: " << mudancaPenalidade << endl;
    cout << "Mudanca Grau Inviabilidade: " << mudancaGrauInv << endl;

    // Impressão com quebras de linha depois
    cout << "\n\n\n";

    solCompleta->setPenalidade(solCompleta->getPenalidade() + mudancaPenalidade);
    solCompleta->setGrauInviabilidade(solCompleta->getGrauInviabilidade() + mudancaGrauInv);
    // reavaliar qualidade dentro do loop
}

shared_ptr<SolucaoCompleta> Instancia::guloso(int alfa, string instancia, int iteracao)
{
    // começa a medir o tempo

    auto start = std::chrono::high_resolution_clock::now();
    Beep(523, 500);

    shared_ptr<SolucaoCompleta> solCompleta = make_unique<SolucaoCompleta>(this->enfermeiros);
    for (int i = 0; i < semanas.size(); i++)
    {
        cout << endl
             << "--------SEMANA " << semanaAtual << ": ---------" << endl;
        setSemanaAtual(i);
        unique_ptr<Solucao> sol = gulosoSemana(alfa, solCompleta->getEnfProg());
        sol->exibirAlocacoes();
        // TENHO QUE PASSAR A AVALIÇÃO PRA FORA E AVALIAR VIABILIDADE FORA TBM
        solCompleta->adicionaSolucaoSemana(*sol);
        semanaAtual++;
    }
    bool viavel = true;
    int grauInviabilidadeSol = 0;
    vector<Solucao> &solucoesSemanas = solCompleta->getSolucoesSemana();
    for (int j = 0; j < solucoesSemanas.size(); j++)
    {
        viavel = viavel && solucoesSemanas[j].avaliaViabilidade();
        grauInviabilidadeSol += solucoesSemanas[j].getGrauInviabilidade();
    }
    solCompleta->setGrauInviabilidade(grauInviabilidadeSol);
    int penalidadeSol = avaliaNota(solucoesSemanas, solCompleta->getEnfProg());
    solCompleta->setPenalidade(penalidadeSol);
    cout << "Viavel: " << (viavel ? "Sim" : "Nao") << "/ Penalidade: " << penalidadeSol << endl;

    for (int numSemana = 0; numSemana < this->getSemanas().size(); numSemana++)
    {
        ils(solCompleta, numSemana, 3, 10);
        // buscaLocal(solCompleta, numSemana, 100);
        // cout << "NUM SEMANA: " << numSemana << endl << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    int duracaMilissegundos = duration.count();

    registraSolucao(solucoesSemanas, solCompleta->getEnfProg(), instancia, iteracao, duracaMilissegundos);
    Beep(523, 500);

    return solCompleta;
}

unique_ptr<Solucao> Instancia::gulosoSemana(int alfa, map<string, EnfermeiroProgresso> &enfProgresso)
{
    // criar a solução

    unique_ptr<Solucao> solucao = make_unique<Solucao>();
    solucao->setSemanaDemandas(semanas[semanaAtual]);
    solucao->inicializaAlocacoes(enfermeiros, tipoTurnos, habilidadesInstancia);

    // ordena enfermeiros por: alocacoesFaltaProMin (acho que as sequenciais não fazem sentido aqui, e sim na escolha dos dias)
    // isso fica numa funcao ordenaVetorEnfermeiros()

    ordenaEnfermeiros(enfProgresso);

    // percorre vetor ordenado, e pra cada enfermeiro:

    for (int i = 0; i < enfermeiros.size(); i++)
    {
        // cria vetor com os trios dia/turno/habilidade (apenas com as habilidades que o enfermeiro em questão tem)
        vector<unique_ptr<Candidato>> candidatos;
        // eu deveria criar um map pra guardar os bools? dia->turno->habilidade->nomeBool;
        map<string, map<string, map<string, bool>>> mapBooleans;

        for (int dia = 0; dia < 7; dia++)
        {
            // criar candidato com turno None
            unique_ptr<Candidato> candNone = make_unique<Candidato>(getDiaSemana(dia), "None", "None", 0, 0, 0);
            candidatos.push_back(move(candNone));

            for (int turno = 0; turno < tipoTurnos.size(); turno++)
            {
                for (int hab = 0; hab < habilidadesInstancia.size(); hab++)
                {
                    if (encontraString(enfermeiros[i]->getHabilidades(), habilidadesInstancia[hab])) // verifica se tem a habilidade
                    {
                        unique_ptr<Candidato> cand = make_unique<Candidato>(
                            getDiaSemana(dia), tipoTurnos[turno], habilidadesInstancia[hab],
                            semanas[semanaAtual].getDemandaMinima(getDiaSemana(dia), tipoTurnos[turno], habilidadesInstancia[hab]) - solucao->getDemandasSupridas()[getDiaSemana(dia)][tipoTurnos[turno]][habilidadesInstancia[hab]],
                            semanas[semanaAtual].getDemandaOtima(getDiaSemana(dia), tipoTurnos[turno], habilidadesInstancia[hab]) - solucao->getDemandasSupridas()[getDiaSemana(dia)][tipoTurnos[turno]][habilidadesInstancia[hab]], 0);
                        candidatos.push_back(move(cand));
                        // setta os booleanos como falso inicialmente, pra serem alterados quando aloca
                        mapBooleans[getDiaSemana(dia)][tipoTurnos[turno]][habilidadesInstancia[hab]] = false;
                    }
                }
            }
        }

        // função calculaValorCand(Candidato &cand) -> void muda a nota de acordo com o valor
        // calcula a nota pra todos os candidatos
        for (int cand = 0; cand < candidatos.size(); cand++)
        {
            unique_ptr<Candidato> &candPtr = candidatos[cand];
            calculaValorCand(candPtr, enfermeiros[i], enfProgresso[enfermeiros[i]->getCodigo()], mapBooleans[candPtr->getDia()][candPtr->getTurno()][candPtr->getHabilidade()], solucao->getSemanaDemandas(), *solucao);
        }

        // função ordenaVetorCand() ordena com base na nota

        ordenaVetorCand(candidatos);

        // FUNCIONA ATÉ AQUI!

        // para todos os candidatos (ainda dentro do for do enfermeiro!) eu vou usando a func alocaCandidato

        while (!candidatos.empty())
        {
            // verifica se o número de candidatos > alfa

            int indiceSelecionado;
            if (candidatos.size() > alfa)
            {
                indiceSelecionado = random(0, alfa - 1);
            }
            else
            {
                indiceSelecionado = random(0, candidatos.size() - 1);
            }
            // sorteia um número aleatório entre 0 e alfa

            // aloca primeiro candidato
            alocaCandidato(candidatos[indiceSelecionado], enfermeiros[i], enfProgresso[enfermeiros[i]->getCodigo()], solucao->getSemanaDemandas(), *solucao, candidatos, mapBooleans);
            // refaz a nota do resto
            // reordena vetor
            for (int cand = 0; cand < candidatos.size(); cand++)
            {
                unique_ptr<Candidato> &candPtr = candidatos[cand];
                calculaValorCand(candPtr, enfermeiros[i], enfProgresso[enfermeiros[i]->getCodigo()], mapBooleans[candPtr->getDia()][candPtr->getTurno()][candPtr->getHabilidade()], solucao->getSemanaDemandas(), *solucao);
            }
            ordenaVetorCand(candidatos);
        }
    }

    solucao->exibirAlocacoes();
    // solucao->exibirAlocacoes();
    //       é isso, acho, essa função é rodada pra cada semana
    //       aplicar avaliador de viabilidade e qualidade

    return solucao;
}
