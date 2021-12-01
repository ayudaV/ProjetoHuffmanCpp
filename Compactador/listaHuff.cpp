#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listaHuff.h"

using namespace std;
typedef unsigned char BYTE;

char ListaHuff::Erro = 0;

void ListaHuff::DescarteTudo(pcNo P)
{
    if (P->Esq != NULL)
    {
        DescarteTudo(P->Esq);
        DescarteTudo(P->Dir);
    }
    delete P;
}

void ListaHuff::PreencherTabela()
{
    this->TabelaCaminhos = new char *[256];
    int Altura = GetAltura(&this->Inicio->Info);
    for (int i = 0; i < 256; i++)
    {
        TabelaCaminhos[i] = new char[Altura];
        memset(TabelaCaminhos[i], 0, Altura);
    }
    char Caminho[256] = {'0'};
    GerarCaminhos(&this->Inicio->Info, Caminho, this->TabelaCaminhos);
}

void ListaHuff::GerarCaminhos(pcNo Atual, char Caminho[256], char **TabelaCaminhos)
{
    char CaminhoAtual[256] = {0};
    strcpy(CaminhoAtual, Caminho);
    if (Atual->Esq == NULL)
    {
        char *nCaminhoChar = (char *)malloc(sizeof(strlen(CaminhoAtual)));
        strcpy(nCaminhoChar, CaminhoAtual);
        printf("Gerando Caminho: %s\n", nCaminhoChar);
        TabelaCaminhos[Atual->Ch] = nCaminhoChar;
    }
    if (Atual->Esq != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '0';
        char _Caminho[256];
        strcpy(_Caminho, CaminhoAtual);
        GerarCaminhos(Atual->Esq, _Caminho, TabelaCaminhos);
    }
    if (Atual->Dir != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '1';
        char _Caminho[256];
        strcpy(_Caminho, CaminhoAtual);
        GerarCaminhos(Atual->Dir, _Caminho, TabelaCaminhos);
    }
}

void ListaHuff::GetArvoreComprimida(pcNo P, BYTE *Str, int *Count)
{
    Str[(*Count)] = P->Ch;
    (*Count)++;
    Str[(*Count)] = 1;
    (*Count)++;
    printf("Ch: %c | True: %c\n", Str[(*Count) - 2], Str[(*Count) - 1]);

    if (P->Esq != NULL)
    {
        GetArvoreComprimida(P->Esq, Str, Count);
        GetArvoreComprimida(P->Dir, Str, Count);
    }
}

BYTE *ListaHuff::Compactar(BYTE *Buffer, int TamArq, int *TamComp)
{
    *TamComp = 0;
    BYTE *TextoCompactado = new BYTE[100]; //Arrumar
    BYTE Aux = 0;
    int Count = 0;
    printf("---------------------------\n");
    printf("Tamanho: %d\n", TamArq);

    for (int i = 0; i < TamArq; i++)
    {
        printf("Lendo um Char: %c, Tam Caminho: %d\n", Buffer[i], strlen(TabelaCaminhos[Buffer[i]]));
        /*Percorre char a char ("bit a bit") o endereco do caracter lido*/
        for (int j = 0; j < strlen(TabelaCaminhos[Buffer[i]]); j++)
        {
            printf("o\n");
            if ((TabelaCaminhos[Buffer[i]])[j] == '1')
            {
                /*Se o codigo do char for 1 ele adiciona 1 bit contendo True*/
                Aux = Aux | (1 << ((*TamComp) % 8));
            }

            (*TamComp)++;
            /*Terminou de ocupar 1 byte, escreve ele e reseta*/
            if ((*TamComp) % 8 == 0)
            {
                TextoCompactado[Count] = Aux;
                Count++;
                Aux = 0;
            }
        }
    }
    return TextoCompactado;
}

char ListaHuff::DeuErro() { return ListaHuff::Erro; }

char ListaHuff::eValida() const { return this->Valida; }

ListaHuff::ListaHuff() : Inicio(NULL), Valida(1) {}

ListaHuff::ListaHuff(const ListaHuff &L) : Inicio(NULL), Valida(1) { *this = L; }

ListaHuff::~ListaHuff()
{
    for (plNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
    {
        this->Inicio = this->Inicio->Prox;
        this->DescarteTudo(&this->Inicio->Info);
        delete P;
    }
}

void ListaHuff::Incorpore(BYTE Ch, int Prio, pcNo Esq, pcNo Dir)
{
    ListaHuff::Erro = 0;

    if (!this->Valida)
    {
        ListaHuff::Erro = 1;
        return;
    }
    if (this->Inicio == NULL)
    {
        if ((this->Inicio = new liNo) == NULL)
        {
            ListaHuff::Erro = 1;
            return;
        }
        this->Inicio->Info.Ch = Ch;
        this->Inicio->Info.Prio = Prio;
        this->Inicio->Info.Esq = Esq;
        this->Inicio->Info.Dir = Dir;
        this->Inicio->Prox = NULL;
        return;
    }
    if (Prio < this->Inicio->Info.Prio)
    {
        plNo N;
        if ((N = new liNo) == NULL)
        {
            ListaHuff::Erro = 1;
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
        ListaHuff::Erro = 1;
        return;
    }
    N->Info.Ch = Ch;
    N->Info.Prio = Prio;
    N->Info.Esq = Esq;
    N->Info.Dir = Dir;
    N->Prox = P;
    A->Prox = N;
}

void ListaHuff::JunteNos()
{
    while (Inicio->Prox != NULL)
    {
        pcNo Esq, Dir;
        Esq = new charNo;
        Dir = new charNo;
        *Esq = Inicio->Info;
        *Dir = Inicio->Prox->Info;
        int Prio = Esq->Prio + Dir->Prio;
        DescarteDoInicio();
        DescarteDoInicio();
        Incorpore(NULL, Prio, Esq, Dir);
    }
}

int ListaHuff::DescarteDoInicio()
{
    if (Inicio == NULL)
    {
        ListaHuff::Erro = 1;
        return -1;
    }
    plNo P = Inicio;
    Inicio = Inicio->Prox;
    delete P;
    return 1;
}

//Visuais

BYTE *ListaHuff::NaFormaDeString(int *Count)
{
    BYTE *Str;
    Str = new BYTE[1024];
    ListaHuff::Erro = 0;
    if (!this->Valida)
    {
        ListaHuff::Erro = 1;
        return NULL;
    }
    GetArvoreComprimida(&this->Inicio->Info, Str, Count);
    return Str;
}

int ListaHuff::GetAltura(pcNo Atual)
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

void Padding(BYTE ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}

void ListaHuff::PrintArvore(pcNo Atual, int Level)
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

void ListaHuff::GerarDiagramaDeArvore()
{
    int altura = GetAltura(&this->Inicio->Info);
    printf("Altura: %d\n", altura);
    PrintArvore(&this->Inicio->Info, altura);
}
