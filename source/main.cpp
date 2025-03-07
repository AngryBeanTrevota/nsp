#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../header/Instancia.h"
#include "../header/Enfermeiro.h"
#include "../header/Semana.h"
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> parseStringToVector(const string &input)
{
    vector<int> result;

    // Remove os parênteses da string
    string cleanInput = input.substr(1, input.size() - 2);

    // Usa stringstream para processar os números separados por vírgula
    stringstream ss(cleanInput);
    string value;

    while (getline(ss, value, ','))
    {                                  // Lê até encontrar uma vírgula
        result.push_back(stoi(value)); // Converte cada número para int e adiciona ao vetor
    }

    return result;
}

unique_ptr<Instancia> leitorArquivo(string caminhoArquivo)
{
    string line;
    ifstream myfile(caminhoArquivo);
    if (myfile.is_open())
    {
        unique_ptr<Instancia> instanciaPtr = make_unique<Instancia>();
        while (getline(myfile, line))
        {
            if (line.find("WEEKS") != string::npos)
            {
                size_t pos = line.find('=');
                if (pos != string::npos)
                {
                    string valueStr = line.substr(pos + 2);
                    int weeks = stoi(valueStr);
                    instanciaPtr->setTotalSemanas(weeks);
                }
            }
            if (line.find("SKILLS") != string::npos)
            {
                size_t pos = line.find('=');
                if (pos != string::npos)
                {
                    string valueStr = line.substr(pos + 2);
                    int skills = stoi(valueStr);
                    getline(myfile, line);
                    for (int i = 0; i < skills; i++)
                    {
                        instanciaPtr->adicionarHabilidade(line);
                        getline(myfile, line);
                    }
                }
            }
            if (line.find("SHIFT_TYPES") != string::npos)
            {
                size_t pos = line.find('=');
                if (pos != string::npos)
                {
                    string valueStr = line.substr(pos + 2);
                    int shifts = stoi(valueStr);
                    getline(myfile, line);
                    for (int i = 0; i < shifts; i++)
                    {
                        size_t pos = line.find('(');
                        string palavraAntesParenteses = line.substr(0, pos - 1);
                        instanciaPtr->adicionarTurno(palavraAntesParenteses);
                        getline(myfile, line);
                    }
                }
            }
            if (line.find("FORBIDDEN_SHIFT_TYPES_SUCCESSIONS") != string::npos)
            {
                getline(myfile, line);
                int qtdTurnos = instanciaPtr->getTipoTurnos().size();
                for (int i = 0; i < qtdTurnos; i++)
                {
                    stringstream ss(line);
                    string turno;
                    int qtdValores;

                    ss >> turno >> qtdValores;

                    for (int j = 0; j < qtdValores; ++j)
                    {
                        string valor;
                        ss >> valor;
                        instanciaPtr->configurarSequenciaTurnosImpossivel(turno, valor);
                    }
                    getline(myfile, line);
                }
            }
            if (line.find("CONTRACTS") != string::npos)
            {
                stringstream ss(line);
                string numContratosString;
                ss >> numContratosString; // ignora a palavra CONTRACTS
                ss >> numContratosString; // ignora =
                ss >> numContratosString;
                int numContratos = stoi(numContratosString);
                getline(myfile, line);
                for (int i = 0; i < numContratos; i++)
                {
                    stringstream ss(line);
                    string nomeContrato;
                    string alocacoesTotaisMinMax;
                    string diasTrabConsecutivoMinMax;
                    string diasFolgaConsecutivasMinMax;
                    string maxFdsTraballhados;
                    string precisaFdsCompleto;

                    ss >> nomeContrato >> alocacoesTotaisMinMax >> diasTrabConsecutivoMinMax >> diasFolgaConsecutivasMinMax >> maxFdsTraballhados >> precisaFdsCompleto;
                    vector<int> alocacoesTotaisMinMaxVec = parseStringToVector(alocacoesTotaisMinMax);
                    vector<int> diasTrabConsecutivoMinMaxVec = parseStringToVector(diasTrabConsecutivoMinMax);
                    vector<int> diasFolgaConsecutivasMinMaxVec = parseStringToVector(diasFolgaConsecutivasMinMax);

                    Contrato *contrato = new Contrato(alocacoesTotaisMinMaxVec[0], alocacoesTotaisMinMaxVec[1], diasTrabConsecutivoMinMaxVec[0], diasTrabConsecutivoMinMaxVec[1], diasFolgaConsecutivasMinMaxVec[0], diasFolgaConsecutivasMinMaxVec[1], stoi(maxFdsTraballhados), stoi(precisaFdsCompleto));
                    instanciaPtr->adicionarContrato(nomeContrato, *contrato);
                    getline(myfile, line);
                }
            }
            if (line.find("NURSES") != string::npos)
            {
                stringstream ss(line);
                string numEnfermeirosString;
                ss >> numEnfermeirosString; // ignora a palavra CONTRACTS
                ss >> numEnfermeirosString; // ignora =
                ss >> numEnfermeirosString;
                int numEnfermeiros = stoi(numEnfermeirosString);
                getline(myfile, line);
                for (int i = 0; i < numEnfermeiros; i++)
                {
                    stringstream ss(line);

                    string nomeEnfermeiro;
                    string tipoContrato;
                    string numHabilidades;

                    ss >> nomeEnfermeiro >> tipoContrato >> numHabilidades;

                    vector<string> habilidades;
                    string habilidadeAtual;

                    for (int i = 0; i < stoi(numHabilidades); i++)
                    {
                        ss >> habilidadeAtual;
                        habilidades.push_back(habilidadeAtual);
                    }

                    Contrato contrato = instanciaPtr->getTiposContratos()[tipoContrato];

                    // Enfermeiro* enf = new Enfermeiro(nomeEnfermeiro, contrato, habilidades, 0, 0, "None", 0, 0);
                    shared_ptr<Enfermeiro> enf = make_shared<Enfermeiro>(); // não sei o que tem de errado com o construtor, ver depois

                    enf->setCodigo(nomeEnfermeiro);
                    enf->setContrato(contrato);
                    enf->setHabilidades(habilidades);

                    instanciaPtr->adicionarEnfermeiro(enf);

                    getline(myfile, line);
                }
            }
        }
        return instanciaPtr;
    }
    else
    {
        cout << "Não foi possível abrir o arquivo." << endl;
        return nullptr;
    }
}

unique_ptr<Semana> leArquivoSemana(string caminhoArquivo)
{
    string line;
    ifstream myfile(caminhoArquivo);
    if (myfile.is_open())
    {
        unique_ptr<Semana> semanaPtr = make_unique<Semana>();
        while (getline(myfile, line))
        {
            getline(myfile, line);
            getline(myfile, line);
            getline(myfile, line);
            if (line.find("REQUIREMENTS") != string::npos)
            {
                getline(myfile, line);
                while (!line.empty())
                {
                    stringstream ss(line);
                    string dia;
                    string turno;
                    string habilidade;
                    string minOtimoString;

                    ss >> turno >> habilidade;

                    for (int i = 0; i < 7; i++)
                    {
                        ss >> minOtimoString;
                        switch (i)
                        {
                        case 0:
                            dia = "Mon";
                            break;
                        case 1:
                            dia = "Tue";
                            break;
                        case 2:
                            dia = "Wed";
                            break;
                        case 3:
                            dia = "Thu";
                            break;
                        case 4:
                            dia = "Fri";
                            break;
                        case 5:
                            dia = "Sat";
                            break;
                        case 6:
                            dia = "Sun";
                            break;
                        }
                        vector<int> minOpt = parseStringToVector(minOtimoString);
                        semanaPtr->adicionarDemanda(dia, turno, habilidade, minOpt[0], minOpt[1]);
                    }
                    getline(myfile, line);
                }
            }

            getline(myfile, line);

            if (line.find("SHIFT_OFF_REQUESTS") != string::npos)
            {

                stringstream ss(line);
                string qtdFolgasRequeridas;

                ss >> qtdFolgasRequeridas >> qtdFolgasRequeridas >> qtdFolgasRequeridas;
                getline(myfile, line);

                for (int i = 0; i < stoi(qtdFolgasRequeridas); i++)
                {
                    stringstream ss(line);
                    string enf;
                    string dia;
                    string turno;

                    ss >> enf >> dia >> turno;

                    semanaPtr->adicionarPreferenciaFolga(enf, dia, turno);
                    getline(myfile, line);
                }
            }
            return semanaPtr;
        }
    }
    else
    {
        cout << "Não foi possível abrir o arquivo." << endl;
        return nullptr;
    }
}

unique_ptr<Instancia> leInstanciaSemanasPeloCodigo(string codigo)
{
    string instanciaCaminho = "datasets/" + codigo + "/Sc-" + codigo + ".txt";
    unique_ptr<Instancia> instancia = leitorArquivo(instanciaCaminho);
    int qtdSemanas = instancia->getTotalSemanas();
    {
        for (int i = 0; i < qtdSemanas; i++)
        {
            string semanaCaminho = "datasets/" + codigo + "/WD-" + codigo + "-" + to_string(i) + ".txt";
            unique_ptr<Semana> semana = leArquivoSemana(semanaCaminho);
            instancia->adicionarSemana(*semana);
        }
    }
    return instancia;
}

int main(int argc, char **argv)
{
    string arg1 = "nao foi";
    int iteracao;
    if (argc >= 1)
    {
        arg1 = argv[1];
        iteracao = stoi(argv[2]);
    }

    // seed pra randomizar coisas

    int x = time(0);
    srand(x);

    // unique_ptr<Instancia> instancia = leitorArquivo("testdatasets_txt/n005w4/Sc-n005w4.txt");

    unique_ptr<Instancia> instancia = leInstanciaSemanasPeloCodigo(arg1);
    if (instancia)
    {
        instancia->guloso(2, arg1, iteracao);
    }
    else
    {
        cout << "Falha ao carregar a instância." << endl;
    }

    return 0;
}
