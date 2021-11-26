#include <iostream>
#include "lista.cpp"
#include "listacpt.cpp"
using namespace std;
//a
int main()
{
    int I, N;
    cout << "\n================================\n"
         << "Testecom objeto da classe Lista\n"
         << "================================\n\n";
    Lista L1;
    cout << "Entre com 10 numeros separados por espacos:\n";
    for (I = 1; I <= 10; I++)
    {
        cin >> N;
        L1.Incorpore(N);
    }
    cout << "\nEm ordem, os numeros digitados sao:\n"
         << "L1 = " << L1.NaFormaDeString();
    cout << "\n\nEntre com um numero para ser excluido da lista original:\n";
    cin >> N;
    L1.Descarte(N);
    cout << "\nEm ordem, apos a exclusao, a lista ficou:\n"
         << "L1 = " << L1.NaFormaDeString();
    cout << "\n\nEntre com dois numeros separados por um espaco\n"
         << "para que seja verificado se pertencem ou nao a lista:\n";
    cin >> N;
    if (L1.Contem(N))
        cout << "O primeiro numero pertence a lista";
    else
        cout << "O primeiro numero nao pertence a lista";
    cin >> N;
    if (L1.Contem(N))
        cout << "\nO segundo numero pertence a lista";
    else
        cout << "\nO segundo numero nao pertence a lista";
    Lista L2 = L1;
    cout << "\n\nFoi feita uma copia de sua lista de numeros;"
         << "\nVerifique se a copia esta correta:\n"
         << "L2 = " << L2.NaFormaDeString();
    Lista L3;
    L3 = L1;
    cout << "\n\nFoi feita uma outra copia de sua lista de numeros;"
         << "\nVerifique se esta outra copia esta correta:\n"
         << "L3 = " << L3.NaFormaDeString();
    cout << "\n\n";
    cout << "\n\n========================================\n"
         << "Teste com objeto da classe ListaCompleta\n"
         << "========================================\n\n";
    ListaCompleta LC1;
    cout << "Entre com 10 numeros separados por espacos\n"
         << "para que sejam incluidos na lista LC1:\n";
    for (I = 1; I <= 10; I++)
    {
        cin >> N;
        LC1.Incorpore(N);
    }
    cout << "\nEm ordem, os numeros digitados sao:\n"
         << "LC1 = " << LC1.NaFormaDeString();
    cout << "\n\nEntre com um numero para ser excluido da lista LC1:\n";
    cin >> N;
    LC1.Descarte(N);
    cout << "\nEm ordem, apos a exclusao, a lista ficou:\n"
         << "LC1 = " << LC1.NaFormaDeString();
    cout << "\n\nEntre com dois numeros separados por um espaco para\n"
         << "que seja verificado se pertencem ou nao a lista LC1:\n";
    cin >> N;
    if (LC1.Contem(N))
        cout << "O primeiro numero pertence a lista LC1";
    else
        cout << "O primeiro numero nao pertence a lista LC1";
    cin >> N;
    if (LC1.Contem(N))
        cout << "\nO segundo numero pertence a lista LC1";
    else
        cout << "\nO segundo numero nao pertence a lista LC1";
    cout << "\n\nEntre com dois numeros separados por espacos\n"
         << "(um para ser incluido no inicio "
         << "e outro no final da lista LC1):\n";
    cin >> N;
    LC1.IncorporeNoInicio(N);
    cin >> N;
    LC1.IncorporeNoFinal(N);
    cout << "\nApos as inclusoes, a lista ficou:\n"
         << "LC1 = " << LC1.NaFormaDeString();
    ListaCompleta LC2 = LC1;
    cout << "\n\nFoi feita uma copia da lista LC1;"
         << "\nVerifique se a copia esta correta:\n"
         << "LC2 = " << LC2.NaFormaDeString();
    ListaCompleta LC3;
    LC3 = LC1;
    cout << "\n\nFoi feita uma outra copia da lista LC1;"
         << "\nVerifique se esta outra copia esta correta:\n"
         << "LC3 = " << LC3.NaFormaDeString();
    LC1.DescarteDoInicio();
    LC1.DescarteDoFinal();
    cout << "\n\nApos a exclusao do primeiro e do ultimo, "
         << "a lista ficou:\n"
         << "LC1 = " << LC1.NaFormaDeString();
    cout << "\n\n=====================================\n"
         << "Teste com ponteiro da classe Lista\n"
         << "apontando para objeto da classe Lista\n"
         << "=====================================\n\n";
    Lista *PL1 = new Lista;
    cout << "Entre com 10 numeros separados por espacos\n"
         << "para que sejam incluidos na lista *PL1:\n";
    for (I = 1; I <= 10; I++)
    {
        cin >> N;
        PL1->Incorpore(N);
    }
    cout << "\nEm ordem, os numeros digitados sao:\n"
         << "*PL1 = " << PL1->NaFormaDeString();
    cout << "\n\nEntre com um numero para ser excluido da lista *PL1:\n";
    cin >> N;
    PL1->Descarte(N);
    cout << "\nEm ordem, apos a exclusao, a lista ficou:\n"
         << "*PL1 = " << PL1->NaFormaDeString();
    cout << "\n\nEntre com dois numeros separados por um espaco\n"
         << "para que seja verificado se pertencem ou nao a lista *PL1:\n";
    cin >> N;
    if (PL1->Contem(N))
        cout << "O primeiro numero pertence a lista *PL1";
    else
        cout << "O primeiro numero nao pertence a lista *PL1";
    cin >> N;
    if (PL1->Contem(N))
        cout << "\nO segundo numero pertence a lista *PL1";
    else
        cout << "\nO segundo numero nao pertence a lista *PL1";
    Lista *PL2 = new Lista(*PL1);
    cout << "\n\nFoi feita uma copia da lista *PL1;"
         << "\nVerifique se a copia esta correta:\n"
         << "*PL2 = " << PL2->NaFormaDeString();
    Lista *PL3 = new Lista;
    *PL3 = *PL1;
    cout << "\n\nFoi feita uma outra copia da lista *PL1;"
         << "\nVerifique se esta outra copia esta correta:\n"
         << "*PL3 = " << PL3->NaFormaDeString();
    delete PL1;
    delete PL2;
    delete PL3;
    cout << "\n\n===========================================\n"
         << "Teste com ponteiro da classe ListaCompleta\n"
         << "apontando para objeto da classe ListaCompleta\n"
         << "=============================================\n\n";
    ListaCompleta *PLC1 = new ListaCompleta;
    cout << "Entre com 10 numeros separados por espacos\n"
         << "para que sejam incluidos na lista *PLC1:\n";
    for (I = 1; I <= 10; I++)
    {
        cin >> N;
        PLC1->Incorpore(N);
    }
    cout << "\nEm ordem, os numeros digitados sao:\n"
         << "*PLC1 = " << PLC1->NaFormaDeString();
    cout << "\n\nEntre com um numero para ser excluido da lista *PLC1:\n";
    cin >> N;
    PLC1->Descarte(N);
    cout << "\nEm ordem, apos a exclusao, a lista ficou:\n"
         << "*PLC1 = " << PLC1->NaFormaDeString();
    cout << "\n\nEntre com dois numeros separados por um espaco para\n"
         << "que seja verificado se pertencem ou nao a lista *PLC1:\n";
    cin >> N;
    if (PLC1->Contem(N))
        cout << "O primeiro numero pertence a lista *PLC1";
    else
        cout << "O primeiro numero nao pertence a lista *PLC1";
    cin >> N;
    if (PLC1->Contem(N))
        cout << "\nO segundo numero pertence a lista *PLC1";
    else
        cout << "\nO segundo numero nao pertence a lista *PLC1";
    cout << "\n\nEntre com dois numeros separados por espacos\n"
         << "(um para ser incluido no inicio "
         << "e outro no final da lista *PLC1):\n";
    cin >> N;
    PLC1->IncorporeNoInicio(N);
    cin >> N;
    PLC1->IncorporeNoFinal(N);
    cout << "\nApos as inclusoes, a lista ficou:\n"
         << "*PLC1 = " << PLC1->NaFormaDeString();
    ListaCompleta *PLC2 = new ListaCompleta(*PLC1);
    cout << "\n\nFoi feita uma copia da lista *PLC1;"
         << "\nVerifique se a copia esta correta:\n"
         << "*PLC2 = " << PLC2->NaFormaDeString();
    ListaCompleta *PLC3 = new ListaCompleta;
    *PLC3 = *PLC1;
    cout << "\n\nFoi feita uma outra copia da lista *PLC1;"
         << "\nVerifique se esta outra copia esta correta:\n"
         << "*PLC3 = "
         << PLC3->NaFormaDeString();
    PLC1->DescarteDoInicio();
    PLC1->DescarteDoFinal();
    cout << "\n\nApos a exclusao do primeiro e do ultimo, "
         << "a lista ficou:\n"
         << "*PLC1 = " << PLC1->NaFormaDeString();
    delete PLC1;
    delete PLC2;
    delete PLC3;
    cout << "\n\n===========================================\n"
         << "TESTE COM PONTEIRO DA CLASSE Lista\n"
         << "APONTANDO PARA OBJETO DA CLASSE ListaCompleta\n"
         << "=============================================\n\n";
    PL1 = new ListaCompleta; // OBSERVE COM ATENCAO!
    cout << "Entre com 10 numeros separados por espacos\n"
         << "para que sejam incluidos na lista *PL1:\n";
    for (I = 1; I <= 10; I++)
    {
        cin >> N;
        PL1->Incorpore(N);
    }
    cout << "\nEm ordem, os numeros digitados sao:\n"
         << "*PL1 = " << PL1->NaFormaDeString();
    cout << "\n\nEntre com um numero para ser excluido da lista *PL1:\n";
    cin >> N;
    PL1->Descarte(N);
    cout << "\nEm ordem, apos a exclusao, a lista ficou:\n"
         << "*PL1 = " << PL1->NaFormaDeString();
    cout << "\n\nEntre com dois numeros separados por um espaco\n"
         << "para que seja verificado se pertencem ou nao a lista *PL1:\n";
    cin >> N;
    if (PL1->Contem(N))
        cout << "O primeiro numero pertence a lista *PL1";
    else
        cout << "O primeiro numero nao pertence a lista *PL1";
    cin >> N;
    if (PL1->Contem(N))
        cout << "\nO segundo numero pertence a lista *PL1";
    else
        cout << "\nO segundo numero nao pertence a lista *PL1";
    PL2 = new ListaCompleta(*(ListaCompleta *)PL1);
    cout << "\n\nFoi feita uma copia da lista *PL1;"
         << "\nVerifique se a copia esta correta:\n"
         << "*PL2 = "
         << PL2->NaFormaDeString();
    PL3 = new ListaCompleta;
    *PL3 = *PL1;
    cout << "\n\nFoi feita uma outra copia da lista *PL1;"
         << "\nVerifique se esta outra copia esta correta:\n"
         << "*PL3 = " << PL3->NaFormaDeString();
    delete PL1;
    delete PL2;
    delete PL3;
    cout << "\n\n";
    return 0;
}
