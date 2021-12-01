#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H

typedef unsigned char BYTE;

class Descompactador
{
protected:
    typedef struct charNo
    {
        unsigned char Ch;
        struct charNo *Esq;
        struct charNo *Dir;
    } charNo;

    typedef charNo *pcNo;
    static char Erro;
    char Valida;
    pcNo Raiz;
    void DescarteTudo(pcNo);
    void NewArvore(unsigned char[], int *, pcNo);
    int GetAltura(charNo *noAtual);
    void PrintArvore(pcNo, int);

public:
    Descompactador(unsigned char *ArvBuilder);
    ~Descompactador();

    static char DeuErro();
    char eValida() const;
    void GerarDiagramaDeArvore();
    void Descompactar(unsigned char[], int, unsigned char*);
};

#endif // DESCOMPACTADOR_H
