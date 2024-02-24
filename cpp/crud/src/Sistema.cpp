#include "../include/Sistema.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

Sistema::Sistema(){

    lerDados();
}
/*
Sistema::~Sistema(){
    
    for(int i = 0; i < medicos.size(); i++){

        delete medicos[i];
    }
}*/

std::vector<Medico*> Sistema::getMedicos(){
 
    return medicos;
}

void Sistema::setMedicos(std::vector<Medico*> medicos){

    this->medicos = medicos;
}

void Sistema::cadastrarMedico(Medico* medico){

    if(procurarMedico(medico->getCPF()) != nullptr){

        std::cout << "Medico já cadastrado!" << std::endl;
        return;
    }

    medicos.push_back(medico);
}

void Sistema::cadastrarPaciente(Paciente* paciente, std::string cpfMedico){

    Medico* ptr = procurarMedico(cpfMedico);

    if(ptr == nullptr){

        std::cout << "Medico não encontrado!" << std::endl;
        return;
    }

    if(procurarPaciente(paciente->getCPF()) != nullptr){

        std::cout << "Paciente já cadastrado!" << std::endl;
        return;
    }

    ptr->adicionarPaciente(paciente);
}

void Sistema::removerMedico(std::string cpf){

    Medico* ptr = procurarMedico(cpf);

    if(ptr == nullptr){

        throw 0;
        return;
    }

    else{

        delete ptr;
        medicos.erase(std::find(medicos.begin(), medicos.end(), ptr));
    }
}

void Sistema::removerPaciente(std::string cpf){

    Paciente* ptr = procurarPaciente(cpf);

    if(ptr == nullptr){

        throw 0;
    }

    else{

        delete ptr;
        
        for(auto m : medicos){

            m->removerPaciente(cpf);
        }
    }
}

Medico* Sistema::procurarMedico(std::string cpf){

    for(auto m : medicos){

        if(m->getCPF() == cpf){

            return m;
        }
    }

    return nullptr;
}

Paciente* Sistema::procurarPaciente(std::string cpf){

    for(auto m : medicos){

        for(auto p : m->getPacientes()){
            
            if(p->getCPF() == cpf){

                return p;
            }
        }
    }

    return nullptr;
}

void Sistema::listarMedicos(){

    for(auto m : medicos){

        std::cout << m->getNome() << std::endl;
    }
}

void Sistema::listarPacientes(){

    for(auto m : medicos){

        for(auto p : m->getPacientes()){

            std::cout << p->getNome() << std::endl;
        }
    }
}

void Sistema::listarDetalhesMedicos(){

    for(auto m : medicos){

        std::cout << m->toString() << std::endl;
    }
}

void Sistema::listarDetalhesPacientes(){

    for(auto m : medicos){

        for(auto p : m->getPacientes()){

            std::cout << p->toString() << std::endl;
        }
    }
}

void Sistema::lerMedicos(){

    char confirmar;

    do{
        Medico* medico = new Medico();
        medico->lerAtributos();
        cadastrarMedico(medico);

        std::cout << "Deseja cadastrar outro medico? (s/n): " ;
        std::cin >> confirmar;
        std::cin.ignore();
        confirmar = tolower(confirmar);

    }while(confirmar == 's');

    std::cout << "Medicos cadastrados com sucesso" << std::endl;
}

void Sistema::lerDados(){

    std::ifstream arquivo("data/dados.crud");

    if(!arquivo.is_open()){

        std::ofstream("data/dados.crud");
        return;
    }

    std::string linha;

    while(std::getline(arquivo, linha)){

        Medico* medico = new Medico();

        medico->setNome(linha);

        getline(arquivo, linha);
        medico->setCPF(linha);
        
        getline(arquivo, linha);
        medico->setEndereco(linha);
        
        getline(arquivo, linha);
        medico->setTelefone(linha);
        
        getline(arquivo, linha);
        medico->setSalarioMensal(stod(linha));

        while(true){
        
            std::vector<std::pair<int, std::pair<int, int>>> horario;
            int diaDaSemana;
            int horaInicio;
            int horaFim;

            getline(arquivo, linha);
            if(linha == "fimHorario"){

                break;
            }
            diaDaSemana = stoi(linha);
            
            getline(arquivo, linha);
            horaInicio = std::stoi(linha);
            
            getline(arquivo, linha);
            horaFim = std::stoi(linha);

            horario.push_back(std::make_pair(diaDaSemana, std::make_pair(horaInicio, horaFim)));
            medico->setHorariotrabalho(horario);
        }

        getline(arquivo, linha);
        medico->setCrm(linha);

        medico->calcularHorasSemanais();

        while(true){

            Paciente* paciente = new Paciente();

            getline(arquivo, linha);   
            if(linha == "fim"){

                break;
            }
            paciente->setNome(linha);

            getline(arquivo, linha);
            paciente->setCPF(linha);

            getline(arquivo, linha);
            paciente->setEndereco(linha);

            getline(arquivo, linha);
            paciente->setTelefone(linha);

            getline(arquivo, linha);
            paciente->setConvenio(linha);

            getline(arquivo, linha);
            paciente->setTipoSanguineo(linha);

            getline(arquivo, linha);
            paciente->setFatorRH(linha);

            while(true){
                getline(arquivo, linha);
                
                if(linha == "fimAlergia"){
                
                    break;
                }
                
                paciente->adicionarAlergia(linha);
            }

            medico->adicionarPaciente(paciente);
        }

        cadastrarMedico(medico);
    }

    arquivo.close();
}

void Sistema::salvarDados(){

    std::fstream arquivo;
    arquivo.open("data/dados.crud", std::ios::out | std::ios::trunc);

    for(auto m : medicos){

        arquivo << m->toArquivo() << std::endl;
    }

    arquivo.close();
}

void Sistema::lerNovoMedico(){

    Medico* medico = new Medico();
    medico->lerAtributos();
    cadastrarMedico(medico);
    std::cout << "Medico cadastrado com sucesso!" << std::endl;
}

void Sistema::lerNovoPaciente(){

    std::string cpf;

    Paciente* paciente = new Paciente();
    paciente->lerAtributos();
    std::cout << "Digite o CPF do medico responsavel: ";
    std::cin >> cpf;
    std::cin.ignore();
    cadastrarPaciente(paciente, cpf);
}

double Sistema::calcularFolhaPagamento(){

    double total = 0;

    for(auto m : medicos){

        total += m->getSalarioMensal();
    }

    return total;
}

void Sistema::gerarRelatorio(){

    std::fstream arquivo("data/relatorio.txt", std::ios::out | std::ios::trunc);

    arquivo << "Medicos: " << std::endl;
    arquivo << "Quantidade = " << medicos.size() << std::endl << std::endl;

    for(auto m : medicos){

        arquivo << m->toString() << std::endl;
    }
    arquivo << "Folha de pagamento: " << calcularFolhaPagamento() << std::endl;
}