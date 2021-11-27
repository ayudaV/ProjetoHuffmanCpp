#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listaHuff.h"

using namespace std;

char ListaHuff::Erro = 0;

void ListaHuff::DescarteTudo()
{
    for (plNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
    {
        this->Inicio = this->Inicio->Prox;
        delete P;
    }
}

char ListaHuff::DeuErro() { return ListaHuff::Erro; }

char ListaHuff::eValida() const { return this->Valida; }

ListaHuff::ListaHuff() : Inicio(NULL), Valida(1) {}

ListaHuff::ListaHuff(const ListaHuff &L) : Inicio(NULL), Valida(1) { *this = L; }

ListaHuff::~ListaHuff() { this->DescarteTudo(); }

ListaHuff &ListaHuff::operator=(const ListaHuff &L)
{
    this->DescarteTudo();
    this->Valida = 1;
    ListaHuff::Erro = 0;
    plNo PT, PL;
    for (PL = L.Inicio; PL != NULL; PL = PL->Prox)
        if (this->Inicio == NULL)
        {
            if ((this->Inicio = new liNo) == NULL)
            {
                this->Valida = 0;
                ListaHuff::Erro = 1;
                break;
            }
            this->Inicio->Info = PL->Info;
            this->Inicio->Prox = NULL;
            PT = this->Inicio;
        }
        else
        {
            if ((PT->Prox = new liNo) == NULL)
            {
                this->Valida = 0;
                ListaHuff::Erro = 1;
                break;
            }
            PT = PT->Prox;
            PT->Info = PL->Info;
            PT->Prox = NULL;
        }
    return *this;
}

void ListaHuff::Incorpore(unsigned char Ch, int Prio, pcNo Esq, pcNo Dir)
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
char *ListaHuff::NaFormaDeString() const
{
    ListaHuff::Erro = 0;
    if (!this->Valida)
    {
        ListaHuff::Erro = 1;
        return NULL;
    }
    static char S[16], R[1025];
    strcpy(R, "");
    for (plNo P = this->Inicio; P != NULL; P = P->Prox)
    {

        char C = (P->Info.Ch);
        int Prio = (P->Info.Prio);
        printf("%c : %d", C, Prio);

        /*
        char PrioStr[5];
        itoa(Prio, PrioStr, 10);
        strcpy(S, "");
        strcat(S, &C);
        strcat(S, " : ");
        strcat(S, PrioStr);
        strcat(R, S);
        strcat(R, P->Prox == NULL ? "" : ", ");*/
    }
    return R;
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
void Padding(unsigned char ch, int n)
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
