#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Compactador.h"

using namespace std;
typedef unsigned char BYTE;

char Compactador::Erro = 0;

// Percorre de forma recursiva deletando da memoria todos os nodos da arvore
void Compactador::DescarteTudo(pcNo P)
{
    if (P->Esq != NULL)
    {
        DescarteTudo(P->Esq);
        DescarteTudo(P->Dir);
    }
    delete P;
}

// Instancia a variavel TabelaCaminhos como uma matriz de char, definindo a comprimento como 256
//  e a largura como a altura da arvore, alem de definir todas as posicoes como 0
void Compactador::PreencherTabela()
{
    this->TabelaCaminhos = new char *[256];
    int Altura = GetAltura(&this->Inicio->Info);
    for (int i = 0; i < 256; i++)
    {
        TabelaCaminhos[i] = new char[Altura];
        memset(TabelaCaminhos[i], 0, Altura);
    }
    // Cria a variavel caminho e chama o metodo GerarCaminhos passando o endereco de Inicio->Info e o Caminho
    char Caminho[256] = {'0'};
    GerarCaminhos(&this->Inicio->Info, Caminho);
}

// Percorre de forma recursiva a arvore e a cada movimento um novo caracter [0 ou 1] e posto no caminho
// Ao achar um char, uma copia do caminho atual e criada e gravada na tabela de caminhos
void Compactador::GerarCaminhos(pcNo Atual, char Caminho[256])
{
    char CaminhoAtual[256] = {0};
    strcpy(CaminhoAtual, Caminho);
    // Se a esquerda do atual for null significa que chegou em uma folha por isso cria uma copia do caminho atual e grava ela
    if (Atual->Esq == NULL)
    {
        char *nCaminhoChar = new char[256];
        strcpy(nCaminhoChar, CaminhoAtual);
        this->TabelaCaminhos[Atual->Ch] = nCaminhoChar;
    }
    // Se a esquerda nao for null escreve 0 no caminho e chama recursivamente o metodo passando a esquerda do atual
    if (Atual->Esq != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '0';
        GerarCaminhos(Atual->Esq, CaminhoAtual);
    }
    // Se a direita nao for null escreve 1 no caminho e chama recursivamente o metodo passando a direita do atual
    if (Atual->Dir != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '1';
        GerarCaminhos(Atual->Dir, CaminhoAtual);
    }
}

// Percorre de forma recursiva a arvore gerando uma string contendo a "receita para recria-la"
void Compactador::GetArvoreComprimida(pcNo P, BYTE *Str, short *Count)
{
    // Escre o carater atual na string e soma mais um no tamanho da string
    Str[(*Count)] = P->Ch;
    (*Count)++;
    // Se a esquerda nao for null significa que esta em um galho portanto o char de auxilo recebe null e
    // chama recursivamente para a esquerda e depois para a direita do atual
    if (P->Esq != NULL)
    {
        Str[(*Count)] = NULL;
        (*Count)++;
        GetArvoreComprimida(P->Esq, Str, Count);
        GetArvoreComprimida(P->Dir, Str, Count);
    }
    // Senao, o char de auxilo recebe true e apenas incrementa o tamanho da string
    else
    {
        Str[(*Count)] = 1;
        (*Count)++;
    }
}

// Recebe o texto a ser compactado, o tamanho dele e retorna o texto compactado e seu tamanho em bits
BYTE *Compactador::Compactar(BYTE *Buffer, int TamArq, int *TamComp)
{
    // Zera a variavel TamComp e depois aloca 1024 bytes na memoria para TextoCompactado
    *TamComp = 0;
    int BytesAlocados = 1024;
    BYTE *TextoCompactado = new BYTE[BytesAlocados];
    BYTE Aux = 0;
    int Count = 0;
    // Percorre todo o arquivo a ser compactado
    for (int i = 0; i < TamArq; i++)
    {
        // Percorre char a char ("bit a bit") o endereco do caracter lido
        for (int j = 0; j < strlen(TabelaCaminhos[Buffer[i]]); j++)
        {
            if ((TabelaCaminhos[Buffer[i]])[j] == '1')
            {
                // Se o codigo do char for 1 ele adiciona 1 bit contendo True
                Aux = Aux | (1 << ((*TamComp) % 8));
            }
            (*TamComp)++;
            // Terminou de ocupar 1 byte, escreve ele e reseta
            if ((*TamComp) % 8 == 0)
            {
                TextoCompactado[Count] = Aux;
                Count++;
                Aux = 0;
                // Se o numero de bytes ultilizado chegar no limite de bytes alocados
                // ele redimensiona o vetor TextoCompactado
                if (Count >= BytesAlocados)
                {
                    BytesAlocados *= 2;
                    BYTE *_TextoCompactado = new BYTE[BytesAlocados];
                    for (int i = 0; i < BytesAlocados / 2; i++)
                        _TextoCompactado[i] = TextoCompactado[i];
                    TextoCompactado = _TextoCompactado;
                }
            }
        }
    }
    // TextoCompactado recebe o resto de aux e retorna TextoCompactado
    TextoCompactado[Count] = Aux;
    return TextoCompactado;
}

// Retorna o codigo de erro que o compactador possui
char Compactador::DeuErro() { return Compactador::Erro; }

// Retorna um "boolean" se o compactador esta valido
char Compactador::eValida() const { return this->Valida; }

// Construtor
Compactador::Compactador() : Inicio(NULL), Valida(1) {}

// Destrutor, percorre a lista ligada e destroi qualquer arvore que possa existir dentro de cada no da lista
Compactador::~Compactador()
{
    for (plNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
    {
        this->DescarteTudo(&P->Info);
        this->Inicio = this->Inicio->Prox;
        delete P;
    }
}

// Inclui um novo no na lista ligada
void Compactador::Incorpore(BYTE Ch, int Prio, pcNo Esq, pcNo Dir)
{
    Compactador::Erro = 0;
    // se o compactador for invalido atribui erro 1 e retorna
    if (!this->Valida)
    {
        Compactador::Erro = 1;
        return;
    }
    // Se a lista for vazia
    if (this->Inicio == NULL)
    {
        if ((this->Inicio = new liNo) == NULL)
        {
            Compactador::Erro = 1;
            return;
        }
        this->Inicio->Info.Ch = Ch;
        this->Inicio->Info.Prio = Prio;
        this->Inicio->Info.Esq = Esq;
        this->Inicio->Info.Dir = Dir;
        this->Inicio->Prox = NULL;
        return;
    }
    // Se prioridade for menor que a do inicio
    if (Prio < this->Inicio->Info.Prio)
    {
        plNo N;
        if ((N = new liNo) == NULL)
        {
            Compactador::Erro = 1;
            return;
        }
        N->Info.Ch = Ch;
        N->Info.Prio = Prio;
        N->Info.Esq = Esq;
        N->Info.Dir = Dir;
        N->Prox = this->Inicio;
        this->Inicio = N;
        return;
    }
    // Percorre a lista e insere na posicao ordenada
    plNo N, A, P;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox)
    {
        if (P == NULL)
            break;
        if (Prio < (P->Info.Prio))
            break;
    }
    if ((N = new liNo) == NULL)
    {
        Compactador::Erro = 1;
        return;
    }
    N->Info.Ch = Ch;
    N->Info.Prio = Prio;
    N->Info.Esq = Esq;
    N->Info.Dir = Dir;
    N->Prox = P;
    A->Prox = N;
}

// Enquanto existir mais de um no na lista ele criara um novo no usando os nodeChar dos dois primeiros nos da lista
// como esquerda e direita e a priopridade sendo a soma da prioridade esquerda e a prioridade direita. Depois excluira
// o primeiro e o segundo no da lista e incluira esse novo no na lista.
void Compactador::JunteNos()
{
    if (this->Inicio == NULL)
        return;
    while (this->Inicio->Prox != NULL)
    {
        pcNo Esq, Dir;
        Esq = new charNo;
        Dir = new charNo;
        *Esq = Inicio->Info;              // Atrubui esquerda
        *Dir = Inicio->Prox->Info;        // Atribui direita
        int Prio = Esq->Prio + Dir->Prio; // Atribui prioridade
        DescarteDoInicio();               // Descarta os dois primeiros
        DescarteDoInicio();
        Incorpore(NULL, Prio, Esq, Dir); // Insere o novo no
    }
}

//Remove o primeiro no da lista
int Compactador::DescarteDoInicio()
{
    if (Inicio == NULL)
    {
        Compactador::Erro = 1;
        return -1;
    }
    plNo P = Inicio;
    Inicio = Inicio->Prox;
    delete P;
    return 1;
}

//Retorna uma string com a "formula de construcao da arvore" e o tamanho dela
BYTE *Compactador::GetArvoreBuilder(short *Count)
{
    BYTE *Str = new BYTE[1024];
    Compactador::Erro = 0;
    if (!this->Valida)
    {
        Compactador::Erro = 1;
        return NULL;
    }
    //chama o metodo GetArvoreComprimida passando o endereco da raiz, 
    // o endereco da string em que será escrita a formula e o endereco do tamanho dessa string
    GetArvoreComprimida(&this->Inicio->Info, Str, Count);
    return Str;
}

//Percorre a arvore de forma recursiva contando quantos niveis cada folha tem e o final retorna o maior nivel encontrado
int Compactador::GetAltura(pcNo Atual)
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

//Escreve um char especifico n vezes
void Padding(BYTE ch, int n)
{
    for (int i = 0; i < n; i++)
        putchar(ch);
}

//Percorre a arvore recursivamente escrevendo todos as ramificacoes dela
void Compactador::PrintArvore(pcNo Atual, int Level)
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
        printf("|%c: %d|\n", Atual->Ch, Atual->Prio);
        PrintArvore(Atual->Esq, Level + 1);
    }
}

//Imprime na tela a arvore completa
void Compactador::GerarDiagramaDeArvore()
{
    int Altura = GetAltura(&this->Inicio->Info);
    printf("Altura: %d\n", Altura);
    PrintArvore(&this->Inicio->Info, Altura);
}
