#pragma once

#include <string>

class Pessoa{

    protected:
        std::string nome;
        std::string cpf;
        std::string endereco;
        std::string telefone;

    public:
        Pessoa();
        Pessoa(std::string nome, std::string cpf, std::string endereco, std::string telefone);

        std::string getNome();
        std::string getCPF();
        std::string getEndereco();
        std::string getTelefone();
        void setNome(std::string nome);
        void setCPF(std::string cpf);
        void setEndereco(std::string endereco);
        void setTelefone(std::string telefone);

        virtual std::string toString();
        virtual std::string toArquivo();
        
        void lerNome();
        void lerCPF();
        void lerEndereco();
        void lerTelefone();

        virtual void lerAtributos();
};