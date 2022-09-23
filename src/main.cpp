#include "huffman.hpp"

int main()
{

    map<string, float> frequencia;

    priority_queue<Arvore *, vector<Arvore *>, Comp> fila;
    string palavra;
    int contPalavras = 0;
    Arvore *arvoreHuffman;
    vector<bool> codigo;
    int altura = 0;
    vector<string> textoAux;

    ifstream file("src/arquivo.txt");

    if (!file.good())
    {
        cout << "deu ruim " << endl;
        return -1;
    }

    while (file >> palavra)
    {

        palavra.erase(remove_if(palavra.begin(), palavra.end(), ::ispunct), palavra.end());
        transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

        // cout << palavra << endl;
        frequencia[palavra]++;
        contPalavras++;
    }
    file.close();

    for (auto item : frequencia)
    {
        cout << "palavra: " << item.first << " | Frequencia: " << item.second << endl;
        item.second /= contPalavras;

        Arvore *no = new Arvore(item.first, item.second);
        fila.push(no);
    }
    // cout << contPalavras << endl;

    while (fila.size() != 1)
    {
        Arvore *esq = fila.top();
        fila.pop();
        Arvore *dir = fila.top();
        fila.pop();
        Arvore *no = new Arvore("$", esq->frequencia + dir->frequencia);
        no->esq = esq;
        no->dir = dir;
        fila.push(no);
    }
    arvoreHuffman = fila.top();

    imprimirArvore(arvoreHuffman, codigo, altura);
    textoVector(&textoAux);
    convertBinary(textoAux);

    return 0;
}