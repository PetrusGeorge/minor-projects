#include <iostream>

#include "../include/CRUD.hpp"
#include <algorithm>

int lerInput(){

    int opcao;
    std::string ler;

    std::cin >> ler;
    std::cin.ignore();
    
    while(!std::all_of(ler.begin(), ler.end(), ::isdigit)){
        
        std::cout << "Input Invalido" << std::endl;
        std::cin >> ler;
        std::cin.ignore();
    };
    
    opcao = std::stoi(ler);
    return opcao;
}

CRUD::CRUD(){

}

void CRUD::menu(){

    int opcao;

    do{

        std::cout << "1 - Cadastrar\n2 - Listar\n3 - Atualizar\n4 - Deletar\n5 - Relatorio\n0 - Sair\n";
        opcao = lerInput() ; 

        switch(opcao){

            case 1:
                system("clear");
                create();
                break;
            case 2:
                system("clear");
                read();
                break;
            case 3:
                system("clear");
                upd();
                break;
            case 4:
                system("clear");
                del();
                break;
            case 5:
                system("clear");
                relatorio();
                std::cout << "Relatorio gerado!";
                std::cin.get();
                system("clear");
                break;
            case 0:
                system("clear");
                sistema.salvarDados();
                break;
            default:
                system("clear");
                std::cout << "Opcao invalida\n";
        }
    }while(opcao != 0);
}

void CRUD::create(){

    int opcao;

    do{

        std::cout << "1 - Cadastrar medico\n2 - Cadastrar paciente\n0 - Voltar\n";
        opcao = lerInput();

        std::string cpfMedico;
        

        switch(opcao){

            case 1:
                system("clear");
                sistema.lerMedicos();
                std::cin.get();
                system("clear");
                break;

            case 2:
                system("clear");
                sistema.lerNovoPaciente();
                std::cout << "Paciente cadastrado com sucesso!" << std::endl;
                std::cin.get();
                system("clear");
                break;

            case 0:
                system("clear");
                break;
            default:
                system("clear");
                std::cout << "Opcao invalida\n";
        }
    }while(opcao != 0);
}

void CRUD::read(){

    int opcao;

    do{

        std::cout << "1 - Listar medicos\n2 - Listar pacientes\n3 - Listar detalhes medicos\n4 - Listar detalhes pacientes\n0 - Voltar\n";
        opcao = lerInput();

        switch(opcao){

            case 1:
                system("clear");
                sistema.listarMedicos();
                std::cin.get();
                system("clear");
                break;

            case 2:
                system("clear");
                sistema.listarPacientes();
                std::cin.get();
                system("clear");
                break;

            case 3:
                system("clear");
                sistema.listarDetalhesMedicos();
                std::cin.get();
                system("clear");
                break;

            case 4:
                system("clear");
                sistema.listarDetalhesPacientes();
                std::cin.get();
                system("clear");
                break;

            case 0:
                system("clear");
                break;
            default:
                system("clear");
                std::cout << "Opcao invalida\n";
        }
    }while(opcao != 0);
}

void CRUD::upd(){

    int opcao;

    do{

        std::cout << "1 - Atualizar medico\n2 - Atualizar paciente\n0 - Voltar\n";
        opcao = lerInput();
        std::string cpf;

        switch(opcao){

            case 1:
                system("clear");
                std::cout << "Digite o CPF atual do medico a ser atualizado: ";
                std::cin >> cpf;
                std::cin.ignore();
                try{
                    sistema.removerMedico(cpf);
                }catch(int e){
                        
                        std::cout << "Medico nao encontrado\n";
                        std::cin.get();
                        system("clear");
                        break;   
                }
                sistema.lerNovoMedico();
                std::cin.get();
                system("clear");
                break;

            case 2:
                system("clear");
                std::cout << "Digite o CPF atual do paciente a ser atualizado: ";
                std::cin >> cpf;
                std::cin.ignore();

                if(sistema.procurarPaciente(cpf) == nullptr){
                    std::cout << "Paciente nao encontrado\n";
                    std::cin.get();
                    system("clear");
                    break;
                }
                
                sistema.lerNovoPaciente();
                std::cin.get();
                system("clear");
                sistema.removerPaciente(cpf);
                break;

            case 0:
                system("clear");
                break;
            default:
                system("clear");
                std::cout << "Opcao invalida\n";
        }
    }while(opcao != 0);
}

void CRUD::del(){

    int opcao;

    do{

        std::cout << "1 - Deletar medico\n2 - Deletar paciente\n0 - Voltar\n";
        opcao = lerInput();
        std::string cpf;

        switch(opcao){

            case 1:
                system("clear");
                std::cout << "Digite o CPF do medico a ser removido: ";
                std::cin >> cpf;
                std::cin.ignore();
                try{
                 
                    sistema.removerMedico(cpf);
                }catch(int e){
                        
                        std::cout << "Medico nao encontrado\n";
                        std::cin.get();
                        break;
                }
                std::cout << "Medico removido com sucesso\n";
                std::cin.get();
                
                break;

            case 2:
                system("clear");
                std::cout << "Digite o CPF do paciente a ser removido: ";
                std::cin >> cpf;
                std::cin.ignore();
                try{
                 
                    sistema.removerPaciente(cpf);
                }catch(int e){
                        
                        std::cout << "Paciente nao encontrado\n";
                        std::cin.get();
                        break;
                }
                std::cout << "Paciente removido com sucesso\n";
                break;

            case 0:
                system("clear");
                break;
            default:
                system("clear");
                std::cout << "Opcao invalida\n";
        }
    }while(opcao != 0);
}

void CRUD::relatorio(){

    sistema.gerarRelatorio();
}