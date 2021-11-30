#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Arvore.h"
char Arvore::Erro = 0;

void Arvore::DescarteTudo()
{
    for (pcNo P = this->Raiz; this->Raiz != NULL; P = this->Raiz)
    {
        //Implementar metodo recursivo para deletar a arvore
        delete P;
    }
}
void Arvore::NewArvore(unsigned char ArvBuilder[], int *Pos, pcNo pCharNo)
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
Arvore::~Arvore() { this->DescarteTudo(); }
Arvore::Arvore(unsigned char arvBuilder[]) : Valida(1)
{
    int pos = 0;
    this->Raiz = new charNo;
    NewArvore(arvBuilder, &pos, this->Raiz);
}
Arvore::Arvore(const Arvore &L) : Raiz(NULL), Valida(1) { *this = L; }

void Arvore::Descompactar(unsigned char Buffer[], int TamTexto, unsigned char *Texto)
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
                printf("New Byte\n");
                Aux = Buffer[nBytes];
                nBytes++;
            }

            if (CountCaminho != 0)
            {
                printf("Walking\n");
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
                printf("New Char: %c, %d\n", Atual->Ch, nChar);

                CountCaminho = 0;
                Atual = this->Raiz;
            }
        }
    }
    printf("%s\n", Texto);
}

char Arvore::DeuErro() { return Arvore::Erro; }
char Arvore::eValida() const { return this->Valida; }

int Arvore::GetAltura(pcNo Atual)
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
void Arvore::PrintArvore(pcNo Atual, int Level)
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
void Arvore::GerarDiagramaDeArvore()
{
    int altura = GetAltura(this->Raiz);
    printf("Altura: %d\n", altura);
    PrintArvore(this->Raiz, altura);
}
