//Bibliotecas
#include "common.h"

//Defini??o do registro de produtos
typedef struct
{
    char NOMEPROD[100];
    char DESC[100];
    char PESO[10];
    char PRECO[10];
} PRODUTO;

typedef struct prod
{
    PRODUTO regprod;
    struct prod *PROX;
} ELEMPROD;

typedef ELEMPROD *POINT;

typedef struct
{
    POINT topo;
} PILHA;

typedef struct
{
    PILHA prateleira[10];
} GONDOLA;

int tamanhoPilha(PILHA *);
void inicializarPilha(PILHA *);
void inicializarGondola(GONDOLA *);
bool pilhaVazia(PILHA *);
void gondolaVazia(GONDOLA *);
void insereNaGondola(GONDOLA *);
void insereNaPilha(PILHA *);
PRODUTO oqueInserirPilha();
bool inserirElemPilha(PILHA *, PRODUTO );
void exibirQuantGondola(GONDOLA *);
void excluirDaPilha(PILHA *, PILHA *);
bool inserirNoCarrinho(PILHA *, PILHA *, PRODUTO *);
bool excluirElemPilha(PILHA *, PRODUTO *);
void exibirPilha(PILHA *);
void exibirGondola(GONDOLA *);
void excluirDaGondola(GONDOLA *, PILHA *);
bool inserirNoCarrinho(PILHA *, PILHA *, PRODUTO *);
void exibirCarrinho(PILHA *);
void reinicializarGondola(GONDOLA *);
void reinicializarPilha(PILHA *);
void salvarArquivoProd(PILHA *, char *);
PRODUTO * convertPilhaToArray(PILHA *);
PRODUTO * lerArquivoPilha(char * );
void salvarGondola(GONDOLA *);
void carregaGondula(GONDOLA *);
