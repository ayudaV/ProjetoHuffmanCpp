#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string.h>
#include "Descompactador.cpp"

using namespace std;
int main()
{
    // Gera o endereco do arquivo
    char FilePath[] = "C:\\temp\\";
    char FileName[100];
    cout << "Digite o nome do arquivo a ser descompactado [Sem Extencao]:";
    cin >> FileName;
    strcat(FilePath, FileName);
    strcat(FilePath, ".mali");
    /*
        // Abre o arquivo e copia todos os bytes para dentro de um vetor
        ifstream Input(FilePath, ios::binary);

        if (Input)
        {
            // get length of file:
            Input.seekg(0, Input.end);
            int Length = Input.tellg();
            Input.seekg(0, Input.beg);

            BYTE *Buffer = new BYTE[Length];

            cout << "Reading " << Length << " characters... ";
            // read data as a block:
            Input >> TamSaida;
            Input >> TamArvore;
            Input >> TamTexto;
            printf("%d | %d | %d\n", TamSaida, TamArvore, TamTexto);
            for(int i = 7; i < Length; i++)
                Input >> Buffer[i];

            if (Input)
                cout << "all characters read successfully.";
            else
                cout << "error: only " << Input.gcount() << " could be read";
        }

        vector<BYTE> Buffer(istreambuf_iterator<char>(Input), {});*/

    FILE *Arquivo = fopen(FilePath, "rb");
    if (Arquivo == NULL)
        printf("File Not Found!\n");
    else
    {
        fseek(Arquivo, 0L, SEEK_END);
        int Length = ftell(Arquivo);
        rewind (Arquivo);

        printf("Tamanho do arquivo: %d bytes\n", Length);
        BYTE TamSaida;
        short TamArvore;
        int TamTextoComp;
        fread(&TamSaida, sizeof(BYTE), 1, Arquivo);
        fread(&TamArvore, sizeof(short), 1, Arquivo);
        fread(&TamTextoComp, sizeof(int), 1, Arquivo);
        printf("%d | %d | %d\n", TamSaida, TamArvore, TamTextoComp);

        char CaminhoSaida[TamSaida] = {0};
        BYTE ArvBuilder[TamArvore] = {0};
        BYTE TextBuffer[TamTextoComp] = {0};

        fread(CaminhoSaida, sizeof(BYTE), TamSaida, Arquivo);
        fread(ArvBuilder, sizeof(BYTE), TamArvore, Arquivo);
        fread(TextBuffer, sizeof(BYTE), TamTextoComp, Arquivo);


        printf("Caminho saida: %s\n", CaminhoSaida);

        Descompactador Descompactador(ArvBuilder);
        Descompactador.GerarDiagramaDeArvore();

        ofstream Output;
        char OutFilePath[100] = "C:\\temp\\";
        strcat(OutFilePath, CaminhoSaida);

        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);
        int nChar = 0;
        BYTE *Texto = Descompactador.Descompactar(TextBuffer, TamTextoComp, &nChar);
        Output.write(reinterpret_cast<const char *>(Texto), sizeof(char) * nChar);
        Output.close();
        printf("Acabou");
    }
    return 0;
}
