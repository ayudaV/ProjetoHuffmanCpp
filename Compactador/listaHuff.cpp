#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listaHuff.h"
using namespace std;

char ListaHuff::Erro = 0;
void ListaHuff::DescarteTudo()
{
    for (pNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
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
    pNo PT, PL;
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
void ListaHuff::Incorpore(charNo CharNo)
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
        this->Inicio->Info = CharNo;
        this->Inicio->Prox = NULL;
        return;
    }
    if (CharNo.Prio < this->Inicio->Info.Prio)
    {
        pNo N;
        if ((N = new liNo) == NULL)
        {
            ListaHuff::Erro = 1;
            return;
        }
        N->Info = CharNo;
        N->Prox = this->Inicio;
        this->Inicio = N;
        return;
    }
    pNo A, P;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox)
    {
        if (P == NULL)
            break;
        if (CharNo.Prio < P->Info.Prio)
            break;
    }
    pNo N;
    if ((N = new liNo) == NULL)
    {
        ListaHuff::Erro = 1;
        return;
    }
    N->Info = CharNo;
    N->Prox = P;
    A->Prox = N;
}
int ListaHuff::Contem(char Ch) const
{
    ListaHuff::Erro = 0;
    if (!this->Valida)
    {
        ListaHuff::Erro = 1;
        return -1;
    }
    for (pNo P = Inicio;; P = P->Prox)
    {
        if (P == NULL)
            break;
        if (Ch == P->Info.Ch)
            return 1;
    }
    return 0;
}
void ListaHuff::Descarte(char Ch)
{
    ListaHuff::Erro = 0;
    if (!this->Valida || this->Inicio == NULL)
    {
        ListaHuff::Erro = 1;
        return;
    }
    pNo A, P;
    int Achou = 0, Prim = 1;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox, Prim = 0)
    {
        if (P == NULL)
            break;
        if (P->Info.Ch == Ch)
        {
            Achou = 1;
            break;
        }
    }
    if (!Achou)
    {
        ListaHuff::Erro = 1;
        return;
    }
    if (Prim)
        Inicio = P->Prox;
    else
        A->Prox = P->Prox;
    delete P;
}
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
    for (pNo P = this->Inicio; P != NULL; P = P->Prox)
    {
        strcat(S,"Ch:");
        itoa(P->Info.Prio, S, 10);
        strcat(R, S);
        strcat(R, P->Prox == NULL ? "" : ", ");
    }
    return R;
}
