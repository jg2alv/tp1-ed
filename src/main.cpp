#include <iostream>
#include <fstream>

#include "Pessoa.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    // Abertura do arquivo
    // Estrategia de robustez: verificar erro na abertura
    std::ifstream arquivo;
    try {
        arquivo.open(argv[1]);
        if(!arquivo.good())
            throw std::runtime_error("erro na abertura do arquivo xcsv");
    } catch(std::exception& exc) {
        std::cout << exc.what() << std::endl;
        arquivo.close();
        return 1;
    }

    // Lendo o cabecalho do arquivo
    std::string header;
    header.resize(34, ' ');
    arquivo.read(&*header.begin(), 34);

    // Lendo o numero de pessoas do arquivo
    int n; arquivo >> n;
    Pessoa* pessoas, **adresses, **ids, **names;
    
    // Estrategia de robustez: verifica se ha memoria disponivel para ser alocada
    try {
        pessoas = new Pessoa[n];
        adresses = new Pessoa*[n];
        ids = new Pessoa*[n];
        names = new Pessoa*[n];
    } catch(std::bad_alloc& exc) {
        std::cout << exc.what() << std::endl;
        return 1;
    }

    // Tenta ler o arquivo.
    // Caso qualquer excessao ocorra, interrompe a execucao da funcao
    // Ignorando o \n extra que ficou no arquivo
    try {
        arquivo.ignore();
        leArquivo(arquivo, n, pessoas);
    } catch(std::exception& exc) {
        std::cout << exc.what() << std::endl;
        limpaMemoria(pessoas, names, ids, adresses);
        arquivo.close();
        return 1;
    }
    
    // Atribuicao dos vetores de apontadores
    for(int i = 0; i < n; i++) {
        adresses[i] = &pessoas[i];
        ids[i] = &pessoas[i];
        names[i] = &pessoas[i];
    }

    // Uso da funcao chamaSort para ordenar o vetor de nomes, ids e enderecos
    // usando o insertionsort passando os parametros necessarios
    chamaSort(insertionsort, 0, n-1, names, &Pessoa::name, header, n);
    chamaSort(insertionsort, 0, n-1, ids, &Pessoa::id, header, n);
    chamaSort(insertionsort, 0, n-1, adresses, &Pessoa::adress, header, n);

    // Uso da funcao chamaSort para ordenar o vetor de nomes, ids e enderecos
    // usando o mergesort passando os parametros necessarios
    chamaSort(mergesort, 0, n-1, names, &Pessoa::name, header, n);
    chamaSort(mergesort, 0, n-1, ids, &Pessoa::id, header, n);
    chamaSort(mergesort, 0, n-1, adresses, &Pessoa::adress, header, n);

    // Uso da funcao chamaSort para ordenar o vetor de nomes, ids e enderecos
    // usando o quicksort passando os parametros necessarios
    chamaSort(quicksort, 0, n-1, names, &Pessoa::name, header, n);
    chamaSort(quicksort, 0, n-1, ids, &Pessoa::id, header, n);
    chamaSort(quicksort, 0, n-1, adresses, &Pessoa::adress, header, n, false);

    // Desalocacao das variaveis utilizadas e fechamento do arquivo
    limpaMemoria(pessoas, names, ids, adresses);
    arquivo.close();
}