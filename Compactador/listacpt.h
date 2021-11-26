#ifndef LISTA_COMPLETA 
#define LISTA_COMPLETA 
#include "lista.h" 

class ListaCompleta : public Lista
{
public:
    void IncorporeNoInicio(int);
    int DescarteDoInicio();
    void IncorporeNoFinal(int);
    int DescarteDoFinal();
    int Contem(int) const;
    void Descarte(int);
    char *NaFormaDeString() const;
};
#endif