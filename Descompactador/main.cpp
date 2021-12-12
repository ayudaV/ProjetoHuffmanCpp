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
    char FilePath[100] = "C:\\temp\\";
    char FileName[50];
    cout << "Digite o nome do arquivo a ser descompactado [Sem Extencao]: ";
    cin >> FileName;
    strcat(FilePath, FileName);
    strcat(FilePath, ".mali"); // caminho do arquivo a ser descompactado

    FILE *Arquivo = fopen(FilePath, "rb");
    if (Arquivo == NULL)
        printf("File Not Found!\n");
    else
    {
        fseek(Arquivo, 0L, SEEK_END); // posiciona indicador no fim do arquivo
        int Length = ftell(Arquivo);  // pega tamanho do arquivo pela posição do indicador
        rewind(Arquivo);              // reposiciona indicador para o início do arquivo

        // define tamanhos para ler do arquivo
        BYTE TamSaida;
        short TamArvore;
        int TamTextoComp;
        fread(&TamSaida, sizeof(BYTE), 1, Arquivo);
        fread(&TamArvore, sizeof(short), 1, Arquivo);
        fread(&TamTextoComp, sizeof(int), 1, Arquivo);

        char CaminhoSaida[TamSaida + 1] = {0};
        BYTE ArvBuilder[TamArvore] = {0};
        BYTE TextBuffer[TamTextoComp] = {0};

        // Leitura do arquivo
        fread(CaminhoSaida, sizeof(BYTE), TamSaida, Arquivo);
        fread(ArvBuilder, sizeof(BYTE), TamArvore, Arquivo);
        fread(TextBuffer, sizeof(BYTE), TamTextoComp, Arquivo);
        fclose(Arquivo);

        Descompactador Descompactador(ArvBuilder); // árvore lida é passada para o descompactador
        Descompactador.GerarDiagramaDeArvore();

        ofstream Output;
        char OutFilePath[100] = "C:\\temp\\";
        strcat(OutFilePath, CaminhoSaida); // caminho para salvar arquivo descompactado

        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary); // abre arquivo para escrever em binário
        int TamTextoDesc = 0;
        BYTE *Texto = Descompactador.Descompactar(TextBuffer, TamTextoComp, &TamTextoDesc); // retorna arquivo descompactado
        Output.write(reinterpret_cast<const char *>(Texto), sizeof(char) * TamTextoDesc);   // escreve no arquivo
        Output.close();
        // Informações sobre a descompactação
        printf("----------------------------------------------------\n");
        printf("Tamanho do arquivo: %d Bytes\n", Length);
        printf("Nome do arquivo descompactado: %s\n", CaminhoSaida);
        printf("Tamanho do arquivo descompactado: %d Bytes\n", TamTextoDesc);
        printf("----------------------------------------------------\n");
        cout << "Descompactado com sucesso!\n";
    }
    return 0;
}