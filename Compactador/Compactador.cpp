#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Compactador.h"

using namespace std;
typedef unsigned char BYTE;

char Compactador::Erro = 0;

void Compactador::DescarteTudo(pcNo P)
{
    if (P->Esq != NULL)
    {
        DescarteTudo(P->Esq);
        DescarteTudo(P->Dir);
    }
    delete P;
}

void Compactador::PreencherTabela()
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

void Compactador::GerarCaminhos(pcNo Atual, char Caminho[256], char **TabelaCaminhos)
{
    char CaminhoAtual[256] = {0};
    strcpy(CaminhoAtual, Caminho);
    if (Atual->Esq == NULL)
    {
        char *nCaminhoChar = new char[256];
        strcpy(nCaminhoChar, CaminhoAtual);
        TabelaCaminhos[Atual->Ch] = nCaminhoChar;
    }
    if (Atual->Esq != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '0';
        GerarCaminhos(Atual->Esq, CaminhoAtual, TabelaCaminhos);
    }
    if (Atual->Dir != NULL)
    {
        CaminhoAtual[strlen(Caminho)] = '1';
        GerarCaminhos(Atual->Dir, CaminhoAtual, TabelaCaminhos);
    }
}

void Compactador::GetArvoreComprimida(pcNo P, BYTE *Str, short *Count)
{
    Str[(*Count)] = P->Ch;
    (*Count)++;
    if (P->Esq != NULL)
    {
        Str[(*Count)] = NULL;
        (*Count)++;
        GetArvoreComprimida(P->Esq, Str, Count);
        GetArvoreComprimida(P->Dir, Str, Count);
    }
    else
    {
        Str[(*Count)] = 1;
        (*Count)++;
    }
}

BYTE *Compactador::Compactar(BYTE *Buffer, int TamArq, int *TamComp)
{
    *TamComp = 0;
    int BytesAlocados = 1024;
    BYTE *TextoCompactado = new BYTE[BytesAlocados];
    BYTE Aux = 0;
    int Count = 0;

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
                if (Count >= BytesAlocados) // aloca mais espaco na memoria
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
    TextoCompactado[Count] = Aux;
    return TextoCompactado;
}

char Compactador::DeuErro() { return Compactador::Erro; }

char Compactador::eValida() const { return this->Valida; }

Compactador::Compactador() : Inicio(NULL), Valida(1) {}

Compactador::~Compactador()
{
    for (plNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
    {
        this->Inicio = this->Inicio->Prox;
        this->DescarteTudo(&this->Inicio->Info);
        delete P;
    }
}

void Compactador::Incorpore(BYTE Ch, int Prio, pcNo Esq, pcNo Dir)
{
    Compactador::Erro = 0;

    if (!this->Valida)
    {
        Compactador::Erro = 1;
        return;
    }
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

void Compactador::JunteNos()
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

// Visuais

BYTE *Compactador::GetArvoreBuilder(short *Count)
{
    BYTE *Str = new BYTE[1024];
    Compactador::Erro = 0;
    if (!this->Valida)
    {
        Compactador::Erro = 1;
        return NULL;
    }
    GetArvoreComprimida(&this->Inicio->Info, Str, Count);
    return Str;
}

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

void Padding(BYTE ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}

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

void Compactador::GerarDiagramaDeArvore()
{
    int altura = GetAltura(&this->Inicio->Info);
    printf("Altura: %d\n", altura);
    PrintArvore(&this->Inicio->Info, altura);
}
