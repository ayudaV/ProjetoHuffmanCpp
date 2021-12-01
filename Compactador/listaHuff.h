#ifndef LISTAHUFF
#define LISTAHUFF

typedef unsigned char BYTE;

class ListaHuff
{
protected:
    typedef struct charNo
    {
        BYTE Ch;
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
    void GetArvoreComprimida(pcNo, BYTE*, int*);

public:
    static char DeuErro();
    char eValida() const;

    ListaHuff();
    ListaHuff(const ListaHuff &);
    ~ListaHuff();

    void Incorpore(BYTE, int, pcNo, pcNo);
    void JunteNos();
    int DescarteDoInicio();
    BYTE *NaFormaDeString(int *);
    void GerarDiagramaDeArvore();
    void PreencherTabela();
    BYTE * Compactar(BYTE*, int, int*);
};
#endif