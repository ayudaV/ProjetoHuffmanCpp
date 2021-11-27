#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string.h>

#include "listaHuff.cpp"
using namespace std;
typedef unsigned char BYTE;

int main()
{
    //Gera o endereco do arquivo
    char filePath[] = "C:\\temp\\";
    char filename[100];
    cout << "Digite o nome do arquivo:";
    cin >> filename;
    strcat(filePath, filename);

    //Abre o arquivo e copia todos os bytes para dentro de um vetor
    ifstream Input(filePath, ios::binary);
    vector<BYTE> Buffer(istreambuf_iterator<char>(Input), {});

    //Cria a tabela de frequencia
    int TabelaDeFrequencia[256] = {0};
    for (auto i = Buffer.cbegin(); i != Buffer.cend(); ++i)
        TabelaDeFrequencia[*i]++;

    //system("cls");
    ListaHuff ListaHuff;

    cout << "\nTabela de Frequencia:\n";
    for (int i = 0; i < 256; i++)
    {
        if (TabelaDeFrequencia[i] > 0)
        {
            printf("| %c : %d |\n", i, TabelaDeFrequencia[i]);
            ListaHuff.Incorpore(i, TabelaDeFrequencia[i], NULL, NULL);
        }
    }
    //printf(ListaHuff.NaFormaDeString());
    ListaHuff.JunteNos();
    ListaHuff.GerarDiagramaDeArvore();

    return 0;
}
