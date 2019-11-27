#include "common.h"
#include "gondola.h"

//Menu Abastecer Gondolas
void abastecerGondolas(GONDOLA *gon)
{
	PILHA p;
	inicializarPilha(&p);
    char opc;
    do
    {
        system("cls");
        system("color 3F");
        printf("\n\t__________________________________________________________");
        printf("\n\t|                ABASTECER GONDOLAS                      |");
        printf("\n\t|========================================================|");
        printf("\n\t| 1. Exibir Quantidade de Itens por Prateleira           |");
        printf("\n\t| 2. Exibir Itens por Prateleira                         |");
        printf("\n\t| 3. Verificar se a pilha esta vazia                     |");
        printf("\n\t| 4. Inserir elemento na Pilha                           |");
        printf("\n\t| 5. Retirar elemento da Pilha e Inseri-lo no Carrinho   |");
        printf("\n\t| 6. Visualizar Itens no Carrinho                        |");
        printf("\n\t| 7. Reinicializa Gondola                                |");
        printf("\n\t| 8. Salvar Alterações no Arquivo                        |");
        printf("\n\t| 0. Menu Principal                                      |");
        printf("\n\t|________________________________________________________|");
        printf("\n\t Escolha: ");
        fflush(stdin);
        opc = getche();

        switch (opc)
        {
        case '1':
        	system("cls");
        	exibirQuantGondola(gon);
            break;
        case '2':
        	system("cls");
        	exibirGondola(gon);
            break;
        case '3':
        	system("cls");
        	gondolaVazia(gon);
            break;
        case '4':
        	system("cls");
        	insereNaGondola(gon);
            break;
        case '5':
        	system("cls");
        	excluirDaGondola(gon, &p);
            break;
        case '6':
        	system("cls");
        	exibirCarrinho(&p);
            break;
        case '7':
        	system("cls");
        	reinicializarGondola(gon);
            break;
        case '8':
        	system("cls");
        	salvarGondola(gon);
        	break;
        case '0':
        	menuPrincipal();
            break;
        default:
            printf("\n\n\tOpção Inválida...");
            break;
        }

        printf("\n\n\tNovo teste? [n/N = NEGATIVO]");
        fflush(stdin);
        opc = getche();
    } while (opc != 'n' && opc != 'N');
}

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

void inicializarPilha(PILHA *p)
{
    p->topo = NULL;
}
void inicializarGondola(GONDOLA *g)
{
	int i, quantPrat;
	quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
	for(i = 0; i < quantPrat; i++)
	{
		inicializarPilha(&g->prateleira[i]);
	}
}

void gondolaVazia(GONDOLA *g)
{
	int i, quantPrat;
	bool item = false;
	quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
	for(i = 0; i < quantPrat; i++)
	{
		if(pilhaVazia(&g->prateleira[i]) != true){
			item = true;
		}
	}
	if(item != true)
	{
		printf("\n\n\tGôndola SEM itens!");		
	}
	else
	{
		printf("\n\n\tGôndola COM itens!");
	}
}
bool pilhaVazia(PILHA *p)
{
	bool i = false;
	if(tamanhoPilha(p) == 0){
		i = true;
	}
	return i;
}
//Registrando novos dados na Pilha
PRODUTO oqueInserirPilha()
{
    PRODUTO rp;
    printf("\n\tNOME DO PRODUTO  : ");
    fflush(stdin);
    gets(rp.NOMEPROD);
    printf("\n\tDESCRIÇÃO : ");
    fflush(stdin);
    gets(rp.DESC);
    printf("\n\tPESO : ");
    fflush(stdin);
    gets(rp.PESO);
    printf("\n\tPREÇO : ");
    fflush(stdin);
    gets(rp.PRECO);
    return rp;
}
void insereNaPilha(PILHA *p)
{
    PRODUTO elem;
    elem = oqueInserirPilha();
    if (inserirElemPilha(p, elem) == true)
        printf("\n\tProduto [%s] inserida com sucesso.", elem.NOMEPROD);
    else
        printf("\n\tERRO ao inserir o produto [%s]", elem.NOMEPROD);
}
//Inserir Itens na Prateleira Escolhida
void insereNaGondola(GONDOLA *g)
{
    int num = 0;
    system("cls");
    printf("\n\tDeseja inserir o item em qual prateleira? ");
    fflush(stdin);
    scanf("%d", &num);
    if (num > 0 && num <= 10)
    {
        PILHA *p = &g->prateleira[num - 1];
        if (tamanhoPilha(p) >= 5)
        {
            printf("\n\tA prateleira está cheia!");
        }
        else
        {
            insereNaPilha(p);
        }
    }
    else
    {
        printf("\n\tA prateleira não existe!  Digite um número de 1 a 10...");
    }
}

bool inserirElemPilha(PILHA *p, PRODUTO regprod)
{
    POINT novo = (POINT)malloc(sizeof(ELEMPROD));
    novo->regprod = regprod;
    novo->PROX = p->topo;
    p->topo = novo;
    return true;
}

//Exibir Quantidade de Itens em cada Prateleira
void exibirQuantGondola(GONDOLA *g)
{
    system("cls");
    int i, quant = 0, quantTotal = 0, quantPrat;
    quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
    for (i = 0; i < quantPrat; i++)
    {
        quant = tamanhoPilha(&g->prateleira[i]);
        quantTotal += quant;
        printf("\n\tQuantidade de produtos na Prateleira[%02d]: %d", i + 1, tamanhoPilha(&g->prateleira[i]));
    }
    printf("\n\tTotal de itens: %d", quantTotal);
}
//Tirar Item da Prateleira Escolhida
void excluirDaGondola(GONDOLA *g, PILHA *car)
{
    int num = 0;
    system("cls");

    printf("\n\tDeseja tirar um  item de qual prateleira? ");
    fflush(stdin);
    scanf("%d", &num);
    if (num > 0 && num < 10)
    {
        PILHA *p = &g->prateleira[num - 1];
        if (tamanhoPilha(p) == 0)
        {
            printf("\n\tA prateleira está vazia!");
        }
        else
        {
            excluirDaPilha(p, car);
        }
    }
    else
    {
        printf("\n\tA prateleira não existe! Digite um número de 1 a 10...");
    }
}

//Realiza a exclusao do elemento desejado da Pilha
void excluirDaPilha(PILHA *p, PILHA *car)
{
    PRODUTO regExcluido;
    if (inserirNoCarrinho(p, car, &regExcluido) == true)
        printf("\n\tProduto [%s][%s][%s][%s] inserido no carrinho com sucesso.",  regExcluido.NOMEPROD, regExcluido.DESC, regExcluido.PESO, regExcluido.PRECO);
    else
        printf("\n\tNão foi possivel inserir o item  [%s][%s][%s][%s] no carrinho.", regExcluido.NOMEPROD, regExcluido.DESC, regExcluido.PESO, regExcluido.PRECO);
}
//Função booleana para excluir um Elemento especifico da Pilha
bool inserirNoCarrinho(PILHA *p, PILHA *car, PRODUTO *regprod)
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
//Função booleana para excluir um Elemento especifico da Pilha
bool excluirElemPilha(PILHA *p, PRODUTO *regprod)
{
    if (p->topo == NULL)
        return false;
    *regprod = p->topo->regprod;
    POINT apagar = p->topo;
    p->topo = apagar->PROX;
    free(apagar);
    return true;
}
//Exibindo a Pilha
void exibirPilha(PILHA *p)
{
    int cont = 0;
    POINT end = p->topo;
    while (end != NULL)
    {	
    	cont++;
    	printf("\n\t%02d - %s - %s - %s - %s",cont, end->regprod.NOMEPROD, end->regprod.DESC, end->regprod.PESO, end->regprod.PRECO);
        end = end->PROX;
    }
    printf("\n");
}
//ExibirGondola
void exibirGondola(GONDOLA *g)
{
    int i, quantPrat;
    quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
    for (i = 0; i < quantPrat; i++)
    {
        printf("\n\tPrateleira[%02d]:\n", i + 1);
        exibirPilha(&g->prateleira[i]);
    }
}
//Exibir itens no Carrinho
void exibirCarrinho(PILHA *p)
{
    printf("\n\tItens no Carrinho:\n");
    exibirPilha(p);
    printf("\n\n\tTotal de itens no Carrinho: %d", tamanhoPilha(p));
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
    int i, quantPrat;
    quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
    for (i = 0; i < quantPrat; i++)
    {
        reinicializarPilha(&g->prateleira[i]);
    }
    printf("\n\tGôndula reinicializada");
}

void salvarGondola(GONDOLA *g)
{
	int i, quantPrat;
	char buffer[25];
    quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
    for (i = 0; i < quantPrat; i++)
    {
        snprintf(buffer, 25, "data/prateleira%d.dat", i+1);
       	salvarArquivoProd(&g->prateleira[i], buffer);
    }
}

PRODUTO * convertPilhaToArray(PILHA *l)
{
	PRODUTO *vet;
    vet = (PRODUTO *)malloc(tamanhoPilha(l) * sizeof(PRODUTO));
    int taml = 0;
    POINT end = l->topo;
    while (end != NULL)
    {
        vet[taml] = end->regprod;
        taml++;
        end = end->PROX;
    }
    return vet;
}

void salvarArquivoProd(PILHA * p, char * fileName)
{
	FILE * arq;
	arq = fopen(fileName, "w");
	PRODUTO * vet = convertPilhaToArray(p);
	int flag_legrava;
    flag_legrava = fwrite(vet, tamanhoPilha(p) * sizeof(PRODUTO), 1, arq);
    if (flag_legrava != 1 && tamanhoPilha(p) != 0)
    {
        system("mode con:cols=75 lines=10");
        system("color 0c");
        printf("\n\n\tERRO DE GRAVAÇÃO NO ARQUIVO %s", fileName);
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    else
        printf("\n\n\tARQUIVO %s SALVO COM SUCESSO\n", fileName);
    fclose(arq);
}

PRODUTO * lerArquivoPilha(char * file)
{
	FILE *arq;
    int nroDeRegistros, flag_legrava;
    arq = fopen(file, "r");
    if (arq == NULL)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tARQUIVO %s INEXISTENTE!\n\n", file);
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    fseek(arq, 0L, SEEK_END);
    
    nroDeRegistros = ftell(arq) / sizeof(PRODUTO);

    PRODUTO *vet;
    
	vet = (PRODUTO *)malloc(nroDeRegistros * sizeof(PRODUTO));

    if (vet == NULL)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tMalloc devolveu NULL!\n");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
	
    fseek(arq, 0, SEEK_SET);

	flag_legrava = fread(vet, nroDeRegistros * sizeof(PRODUTO), 1, arq);
    
	if (flag_legrava != 1)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tERRO DE LEITURA DO ARQUIVO %s", file);
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }

    fclose(arq);
    return vet;
}

void carregaPilha(PILHA *l, char * file)
{
    PRODUTO *arq = lerArquivoPilha(file);
    int i = 0;
    for (; i < quantRegistroProduto(file); i++)
    {
        inserirElemPilha(l, arq[i]);
    }
}

void carregaGondula(GONDOLA * g)
{
	int i, quantPrat;
	char buffer[25];
    quantPrat = sizeof(g->prateleira) / sizeof(g->prateleira[0]);
    for (i = 0; i < quantPrat; i++)
    {
        snprintf(buffer, 25, "data/prateleira%d.dat", i+1);
        if(quantRegistroProduto(buffer) > 0){
			carregaPilha(&g->prateleira[i], buffer);	
		}
        
    }
}

int quantRegistroProduto(char * file)
{
    FILE *arq;
    int nroDeRegistros, flag_legrava;
    arq = fopen(file, "r");

    if (arq == NULL)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tARQUIVO %s INEXISTENTE!\n\n", file);
    }

    fseek(arq, 0L, SEEK_END);
    int size = ftell(arq);
    nroDeRegistros = ftell(arq) / sizeof(PRODUTO);
    return nroDeRegistros;
}

void produtoDefault(GONDOLA *g)
{
    PRODUTO tab[30] = {
		{"MILHO", "CEREAL", "1Kg", "R$8,00"},                        //00
	    {"ARROZ", "GRAO", "5Kg", "R$15,00"},                         //01
	    {"FEIJAO CARIOCA", "GRAO", "1Kg", "R$6,50"},                 //02
	    {"OLEO", "GORDURA VEGETAL", "900g", "R$3,80"},               //03
	    {"CAFE EM GRAOS", "GRAO", "1Kg", "R$40,00"},                 //04
	    {"BOLACHA RECHEADA", "BOLACHA", "140g", "R$1,70"},           //05
	    {"BISCOITO DE POLVILHO", "BISCOITO", "50g", "R$5,00"},       //06
	    {"BISCOITO BAUDUCCO", "BISCOITO", "400g", "R$15,00"},        //07
	    {"ACHOCOLATADO", "CHOCOLATE EM PO", "800g", "R$12,00"},      //08
	    {"TORRADA", "PAO TORRADO", "15g", "R$24,90"},                //09
	    {"GELATINA EM PÓ", "SOBREMESA", "20g", "R$1,00"},            //10
	    {"FERMENTO", "LEVEDURA", "10g", "R$1,50"},                   //11
	    {"SAL", "TEMPERO", "1Kg", "R$2,40"},                         //12
	    {"MACARRAO INSTANTANEO", "MASSA", "85g", "R$1,50"},          //13
	    {"PACOTE DE MACARRAO SPAGUETTI", "MASSA", "500g", "R$2,00"}, //14
	    {"MOLHO DE TOMATE", "TEMPERO", "340g", "R$1,40"},            //15
	    {"LATA DE SARDINHA", "ENLATADO", "125g", "R$3,60"},          //16
	    {"LATA DE ERVILHA", "ENLATADO", "200g", "R$2,50"},           //17
	    {"LATA DE MILHO VERDE", "ENLATADO", "285g", "R$13,50"},      //18
	    {"FARINHA DE TRIGO", "GRAO", "1Kg", "R$4,60"},               //19
	    {"FARINHA LACTEA", "CEREAL", "400g", "R$12,30"},             //20
	    {"GRAO DE BICO", "GRAO", "500g", "R$14,00"},                 //21
	    {"SUCRILHOS", "CEREAL", "730g", "R$24,00"},                  //22
	    {"LEITE", "LIQUIDO", "1L", "R$3,00"},                        //23
	    {"SUCO DE SAQUINHO", "SUCO EM PÓ", "8g", "R$1,00"},          //24
	    {"GELEIA", "SOBREMESA", "320g", "R$16,50"},                  //25
	    {"CREME DE LEITE", "SOBREMESA", "200g", "R$3,20"},           //26
	    {"LEITE CONDENSADO", "SOBREMESA", "270g", "R$3,50"},         //27
	    {"DANONE", "SOBREMESA", "480g", "R$8,00"},                   //28
	    {"SORVETE", "SOBREMESA 1", "5L", "R$20,00"},                 //29
	};
	
	PILHA *p;
	int i, j = 0;
	for (i = 1; i < 31; i++)
	{
	    p = &g->prateleira[j];
	    inserirElemPilha(p, tab[i-1]);
	    if (i % 5 == 0)
	    {
	        j++;
	    }
	}

}
