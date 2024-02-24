#include "Medico.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

Paciente* procurarCPF(std::vector<Paciente*> pacientes, std::string cpf) {

    for (auto p : pacientes) {

        if (p->getCPF() == cpf) {

            return p;
        }
    }

    throw 1;
}

Paciente* procurarNome(std::vector<Paciente*> pacientes, std::string nome) {

    for (auto p : pacientes) {

        std::transform(p->getNome().begin(), p->getNome().end(), p->getNome().begin(), ::tolower);

        if (p->getNome() == nome) {

            return p;
        }
    }

    throw 2;
}

Medico::Medico() : Funcionario(){

    funcao = "Medico";
    setCrm("N/A");
    pacientes.clear();
}

Medico::Medico(std::string nome, std::string cpf, std::string endereco, std::string telefone,
double salarioMensal, std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho,
std::vector<Paciente*> pacientes, std::string crm) : Funcionario(nome, cpf, endereco, telefone, salarioMensal, horarioTrabalho) {

    funcao = "Medico";
    setCrm(crm);
    setPacientes(pacientes);
}
/*
Medico::~Medico() {

    for(auto p : pacientes){

        delete p;
    }
}*/

std::string Medico::getCrm() {

    return crm;
}

void Medico::setCrm(std::string crm) {

    this->crm = crm;
}

void Medico::setPacientes(std::vector<Paciente*> pacientes) {

    this->pacientes = pacientes;
}

void Medico::adicionarPaciente(Paciente* paciente) {

    for(auto p : this->pacientes){

        if(p->getCPF() == paciente->getCPF()){
     
            throw 0;
        }
    }
    pacientes.push_back(paciente);
}

std::vector<Paciente*> Medico::getPacientes() {

    return pacientes;
}

Paciente* Medico::getPacienteCPF(std::string cpf) {

    return procurarCPF(pacientes, cpf);
}

Paciente* Medico::getPacienteNome(std::string nome) {

    return procurarNome(pacientes, nome);
}

void Medico::removerPaciente(std::string cpf) {
    
    for (long unsigned i = 0; i < pacientes.size(); i++) {

        if(pacientes[i]->getCPF() == cpf){

            pacientes.erase(pacientes.begin() + i);
            return;
        }
    }

    throw 1;
}

void Medico::printPacientes() {

    for (auto p : pacientes) {

        std::cout << p->getNome() << std::endl;
    }
}

void Medico::printDetalhesPacientes() {

    for (auto p : pacientes) {

        std::cout << p->toString() << std::endl;
    }
}

std::string Medico::toString() {

    std::stringstream stream;
    stream << Funcionario::toString();

    stream << "CRM: " << getCrm() << std::endl;

    stream <<  std::endl << "Pacientes: " << std::endl;
    stream << "Quantidade: " << pacientes.size() << std::endl << std::endl;
    for (auto p : pacientes) {

        stream << p->toString() << std::endl;
    }

    return stream.str();
}

std::string Medico::toArquivo() {

    std::stringstream stream;
    stream << Funcionario::toArquivo();

    stream << getCrm() << std::endl;

    for (auto p : pacientes) {

        stream << p->toArquivo() << std::endl;
    }

    stream << "fim";

    return stream.str();
}

void Medico::lerAtributos() {

    char confirmou = 'n';

    while(confirmou == 'n'){

        std::cout << "Preencha os dados do medico: " << std::endl;
        Funcionario::lerAtributos();

        lerCRM();
        lerPacientes();

        std::cout << std::endl << toString() << std::endl;

        do{
     
            std::cout << "Confirmar cadastro? (s/n): ";
            std::cin >> confirmou;
            confirmou = std::tolower(confirmou);
        }while(confirmou != 's' && confirmou != 'n');
    }
}

void Medico::lerCRM() {


    std::cout << "CRM: ";
    std::cin >> this->crm;
    std::cin.ignore();
}

void Medico::lerPacientes() {

    char confirmou;
    std::cout << "Adicionar pacientes? (s/n): ";
    std::cin >> confirmou;
    confirmou = std::tolower(confirmou);

    while(confirmou != 's' and confirmou != 'n'){
        
        std::cout << "Opção inválida! Digite novamente: " << std::endl;
        std::cin >> confirmou;
        std::cin.ignore();
        confirmou = std::tolower(confirmou);
    }

    std::cin.ignore();

    while(confirmou == 's'){

        std::cout << "Pacientes" << std::endl;

        try{

            adicionarPaciente(ler1Paciente());
        }
        catch(int e){

            std::cout << "Paciente já cadastrado" << std::endl;
        }

        std::cout << "Adicionar mais pacientes? (s/n): ";
        std::cin >> confirmou;
        confirmou = std::tolower(confirmou);
        std::cin.ignore();

        while(confirmou != 's' and confirmou != 'n'){
            
            std::cout << "Opção inválida! Digite novamente: " << std::endl;
            std::cin >> confirmou;
            std::cin.ignore();
            confirmou = std::tolower(confirmou);
        }
    }
}

Paciente* Medico::ler1Paciente() {

    Paciente* paciente = new Paciente();

    paciente->lerAtributos();

    return paciente;
}