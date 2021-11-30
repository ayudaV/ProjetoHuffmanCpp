#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string.h>
#include "Arvore.cpp"

using namespace std;
int main()
{
    //Gera o endereco do arquivo
    char filePath[] = "C:\\temp\\";
    char filename[100];
    cout << "Digite o nome do arquivo a ser descompactado [Sem Extencao]:";
    cin >> filename;
    strcat(filePath, filename);
    strcat(filePath, ".mali");

    //Abre o arquivo e copia todos os bytes para dentro de um vetor
    ifstream Input(filePath, ios::binary);
    vector<unsigned char> Buffer(istreambuf_iterator<char>(Input), {});
    if (Buffer.cbegin() == Buffer.cend())
        cout << "Arquivo nao encontrado ou arquivo vazio!";
    else
    {
        int TamSaida = Buffer[(Buffer.size() - 12)];
        int TamArvore = Buffer[(Buffer.size() - 8)];
        int TamTexto = Buffer[(Buffer.size() - 4)];
        char CaminhoSaida[TamSaida + 1] = {0};
        unsigned char ArvBuilder[TamArvore] = {0};
        unsigned char TextBuffer[TamTexto] = {0};
        int i;
        for (i = 0; i < TamSaida; i++)
        {
            CaminhoSaida[i] = Buffer[i];
        }
        CaminhoSaida[i + 1] = '\0';

        for (int j = 0; j < TamArvore; j++)
        {
            ArvBuilder[j] = Buffer[i];
            i++;
        }
        for (int j = 0; j < TamTexto; j++)
        {
            TextBuffer[j] = Buffer[i];
            i++;
        }

        Arvore Arvore(ArvBuilder);

        Arvore.GerarDiagramaDeArvore();

        ofstream Output;
        Output.open(CaminhoSaida, ofstream::out | ofstream::trunc | ofstream::binary);
        unsigned char Texto[100] = {0};

        Arvore.Descompactar(TextBuffer, TamTexto, Texto);
        Output << Texto;
        Output.close();
        printf("SaiU %s", Texto);
        //Por algum motivo n ta encerrando o programa
    }
    return 0;
}
