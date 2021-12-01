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
    char FilePath[] = "C:\\temp\\";
    char FileName[100];
    cout << "Digite o nome do arquivo:";
    cin >> FileName;
    strcat(FilePath, FileName);

    //Abre o arquivo e copia todos os bytes para dentro de um vetor
    ifstream Input(FilePath, ios::binary);
    vector<BYTE> Buffer(istreambuf_iterator<char>(Input), {});
    if (Buffer.cbegin() == Buffer.cend())
        cout << "Arquivo nao encontrado ou arquivo vazio!";
    else
    {
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
        ListaHuff.PreencherTabela();
        int TamArvore = 0;
        unsigned char *ArvBuilder = ListaHuff.NaFormaDeString(&TamArvore);

        char OutFilePath[] = "C:\\temp\\";
        char OutFileName[100];
        cout << "Digite o nome do arquivo compactado [Sem Extensao]:";
        cin >> OutFileName;
        strcat(OutFilePath, OutFileName);
        ofstream Output;
        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);
        int TamTexto = 0;
        BYTE *TextoCompactado = ListaHuff.Compactar(Buffer, &TamTexto);
        Output << Texto;
        Output.close();
        * /
    }
    return 0;
}
