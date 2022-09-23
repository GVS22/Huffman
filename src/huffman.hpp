#ifndef __HUFFMAN_HPP__
#define __HUFFMAN_HPP__

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

map<string, vector<bool>> gTradutor;

struct Arvore
{
    string palavra;
    float frequencia;
    Arvore *dir, *esq;
    Arvore(string palavra, float frequencia)
    {
        this->palavra = palavra;
        this->frequencia = frequencia;
        esq = dir = nullptr;
    }
};

struct Comp
{
    bool operator()(Arvore *esq, Arvore *dir)
    {
        return (esq->frequencia > dir->frequencia);
    }
};

void imprimirArvore(Arvore *arvoreHuffman, vector<bool> codigo, int altura);
void getTextToVector(vector<string> *vectorPalavra);
void createBinaryFile(vector<string> vectorPalavra);





void imprimirArvore(Arvore *arvoreHuffman, vector<bool> codigo, int altura)
{
    if (arvoreHuffman->esq)
    {
        codigo.insert(codigo.begin(), false);
        imprimirArvore(arvoreHuffman->esq, codigo, altura + 1);
    }
    if (arvoreHuffman->dir)
    {
        codigo.insert(codigo.begin(), true);
        imprimirArvore(arvoreHuffman->dir, codigo, altura + 1);
    }
    if (!arvoreHuffman->esq && !arvoreHuffman->dir)
    {
        pair<string, vector<bool>> aux;
        aux.second.clear();
        aux.first = arvoreHuffman->palavra;
        cout <<"palavra: "<< arvoreHuffman->palavra << " Codigo: ";

        for (int i = 0; i < altura; i++)
        {
            cout << codigo.at(i);
            aux.second.push_back(codigo.at(i));
        }
        cout << endl;
        gTradutor.insert(aux);
    }
}
void textoVector(vector<string> *vectorPalavra)
{

    string palavra;
    ifstream file("src/arquivo.txt");
    while (file >> palavra)
        vectorPalavra->push_back(palavra);

    file.close();
}

void convertBinary(vector<string> vectorPalavra)
{
    ofstream file("src/binary.dat", ios::out | ios::binary);
    if (!file.good())
    {
        cout << "Cannot open file!" << endl;
        return;
    }
    string textoAux;
    map<string, vector<bool>>::iterator it;
    for (auto item : vectorPalavra)
    {
        textoAux.assign("");
        it = gTradutor.find(item);
        if (it != gTradutor.end())
        {
            for (auto i : it->second)
                textoAux.append(to_string(i));
            file.write(textoAux.c_str(), (textoAux.size()));
        }
    }

    file.close();
}



#endif