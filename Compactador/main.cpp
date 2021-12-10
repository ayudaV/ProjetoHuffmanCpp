#include <iostream>
#include <fstream>
#include <string.h>
#include "Compactador.cpp"
using namespace std;
typedef unsigned char BYTE;

int main()
{
    system("cls");
    // Gera o endereco do arquivo
    char FilePath[] = "C:\\temp\\";
    char FileName[100];
    cout << "Digite o nome do arquivo: ";
    cin >> FileName;
    strcat(FilePath, FileName);

    FILE *Arquivo = fopen(FilePath, "rb");
    if (Arquivo == NULL)
        printf("File Not Found!\n");
    else
    {
        fseek(Arquivo, 0L, SEEK_END);
        int TamArquivoOriginal = ftell(Arquivo);
        rewind(Arquivo);

        BYTE Buffer[TamArquivoOriginal];
        int TabelaDeFrequencia[256] = {0};

        for (int i = 0; i < TamArquivoOriginal; i++)
        {
            Buffer[i] = fgetc(Arquivo);
            TabelaDeFrequencia[Buffer[i]]++;
        }
        fclose(Arquivo);
        Compactador Compactador;

        for (int i = 0; i < 256; i++)
        {
            if (TabelaDeFrequencia[i] > 0)
                Compactador.Incorpore(i, TabelaDeFrequencia[i], NULL, NULL);
        }
        Compactador.JunteNos();
        // Compactador.GerarDiagramaDeArvore();
        Compactador.PreencherTabela();
        short TamArvore = 0;
        BYTE *ArvBuilder = Compactador.GetArvoreBuilder(&TamArvore);

        char OutFilePath[100] = "C:\\temp\\";
        char OutFileName[50];
        cout << "Digite o nome do arquivo compactado [Sem Extensao]: ";
        cin >> OutFileName;
        strcat(OutFilePath, OutFileName);
        strcat(OutFilePath, ".mali");

        ofstream Output;
        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);

        int TamTextoComp = 0;

        BYTE *TextoCompactado = Compactador.Compactar(Buffer, TamArquivoOriginal, &TamTextoComp);

        BYTE tamanhoNome = strlen(FileName);
        Output.write(reinterpret_cast<const char *>(&tamanhoNome), sizeof(BYTE));
        Output.write(reinterpret_cast<const char *>(&TamArvore), sizeof(short));
        Output.write(reinterpret_cast<const char *>(&TamTextoComp), sizeof(int));
        Output.write(reinterpret_cast<const char *>(FileName), sizeof(char) * tamanhoNome);
        Output.write(reinterpret_cast<const char *>(ArvBuilder), sizeof(BYTE) * TamArvore);
        Output.write(reinterpret_cast<const char *>(TextoCompactado), sizeof(BYTE) * (1 + (TamTextoComp - 1) / 8));
        Output.close();

        printf("----------------------------------------------------\n");
        printf("Tamanho do arquivo: %d Bytes\n", TamArquivoOriginal);
        printf("Tamanho da arvore compactada: %d Bytes\n", TamArvore);
        printf("Tamanho do arquivo compactado: %d Bytes\n", (TamTextoComp / 8));
        printf("----------------------------------------------------\n");
        cout << "Compactado com sucesso!\n";
    }
    return 0;
}
