//Bibliotecas
#include "common.h"

//Definição do registro de usuarios
typedef char TIPOCHAVE;

typedef struct
{
    char nomeUsuario[100];
    char prontuario[10];
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
void menuPrincipal();
void login();
void gerenciarUsuarios();
void inicializarLista(LISTA *l);
void exibirLista(LISTA *l);
void reinicializarLista(LISTA *l);
void pesquisaLista(LISTA *l);
void insereNaLista(LISTA *l);
void excluiDaLista(LISTA *l);
void carregarLista(LISTA *l);
void cadastro_default();
int tamanhoLista(LISTA *l);
bool inserirElemListaOrd(LISTA *l, REGISTRO reg);
bool excluirElemLista(LISTA *l, char *ch);
void cadastro_default(void);
int salvaArquivo(LISTA *l);
int buscaBinaria(REGISTRO *vetor, int tamanho_vet, char *usuario);
PONT buscaSequencialNome(LISTA *l, char *user, PONT *ant);
PONT buscaSequencialExc(LISTA *l, char *ch, PONT *ant);
PONT buscaSeqOrd(LISTA *l, REGISTRO *ch);
REGISTRO oqueExcluir(void);
REGISTRO oqueBuscar(void);
REGISTRO oqueInserir(void);

