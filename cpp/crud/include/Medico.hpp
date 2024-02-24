#pragma once
#include "Funcionario.hpp"
#include "Paciente.hpp"

class Medico : public Funcionario {

    std::string crm;
    std::vector<Paciente*> pacientes;

    public:
        Medico();
        Medico(std::string nome, std::string cpf, std::string endereco, std::string telefone,
        double salarioMensal, std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho,
        std::vector<Paciente*> pacientes, std::string crm);
        //virtual ~Medico();

        std::string getCrm();
        void setCrm(std::string crm);

        void setPacientes(std::vector<Paciente*> pacientes);
        void adicionarPaciente(Paciente* paciente);
        std::vector<Paciente*> getPacientes();
        Paciente* getPacienteCPF(std::string cpf);
        Paciente* getPacienteNome(std::string nome);

        void removerPaciente(std::string cpf);

        void printPacientes();
        void printDetalhesPacientes();

        std::string toString();
        std::string toArquivo();
        void lerAtributos();

        void lerCRM();
        void lerPacientes();
        Paciente* ler1Paciente();

};