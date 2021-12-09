#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Descompactador.h"

typedef unsigned char BYTE;

char Descompactador::Erro = 0;

void Descompactador::DescarteTudo(pcNo P)
{
    if (P->Esq != NULL)
    {
        DescarteTudo(P->Esq);
        DescarteTudo(P->Dir);
    }
    delete P;
}

void Descompactador::NewArvore(BYTE ArvBuilder[], int *Pos, pcNo pCharNo)
{
    pCharNo->Ch = ArvBuilder[(*Pos)];
    pCharNo->Esq = NULL;
    pCharNo->Dir = NULL;

    if (ArvBuilder[(*Pos)] == NULL && ArvBuilder[(*Pos) + 1] == NULL)
    {
        (*Pos) += 2;
        pcNo pcNoEsq = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoEsq);
        pCharNo->Esq = pcNoEsq;
        (*Pos) += 2;
        pcNo pcNoDir = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoDir);
        pCharNo->Dir = pcNoDir;
    }
};

Descompactador::~Descompactador() { this->DescarteTudo(this->Raiz); }

Descompactador::Descompactador(BYTE arvBuilder[]) : Valida(1)
{
    int pos = 0;
    this->Raiz = new charNo;
    NewArvore(arvBuilder, &pos, this->Raiz);
}

BYTE *Descompactador::Descompactar(BYTE Buffer[], int TamTexto, int* nChar)
{
    int BytesAlocados = TamTexto;
    BYTE *Texto = new BYTE[BytesAlocados];
    if (this->Raiz->Ch != NULL)
    {
        for (int j = 0; j < TamTexto; j++)
            Texto[j] = this->Raiz->Ch;
    }
    else
    {
        BYTE Aux;
        pcNo Atual;
        Atual = this->Raiz;
        int CountCaminho = 0;
        int nBytes = 0;
        *nChar = 0;
        for (int j = 0; j < TamTexto; j++)
        {
            if (j % 8 == 0)
            {
                Aux = Buffer[nBytes];
                nBytes++;
            }

            if (CountCaminho != 0)
            {
                if ((Aux & (1 << (j % 8))) == 0)
                    Atual = Atual->Esq;
                else
                    Atual = Atual->Dir;
            }

            CountCaminho++;
            if (Atual->Esq == NULL)
            {
                Texto[(*nChar)] = Atual->Ch;
                (*nChar)++;
                CountCaminho = 0;
                Atual = this->Raiz;

                if ((*nChar) >= BytesAlocados) // aloca mais espaco na memoria
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

char Descompactador::DeuErro() { return Descompactador::Erro; }

char Descompactador::eValida() const { return this->Valida; }

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

void Padding(BYTE ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}

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

void Descompactador::GerarDiagramaDeArvore()
{
    int altura = GetAltura(this->Raiz);
    printf("Altura: %d\n", altura);
    PrintArvore(this->Raiz, altura);
}
