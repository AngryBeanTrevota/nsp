#include "..\header\Instancia.h"
#include "..\header\Candidato.h"
#include <algorithm>
#include <memory>

// Construtor
Instancia::Instancia()
    : totalSemanas(0), semanaAtual(0) {}

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
}

void Instancia::adicionarSemana(const Semana &semana)
{
    semanas.push_back(semana);
}

void Instancia::adicionarHabilidade(const string &habilidade)
{
    habilidadesInstancia.push_back(habilidade);
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

void Instancia::print() const
{
    cout << "=== Instância ===" << endl;
    cout << "Total de semanas: " << totalSemanas << endl;
    cout << "Semana atual: " << semanaAtual << endl;

    cout << "\nHabilidades da instância:" << endl;
    for (const auto &habilidade : habilidadesInstancia)
    {
        cout << " - " << habilidade << endl;
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

void Instancia::ordenaEnfermeiros()
{
    sort(enfermeiros.begin(), enfermeiros.end(),
         [](shared_ptr<Enfermeiro> a, shared_ptr<Enfermeiro> b)
         {
             return (a->getContrato().getMinAlocacoes() - a->getTotalAloc()) > (b->getContrato().getMinAlocacoes() - a->getTotalAloc()); // Ordem decrescente
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

void Instancia::calculaValorCand(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, bool boolFds, const Semana &semana)
{
    /*ordena esse vetor por ordenaVetorAlocacoes: quantoFaltaDemandaMin(se não faltar,
    considera a demanda ótima no segmento a seguir)
    + ((quantoFaltaDemandaOpt + quantoFaltaAlocacoesSeguidas*boolAnteriorSeguinteAloc -
    quantoFaltaDescansoSeguido*boolAnteriorSeguinteFolga - 1*boolPref(calcula aqui) + 1*boolOutroFds +
    quantoFaltaTotalAloc(pode ser negativo) + quantoFaltaFdsLimite(também pode ser negativo))/7)

    3 bool no vetor: anteriorSeguinteAloc, anteriorSeguinteFolga e outroFdsAloc
    */

    // considerar o caso turno sem ser none, turno fds e turno none

    float quantoFaltaDemandaMin = (cand->getTurno() != "None" && cand->getDemandaMin() > 0) ? cand->getDemandaMin() : 0;                                                                          // h1 check
    float quantoFaltaDemandaOpt = (cand->getTurno() != "None") ? cand->getDemandaOpt() : 0;                                                                                                       // s1 check
    float notaPreferencia = semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()) && (cand->getTurno() == "None") ? 0 : 1;                                                 // s4 check
    float notaFdsCompleto = (cand->getTurno() != "None" && boolFds) ? 1 : 0;                                                                                                                      // s5
    float notaTotalAloc = (cand->getTurno() != "None") ? enf->getContrato().getMinAlocacoes() - enf->getTotalAloc() : 0;                                                                          // s6
    float notaTotalFds = (cand->getTurno() != "None" && (cand->getDia() == "Sat" || cand->getDia() == "Sun")) ? enf->getContrato().getMaxAlocacoesFimSemana() - enf->getTotalAlocFimSemana() : 0; // s7

    float nota = quantoFaltaDemandaMin + ((quantoFaltaDemandaOpt +
                                           notaPreferencia + notaFdsCompleto +
                                           notaTotalAloc + notaTotalFds) /
                                          5);

    cand->setValor(nota);

    /*
        // Imprimir valores intermediários
        std::cout << endl
                  << "Cand " << cand->getDia() << " " << cand->getTurno() << " " << cand->getHabilidade() << endl;
        std::cout << "Quanto falta demanda mínima: " << quantoFaltaDemandaMin << std::endl;
        std::cout << "Quanto falta demanda ótima: " << quantoFaltaDemandaOpt << std::endl;
        std::cout << "Nota alocações consecutivas: " << notaAlocConsecutivas << std::endl;
        std::cout << "Nota folgas consecutivas: " << notaFolgasConsecutivas << std::endl;
        std::cout << "Nota preferência: " << notaPreferencia << std::endl;
        std::cout << "Nota fim de semana completo: " << notaFdsCompleto << std::endl;
        std::cout << "Nota total alocações: " << notaTotalAloc << std::endl;
        std::cout << "Nota total fim de semana: " << notaTotalFds << std::endl;

        // Imprimir nota final
        std::cout << "Nota final: " << nota << endl
                  << std::endl;
    */
}

void Instancia::alocaCandidato(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol, vector<unique_ptr<Candidato>> &candidatos, map<string, map<string, map<string, bool>>> &mapBooleans)
{

    // REMOVE CANDS AGORA IMPOSSÍVEIS

    // Faz alocação na solução

    sol.adicionarAlocacao(enf, cand->getDia(), cand->getTurno(), cand->getHabilidade(), true);

    // AJUSTA DEMANDA

    // if(cand->getTurno() != "None"
    // semana.alocacao(dia, turno, hab) que remove 1 tanto do mínimo quanto do ótimo

    if (cand->getTurno() != "None")
    {
        int novoValMin = semana.getDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) - 1;
        semana.setDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValMin);
        int novoValOpt = semana.getDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) - 1;
        semana.setDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValOpt);

        // AJUSTA ENFERMEIRO

        // totais:
        // if(cand->getTurno() != "None") incrementa alocTotal

        enf->setTotalAloc(enf->getTotalAloc() + 1);
    }

    // pref:
    // if(prefereFolga(<dadosCnd>) incrementa turnosContraPref

    if (semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()))
    {
        enf->setTotalTurnosContraPref(enf->getTotalTurnosContraPref() + 1);
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
        enf->setTotalAlocFimSemana(enf->getTotalAlocFimSemana() + 1);
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

void Instancia::desalocaBuscaLocal(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol)
{
    // REMOVE A ALOCAÇÃO DA SOLUÇÃO
    sol.adicionarAlocacao(enf, cand->getDia(), cand->getTurno(), cand->getHabilidade(), false);

    // AJUSTA DEMANDA (RESTAURA)
    if (cand->getTurno() != "None")
    {
        int novoValMin = semana.getDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) + 1;
        semana.setDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValMin);

        int novoValOpt = semana.getDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) + 1;
        semana.setDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValOpt);

        // REDUZ TOTAL DE ALOCAÇÕES DO ENFERMEIRO
        enf->setTotalAloc(enf->getTotalAloc() - 1);
    }

    // AJUSTA TURNOS CONTRA PREFERÊNCIA
    if (semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()))
    {
        enf->setTotalTurnosContraPref(enf->getTotalTurnosContraPref() - 1);
    }

    // AJUSTA FINAIS DE SEMANA
    if (cand->getDia() == "Sat" || cand->getDia() == "Sun")
    {
        enf->setTotalAlocFimSemana(enf->getTotalAlocFimSemana() - 1);
    }
}

void Instancia::alocaBuscaLocal(const unique_ptr<Candidato> &cand, shared_ptr<Enfermeiro> enf, Semana &semana, Solucao &sol)
{
    // ADICIONA A ALOCAÇÃO DA SOLUÇÃO
    sol.adicionarAlocacao(enf, cand->getDia(), cand->getTurno(), cand->getHabilidade(), true);

    // AJUSTA DEMANDA
    if (cand->getTurno() != "None")
    {
        int novoValMin = semana.getDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) - 1;
        semana.setDemandaMinima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValMin);

        int novoValOpt = semana.getDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade()) - 1;
        semana.setDemandaOtima(cand->getDia(), cand->getTurno(), cand->getHabilidade(), novoValOpt);

        // REDUZ TOTAL DE ALOCAÇÕES DO ENFERMEIRO
        enf->setTotalAloc(enf->getTotalAloc() + 1);
    }

    // AJUSTA TURNOS CONTRA PREFERÊNCIA
    if (semana.prefereFolgaTurno(enf->getCodigo(), cand->getDia(), cand->getTurno()))
    {
        enf->setTotalTurnosContraPref(enf->getTotalTurnosContraPref() + 1);
    }

    // AJUSTA FINAIS DE SEMANA
    if (cand->getDia() == "Sat" || cand->getDia() == "Sun")
    {
        enf->setTotalAlocFimSemana(enf->getTotalAlocFimSemana() + 1);
    }
}

void Instancia::buscaLocal(unique_ptr<Solucao> &sol)
{
    const auto &totalAlocacoes = sol->getTotalAlocacoes();

    // percorrer todos os candidatos
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
                    {
                        unique_ptr<Candidato> cand = make_unique<Candidato>(
                            nomeDia, nomeTurno, habilidade,
                            semanas[semanaAtual].getDemandaMinima(nomeDia, nomeTurno, habilidade),
                            semanas[semanaAtual].getDemandaOtima(nomeDia, nomeTurno, habilidade), 0);
                        // salvar o turno dele

                        //
                        // sol->setNota(avaliaNota(*sol, semanaAtual));
                        // sol->exibirAlocacoes();

                        string turnoCandOriginal = turno.first;
                        // para cada candidato, testar todos os turnos que não são o alocado
                        for (int outroTurno = 0; outroTurno < tipoTurnos.size(); outroTurno++)
                        {
                            if (tipoTurnos[outroTurno] != turnoCandOriginal)
                            {
                                // salva valor da solucao original

                                float penalidadeSolInicial = sol->getNota();

                                // desaloca o atual, aloca o novo

                                desalocaBuscaLocal(cand, enfermeiro.first, semanas[semanaAtual], *sol);
                                unique_ptr<Candidato> newCand = make_unique<Candidato>(
                                    nomeDia, tipoTurnos[outroTurno], habilidade,
                                    semanas[semanaAtual].getDemandaMinima(nomeDia, tipoTurnos[outroTurno], habilidade),
                                    semanas[semanaAtual].getDemandaOtima(nomeDia, tipoTurnos[outroTurno], habilidade), 0);
                                alocaBuscaLocal(newCand, enfermeiro.first, semanas[semanaAtual], *sol);

                                // se melhorar (DIMINUIR A PENALIDADE), passa a solucao nova pra essa func de novo

                                sol->setNota(avaliaNota(*sol, semanaAtual));
                                float penalidadeSolNova = sol->getNota();

                                if (penalidadeSolInicial > penalidadeSolNova)
                                {
                                    buscaLocal(sol); // recomeça com essa nova solução
                                }
                                else
                                {
                                    // se não melhorar, desaloca o novo, volta o original e retorna a nota
                                    desalocaBuscaLocal(newCand, enfermeiro.first, semanas[semanaAtual], *sol);
                                    alocaBuscaLocal(cand, enfermeiro.first, semanas[semanaAtual], *sol);
                                    sol->setNota(avaliaNota(*sol, semanaAtual));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    sol->exibirAlocacoes();
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
    bool viavel = false;
    if (sol.getSemanaDemandas().somaDemandasMinimas() == 0)
    {
        viavel = true;
        cout << "Solucao viável." << endl;
    }
    else
    {
        cout << "Solucao inviavel." << endl;
    }

    return viavel;
}

int Instancia::avaliaNota(Solucao &sol, int semanaAtual)
{

    // demanda otima não cumprida
    int demandaOtimaFalta = sol.getSemanaDemandas().somaDemandasOtimas();

    // coisas do enfermeiro

    int preferenciasFalta = 0;
    int fdsIncompleto = 0;
    int alocTotalFaltaMin = 0;
    int alocTotalAcimaMax = 0;
    int fdsTotalAcimaMax = 0;

    for (int i = 0; i < enfermeiros.size(); i++)
    {
        preferenciasFalta += enfermeiros[i]->getTotalTurnosContraPref();
        fdsIncompleto += enfermeiros[i]->getTotalFdsIncompleto();
        if (enfermeiros[i]->getTotalAloc() <= enfermeiros[i]->getContrato().getMinAlocacoes())
        {
            alocTotalFaltaMin += enfermeiros[i]->getContrato().getMinAlocacoes() - enfermeiros[i]->getTotalAloc();
        }
        else
        {
            if (enfermeiros[i]->getTotalAloc() > enfermeiros[i]->getContrato().getMaxAlocacoes())
            {
                alocTotalAcimaMax += enfermeiros[i]->getTotalAloc() - enfermeiros[i]->getContrato().getMaxAlocacoes();
            }
        }
        if (enfermeiros[i]->getTotalAlocFimSemana() > enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana())
        {
            fdsTotalAcimaMax += enfermeiros[i]->getTotalAlocFimSemana() - enfermeiros[i]->getContrato().getMaxAlocacoesFimSemana();
        }
    }

    int penalidade = demandaOtimaFalta + preferenciasFalta + fdsIncompleto + (alocTotalFaltaMin + alocTotalAcimaMax) + fdsTotalAcimaMax;
    return penalidade;
}

vector<unique_ptr<Solucao>> Instancia::guloso()
{
    vector<unique_ptr<Solucao>> solucoesSemanas;
    for (int i = 0; i < semanas.size(); i++)
    {
        setSemanaAtual(i);
        unique_ptr<Solucao> sol = gulosoSemana();
        cout << endl
             << "--------SEMANA " << semanaAtual << ": ---------" << endl;
        sol->exibirAlocacoes();
        cout << "Viavel: " << (avaliaViabilidade(*sol) ? "Sim" : "Nao") << "/ Penalidade: " << avaliaNota(*sol, semanaAtual) << endl;
        solucoesSemanas.push_back(move(sol));
    }
    return solucoesSemanas;
}

unique_ptr<Solucao> Instancia::gulosoSemana()
{
    // criar a solução

    unique_ptr<Solucao> solucao = make_unique<Solucao>();
    solucao->setSemanaDemandas(semanas[semanaAtual]);

    // ordena enfermeiros por: alocacoesFaltaProMin (acho que as sequenciais não fazem sentido aqui, e sim na escolha dos dias)
    // isso fica numa funcao ordenaVetorEnfermeiros()

    ordenaEnfermeiros();

    // percorre vetor ordenado, e pra cada enfermeiro:

    for (int i = 0; i < enfermeiros.size(); i++)
    {
        cout << endl
             << "Enfermeiro " << enfermeiros[i]->getCodigo() << " demandas: " << endl;
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
                            semanas[semanaAtual].getDemandaMinima(getDiaSemana(dia), tipoTurnos[turno], habilidadesInstancia[hab]),
                            semanas[semanaAtual].getDemandaOtima(getDiaSemana(dia), tipoTurnos[turno], habilidadesInstancia[hab]), 0);
                        candidatos.push_back(move(cand));
                        // setta os booleanos como falso inicialmente, pra serem alterados quando aloca
                        mapBooleans[getDiaSemana(dia)][tipoTurnos[turno]][habilidadesInstancia[hab]] = false;
                    }
                }
            }
        }

        cout << endl
             << endl;

        // função calculaValorCand(Candidato &cand) -> void muda a nota de acordo com o valor
        // calcula a nota pra todos os candidatos
        for (int cand = 0; cand < candidatos.size(); cand++)
        {
            unique_ptr<Candidato> &candPtr = candidatos[cand];
            calculaValorCand(candPtr, enfermeiros[i], mapBooleans[candPtr->getDia()][candPtr->getTurno()][candPtr->getHabilidade()], solucao->getSemanaDemandas());
        }

        // função ordenaVetorCand() ordena com base na nota

        ordenaVetorCand(candidatos);

        // FUNCIONA ATÉ AQUI!

        // para todos os candidatos (ainda dentro do for do enfermeiro!) eu vou usando a func alocaCandidato

        while (!candidatos.empty())
        {
            // aloca primeiro candidato
            alocaCandidato(candidatos[0], enfermeiros[i], solucao->getSemanaDemandas(), *solucao, candidatos, mapBooleans);
            // refaz a nota do resto
            // reordena vetor
            for (int cand = 0; cand < candidatos.size(); cand++)
            {
                unique_ptr<Candidato> &candPtr = candidatos[cand];
                calculaValorCand(candPtr, enfermeiros[i], mapBooleans[candPtr->getDia()][candPtr->getTurno()][candPtr->getHabilidade()], solucao->getSemanaDemandas());
            }
            ordenaVetorCand(candidatos);
        }
    }

    solucao->setViavel(avaliaViabilidade(*solucao));
    solucao->setNota(avaliaNota(*solucao, semanaAtual));
    solucao->exibirAlocacoes();
    buscaLocal(solucao);
    cout << "Pos busca local: " << endl;
    solucao->exibirAlocacoes();
    //      é isso, acho, essa função é rodada pra cada semana
    //      aplicar avaliador de viabilidade e qualidade
}
