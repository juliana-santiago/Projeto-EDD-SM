//Biblioteca
#include "usuario.h"

//Variavel Global
FILE *arq;
REGISTRO R;

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
void exibirLista(LISTA *l)
{
    int cont = 0;
    PONT end = l->inicio;
    system("cls");
    printf("Lista: \n ");
    while (end != NULL)
    {
        cont++;
        printf("\n%02d\t%-10s\t\t%-50s", cont, end->reg.prontuario, end->reg.nomeUsuario);
        end = end->prox;
    }
    printf("\n");
}

//Busca Sequencial Ordenada - Nomes
PONT buscaSeqOrd(LISTA *l, REGISTRO *ch)
{
    PONT pos = l->inicio;
    char *prontuario = ch->prontuario;
    while (pos != NULL && (strcmp(pos->reg.prontuario, prontuario) != 1))
        pos = pos->prox;
    if (pos != NULL && (strcmp(pos->reg.prontuario, prontuario) == 0))
        return pos;
    return NULL;
}
//Função booleana para inserir um Novo Elemento na Lista Ordenada
bool inserirElemListaOrd(LISTA *l, REGISTRO reg)
{
    char *ch = reg.prontuario;
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
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
PONT buscaSequencialExc(LISTA *l, char *ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (strcmp(atual->reg.prontuario, ch) != 1))
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (strcmp(atual->reg.prontuario, ch) == 0))
        return atual;
    return NULL;
}

//Função booleana para excluir um Elemento especifico da Lista Ordenada
bool excluirElemLista(LISTA *l, char *ch)
{
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
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

REGISTRO oqueBuscar()
{
    REGISTRO nbusca;
    printf("\nDigite o prontuario para busca: ");
    fflush(stdin);
    gets(nbusca.prontuario);
    return nbusca;
}

void pesquisaLista(LISTA *l)
{
    PONT ender;
    REGISTRO elem;
    elem = oqueBuscar();
    ender = buscaSeqOrd(l, &elem);
    if (ender == NULL)
        printf("\n Prontuario [%s] nao encontrado!", elem.prontuario);
    else
        printf("\n Prontuario [%s] encontrada em [%p]", elem.prontuario, ender);
}
//Registrando novos dados na Lista
REGISTRO oqueInserir()
{

    printf("\nNOME DO USUARIO      : ");
    fflush(stdin);
    gets(R.nomeUsuario);
    printf("\nPRONTUARIO DO USUARIO: ");
    fflush(stdin);
    gets(R.prontuario);
    return R;
}
//Insere elementos na Lista
void insereNaLista(LISTA *l)
{
    REGISTRO elem;
    elem = oqueInserir();

    printf("\nVai inserir o usuario [%s] [%s]", elem.prontuario, elem.nomeUsuario);
    getch();
    if (inserirElemListaOrd(l, elem) == true) {
    	printf("\n O prontuario [%s] foi inserido com sucesso.", elem.prontuario);
	}
    else
        printf("\n O prontuario [%s] NAO foi inserida!", elem.prontuario);
}
//Armazena qual elemento o usuario deseja excluir
REGISTRO oqueExcluir()
{
    REGISTRO nexclui;
    printf("\nDigite o prontuario para excluir: ");
    fflush(stdin);
    gets(nexclui.prontuario);

    printf("\nVai excluir o prontuario:%s ", nexclui.prontuario);
    getch();
    return nexclui;
}

void excluiDaLista(LISTA *l)
{
    REGISTRO chave;
    chave = oqueExcluir();

    printf("\nVai excluir o prontuario: %s ", chave.prontuario);
    getch();
    if (excluirElemLista(l, chave.prontuario) == true)
        printf("\nO prontuario [%s] foi excluido com sucesso.", chave.prontuario);
    else
        printf("\nO prontuario [%s] NAO foi excluida!", chave.prontuario);
}

void TROCA(REGISTRO vetor[], int i, int j)
{
    REGISTRO aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

int part(REGISTRO vetor[], int ini, int pivo)
{
    int i, p_maior = ini;
    for (i = ini; i < pivo; i++)
    {
        if (strcmp(vetor[i].nomeUsuario, vetor[pivo].nomeUsuario) < 0)
        {
            TROCA(vetor, i, p_maior);
            p_maior++;
        }
    }
    TROCA(vetor, p_maior, pivo);
    return p_maior;
}

void quick_sort(REGISTRO *vet_registros, int ini, int fim)
{
    int pivo;

    if (ini < fim)
    {
        pivo = part(vet_registros, ini, fim);
        quick_sort(vet_registros, ini, pivo - 1);
        quick_sort(vet_registros, pivo + 1, fim);
    }
}

void carregarLista(LISTA *l)
{
	reinicializarLista(l);
    int nroDeRegistros, flag_legrava;
    arq = fopen("usuarios.dat", "r");
    fseek(arq, 0L, SEEK_END);
    int size = ftell(arq);
    nroDeRegistros = ftell(arq) / sizeof(REGISTRO);
	
    printf("\nTamanho do Arquivo: %d", size);

    REGISTRO *vet_registros;
    vet_registros = (REGISTRO *)malloc(nroDeRegistros * sizeof(REGISTRO));
    
    if (vet_registros == NULL)
    {
        printf("malloc devolveu NULL!\n");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }

    fseek(arq, 0, SEEK_SET);

    flag_legrava = fread(vet_registros, nroDeRegistros * sizeof(REGISTRO), 1, arq);
    if (flag_legrava != 1)
    {
        printf("\n\nERRO DE LEITURA DO ARQUIVO USUARIOS.DAT");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    quick_sort(vet_registros, 0, nroDeRegistros - 1);
    fclose(arq);
    arq = fopen("usuarios.dat", "w");
    flag_legrava = fwrite(vet_registros, nroDeRegistros * sizeof(REGISTRO), 1, arq);
    if (flag_legrava != 1)
    {
        printf("\n\nERRO DE GRAVAÇÃO NO ARQUIVO USUARIOS.DAT");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    fclose(arq);
    int ac = 0;
    
	for(; ac < nroDeRegistros; ac ++) {
		inserirElemListaOrd(l, vet_registros[ac]);
	}
}

REGISTRO* listaArray(LISTA *l) {
	int nroDeRegistros, cont = 0;
	nroDeRegistros = tamanhoLista(l);
	REGISTRO vet[nroDeRegistros];
    PONT end = l->inicio;
    system("cls");
    printf("Lista: \n ");
    while (end != NULL)
    {
        vet[cont] = end->reg;
        cont++;
        end = end->prox;
    }
    return &vet;
} 

int salvaArquivo(LISTA *l) {
	int flag_legrava;
	REGISTRO* vet = listaArray(l);
	arq = fopen("usuarios.dat", "w");
	flag_legrava = fwrite(vet, tamanhoLista(l) * sizeof(REGISTRO), 1, arq);
    if (flag_legrava != 1)
    {
        printf("\n\nERRO DE GRAVAÇÃO NO ARQUIVO USUARIOS.DAT");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    return flag_legrava;
}

//Menu Gerenciar Usuarios
void gerenciarUsuarios()
{
    LISTA lis;
    char opc;

    inicializarLista(&lis);
    carregarLista(&lis);

    do
    {
        system("color f5");
        system("cls");
        printf("\n       GERENCIAR USÚARIOS:  ");
        printf("\n---------------------------------------");
        printf("\n 1. Exibir tamanho da Lista ligada");
        printf("\n 2. Exibir Lista ligada           ");
        printf("\n 3. Fazer busca na Lista ligada   ");
        printf("\n 4. Inserir elemento na Lista ligada ");
        printf("\n 5. Excluir elemento da Lista ligada ");
        printf("\n 6. Reinicializa Lista ligada ");
        printf("\n 7. Busca por prontuario ");
        printf("\n 0. Menu Principal");
        printf("\n---------------------------------------");
        printf("\n    Escolha: ");
        fflush(stdin);
        opc = getche();
        printf("\n");
        char aaa;

        switch (opc)
        {
        case '1':
            system("cls");
            printf("\n    Tamanho da Lista = %d", tamanhoLista(&lis));
            break;
        case '2':
            system("cls");
            exibirLista(&lis);
            break;
        case '3':
            system("cls");
            pesquisaLista(&lis);
            break;
        case '4':
            system("cls");
            insereNaLista(&lis);
            salvaArquivo(&lis);
            break;
        case '5':
            system("cls");
            excluiDaLista(&lis);
            salvaArquivo(&lis);
            break;
        case '6':
            reinicializarLista(&lis);
            break;
        case '7':
        	
        	fflush(stdin);
    		gets(&aaa);
    		REGISTRO* vetor = listaArray(&lis);
    		int tamanho;
    		tamanho = tamanhoLista(&lis);
        	printf("%d", buscaBinaria(vetor, tamanho, &aaa));
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

int buscaBinaria (REGISTRO *vetor, int tamanho_vet,  char* pronturario) {

    int inicio=0, fim=tamanho_vet-1, meio;

    while(inicio<=fim){
        meio = (inicio+fim)/2;
            if(strcmp(vetor[meio].prontuario, pronturario) == 0)
                return meio;
            if(strcmp(vetor[meio].prontuario, pronturario) > 0)
                fim = meio - 1;
            else
                inicio=meio+1;
    }
    return -1;
}

void cadastro_default(void)
{

    REGISTRO tab[62] = {
        {"ADRIANO RASPANTE SUARES", "SP3023231"},                    //00
        {"ALEXANDRE BELETTI FERREIRA", "SP226117"},                  //01
        {"ALINE FIRMINO BRITO", "SP230285"},                         //02
        {"ANDRE EVANDRO LOURENCO", "SP100092"},                      //03
        {"ANDRE LUIZ DA SILVA", "SP030028"},                         //04
        {"ANSELMO DE ARAUJO COUTO", "SP232956"},                     //05
        {"ANTONIO AIRTON PALADINO", "SP112197"},                     //06
        {"ANTONIO FERREIRA VIANA", "SP200827"},                      //07
        {"BRUNA RODRIGUES DE OLIVEIRA", "SP3031853"},                //08
        {"BRUNNO PAPIS GUSMAO", "SP3024148"},                        //09
        {"CAIO ALENCAR MARCELLI SANTOS", "SP3017052"},               //10
        {"CAMILA LOPEZ FRANQUEIRA DE FRANCA", "SP302427X"},          //11
        {"CAROLINA DE MORAES JOSEPHIK", "SP3030571"},                //12
        {"CESAR LOPES FERNANDES", "SP890534"},                       //13
        {"CEZAR AUGUSTO DE NORONHA NAJJARIAN BATISTA", "SP3022552"}, //14
        {"CLAUDETE DE OLIVEIRA ALVES", "SP03020X"},                  //15
        {"CLAUDIA MIYUKI WERHMULLER", "SP030041"},                   //16
        {"DANIEL MARQUES GOMES DE MORAIS", "SP220097"},              //17
        {"DIMAS DE OLIVEIRA", "SP3030598"},                          //18
        {"DOMINGOS BERNARDO GOMES SANTOS", "SP090888"},              //19
        {"DOMINGOS LUCAS LATORRE DE OLIVEIRA", "CJ146456"},          //20
        {"EDUARDO VIVI DE ARAUJO", "SP303240X"},                     //21
        {"EURIDES BALBINO", "SP07102X"},                             //22
        {"FABIO MENDES TORRES", "SP3023184"},                        //23
        {"FERNANDO DE SOUSA SILVA", "SP3017061"},                    //24
        {"FRANCISCO VERISSIMO LUCIANO", "SP030247"},                 //25
        {"GABRIELA VIANA BILINSKI", "SP3026868"},                    //26
        {"GAWAN AUGUSTO GOMES FERREIRA", "SP302170X"},               //27
        {"GUSTAVO DA COSTA SOUZA SILVA", "SP3024296"},               //28
        {"GUSTAVO MOLINA FIGUEIREDO", "SP23378X"},                   //29
        {"IVAN FRANCOLIN MARTINEZ", "SP060835"},                     //30
        {"JOAO VIANEI TAMANINI", "SP060914"},                        //31
        {"JOAO VICTOR TEIXEIRA DE OLIVEIRA", "SP3030644"},           //32
        {"JOSCELI MARIA TENORIO", "SP124382"},                       //33
        {"JOSE BRAZ DE ARAUJO", "SP070385"},                         //34
        {"JOSE OSCAR MACHADO ALEXANDRE", "SP070038"},                //35
        {"JOSE RONALDO DA SILVA JUNIOR", "SP3013197"},               //36
        {"JULIANA MACEDO SANTIAGO", "SP3032337"},                    //37
        {"LARISSA GUILGER DE PROENCA", "SP3024202"},                 //38
        {"LEANDRO PINTO SANTANA", "SP144381"},                       //39
        {"LEANDRO SAMPAIO PEREIRA", "SP3026591"},                    //40
        {"LEONARDO BERTHOLDO", "SP204973"},                          //41
        {"LETICIA BRITO DOS SANTOS", "SP3026582"},                   //42
        {"LINEKER EVANGELISTA DA SILVA", "SP3024253"},               //43
        {"LUCAS AMBROZIN GALLO", "SP3030661"},                       //44
        {"LUIS FERNANDO AIRES BRANCO MENEGUETI", "SP141008"},        //45
        {"LUIS FERNANDO ROCA KILZER", "SP3023109"},                  //46
        {"LUK CHO MAN", "SP060380"},                                 //47
        {"MARCELO TAVARES DE SANTANA", "SP20500X"},                  //48
        {"MARIANA DA SILVA ZANGROSSI", "SP3030679"},                 //49
        {"MARIVALDO TORRES JUNIOR", "SP3024792"},                    //50
        {"MATHEUS AUGUSTO DO NASCIMENTO DIAS", "SP3030687"},         //51
        {"MATHEUS CASAGRANDE", "SP3013944"},                         //52
        {"MIGUEL ANGELO TANCREDI MOLINA", "SP102763"},               //53
        {"PAULO ANDRE ZAPPAROLI", "SP236020"},                       //54
        {"PAULO ROBERTO DE ABREU", "SP070816"},                      //55
        {"PEDRO HENRIQUE SILVA DOS SANTOS", "SP3023176"},            //56
        {"RAFAEL DOS SANTOS FERREIRA", "SP3021734"},                 //57
        {"RENAN COELHO SANTOS", "SP3024156"},                        //58
        {"RODRIGO RIBEIRO DE OLIVEIRA", "RG134168"},                 //59
        {"THIAGO DE NOVAES FRANCA", "SP236172"},                     //60
        {"WILLIAM TAKAHIRO MARUYAMA", "SP233250"}                    //61
    };

    arq = fopen("usuarios.dat", "w");
    fwrite(tab, sizeof(tab), 1, arq);

    fclose(arq);
}
