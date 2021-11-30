#ifndef ARVORE_H
#define ARVORE_H
class Arvore
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
    void DescarteTudo();
    void NewArvore(unsigned char[], int *, pcNo);
    int GetAltura(charNo *noAtual);
    void PrintArvore(pcNo, int);

public:
    Arvore(unsigned char *ArvBuilder);
    Arvore(const Arvore &);
    ~Arvore();

    static char DeuErro();
    char eValida() const;
    void GerarDiagramaDeArvore();
    void Descompactar(unsigned char[], int, unsigned char*);
};

#endif // ARVORE_H
