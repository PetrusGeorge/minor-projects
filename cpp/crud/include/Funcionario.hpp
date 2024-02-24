#pragma once
#include <utility>
#include <vector>

#include "Pessoa.hpp"

class Funcionario : public Pessoa{

    protected:
        std::string funcao;
        double salarioMensal;
        std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho;
        int horasSemanais;

    public:
        Funcionario();
        Funcionario(std::string nome, std::string cpf, std::string endereco, std::string telefone,
        double salarioMensal, std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho);
        
        std::string getFuncao();
        double getSalarioMensal();
        void setSalarioMensal(double salarioMensal);
        void setHorariotrabalho(std::vector<std::pair<int,std::pair<int,int>>> horarioTrabalho);
        
        void calcularHorasSemanais();
        virtual std::string toString();
        virtual std::string toArquivo();

        void lerSalarioMensal();
        void lerHorarioTrabalho();
        std::pair<int, std::pair<int,int>> ler1HorarioTrabalho();
        virtual void lerAtributos();
};