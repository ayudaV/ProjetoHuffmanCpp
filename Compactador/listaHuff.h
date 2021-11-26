#ifndef LISTAHUFF
#define LISTAHUFF
class ListaHuff
{
protected:
    typedef struct charNo
    {
        char Ch;
        int  Prio;
        struct charNo *Esq;
        struct charNo *Dir;
    } charNo;

    typedef struct liNo
    {
        struct charNo Info;
        struct liNo  *Prox;
    } liNo;
    typedef liNo *pNo;
    static char Erro;
    char Valida;
    pNo Inicio;
    void DescarteTudo();

public:
    static char DeuErro();
    char eValida() const;
    ListaHuff();
    ListaHuff(const ListaHuff &);
    ~ListaHuff();
    ListaHuff &operator=(const ListaHuff &);
    void Incorpore(charNo);
    virtual int Contem(char) const;
    virtual void Descarte(char);
    virtual char *NaFormaDeString() const;
};
#endif