#include "../include/Funcionario.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

enum{DOMINGO = 1, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO};

static int retornaDiaDaSemanaINT(std::string diaSemana){

    std::transform(diaSemana.begin(), diaSemana.end(), diaSemana.begin(), ::tolower);

    if(diaSemana == "segunda"){

        return SEGUNDA;
    }

    if(diaSemana == "terca" or diaSemana == "terça"){

        return TERCA;
    }

    if(diaSemana == "quarta"){

        return QUARTA;
    }

    if(diaSemana == "quinta"){

        return QUINTA;
    }

    if(diaSemana == "sexta"){

        return SEXTA;
    }

    if(diaSemana == "sabado" or diaSemana == "sábado"){

        return SABADO;
    }

    if(diaSemana == "domingo"){

        return DOMINGO;
    }

    return -1;
}

std::string retornaDiaDaSemanaSTR(int diaSemana){

    switch(diaSemana){

        case DOMINGO:
            return "domingo";
            break;

        case SEGUNDA:
            return "segunda";
            break;

        case TERCA:
            return "terça";
            break;

        case QUARTA:
            return "quarta";
            break;

        case QUINTA:
            return "quinta";
            break;

        case SEXTA:
            return "sexta";
            break;

        case SABADO:
            return "sábado";
            break;

        default:
            return "Dia da semana inválido!";
            break;
    }
}

void ordenaHorario(std::vector<std::pair<int, std::pair<int, int>>>& horario){

    for(long unsigned i = 0; i < horario.size() - 1; i++){

        for(long unsigned j = i + 1; j < horario.size(); j++){

            if(horario[i].first > horario[j].first){

                std::swap(horario[i], horario[j]);
            }
        }
    }
}

Funcionario::Funcionario() : Pessoa(){

    setSalarioMensal(0);
    this->horarioTrabalho.clear();
    this->horasSemanais = 0;
}

Funcionario::Funcionario(std::string nome, std::string cpf, std::string endereco,
std::string telefone, double salarioMensal, std::vector<std::pair<int, std::pair<int, int>>> horarioTrabalho) : Pessoa(nome, cpf, endereco, telefone){

    setHorariotrabalho(horarioTrabalho);
    calcularHorasSemanais();
    setSalarioMensal(salarioMensal);
}

std::string Funcionario::getFuncao(){
 
    return funcao;
}

double Funcionario::getSalarioMensal(){
 
    return salarioMensal;
}

void Funcionario::setSalarioMensal(double salarioMensal){
 
    this->salarioMensal = salarioMensal;
}

void Funcionario::setHorariotrabalho(std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho){
 
    ordenaHorario(horarioTrabalho);
    this->horarioTrabalho = horarioTrabalho;
}

void Funcionario::calcularHorasSemanais(){

    horasSemanais = 0;

    for(auto horario : horarioTrabalho){

        horasSemanais += horario.second.second - horario.second.first;
    }
}

std::string Funcionario::toString(){

    std::stringstream stream;
    
    stream << Pessoa::toString();
    stream << "Função: " << getFuncao() << std::endl;
    stream << "Salário Mensal: " << std::setprecision(2) <<std::fixed << getSalarioMensal() << std::endl;
    stream << "Horário de Trabalho: " << std::endl;
    
    for(auto horario : horarioTrabalho){
    
        stream << '\t' << "Dia da Semana: " << retornaDiaDaSemanaSTR(horario.first) << std::endl;
        stream << "\t\t"<< "Hora de Início: " << horario.second.first << std::endl;
        stream << "\t\t" << "Hora de Término: " << horario.second.second << std::endl;
    }

    stream << "Horas Semanais: " << horasSemanais << std::endl;

    return stream.str();
}

std::string Funcionario::toArquivo(){

    std::stringstream stream;
    
    stream << Pessoa::toArquivo();
    //stream << getFuncao() << std::endl;
    stream << std::fixed << std::setprecision(2) << getSalarioMensal() << std::endl;
    
    for(auto horario : horarioTrabalho){
    
        stream << horario.first << std::endl;
        stream << horario.second.first << std::endl;
        stream << horario.second.second << std::endl;
    }

    stream << "fimHorario" << std::endl;

    return stream.str();
}

void Funcionario::lerSalarioMensal(){

    std::string safe;
    std::cout << "Digite o salário mensal do funcionário: ";
    std::cin >> safe;

    while(!std::all_of(safe.begin(), safe.end(), ::isdigit)){

        std::cout << "Salário mensal inválido! Digite novamente: ";
        std::cin >> safe;
    }

    this->salarioMensal = std::stod(safe);

    while(salarioMensal < 1320){

        std::cout << "Salário mensal inválido! Digite novamente: ";
        std::cin >> this->salarioMensal;
    }
}

void Funcionario::lerHorarioTrabalho(){

    char continuar = 's';

    std::cout << "Digite os horários de trabalho do funcionário: " << std::endl;

    while(continuar == 's'){

        bool falhou = false;

        std::pair<int, std::pair<int, int>> check = ler1HorarioTrabalho();

        for(auto horario : this->horarioTrabalho){

            if(horario.first == check.first){

                std::cout << "Dia da semana já cadastrado!" << std::endl;
                falhou = true;
            }
        }

        if(!falhou){
            this->horarioTrabalho.push_back(check);
            falhou = false;
        }

        std::cout << "Deseja adicionar mais um horário de trabalho? (s/n): ";
        std::cin >> continuar;

        while(continuar != 's' and continuar != 'n'){

            std::cout << "Opção inválida! Digite novamente: ";
            std::cin >> continuar;
        }
    }

    ordenaHorario(horarioTrabalho);
    calcularHorasSemanais();
}

std::pair<int, std::pair<int, int>> Funcionario::ler1HorarioTrabalho(){

    std::string diaSemanaSTR;
    std::string safeRead;
    int diaSemana;
    int horaInicio;
    int horaTermino;

    std::cout << "Digite o dia da semana: ";
    std::cin >> diaSemanaSTR;
    
    diaSemana = retornaDiaDaSemanaINT(diaSemanaSTR);

    while(diaSemana == -1){

        std::cout << "Dia da semana inválido! Digite novamente: ";
        std::cin >> diaSemanaSTR;

        diaSemana = retornaDiaDaSemanaINT(diaSemanaSTR);
    }

    std::cout << "Digite a hora de início: ";
    std::cin >> safeRead;

    while(true){

        while(!std::all_of(safeRead.begin(), safeRead.end(), ::isdigit)){
         
            std::cout << "Hora de início inválida! Digite novamente: ";
            std::cin >> safeRead;
        }

        if(std::stoi(safeRead) >= 0 and std::stoi(safeRead) < 23){

            break;
        }
        safeRead = "a";
    }

    horaInicio =  std::stoi(safeRead);

    std::cout << "Digite a hora de término: ";
    std::cin >> safeRead;
    
    while(true){

        while(!std::all_of(safeRead.begin(), safeRead.end(), ::isdigit)){
         
            std::cout << "Hora de início inválida! Digite novamente: ";
            std::cin >> safeRead;
        }

        if(std::stoi(safeRead) >= horaInicio and std::stoi(safeRead) <= 23){

            break;
        }
        safeRead = "a";
    }

    horaTermino =  std::stoi(safeRead);

    return std::make_pair(diaSemana, std::make_pair(horaInicio, horaTermino));
}

void Funcionario::lerAtributos(){

    Pessoa::lerAtributos();

    lerSalarioMensal();
    lerHorarioTrabalho();
}



