#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Pessoa.hpp"
#include "utils.hpp"

// Funcao de leitura do arquivo xcsv
// Para cada linha do arquivo (paramentro inteiro n),
//  1. le a linha correspondente
//  2. faz o tratamento das informacoes lidas, separando por virgula
//  3. estrategia de robustez: verifica se alguma das informacoes eh um campo vazio
//      o que indicaria algum tipo de erro
//  4. salva as informacoes no objeto pessoas recebido
void leArquivo(std::ifstream &arquivo, int n, Pessoa *pessoas)
{
    for (int i = 0; i < n; i++)
    {
        std::string id, name, adress, payload;
        std::getline(arquivo, name, ',');
        std::getline(arquivo, id, ',');
        std::getline(arquivo, adress, ',');
        std::getline(arquivo, payload);

        bool idvazio = id.length() == 0;
        bool namevazio = name.length() == 0;
        bool adressvazio = adress.length() == 0;
        bool payloadvazio = payload.length() == 0;

        if(idvazio || namevazio || adressvazio || payloadvazio)
            throw std::runtime_error("id, name, adress ou payload vazio");
 
        pessoas[i].id = id;
        pessoas[i].name = name;
        pessoas[i].adress = adress;
        pessoas[i].payload = payload;
    }
}

// Primeira funcao de ordenacao: quicksort com mediana de 3 e insercao
// Ordena os ponteiros de ponteiros de pessoa com base no `campo` recebido
// `campo` assume os valores id, name ou adress
// Realiza a insercao com subvetores de tamanho menor ou igual a 50 elementos
void quicksort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo)
{
    auto median = [campo](Pessoa* x, Pessoa* y, Pessoa* z) {
        std::string a = x->*campo, b = y->*campo, c = z->*campo;
        if ((a <= b) && (b <= c)) return x;
        if ((a <= c) && (c <= b)) return z;
        if ((b <= a) && (a <= c)) return x;
        if ((b <= c) && (c <= a)) return z;
        if ((c <= a) && (a <= b)) return x;
        return y;
    };

    Pessoa* x, *w;
    int i = Esq, j = Dir, mid = (i+j)/2;
    x = median(array[i], array[j], array[mid]);
    do
    {
        while (x->*campo > array[i]->*campo) i++;
        while (x->*campo < array[j]->*campo) j--;
        if (i <= j)
        {
            w = array[i];
            array[i] = array[j];
            array[j] = w;
            i++;
            j--;
        }
    } while (i <= j);

    if(Esq < j) {
        if((j - Esq) <= 50) insertionsort(Esq, j, array, campo);
        else quicksort(Esq, j, array, campo);
    }
    
    if(i < Dir) {
        if((Dir - i) <= 50) insertionsort(i, Dir, array, campo);
        else quicksort(i, Dir, array, campo);
    }
}

// Segunda funcao de ordenacao: mergesort
// Ordena os ponteiros de ponteiros de pessoa com base no `campo` recebido
// `campo` assume os valores id, name ou adress
void mergesort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo)
{
    if (Esq >= Dir) return;

    int mid = Esq + (Dir - Esq) / 2;
    mergesort(Esq, mid, array, campo);
    mergesort(mid + 1, Dir, array, campo);
    int n1 = mid - Esq + 1;
    int n2 = Dir - mid;

    Pessoa** L = new Pessoa*[n1];
    Pessoa** R = new Pessoa*[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[Esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0;
    int k = Esq;

    while (i < n1 && j < n2)
    {
        if (L[i]->*campo <= R[j]->*campo)
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Terceira funcao de ordenacao: insertionsort
// Ordena os ponteiros de ponteiros de pessoa com base no `campo` recebido
// `campo` assume os valores id, name ou adress
void insertionsort(int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo)
{
    int j, n = Dir+1;
    Pessoa* aux;
    for (int i = Esq+1; i < n; i++)
    {
        aux = array[i];
        j = i - 1;
        while ((j >= 0) && (aux->*campo < array[j]->*campo))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = aux;
    }
}

//  Funcao para chamar os algoritmos de ordenacao
// Tem como argumento um ponteiro de funcao: ie, uma funcao que retorna void
// e recebe dois inteiros, um vetor de ponteiros de Pessoa e um ponteiro
// para membro do struct Pessoa (assume `name`, `id` ou `adress`).
// Entao, chama a funcao de ordenacao recebida com os parametros recebidos e
// executa um for loop que imprime as informacoes - e opcionalmente, um \n
void chamaSort(void (*sort)(int, int, Pessoa**, std::string Pessoa::*), int Esq, int Dir, Pessoa* array[], std::string Pessoa::*campo, std::string header, int n, bool newline) {
    sort(Esq, Dir, array, campo);
    std::cout << header << n << std::endl;
    for(int i = 0; i < n; i++) {
        std::string name = array[i]->name;
        std::string id = array[i]->id;
        std::string adress = array[i]->adress;
        std::string payload = array[i]->payload;
        std::cout << name << "," << id << "," << adress << "," << payload;
        if(newline || i != (n-1)) std::cout << std::endl;
    }
}

// Funcao de limpeza: simplesmente desaloca a memoria dinamica chamando `delete`
void limpaMemoria(Pessoa* pessoas, Pessoa** names, Pessoa** ids, Pessoa** adresses) {
    delete[] pessoas;
    delete[] names;
    delete[] ids;
    delete[] adresses;
}