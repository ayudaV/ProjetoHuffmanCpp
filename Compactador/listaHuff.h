#ifndef LISTAHUFF
#define LISTAHUFF
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
    void DescarteTudo();
    int GetAltura(pcNo);
    void PrintArvore(pcNo, int);

public:
    static char DeuErro();
    char eValida() const;
    ListaHuff();
    ListaHuff(const ListaHuff &);
    ~ListaHuff();
    ListaHuff &operator=(const ListaHuff &);
    void Incorpore(unsigned char, int, pcNo, pcNo);
    void JunteNos();
    virtual int DescarteDoInicio();
    virtual char *NaFormaDeString() const;
    void GerarDiagramaDeArvore();
};
#endif