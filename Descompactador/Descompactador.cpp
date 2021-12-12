#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Descompactador.h"

typedef unsigned char BYTE;

char Descompactador::Erro = 0;

// Percorre de forma recursiva deletando da memoria todos os nodos da arvore
void Descompactador::DescarteTudo(pcNo P)
{
    if (P->Esq != NULL)
    {
        DescarteTudo(P->Esq);
        DescarteTudo(P->Dir);
    }
    delete P;
}

// A string ArvBuilder funciona dessa maneira:
// Ex {[null, False],[null, False],[a, True],[b, True],[null,False],[null,True],[d, True]}
void Descompactador::NewArvore(BYTE ArvBuilder[], int *Pos, pcNo pCharNo)
{
    pCharNo->Ch = ArvBuilder[(*Pos)]; // Atrubui no nodo passado como parametro o caracter da string na posicao Pos
    pCharNo->Esq = NULL;
    pCharNo->Dir = NULL;

    if (ArvBuilder[(*Pos) + 1] == NULL) // Se o caracter auxiliar for False
    {
        (*Pos) += 2; // Vai para o proximo conjunto da string
        pcNo pcNoEsq = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoEsq); // Chama recursivamente o metodo NewArvore para gerar o no da esquerda
        pCharNo->Esq = pcNoEsq;
        (*Pos) += 2;
        pcNo pcNoDir = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoDir); // Gerar o no da direita
        pCharNo->Dir = pcNoDir;
    }
};

// Destrutor, chama o metodo DescarteTudo passando a raiz da arvore como parametro
Descompactador::~Descompactador() { this->DescarteTudo(this->Raiz); }

// Construtor, recebe a "receita" de criacao da arvore, atribui True para valida
// Instancia a variavel Raiz e depois chama o metodo NewArvore
Descompactador::Descompactador(BYTE arvBuilder[]) : Valida(1)
{
    int pos = 0;
    this->Raiz = new charNo;
    NewArvore(arvBuilder, &pos, this->Raiz);
}

// Recebe o texto compactado, o tamanho dele em bits, e retorna o texto descompactado e o numero de Bytes que ele possui
BYTE *Descompactador::Descompactar(BYTE Buffer[], int TamTexto, int *TamTextoSaida)
{
    // Aloca para o vetor de BYTE Texto o numero de bits do texto compactado / 4
    int BytesAlocados = TamTexto / 4;
    BYTE *Texto = new BYTE[BytesAlocados];

    // Se a esquerda da raiz for null significa que o texto compactado possui apenas 1 tipo de caracter
    if (this->Raiz->Esq == NULL)
    {
        // Como so ha um tipo de caracter, o codigo dele e apenas 0,
        // portanto o numero de Bytes que o texto descompactado possui e o mesmo que o numero de bits que o compactado possui
        Texto = new BYTE[TamTexto];
        (*TamTextoSaida) = TamTexto;
        for (int j = 0; j < TamTexto; j++) // Percorre o vetor Texto atrubuindo em cada posicao o valor do caracter da raiz
            Texto[j] = this->Raiz->Ch;
    }
    else // Caso haja mais de um tipo de caracter no texto original
    {
        BYTE Aux;
        pcNo Atual;
        Atual = this->Raiz;
        int CountCaminho = 0;
        int nBytes = 0;
        *TamTextoSaida = 0;
        // Percorre o texto compactado
        for (int j = 0; j < TamTexto; j++)
        {
            // Se terminou de ler um byte  do texto compactado
            if (j % 8 == 0)
            {
                Aux = Buffer[nBytes]; // Aux recebe um novo byte do Buffer
                nBytes++;
            }
            // Todos os codigos de caracter comecam como 0, portanto esse primeiro bit dos caminhos deve ser ignorado
            if (CountCaminho != 0) // Caso nao seja esse o caso
            {
                if ((Aux & (1 << (j % 8))) == 0) // Aplica uma mascara de "and" em aux, e se o resultado for 0 vai para a esquerda
                    Atual = Atual->Esq;
                else
                    Atual = Atual->Dir; // Se for != de 0 vai para a direita
            }

            CountCaminho++;
            if (Atual->Esq == NULL) // Se chegou em uma folha
            {
                Texto[(*TamTextoSaida)] = Atual->Ch; // Adiciona no vetor Texto o caracter de Atual
                (*TamTextoSaida)++;
                CountCaminho = 0;
                Atual = this->Raiz; // Volta para o comeco da arvore

                // Se o numero de bytes ultilizado chegar no limite de bytes alocados
                // ele redimensiona o vetor TextoCompactado
                if ((*TamTextoSaida) >= BytesAlocados)
                {
                    BytesAlocados *= 2;
                    BYTE *_Texto = new BYTE[BytesAlocados];
                    for (int i = 0; i < BytesAlocados / 2; i++)
                        _Texto[i] = Texto[i];
                    Texto = _Texto;
                }
            }
        }
    }
    return Texto;
}

// Retorna o codigo de erro que o compactador possui
char Descompactador::DeuErro() { return Descompactador::Erro; }

// Retorna um "boolean" se o compactador esta valido
char Descompactador::eValida() const { return this->Valida; }

// Percorre a arvore de forma recursiva contando quantos niveis
// cada folha tem e o final retorna o maior nivel encontrado
int Descompactador::GetAltura(pcNo Atual)
{
    int AlturaEsq, AlturaDir;
    if (Atual == NULL)
        return 0;

    AlturaEsq = GetAltura(Atual->Esq);
    AlturaDir = GetAltura(Atual->Dir);
    if (AlturaEsq >= AlturaDir)
        return 1 + AlturaEsq;
    return 1 + AlturaDir;
}

// Visuais

// Escreve um char especifico n vezes
void Padding(BYTE ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}

// Percorre a arvore recursivamente escrevendo todos as ramificacoes dela
void Descompactador::PrintArvore(pcNo Atual, int Level)
{
    if (Atual == NULL)
    {
        Padding('\t', Level);
        puts("~");
    }
    else
    {
        PrintArvore(Atual->Dir, Level + 1);
        Padding('\t', Level);
        printf("|%c|\n", Atual->Ch);
        PrintArvore(Atual->Esq, Level + 1);
    }
}

// Imprime na tela a arvore completa
void Descompactador::GerarDiagramaDeArvore()
{
    int altura = GetAltura(this->Raiz);
    printf("Altura: %d\n", altura);
    PrintArvore(this->Raiz, altura);
}
