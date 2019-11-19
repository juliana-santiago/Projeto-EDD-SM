//Biblioteca
#include "usuario.h"

//Arquivo como Variavel Global
FILE *arq;

//Inicializando a Lista
void inicializarLista(LISTA *l)
{
    l->inicio = NULL;

    carregarLista(l);
}
//Definindo o tamanho da Lista
int tamanhoLista(LISTA *l)
{
    PONT end = l->inicio;
    int taml = 0;
    while (end != NULL)
    {
        taml++;
        end = end->prox;
    }
    return taml;
}
//Exibindo a Lista
void exibirLista(LISTA *l)
{
    int i;
    PONT end = l->inicio;
    system("cls");
    printf("Lista:");
    while (end != NULL)
    {
        printf("\n%d - ", end->reg.chave);

        for (i = 0; i < strlen(end->reg.nomeUsuario); i++)
        {
            if (end->reg.nomeUsuario[i] == '_')
            {
                end->reg.nomeUsuario[i] = ' ';
            }
            printf("%c", end->reg.nomeUsuario[i]);
        }
        printf(" - %s\n", end->reg.prontuario);
        end = end->prox;
    }
    printf("\n");
}
//Busca Sequencial Ordenada - Nomes
PONT buscaSeqOrd(LISTA *l, char *ch)
{
    PONT pos = l->inicio;
    while (pos != NULL && strcmp(pos->reg.nomeUsuario, ch) != 1)
        pos = pos->prox;
    if (pos != NULL && strcmp(pos->reg.nomeUsuario, ch) == 0)
        return pos;
    return NULL;
}
//Busca Sequencial Ordenada - Numero
PONT buscaSeqOrdNum(LISTA *l, TIPOCHAVE tch)
{
    PONT pos = l->inicio;
    while (pos != NULL && pos->reg.chave < tch)
        pos = pos->prox;
    if (pos != NULL && pos->reg.chave == tch)
        return pos;
    return NULL;
}
//Função booleana para inserir um Novo Elemento na Lista Ordenada
bool inserirElemListaOrd(LISTA *l, REGISTRO reg)
{
    TIPOCHAVE tch = reg.chave;
    char *ch = reg.nomeUsuario;
    PONT ant, i, j;
    i = buscaSequencialExc(l, tch, &ant);
    j = buscaSequencialOrg(l, ch, &ant);
    if (i != NULL)
        return false;
    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg = reg;
    if (ant == NULL)
    {
        i->prox = l->inicio;
        l->inicio = i;
    }
    else
    {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}
//Executando a Busca Sequencial para Excluir um Elemento
PONT buscaSequencialExc(LISTA *l, TIPOCHAVE tch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (atual->reg.chave < tch))
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == tch))
        return atual;
    return NULL;
}
//Executando a Busca Sequencial para Ordenar
PONT buscaSequencialOrg(LISTA *l, char *ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && strcmp(atual->reg.nomeUsuario, ch) != 1)
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && strcmp(atual->reg.nomeUsuario, ch) == 0)
        return atual;
    return NULL;
}
//Função booleana para excluir um Elemento especifico da Lista Ordenada
bool excluirElemLista(LISTA *l, TIPOCHAVE tch)
{
    PONT ant, i;
    i = buscaSequencialExc(l, tch, &ant);
    if (i == NULL)
        return false;
    if (ant == NULL)
        l->inicio = i->prox;
    else
        ant->prox = i->prox;
    free(i);
    return true;
}
//Reinicializar a Lista
void reinicializarLista(LISTA *l)
{
    PONT apagar;
    PONT end = l->inicio;
    while (end != NULL)
    {
        apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}
//Armazena o Elemento que a pessoa deseja buscar
TIPOCHAVE oqueBuscar()
{
    TIPOCHAVE nbusca;
    printf("\nDigite o numero do elemento para busca: ");
    fflush(stdin);
    scanf("%d", &nbusca);
    return nbusca;
}
//Pesquisa o elemento desejado
void pesquisaLista(LISTA *l)
{
    PONT ender;
    TIPOCHAVE elem;
    elem = oqueBuscar();
    ender = buscaSeqOrdNum(l, elem);
    if (ender == NULL)
        printf("\nChave [%d] nao encontrada!", elem);
    else
        printf("\nChave [%d] encontrada em [%p]", elem, ender);
}
//Registrando novos dados na Lista
REGISTRO oqueInserir()
{
    REGISTRO r;
    printf("\nTIPOCHAVE            : ");
    fflush(stdin);
    scanf("%d", &r.chave);
    printf("\nNOME DO USUARIO      : ");
    fflush(stdin);
    gets(r.nomeUsuario);
    printf("\nPRONTUARIO DO USUARIO: ");
    fflush(stdin);
    gets(r.prontuario);
    return r;
}
//Insere elementos na Lista
void insereNaLista(LISTA *l)
{
    REGISTRO elem;
    elem = oqueInserir();
    if (inserirElemListaOrd(l, elem) == true)
        printf("\nChave [%d] inserida com sucesso.", elem.chave);
    else
        printf("\nChave [%d] NAO inserida!", elem.chave);
}
//Armazena qual elemento o usuario deseja excluir
TIPOCHAVE oqueExcluir()
{
    TIPOCHAVE nexclui;
    printf("\nDigite o elemento para excluir: ");
    fflush(stdin);
    scanf("%d", &nexclui);
    return nexclui;
}
//Realiza a exclusao do elemento desejado da Lista
void excluiDaLista(LISTA *l)
{
    TIPOCHAVE chave;
    chave = oqueExcluir();
    if (excluirElemLista(l, chave) == true)
        printf("\nChave [%d] excluida com sucesso.", chave);
    else
        printf("\nChave [%d] NAO excluida!", chave);
}
// Carrega o arquivo dat LISTA
void carregarLista(LISTA *l)
{
    char ch[100];
    char *linha;
    int i = 0, j;
    REGISTRO r;

    arq = fopen("usuarios.dat", "r");

    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(ch, 100, arq) != NULL)
    {
        linha = strtok(ch, " ");
        printf(" ", linha);
        while (linha != NULL)
        {
            if (i == 0)
            {
                r.chave = atoi(linha);
            }
            if (i == 1)
            {
                strcpy(r.nomeUsuario, linha);
            }
            if (i == 2)
            {
                strncpy(r.prontuario, linha, strlen(linha) - 1);
            }
            linha = strtok(NULL, " ");
            i++;
        }
        i = 0;
        inserirElemListaOrd(l, r);
    }

    fclose(arq);
}
//Menu Gerenciar Usuarios
void gerenciarUsuarios()
{
    LISTA lis;
    char opc;

    do
    {
        system("color f5");
        system("cls");
        printf("\n       GERENCIAR USÚARIOS:  ");
        printf("\n---------------------------------------");
        printf("\n 1. Inicializar Lista ligada      ");
        printf("\n 2. Exibir tamanho da Lista ligada");
        printf("\n 3. Exibir Lista ligada           ");
        printf("\n 4. Fazer busca na Lista ligada   ");
        printf("\n 5. Inserir elemento na Lista ligada ");
        printf("\n 6. Excluir elemento da Lista ligada ");
        printf("\n 7. Reinicializa Lista ligada ");
        printf("\n 0. Menu Principal");
        printf("\n---------------------------------------");
        printf("\n    Escolha: ");
        fflush(stdin);
        opc = getche();
        printf("\n");

        switch (opc)
        {
        case '1':
            inicializarLista(&lis);
            break;
        case '2':
            system("cls");
            printf("\n    Tamanho da Lista = %d", tamanhoLista(&lis));
            break;
        case '3':
            system("cls");
            exibirLista(&lis);
            break;
        case '4':
            system("cls");
            pesquisaLista(&lis);
            break;
        case '5':
            system("cls");
            insereNaLista(&lis);
            break;
        case '6':
            system("cls");
            excluiDaLista(&lis);
            break;
        case '7':
            reinicializarLista(&lis);
            break;
        case '0':
            main();
            break;
        default:
            printf("\n\n    Opção Invalida...");
            break;
        }
        printf("\n    Novo teste? [n/N = NEGATIVO]");
        fflush(stdin);
        opc = getche();
    } while (opc != 'N' && opc != 'n');
}
