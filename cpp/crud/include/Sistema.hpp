#pragma once

#include "Medico.hpp"
#include "Paciente.hpp"
#include <vector>

class Sistema{

   std::vector<Medico*> medicos;

    public:
        Sistema();
        //virtual ~Sistema();

        std::vector<Medico*> getMedicos();

        void setMedicos(std::vector<Medico*> medicos);

        void cadastrarMedico(Medico* medico);
        void cadastrarPaciente(Paciente* paciente, std::string cpfMedico);

        void removerMedico(std::string cpf);
        void removerPaciente(std::string cpf);

        Medico* procurarMedico(std::string cpf);
        Paciente* procurarPaciente(std::string cpf);

        void listarMedicos();
        void listarPacientes();

        void listarDetalhesMedicos();
        void listarDetalhesPacientes();

        void lerMedicos();
        void lerNovoMedico();
        void lerNovoPaciente();

        void salvarDados();
        double calcularFolhaPagamento();
        void gerarRelatorio();
        void lerDados();
};