#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "lista.h"
using namespace std;

char Lista::Erro = 0;
void Lista::DescarteTudo()
{
    for (pNo P = this->Inicio; this->Inicio != NULL; P = this->Inicio)
    {
        this->Inicio = this->Inicio->Prox;
        delete P;
    }
}
char Lista::DeuErro() { return Lista::Erro; }
char Lista::eValida() const { return this->Valida; }
Lista::Lista() : Inicio(NULL), Valida(1) {}
Lista::Lista(const Lista &L) : Inicio(NULL), Valida(1) { *this = L; }
Lista::~Lista() { this->DescarteTudo(); }
Lista &Lista::operator=(const Lista &L)
{
    this->DescarteTudo();
    this->Valida = 1;
    Lista::Erro = 0;
    pNo PT, PL;
    for (PL = L.Inicio; PL != NULL; PL = PL->Prox)
        if (this->Inicio == NULL)
        {
            if ((this->Inicio = new sNo) == NULL)
            {
                this->Valida = 0;
                Lista::Erro = 1;
                break;
            }
            this->Inicio->Info = PL->Info;
            this->Inicio->Prox = NULL;
            PT = this->Inicio;
        }
        else
        {
            if ((PT->Prox = new sNo) == NULL)
            {
                this->Valida = 0;
                Lista::Erro = 1;
                break;
            }
            PT = PT->Prox;
            PT->Info = PL->Info;
            PT->Prox = NULL;
        }
    return *this;
}
void Lista::Incorpore(int I)
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return;
    }
    if (this->Inicio == NULL)
    {
        if ((this->Inicio = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        this->Inicio->Info = I;
        this->Inicio->Prox = NULL;
        return;
    }
    if (I < this->Inicio->Info)
    {
        pNo N;
        if ((N = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        N->Info = I;
        N->Prox = this->Inicio;
        this->Inicio = N;
        return;
    }
    pNo A, P;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox)
    {
        if (P == NULL)
            break;
        if (I < P->Info)
            break;
    }
    pNo N;
    if ((N = new sNo) == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    N->Info = I;
    N->Prox = P;
    A->Prox = N;
}
int Lista::Contem(int I) const
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return -1;
    }
    for (pNo P = Inicio;; P = P->Prox)
    {
        if (P == NULL)
            break;
        if (P->Info > I)
            break;
        if (I == P->Info)
            return 1;
    }
    return 0;
}
void Lista::Descarte(int I)
{
    Lista::Erro = 0;
    if (!this->Valida || this->Inicio == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    pNo A, P;
    int Achou = 0, Prim = 1;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox, Prim = 0)
    {
        if (P == NULL)
            break;
        if (P->Info > I)
            break;
        if (P->Info == I)
        {
            Achou = 1;
            break;
        }
    }
    if (!Achou)
    {
        Lista::Erro = 1;
        return;
    }
    if (Prim)
        Inicio = P->Prox;
    else
        A->Prox = P->Prox;
    delete P;
}
char *Lista::NaFormaDeString() const
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return NULL;
    }
    static char S[16], R[1025];
    strcpy(R, "");
    for (pNo P = this->Inicio; P != NULL; P = P->Prox)
    {
        itoa(P->Info, S, 10);
        strcat(R, S);
        strcat(R, P->Prox == NULL ? "" : ", ");
    }
    return R;
}
