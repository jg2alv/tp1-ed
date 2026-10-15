#ifndef UTILS_HPP
#define UTILS_HPP

// Funcao que recebe referencia do arquivo e le n linhas do objeto recebido
// salva os dados lidos no objeto pessoas
void leArquivo(std::ifstream &arquivo, int n, Pessoa *pessoas);

// Funcoes de ordenacao implementadas:
//  1. quicksort com mediana de 3 e insercao
//  2. mergesort
//  3. insertionsort
// As 3 funcoes podem ser usadas para ordenar quaisquer dos 3 atributos
void quicksort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo);
void mergesort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo);
void insertionsort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo);

// Funcao que chama um dos tres metodos de ordenacao e executa o loop de impressao
// das informacoes
void chamaSort(void (*sort)(int, int, Pessoa**, std::string Pessoa::*), int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo, std::string header, int n, bool newline=true);

// Desaloca a memoria alocada dinamicamente
void limpaMemoria(Pessoa* pessoas, Pessoa** names, Pessoa** ids, Pessoa** adresses);

#endif