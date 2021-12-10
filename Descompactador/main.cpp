#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Descompactador.cpp"

using namespace std;
int main()
{
    system("cls");
    // Gera o endereco do arquivo
    char FilePath[] = "C:\\temp\\";
    char FileName[100];
    cout << "Digite o nome do arquivo a ser descompactado [Sem Extencao]: ";
    cin >> FileName;
    strcat(FilePath, FileName);
    strcat(FilePath, ".mali");

    FILE *Arquivo = fopen(FilePath, "rb");
    if (Arquivo == NULL)
        printf("File Not Found!\n");
    else
    {
        fseek(Arquivo, 0L, SEEK_END);
        int Length = ftell(Arquivo);
        rewind(Arquivo);

        BYTE TamSaida;
        short TamArvore;
        int TamTextoComp;
        fread(&TamSaida, sizeof(BYTE), 1, Arquivo);
        fread(&TamArvore, sizeof(short), 1, Arquivo);
        fread(&TamTextoComp, sizeof(int), 1, Arquivo);

        char CaminhoSaida[TamSaida + 1] = {0};
        BYTE ArvBuilder[TamArvore] = {0};
        BYTE TextBuffer[TamTextoComp] = {0};

        fread(CaminhoSaida, sizeof(BYTE), TamSaida, Arquivo);
        fread(ArvBuilder, sizeof(BYTE), TamArvore, Arquivo);
        fread(TextBuffer, sizeof(BYTE), TamTextoComp, Arquivo);
        fclose(Arquivo);

        Descompactador Descompactador(ArvBuilder);
        // Descompactador.GerarDiagramaDeArvore();

        ofstream Output;
        char OutFilePath[100] = "C:\\temp\\";
        strcat(OutFilePath, CaminhoSaida);

        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);
        int TamTextoDesc = 0;
        BYTE *Texto = Descompactador.Descompactar(TextBuffer, TamTextoComp, &TamTextoDesc);
        Output.write(reinterpret_cast<const char *>(Texto), sizeof(char) * TamTextoDesc);
        Output.close();
        printf("----------------------------------------------------\n");
        printf("Tamanho do arquivo: %d Bytes\n", Length);
        printf("Nome do arquivo descompactado: %s\n", CaminhoSaida);
        printf("Tamanho do rquivo descompactado: %d Bytes\n", TamTextoDesc);
        printf("----------------------------------------------------\n");
        cout << "Descompactado com sucesso!\n";
    }
    return 0;
}
