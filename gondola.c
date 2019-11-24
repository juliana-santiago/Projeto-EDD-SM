//Biblioteca
#include "gondola.h"

//Arquivo como Variavel Global
FILE *arq2;

//Tirar Item da Prateleira Escolhida
void excluirDaGondola(GONDOLA *g, PILHA *car)
{
    int num = 0;
    system("cls");

    printf("    Deseja tirar um  item de qual prateleira? ");
    fflush(stdin);
    scanf("%d", &num);
    if (num > 0 && num < 10)
    {
        PILHA *p = &g->prateleira[num - 1];
        if (tamanhoPilha(p) == 0)
        {
            printf("    A prateleira está vazia!");
        }
        else
        {
            excluirDaPilha(p, car);
        }
    }
    else
    {
        printf("    A prateleira não existe! Digite um numero de 1 a 10...");
    }
}
//Inserir Itens na Prateleira Escolhida
void insereNaGondola(GONDOLA *g)
{
    int num = 0;
    system("cls");
    printf("    Deseja inserir o item em qual prateleira? ");
    fflush(stdin);
    scanf("%d", &num);
    if (num > 0 && num < 10)
    {
        PILHA *p = &g->prateleira[num - 1];
        if (tamanhoPilha(p) == 5)
        {
            printf("    A prateleira está cheia!");
        }
        else
        {
            insereNaPilha(p);
        }
    }
    else
    {
        printf("    A prateleira não existe!  Digite um numero de 1 a 10...");
    }
}
//Exibir Quantidade de Itens em cada Prateleira
void exibirQuantGondola(GONDOLA *g)
{
    system("cls");
    int i, quant = 0, quantTotal = 0;
    for (i = 0; i < 10; i++)
    {
        quant = tamanhoPilha(&g->prateleira[i]);
        quantTotal += quant;
        printf("\n    Quantidade de produtos na prateleira %d: %d", i + 1, tamanhoPilha(&g->prateleira[i]));
    }
    printf("\n    Total de itens: %d", quantTotal);
}

//Inicializando a Pilha
void inicializarPilha(PILHA *p)
{
    p->topo = NULL;
}
//Inicializar gondolas
void inicializarGondola(GONDOLA *g)
{

    int i;

    for (i = 0; i < 10; i++)
    {
        inicializarPilha(&g->prateleira[i]);
    }
    carregarGondola(g);
}
//Inicializa as pilhas da gondola
void inicializarProg(GONDOLA *g)
{

    int i;

    for (i = 0; i < 10; i++)
    {
        inicializarPilha(&g->prateleira[i]);
    }
}
//Definindo o tamanho de cada Prateleira
int tamanhoPilha(PILHA *p)
{
    POINT end = p->topo;
    int tamp = 0;
    while (end != NULL)
    {
        tamp++;
        end = end->PROX;
    }
    return tamp;
}
//Verificar se a Gondola esta Vazia
bool estaVaziaGondola(GONDOLA *g)
{
    int i, tam;
    bool retorno = false;

    for (i = 0; i < 10; i++)
    {
        PILHA *p = &g->prateleira[i];
        tam = tamanhoPilha(p);
        if (tam != 0)
        {
            retorno = true;
        }
    }
    return retorno;
}
//Verificando se a Pilha esta vazia
bool estaVaziaPilha(PILHA *p)
{
    if (p->topo == NULL)
        return true;
    return false;
}
//ExibirGondola
void exibirGondola(GONDOLA *g)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("\n    Prateleira %d:\n", i + 1);
        exibirPilha(&g->prateleira[i]);
    }
}
//Exibindo a Pilha
void exibirPilha(PILHA *p)
{
    int i, j, k;
    POINT end = p->topo;

    while (end != NULL)
    {
        printf("\n    %d - ", end->regprod.chave);

        for (j = 0; j < strlen(end->regprod.NOMEPROD); j++)
        {
            if (end->regprod.NOMEPROD[j] == '_')
            {
                end->regprod.NOMEPROD[j] = ' ';
            }
            printf("%c", end->regprod.NOMEPROD[j]);
        }
        printf(" - ");
        for (i = 0; i < strlen(end->regprod.DESC); i++)
        {
            if (end->regprod.DESC[i] == '_')
            {
                end->regprod.DESC[i] = ' ';
            }
            printf("%c", end->regprod.DESC[i]);
        }

        printf(" - %s - %s\n", end->regprod.PESO, end->regprod.PRECO);

        end = end->PROX;
    }
}
//Função booleana para inserir um Novo Elemento na Pilha
bool inserirElemPilha(PILHA *p, REGISTROPROD regprod)
{
    POINT novo = (POINT)malloc(sizeof(ELEMENTOPROD));
    novo->regprod = regprod;
    novo->PROX = p->topo;
    p->topo = novo;
    return true;
}
//Função booleana para excluir um Elemento especifico da Pilha
bool inserirNoCarrinho(PILHA *p, PILHA *car, REGISTROPROD *regprod)
{
    if (p->topo == NULL)
        return false;
    *regprod = p->topo->regprod;
    inserirElemPilha(car, p->topo->regprod);
    POINT apagar = p->topo;
    p->topo = apagar->PROX;
    free(apagar);
    return true;
}
//Exibir itens no Carrinho
void exibirCarrinho(PILHA *p)
{
    printf("\n    Itens no Carrinho:\n");
    exibirPilha(p);
    printf("\n    Total de Itens no Carrinho: %d", tamanhoPilha(p));
}
//Função booleana para excluir um Elemento especifico da Pilha
bool excluirElemPilha(PILHA *p, REGISTROPROD *regprod)
{
    if (p->topo == NULL)
        return false;
    *regprod = p->topo->regprod;
    POINT apagar = p->topo;
    p->topo = apagar->PROX;
    free(apagar);
    return true;
}
//Reinicializar a Pilha
void reinicializarPilha(PILHA *p)
{
    POINT apagar;
    POINT posicao = p->topo;
    while (posicao != NULL)
    {
        apagar = posicao;
        posicao = posicao->PROX;
        free(apagar);
    }
    p->topo = NULL;
}
//Reinicializar Gondola
void reinicializarGondola(GONDOLA *g)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        reinicializarPilha(&g->prateleira[i]);
    }
}
//Reinicializar Carrinho
void reinicializarCarrinho(PILHA *p)
{
    reinicializarPilha(p);
}
//Registrando novos dados na Pilha
REGISTROPROD oqueInserirPilha()
{
    REGISTROPROD rp;
    printf("\n    TIPOCHAVE(PRODUTO)        : ");
    fflush(stdin);
    scanf("%d", &rp.chave);
    printf("\n    NOME DO PRODUTO  : ");
    fflush(stdin);
    gets(rp.NOMEPROD);
    printf("\n    DESCRIÇÃO : ");
    fflush(stdin);
    gets(rp.DESC);
    printf("\n    PESO : ");
    fflush(stdin);
    gets(rp.PESO);
    printf("\n    PREÇO : ");
    fflush(stdin);
    gets(rp.PRECO);
    return rp;
}
//Inserindo elemento na Pilha
void insereNaPilha(PILHA *p)
{
    REGISTROPROD elem;
    elem = oqueInserirPilha();
    if (inserirElemPilha(p, elem) == true)
        printf("\n    Chave [%d] inserida com sucesso.", elem.chave);
    else
        printf("\n    Chave [%d] NAO inserida!", elem.chave);
}
//Realiza a exclusao do elemento desejado da Pilha
void excluirDaPilha(PILHA *p, PILHA *car)
{
    REGISTROPROD regExcluido;
    if (inserirNoCarrinho(p, car, &regExcluido) == true)
        printf("\n    Produto [%d][%s][%s][%s][%s] inserido no carrinho com sucesso.", regExcluido.chave, regExcluido.NOMEPROD, regExcluido.DESC, regExcluido.PESO, regExcluido.PRECO);
    else
        printf("\n    Nao foi possivel inserir o item  [%d][%s][%s][%s][%s] no carrinho.", regExcluido.chave, regExcluido.NOMEPROD, regExcluido.DESC, regExcluido.PESO, regExcluido.PRECO);
}
// Carrega o arquivo dat
void carregarGondola(GONDOLA *g)
{

    char ch1[100];
    char *linha1;
    int i = 0, j = 0, quant = 0, prat = 0;
    PILHA *p;
    p = &g->prateleira[i];
    REGISTROPROD rp;

    arq2 = fopen("produtos.dat", "r");

    if (arq2 == NULL)
    {
        perror("    Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(ch1, 100, arq2) != NULL)
    {
        linha1 = strtok(ch1, " ");
        printf(" ", linha1);
        while (linha1 != NULL)
        {
            if (j == 0)
            {
                rp.chave = atoi(linha1);
            }
            if (j == 1)
            {
                strcpy(rp.NOMEPROD, linha1);
            }
            if (j == 2)
            {
                strcpy(rp.DESC, linha1);
            }
            if (j == 3)
            {
                strcpy(rp.PESO, linha1);
            }
            if (j == 4)
            {
                strcpy(rp.PRECO, linha1);
            }
            linha1 = strtok(NULL, " ");
            j++;
        }
        j = 0;
        inserirElemPilha(p, rp);
        quant++;
        if (quant % 5 == 0)
        {
            i++;
            p = &g->prateleira[i];
        }
    }

    fclose(arq2);
}
//Menu Abastecer Gondolas
void abastecerGondolas()
{
    PILHA car;
    GONDOLA gon;
    char opc;

    inicializarProg(&gon);
    inicializarPilha(&car);
    inicializarGondola(&gon);

    do
    {
        system("cls");
        system("color 3F");
        printf("\n       ABASTECER GÔNDOLAS    ");
        printf("\n---------------------------------------");
        printf("\n 1. Exibir Quantidade de Itens por Prateleira    ");
        printf("\n 2. Exibir Itens por Prateleira       ");
        printf("\n 3. Verificar se a pilha esta vazia ");
        printf("\n 4. Inserir elemento na Pilha");
        printf("\n 5. Retirar elemento da Pilha e Inseri-lo no Carrinho");
        printf("\n 6. Visualizar Itens no Carrinho");
        printf("\n 7. Reinicializa Pilha");
        printf("\n 8. Salvar Alteraçoes no Arquivo");
        printf("\n 0. Menu Principal");
        printf("\n---------------------------------------");
        printf("\n    Escolha: ");
        fflush(stdin);
        opc = getche();

        switch (opc)
        {
        case '1':
            system("cls");
            exibirQuantGondola(&gon);
            break;
        case '2':
            system("cls");
            exibirGondola(&gon);
            break;
        case '3':
            system("cls");
            if (estaVaziaGondola(&gon) == false)
                printf("\n\n    Gondola SEM itens");
            else
                printf("\n\n    Gondola COM Itens");
            break;
        case '4':
            system("cls");
            insereNaGondola(&gon);
            break;
        case '5':
            system("cls");
            excluirDaGondola(&gon, &car);
            break;
        case '6':
            system("cls");
            exibirCarrinho(&car);
            break;
        case '7':
            reinicializarGondola(&gon);
            reinicializarCarrinho(&car);
            break;
        case '8':
            salvaArquivo(&gon);
        case '0':
            menuPrincipal();
            break;
        default:
            printf("\n\n    Opção Inválida...");
            break;
        }

        printf("\n\n    Novo teste? [n/N = NEGATIVO]");
        fflush(stdin);
        opc = getche();
    } while (opc != 'n' && opc != 'N');
}
