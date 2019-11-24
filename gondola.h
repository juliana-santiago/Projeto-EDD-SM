//Bibliotecas
#include "common.h"

//Definição do tipo chave
typedef int TIPOCHAVEPROD;

//Definição do registro de produtos
typedef struct
{
    TIPOCHAVEPROD chave;
    char NOMEPROD[100 + 1];
    char DESC[100 + 1];
    char PESO[10 + 1];
    char PRECO[10 + 1];
} REGISTROPROD;

typedef struct prod
{
    REGISTROPROD regprod;
    struct prod *PROX;
} ELEMENTOPROD;

typedef ELEMENTOPROD *POINT;

typedef struct
{
    POINT topo;
} PILHA;

typedef struct
{
    PILHA prateleira[10];
} GONDOLA;

//Funçoes Pilha
void abastecerGondolas();
void inicializarPilha(PILHA *p);
void exibirPilha(PILHA *p);
void reinicializarPilha(PILHA *p);
void insereNaPilha(PILHA *p);
void insereNaGondola(GONDOLA *g);
void excluirDaPilha(PILHA *p, PILHA *car);
void excluirDaGondola(GONDOLA *g, PILHA *car);
void carregarPilha(PILHA *p);
void carregarGondola(GONDOLA *g);
void exibirCarrinho(PILHA *p);
void inicializarGondola(GONDOLA *g);
void inicializarProg(GONDOLA *g);
void exibirGondola(GONDOLA *g);
int tamanhoPilha(PILHA *p);
bool inserirNoCarrinho(PILHA *p, PILHA *car, REGISTROPROD *regprod);
bool inserirElemPilha(PILHA *p, REGISTROPROD regprod);
bool excluirElemPilha(PILHA *p, REGISTROPROD *regprod);
bool estaVaziaPilha(PILHA *p);
bool estaVaziaGondola(GONDOLA *g);
void exibirQuantGondola(GONDOLA *g);

REGISTROPROD oqueInserirPilha(void);
