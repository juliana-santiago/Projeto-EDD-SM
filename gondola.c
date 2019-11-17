//Biblioteca
#include "gondola.h"

//Arquivo como Variavel Global
FILE *arq2;

//Inicializando a Pilha
void inicializarPilha (PILHA *p)
{
  p->topo = NULL;
}
//Inicializar gondolas
/*void inicializarGondolas(GONDOLA *g){
	
	int i;
	
	for(i=0;i<10; i++){
		inicializarPilha(&g->prateleira[i]);
	}	
}*/
//Definindo o tamanho de cada Prateleira
int tamanhoPilha (PILHA *p) 
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
//Verificando se a Pilha esta vazia
bool estaVaziaPilha(PILHA *p) 
{
   if (p->topo == NULL) 
      return true;  
   return false;
}
//ExibirGondola
void exibirGondola (GONDOLA *g){
	
	int i;
	
	for(i=0; i<10;i++){
		exibirPilha(g->prateleira);
	}	
}
//Exibindo a Pilha
void exibirPilha (PILHA *p) 
{  
   int j;
   POINT end = p->topo;  
   system ("cls");
   printf("Pilha:");  
   while (end != NULL) 
   {	
   		printf("\n%d - ", end->regprod.chave); 
   		
   		for (j=0;j<strlen(end->regprod.NOMEPROD); j++){
		if (end->regprod.NOMEPROD[j]=='_'){
			end->regprod.NOMEPROD[j]=' ';
		}
		printf("%c", end->regprod.NOMEPROD[j]);
		}
		printf(" - %s\n", end->regprod.DATAVENC); 
		end = end->PROX;
	}
}
//Função booleana para inserir um Novo Elemento na Pilha
bool inserirElemPilha(PILHA *p, REGISTROPROD regprod) 
{  
   POINT novo  = (POINT) malloc(sizeof(ELEMENTOPROD));  
   novo->regprod  = regprod;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}
//Função booleana para excluir um Elemento especifico da Pilha
bool excluirElemPilha(PILHA *p, REGISTROPROD *regprod) 
{  
   if ( p->topo == NULL) 
      return false;
   *regprod        = p->topo->regprod;  
   POINT apagar = p->topo;
   p->topo     = apagar->PROX; 
   free(apagar);
   return true;
}
//Reinicializar a Pilha
void reinicializarPilha (PILHA *p) 
{  
   POINT apagar;
   POINT posicao = p->topo;  
   while (posicao != NULL) 
   {
      apagar  = posicao;  
      posicao = posicao->PROX;  
      free(apagar);
   }
   p->topo = NULL;
}
//Registrando novos dados na Pilha
REGISTROPROD oqueInserirPilha ()
{	REGISTROPROD rp;
	printf ("\n    TIPOCHAVE(PRODUTO)        : "); fflush (stdin); scanf("%d", &rp.chave);
	printf ("\n    NOME DO PRODUTO  : "); fflush (stdin); gets(rp.NOMEPROD);
	printf ("\n    DATA DE VALIDADE : "); fflush (stdin); gets(rp.DATAVENC);
	return rp;
}
//Inserindo elemento na Pilha
void insereNaPilha (PILHA *p)
{
	REGISTROPROD	elem;
	elem  = oqueInserirPilha();
	if ( inserirElemPilha(p, elem) == true )
	   printf ("\nChave [%d] inserida com sucesso.", elem.chave );
	else
	   printf ("\nChave [%d] NAO inserida!", elem.chave );
}
//Realiza a exclusao do elemento desejado da Pilha
void excluirDaPilha (PILHA *p)
{	REGISTROPROD regExcluido;
 	if ( excluirElemPilha(p, &regExcluido) == true )
	   printf ("\nRegistro do Produto: [%d][%s][%s]excluido com sucesso.", regExcluido.chave, regExcluido.NOMEPROD, regExcluido.DATAVENC );
	else
	   printf ("\nNao foi possivel excluir o registro.");
}
// Carrega o arquivo dat PILHA
void carregarPilha(PILHA *p)
{
	char ch1[150];
	char *linha1;
	int j = 0;
	REGISTROPROD rp;
	
	arq2 = fopen("produtos.dat", "r");

	if (arq2 == NULL)
	{
		perror("Erro ao abrir o arquivo\n");
		exit(EXIT_FAILURE);
	}	
	
	while (fgets(ch1,150,arq2) != NULL){
		linha1 = strtok(ch1," ");
		printf(" ", linha1);
		while(linha1 != NULL){
			if(j==0){
				rp.chave = atoi(linha1);
			}
			if(j==1){
			strcpy(rp.NOMEPROD, linha1);
			}
			if(j==2){
			strncpy(rp.DATAVENC,linha1,strlen(linha1)-1);
			}
			linha1 = strtok(NULL, " ");
			j++;
		}
		j = 0;
		inserirElemPilha(p, rp);
	}
	
	fclose(arq2);
}
//Menu Abastecer Gondolas
void abastecerGondolas()
{
   PILHA pil;
   GONDOLA gon; 
   char opc;
   
   do
   { 	system ("color f5");
   		system ("cls");
   		printf ("\n       ABASTECER GÔNDOLAS    ");
   		printf ("\n---------------------------------------");
   		printf ("\n 1. Inicializar Gondola               ");
   		printf ("\n 2. Exibir tamanho da Pilha         ");
   		printf ("\n 3. Exibir Pilha                    ");
   		printf ("\n 4. Verificar se a pilha esta vazia ");
   		printf ("\n 5. Inserir Carrinho");
     	printf ("\n 6. Carregar Carrinho");
	    printf ("\n 7. Inserir elemento na Pilha");
   		printf ("\n 8. Excluir elemento da Pilha");
   		printf ("\n 9. Reinicializa Pilha");
   		printf ("\n 10. Carregar Pilha");
   		printf ("\n 0. Menu Principal");
   		printf ("\n---------------------------------------");
   		printf ("\n    Escolha: "); fflush (stdin); opc = getche();
   		
		switch (opc)
   	    {
   	    	case '1': inicializarPilha(&pil); 										break;
   	    	case '2': printf("\n\n    Tamanho da Pilha = %d", tamanhoPilha(&pil) ); 	break;								
			case '3': exibirPilha (&pil);												break;			
   	    	case '4': if ( estaVaziaPilha (&pil) == true ) 
			               printf ("\n\n    Pilha SEM itens");	
					  else printf ("\n\n    Pilha COM Itens");		        break;
		   	case '5': insereNaPilha (&pil);									break;
   	    	case '6': excluirDaPilha (&pil);								break;
   	    	case '7': reinicializarPilha (&pil);							break;
   			case '8': carregarPilha(&pil);									break;	    	
			case '0': main();												break;
   		}

		printf ("\n    Novo teste? [n/N = NEGATIVO]"); fflush (stdin); opc = getche();
   }
   while ( opc != 'n' && opc != 'N');
}
