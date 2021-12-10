#ifndef LISTAHUFF
#define LISTAHUFF

typedef unsigned char BYTE;

class Compactador
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
    void GetArvoreComprimida(pcNo, BYTE *, short *);

public:
    static char DeuErro();
    char eValida() const;

    Compactador();
    Compactador(const Compactador &);
    ~Compactador();

    void Incorpore(BYTE, int, pcNo, pcNo);
    void JunteNos();
    int DescarteDoInicio();

    void PreencherTabela();

    BYTE *GetArvoreBuilder(short *);
    BYTE *Compactar(BYTE *, int, int *);

    void GerarDiagramaDeArvore();
};
#endif