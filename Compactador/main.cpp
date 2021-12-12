#include <iostream>
#include <fstream>
#include <string.h>
#include "Compactador.cpp"
using namespace std;
typedef unsigned char BYTE;

int main()
{
    system("cls"); // Limpa a tela
    // Gera o endereco do arquivo de entrada
    char FilePath[100] = "C:\\temp\\";
    char FileName[50];
    cout << "Digite o nome do arquivo [Com Extencao]: ";
    cin >> FileName;
    strcat(FilePath, FileName);

    // Abre o arquivo de entrada
    FILE *Arquivo = fopen(FilePath, "rb");
    if (Arquivo == NULL) // Se o arquivo nao existir ou for vasio ele nao compacta
        printf("File Not Found!\n");
    else
    {
        // Obtem o tamanho do arquivo a ser lido
        fseek(Arquivo, 0L, SEEK_END);
        int TamArquivoOriginal = ftell(Arquivo);
        rewind(Arquivo);

        // Cria um vetor de BYTE e uma tabela de frequencia
        BYTE Buffer[TamArquivoOriginal];
        int TabelaDeFrequencia[256] = {0};

        // Percorre o arquivo de entrada e grava char a char no buffer e manipula a tabela de frequencia
        for (int i = 0; i < TamArquivoOriginal; i++)
        {
            Buffer[i] = fgetc(Arquivo);
            TabelaDeFrequencia[Buffer[i]]++;
        }
        // fecha o arquivo
        fclose(Arquivo);

        // Instancia um objeto da classe Compactador
        Compactador Compactador;
        // Percorre a tabela de frequencia e se o caracter tiver aparecido ao menos uma vez no texto
        //  ele e inserido na lista ligada
        for (int i = 0; i < 256; i++)
        {
            if (TabelaDeFrequencia[i] > 0)
                Compactador.Incorpore(i, TabelaDeFrequencia[i], NULL, NULL);
        }
        Compactador.JunteNos();              // Chama o metodo para juntar os nos em forma de arvore
        Compactador.GerarDiagramaDeArvore(); // Imprime a arvore
        Compactador.PreencherTabela();       // Preenche a tabela contendo todos os caminhos dos caracteres
        short TamArvore = 0;
        BYTE *ArvBuilder = Compactador.GetArvoreBuilder(&TamArvore); // Obtem a string de construcao de arvore e seu tamanho

        // Gera o endereco do arquivo de saida
        char OutFilePath[100] = "C:\\temp\\";
        char OutFileName[50];
        cout << "Digite o nome do arquivo compactado [Sem Extencao]: ";
        cin >> OutFileName;
        strcat(OutFilePath, OutFileName);
        strcat(OutFilePath, ".mali");

        // Cria um objeto da classe Output e abre ele usando o endereco do arquivo de saida
        ofstream Output;
        Output.open(OutFilePath, ofstream::out | ofstream::trunc | ofstream::binary);

        int TamTextoComp = 0;

        // Chama o metodo que compacta o texto passando o texto original,
        // seu tamanho e obtendo como saida o texto compactado e o tamanho em bits do texto compactado
        BYTE *TextoCompactado = Compactador.Compactar(Buffer, TamArquivoOriginal, &TamTextoComp);

        BYTE tamanhoNome = strlen(FileName);
        // Escreve todos os dados importantes no arquivo de saida e depois fecha ele
        Output.write(reinterpret_cast<const char *>(&tamanhoNome), sizeof(BYTE));
        Output.write(reinterpret_cast<const char *>(&TamArvore), sizeof(short));
        Output.write(reinterpret_cast<const char *>(&TamTextoComp), sizeof(int));
        Output.write(reinterpret_cast<const char *>(FileName), sizeof(char) * tamanhoNome);
        Output.write(reinterpret_cast<const char *>(ArvBuilder), sizeof(BYTE) * TamArvore);
        Output.write(reinterpret_cast<const char *>(TextoCompactado), sizeof(BYTE) * (1 + (TamTextoComp - 1) / 8));
        Output.close();

        // Exibe para o usuario os dados de relevancia
        printf("----------------------------------------------------\n");
        printf("Tamanho do arquivo: %d Bytes\n", TamArquivoOriginal);
        printf("Tamanho da arvore compactada: %d Bytes\n", TamArvore);
        printf("Tamanho do arquivo compactado: %d Bytes\n", (1 + (TamTextoComp - 1) / 8));
        printf("----------------------------------------------------\n");
        printf("Compactado com sucesso!\n");
    }
    return 0;
}
