#ifndef LISTAHUFF
#define LISTAHUFF

typedef unsigned char BYTE;

class ListaHuff
{
protected:
    typedef struct charNo
    {
        unsigned char Ch;
        int Prio;
        struct charNo *Esq;
        struct charNo *Dir;
    } charNo;

    typedef struct liNo
    {
        charNo Info;
        struct liNo *Prox;
    } liNo;

    typedef charNo *pcNo;
    typedef liNo *plNo;

    static char Erro;
    char Valida;
    plNo Inicio;
    char **TabelaCaminhos;
    void DescarteTudo(pcNo);
    int GetAltura(pcNo);
    void PrintArvore(pcNo, int);
    void GerarCaminhos(pcNo, char[], char **);
    void GetArvoreComprimida(pcNo, unsigned char*, int*);

public:
    static char DeuErro();
    char eValida() const;

    ListaHuff();
    ListaHuff(const ListaHuff &);
    ~ListaHuff();

    void Incorpore(unsigned char, int, pcNo, pcNo);
    void JunteNos();
    int DescarteDoInicio();
    unsigned char *NaFormaDeString(int *);
    void GerarDiagramaDeArvore();
    void PreencherTabela();
    unsigned char * Compactar(unsigned char*, int*) 
};
#endif