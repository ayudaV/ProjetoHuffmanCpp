#ifndef LISTA
#define LISTA
class Lista
{
protected:
    typedef struct sNo
    {
        int Info;
        struct sNo *Prox;
    }
    sNo;
    typedef sNo *pNo;
    static char Erro;
    char Valida;
    pNo Inicio;
    void DescarteTudo();

public:
    static char DeuErro();
    char eValida() const;
    Lista();
    Lista(const Lista &);
    ~Lista();
    Lista &operator=(const Lista &);
    void Incorpore(int);
    virtual int Contem(int) const;
    virtual void Descarte(int);
    virtual char *NaFormaDeString() const;
};
#endif