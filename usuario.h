//BIBLIOTECA
#include "common.h"

//STRUCTS ARQUIVO USUARIO;C
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


//FUNÇOES ARQUIVO USUARIO.C
void cadastroDefault(void);
void gerenciarUsuarios(LISTA *);
REGISTRO *lerArquivo();
void quick_sort(REGISTRO *, int, int);
int part(REGISTRO[], int, int);
void troca(REGISTRO[], int, int);
int quantRegistro(void);
void exibeArquivo(void);
bool inserirElemListaOrd(LISTA *, REGISTRO);
PONT buscaSequencialNome(LISTA *, char *, PONT *);
PONT buscaSequencialPront(LISTA *, char *, PONT *);
void inicializarLista(LISTA *);
void carregaLista(LISTA *);
void exibirLista(LISTA *);
int tamanhoLista(LISTA *);
void buscaPorProntuario(LISTA *);
void insereNaLista(LISTA *);
REGISTRO oqueInserir();
REGISTRO * convertToArray(LISTA *);
REGISTRO oqueExcluir ();
void excluiDaLista(LISTA *);
bool excluirElemLista(LISTA *, char *);
int salvaArquivo(LISTA *);
void reinicializarLista (LISTA *l);

