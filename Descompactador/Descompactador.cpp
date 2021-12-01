#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Descompactador.h"
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
void Descompactador::NewArvore(unsigned char ArvBuilder[], int *Pos, pcNo pCharNo)
{
    pCharNo->Ch = ArvBuilder[(*Pos)];
    pCharNo->Esq = NULL;
    pCharNo->Dir = NULL;

    if (ArvBuilder[(*Pos)] == NULL)
    {
        (*Pos)++;
        pcNo pcNoEsq = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoEsq);
        pCharNo->Esq = pcNoEsq;
        (*Pos)++;
        pcNo pcNoDir = new charNo;
        NewArvore(ArvBuilder, Pos, pcNoDir);
        pCharNo->Dir = pcNoDir;
    }
};
Descompactador::~Descompactador() { this->DescarteTudo(this->Raiz); }
Descompactador::Descompactador(unsigned char arvBuilder[]) : Valida(1)
{
    int pos = 0;
    this->Raiz = new charNo;
    NewArvore(arvBuilder, &pos, this->Raiz);
}
Descompactador::Descompactador(const Descompactador &L) : Raiz(NULL), Valida(1) { *this = L; }

void Descompactador::Descompactar(unsigned char Buffer[], int TamTexto, unsigned char *Texto)
{
    if (this->Raiz->Ch != NULL)
    {
        for (int j = 0; j < TamTexto; j++)
            Texto[j] = this->Raiz->Ch;
    }
    else
    {
        unsigned char Aux;
        pcNo Atual;
        Atual = this->Raiz;
        int CountCaminho = 0;
        int nBytes = 0;
        int nChar = 0;
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
                Texto[nChar] = Atual->Ch;
                nChar++;
                CountCaminho = 0;
                Atual = this->Raiz;
            }
        }
    }
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
void Padding(unsigned char ch, int n)
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