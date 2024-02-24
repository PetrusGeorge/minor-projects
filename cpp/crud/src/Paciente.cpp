#include "../include/Paciente.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

Paciente::Paciente() : Pessoa(){

    setConvenio("N/A");
    setTipoSanguineo("N/A");
    setFatorRH("N/A");
    setAlergias(std::vector<std::string>());
}

Paciente::Paciente(std::string nome, std::string cpf, std::string endereco,
std::string telefone, std::string convenio, std::string tipoSanguineo,
std::string fatorRH, std::vector<std::string> alergias) : Pessoa(nome, cpf, endereco, telefone){

    setConvenio(convenio);
    setTipoSanguineo(tipoSanguineo);
    setFatorRH(fatorRH);
    setAlergias(alergias);
}

Paciente::~Paciente(){

}

std::string Paciente::getConvenio(){
 
    return convenio;
}

std::string Paciente::getTipoSanguineo(){
 
    return tipoSanguineo;
}

std::string Paciente::getFatorRH(){
 
    return fatorRH;
}

std::vector<std::string> Paciente::getAlergias(){
 
    return alergias;
}

bool Paciente::possuiAlergia(std::string alergia){
 
    for(auto a : alergias){

        if(a == alergia){

            return true;
        }
    }

    return false;
}

void Paciente::setConvenio(std::string convenio){
 
    this->convenio = convenio;
}

void Paciente::setTipoSanguineo(std::string tipoSanguineo){
 
    this->tipoSanguineo = tipoSanguineo;
}

void Paciente::setFatorRH(std::string fatorRH){
 
    this->fatorRH = fatorRH;
}

void Paciente::setAlergias(std::vector<std::string> alergias){
 
    this->alergias = alergias;
}

void Paciente::adicionarAlergia(std::string alergia){
 
    this->alergias.push_back(alergia);
}

std::string Paciente::toString(){

    std::stringstream stream;

    std::string alergias = "";

    for(auto a : this->alergias){

        alergias += a + " ";

        if((std::count(alergias.begin(), alergias.end(), ' ') + 1) % 5 == 0){

            alergias += "\n";
        }
    }

    stream << Pessoa::toString();
    stream << "Convenio: " << getConvenio() << std::endl;
    stream << "Tipo Sanguineo: " << getTipoSanguineo() << getFatorRH() << std::endl;
    stream << "Alergias: " << alergias << std::endl;    

    return stream.str();
}

std::string Paciente::toArquivo(){

    std::stringstream stream;


    stream << Pessoa::toArquivo();
    stream << getConvenio() << std::endl;
    stream << getTipoSanguineo() << std::endl;
    stream << getFatorRH() << std::endl;

    for(auto a : getAlergias()){

        stream << a << std::endl;
    }

    stream << "fimAlergia";
    
    return stream.str();
}

void Paciente::lerAtributos(){

    char confirmou = 'n';

    while(confirmou == 'n'){

        std::cout << "Preencha os dados do paciente: " << std::endl;
        Pessoa::lerAtributos();

        std::cout << "Convenio: ";
        getline(std::cin, this->convenio);

        std::cout << "Tipo Sanguineo: (A, B, AB, O): ";
        std::cin >> this->tipoSanguineo;
        std::transform(this->tipoSanguineo.begin(), this->tipoSanguineo.end(), this->tipoSanguineo.begin(), ::toupper);
        
        while(this->tipoSanguineo != "A" and this->tipoSanguineo != "B" and this->tipoSanguineo != "AB" and this->tipoSanguineo != "O"){

            std::cout << "Tipo sanguineo invalido! Digite novamente: ";
            std::cin >> this->tipoSanguineo;
            std::transform(this->tipoSanguineo.begin(), this->tipoSanguineo.end(), this->tipoSanguineo.begin(), ::toupper);
        }

        std::cout << "Fator RH: (+/-))";
        std::cin >> this->fatorRH;

        while(this->fatorRH != "-" and this->fatorRH != "+"){

            std::cout << "Fator RH invalido! Digite novamente: " << std::endl;
            std::cin >> this->fatorRH;
        }

        std::string alergia;
        std::cout << "Alergias (digite 'fim' para parar): ";
        std::cin >> alergia;

        while (alergia != "fim"){

            alergias.push_back(alergia);
            std::cin >> alergia;
        }

        std::cout << std::endl << toString() << std::endl;

        std::cout << "Os dados acima estão corretos? (s/n): ";
        std::cin >> confirmou;
        confirmou = tolower(confirmou);

        while(confirmou != 'n' and confirmou != 's'){

            std::cout << "Opcao invalida! Digite novamente: ";
            std::cin >> confirmou;
            confirmou = tolower(confirmou);
        }
    }
}