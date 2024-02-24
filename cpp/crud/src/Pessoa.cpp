#include "../include/Pessoa.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

Pessoa::Pessoa(){

    setNome("N/A");
    setCPF("N/A");
    setEndereco("N/A");
    setTelefone("N/A");
}

Pessoa::Pessoa(std::string nome, std::string cpf, std::string endereco, std::string telefone){

    setNome(nome);
    setCPF(cpf);
    setEndereco(endereco);
    setTelefone(telefone);
}

std::string Pessoa::getNome(){

    return nome;
}

std::string Pessoa::getCPF(){

    return cpf;
}

std::string Pessoa::getEndereco(){

    return endereco;
}

std::string Pessoa::getTelefone(){

    return telefone;
}

void Pessoa::setNome(std::string nome){

    this->nome = nome;
}

void Pessoa::setCPF(std::string cpf){

    this->cpf = cpf;
}

void Pessoa::setEndereco(std::string endereco){

    this->endereco = endereco;
}

void Pessoa::setTelefone(std::string telefone){

    this->telefone = telefone;
}

std::string Pessoa::toString(){

    std::stringstream stream;
    stream << "Nome: " << getNome() << std::endl;
    stream << "CPF: " << getCPF() << std::endl;
    stream << "Endereco: " << getEndereco() << std::endl;
    stream << "Telefone: " << getTelefone() << std::endl;

    return stream.str();
}

std::string Pessoa::toArquivo(){

    std::stringstream stream;
    stream << getNome() << std::endl;
    stream << getCPF() << std::endl;
    stream << getEndereco() << std::endl;
    stream << getTelefone() << std::endl;

    return stream.str();
}

void Pessoa::lerNome(){

    std::cout << "Digite o nome da pessoa: ";
    getline(std::cin, this->nome);
}

void Pessoa::lerCPF(){

    std::cout << "Digite o CPF da pessoa (apenas numeros): ";
    std::cin >> cpf;
    
    while(cpf.size() != 11 || !std::all_of(cpf.begin(), cpf.end(), ::isdigit)){
     
        std::cout << "cpf nao valido, digite novamente: ";
        std::cin >> this->cpf;
    }
    std::cin.ignore();
}

void Pessoa::lerEndereco(){

    std::cout << "Digite o endereco da pessoa: ";
    getline(std::cin, this->endereco);
}

void Pessoa::lerTelefone(){

    std::cout << "Digite o telefone da pessoa (apenas numeros, e com DDD): ";
    std::cin >> telefone;

    while(telefone.size() != 11 || !std::all_of(telefone.begin(), telefone.end(), ::isdigit)){
     
        std::cout << "Numero nao valido, digite novamente: ";
        std::cin >> this->telefone;
    }
    std::cin.ignore();
}

void Pessoa::lerAtributos(){

    lerNome();
    lerCPF();
    lerEndereco();
    lerTelefone();   
}