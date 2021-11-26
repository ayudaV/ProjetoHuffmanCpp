#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "listacpt.h"
using namespace std;

void ListaCompleta::IncorporeNoInicio(int I)
{
    pNo N;
    if ((N = new sNo) == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    N->Info = I;
    N->Prox = Inicio;
    Inicio = N;
}
int ListaCompleta::DescarteDoInicio()
{
    if (Inicio == NULL)
    {
        Lista::Erro = 1;
        return -1;
    }
    int R = Inicio->Info;
    pNo P = Inicio;
    Inicio = Inicio->Prox;
    delete P;
    return R;
}
void ListaCompleta::IncorporeNoFinal(int I)
{
    if (Inicio == NULL)
    {
        if ((Inicio = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        Inicio->Info = I;
        Inicio->Prox = NULL;
    }
    else
    {
        pNo A, P, N;
        for (A = NULL, P = Inicio; P != NULL; A = P, P = P->Prox)
            ;
        if ((N = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        N->Info = I;
        N->Prox = NULL;
        A->Prox = N;
    }
}
int ListaCompleta::DescarteDoFinal()
{
    if (Inicio == NULL)
    {
        Lista::Erro = 1;
        return -1;
    }
    int R;
    if (Inicio->Prox == NULL)
    {
        R = Inicio->Info;
        delete Inicio;
        Inicio = NULL;
    }
    else
    {
        pNo A, P, D;
        for (A = Inicio, P = Inicio->Prox, D = P->Prox; D != NULL; A = P, P = D, D = D->Prox)
            ;
        R = P->Info;
        A->Prox = NULL;
        delete P;
    }
    return R;
}
int ListaCompleta::Contem(int I) const
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
        if (I == P->Info)
            return 1;
    }
    return 0;
}
void ListaCompleta::Descarte(int I)
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
    free(P);
}
char *ListaCompleta::NaFormaDeString() const
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return NULL;
    }
    static char R[1025];
    strcpy(R, "{");
    strcat(R, Lista::NaFormaDeString());
    strcat(R, "}");
    return R;
}