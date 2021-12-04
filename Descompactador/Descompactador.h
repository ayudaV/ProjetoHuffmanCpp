#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H

typedef unsigned char BYTE;

class Descompactador
{
protected:
    typedef struct charNo
    {
        BYTE Ch;
        struct charNo *Esq;
        struct charNo *Dir;
    } charNo;

    typedef charNo *pcNo;
    static char Erro;
    char Valida;
    pcNo Raiz;
    void DescarteTudo(pcNo);
    void NewArvore(BYTE[], int *, pcNo);
    int GetAltura(charNo *noAtual);
    void PrintArvore(pcNo, int);

public:
    Descompactador(BYTE *ArvBuilder);
    ~Descompactador();

    static char DeuErro();
    char eValida() const;
    void GerarDiagramaDeArvore();
    BYTE* Descompactar(BYTE[], int);
};

#endif // DESCOMPACTADOR_H
