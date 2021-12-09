#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string.h>

#include "Compactador.cpp"
using namespace std;
typedef unsigned char BYTE;

int main()
{
    // Gera o endereco do arquivo
    char FilePath[] = "C:\\temp\\";
    char FileName[100];
    cout << "Digite o nome do arquivo:";
    cin >> FileName;
    strcat(FilePath, FileName);

    // Abre o arquivo e copia todos os bytes para dentro de um vetor
    ifstream Input(FilePath, ios::binary);
    vector<BYTE> Buffer(istreambuf_iterator<char>(Input), {});
    if (Buffer.cbegin() == Buffer.cend())
        cout << "Arquivo nao encontrado ou arquivo vazio!";
    else
    {
        // Cria a tabela de frequencia
        int TabelaDeFrequencia[256] = {0};
        for (auto i = Buffer.cbegin(); i != Buffer.cend(); ++i)
            TabelaDeFrequencia[*i]++;

        // system("cls");
        Compactador Compactador;

        cout << "\nTabela de Frequencia:\n";
        for (int i = 0; i < 256; i++)
        {
            if (TabelaDeFrequencia[i] > 0)
            {
                printf("| %c : %d |\n", i, TabelaDeFrequencia[i]);
                Compactador.Incorpore(i, TabelaDeFrequencia[i], NULL, NULL);
            }
        }
        // printf(Compactador.NaFormaDeString());
        Compactador.JunteNos();
        Compactador.GerarDiagramaDeArvore();
        Compactador.PreencherTabela();
        int TamArvore = 0;
        BYTE *ArvBuilder = Compactador.NaFormaDeString(&TamArvore);

        char OutFilePath[100] = "C:\\temp\\";
        char OutFileName[50];
        cout << "Digite o nome do arquivo compactado [Sem Extensao]:";
        cin >> OutFileName;
        strcat(OutFilePath, OutFileName);
        strcat(OutFilePath, ".mali");
        ofstream Output;

        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);

        int TamTextoComp = 0;
        BYTE *ArrayBuffer = new BYTE[Buffer.size()];
        for (int i = 0; i < Buffer.size(); i++)
        {
            ArrayBuffer[i] = Buffer[i];
        }

        BYTE *TextoCompactado = Compactador.Compactar(ArrayBuffer, Buffer.size(), &TamTextoComp);
        int TamArquivoOriginal = Buffer.size();
        printf("%d | %d | %d | %d\n", strlen(FileName), Buffer.size(), TamArvore, TamTextoComp);

        BYTE tamanhoNome = strlen(FileName);
        Output.write(reinterpret_cast<const char *>(&tamanhoNome), sizeof(char));
        Output.write(reinterpret_cast<const char *>(&TamArvore), sizeof(short));
        Output.write(reinterpret_cast<const char *>(&TamTextoComp), sizeof(int));
        Output.write(reinterpret_cast<const char *>(FileName), sizeof(char) * strlen(FileName));
        Output.write(reinterpret_cast<const char *>(ArvBuilder), sizeof(BYTE) * TamArvore);
        Output.write(reinterpret_cast<const char *>(TextoCompactado), sizeof(BYTE) * (1 + (TamTextoComp - 1) / 8));

        printf("Acabou!");
        Output.close();
    }
    return 0;
}
