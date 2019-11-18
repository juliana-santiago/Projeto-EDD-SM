//Bibliotecas
#include "common.h"

//Definição do tipo chave
typedef int TIPOCHAVE;

//Definição do registro de usuarios
typedef struct
{
    TIPOCHAVE chave;
    char nomeUsuario[100 + 1];
    char prontuario[10 + 1];
} REGISTRO;

typedef struct aux
{
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT inicio;
} LISTA;

//Funções Busca Encadeada
void gerenciarUsuarios();
void inicializarLista(LISTA *l);
void exibirLista(LISTA *l);
void reinicializarLista(LISTA *l);
void pesquisaLista(LISTA *l);
void insereNaLista(LISTA *l);
void excluiDaLista(LISTA *l);
void carregarLista(LISTA *l);
int tamanhoLista(LISTA *l);
bool inserirElemListaOrd(LISTA *l, REGISTRO reg);
bool excluirElemLista(LISTA *l, TIPOCHAVE tch);
char *replace(char *, char, char);

PONT buscaSequencialExc(LISTA *l, TIPOCHAVE tch, PONT *ant);
PONT buscaSequencialOrg(LISTA *l, char *ch, PONT *ant);
PONT buscaSeqOrdNum(LISTA *l, TIPOCHAVE tch);
PONT buscaSeqOrd(LISTA *l, char *ch);
TIPOCHAVE oqueExcluir(void);
TIPOCHAVE oqueBuscar(void);
REGISTRO oqueInserir(void);

