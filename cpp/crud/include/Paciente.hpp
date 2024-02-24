#pragma once
#include "Pessoa.hpp"
#include <vector>

class Paciente : public Pessoa{

    std::string convenio;
    std::string tipoSanguineo;
    std::string fatorRH;
    std::vector<std::string> alergias;

    public:
        Paciente();
        Paciente(std::string nome, std::string cpf, std::string endereco,
        std::string telefone, std::string convenio, std::string tipoSanguineo,
        std::string fatorRH, std::vector<std::string> alergias);
        virtual ~Paciente();

        std::string getConvenio();
        std::string getTipoSanguineo();
        std::string getFatorRH();
        std::vector<std::string> getAlergias();
        bool possuiAlergia(std::string alergia);
        void setConvenio(std::string convenio);
        void setTipoSanguineo(std::string tipoSanguineo);
        void setFatorRH(std::string fatorRH);
        void setAlergias(std::vector<std::string> alergias);
        void adicionarAlergia(std::string alergia);

        void lerAtributos();
        std::string toString();
        std::string toArquivo();

};