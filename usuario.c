#include "common.h"
#include "usuario.h"

void gerenciarUsuarios(LISTA *lis)
{
    char opc;
    do
    {
        system("color 3F");
        system("cls");
        printf("\n\t______________________________________");
        printf("\n\t|         GERENCIAR USUARIOS:        |");
        printf("\n\t|====================================|");
        printf("\n\t| 1. Exibir tamanho da Lista         |");
        printf("\n\t| 2. Exibir Lista                    |");
        printf("\n\t| 3. Buscar por Prontuário na Lista  |");
        printf("\n\t| 4. Inserir elemento na Lista       |");
        printf("\n\t| 5. Excluir elemento da Lista       |");
        printf("\n\t| 6. Reinicializa Lista              |");
        printf("\n\t| 7. Salvar Alterações no Arquivo    |");
        printf("\n\t| 0. Menu Principal                  |");
        printf("\n\t|____________________________________|");
        printf("\n\t Escolha: ");
        fflush(stdin);
        opc = getche();
        printf("\n");
        char aaa;

        switch (opc)
        {
        case '1':
            system("cls");
            printf("\n\tQuantidade: %d", tamanhoLista(lis));
            break;
        case '2':
            system("cls");
            exibirLista(lis);
            break;
        case '3':
            system("cls");
            buscaPorProntuario(lis);
            break;
        case '4':
            system("cls");
            insereNaLista(lis);
            break;
        case '5':
            system("cls");
            excluiDaLista(lis);
            break;
        case '6':
            system("cls");
            break;
        case '7':
            system("cls");
            salvaArquivo(lis);
            break;
        case '0':
            menuPrincipal();
            break;
        default:
            printf("\n\n\tOpção Invalida...");
            break;
        }
        printf("\n\tNovo teste? [n/N = NEGATIVO]");
        fflush(stdin);
        opc = getche();
    } while (opc != 'N' && opc != 'n');
}

int buscaBinaria(REGISTRO *vetor, int tamanho_vet, char *user)
{

    int inicio = 0, fim = tamanho_vet - 1, meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        if (strcmp(vetor[meio].nomeUsuario, user) == 0)
            return meio;
        if (strcmp(vetor[meio].nomeUsuario, user) > 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

void login()
{
    system("color 9F");
    REGISTRO reg;
    REGISTRO *vetRegistros = lerArquivo();

    printf("\n\tNOME DO USUÁRIO:");
    fflush(stdin);
    gets(reg.nomeUsuario);
    printf("\n\tPRONTUARIO DO USUÁRIO:");
    fflush(stdin);
    gets(reg.prontuario);

    int pos = buscaBinaria(vetRegistros, tamanhoArquivo(), reg.nomeUsuario);

    if (pos != -1)
    {
        if (strcmp(vetRegistros[pos].prontuario, reg.prontuario) != 0)
        {
            system("mode con:cols=75 lines=10");
            system("cls");
            system("color c0");
            printf("\n\n\tUSUÁRIO E/OU PRONTUÁRIO INVÁLIDO!\n\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color c0");
        printf("\n\n\tUSUÁRIO E/OU PRONTUÁRIO INVÁLIDO!\n\n");
        exit(EXIT_FAILURE);
    }
}

int tamanhoArquivo()
{
	int quantRegistros;
	FILE *arq;
	arq = fopen("data/usuarios.dat", "r");
	
	fseek(arq, 0L, SEEK_END);
    quantRegistros = ftell(arq) / sizeof(REGISTRO);
    fclose(arq);
    return quantRegistros;	
}

REGISTRO *lerArquivo()
{
    FILE *arq;
    int nroDeRegistros, flag_legrava;
    arq = fopen("data/usuarios.dat", "r");

    if (arq == NULL)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tARQUIVO USUARIOS.DAT INEXISTENTE!\n\n");
    }

    fseek(arq, 0L, SEEK_END);
    
    nroDeRegistros = ftell(arq) / sizeof(REGISTRO);

    REGISTRO *vet_registros;
    vet_registros = (REGISTRO *)malloc(nroDeRegistros * sizeof(REGISTRO));

    if (vet_registros == NULL)
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

    flag_legrava = fread(vet_registros, nroDeRegistros * sizeof(REGISTRO), 1, arq);
    if (flag_legrava != 1)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tERRO DE LEITURA DO ARQUIVO USUARIOS.DAT");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }

    quick_sort(vet_registros, 0, nroDeRegistros - 1);
    fclose(arq);
    return vet_registros;
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

void troca(REGISTRO vetor[], int i, int j)
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
            troca(vetor, i, p_maior);
            p_maior++;
        }
    }
    troca(vetor, p_maior, pivo);
    return p_maior;
}

void exibeArquivo(void)
{
    REGISTRO *arq = lerArquivo();
    int i = 0;
    printf("%d", quantRegistro());
    for (; i < quantRegistro(); i++)
    {
        printf("\n%02d\t%-10s\t\t%-50s", i, arq[i].prontuario, arq[i].nomeUsuario);
    }
}

bool inserirElemListaOrd(LISTA *l, REGISTRO reg)
{
    char *user = reg.nomeUsuario;

    PONT ant, j, i;
    i = buscaSequencialNome(l, user, &ant);

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
PONT buscaSequencialNome(LISTA *l, char *ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (strcmp(atual->reg.nomeUsuario, ch) != 0))
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (strcmp(atual->reg.nomeUsuario, ch) == 0))
        return atual;
    return NULL;
}
PONT buscaSequencialPront(LISTA *l, char *pront, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (strcmp(atual->reg.prontuario, pront) != 0))
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (strcmp(atual->reg.prontuario, pront) == 0))
    {
        return atual;
    }

    return NULL;
}
void cadastroDefault(void)
{
    FILE *arq;
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

    arq = fopen("data/usuarios.dat", "w");
    fwrite(tab, sizeof(tab), 1, arq);

    fclose(arq);
}
int quantRegistro(void)
{
    FILE *arq;
    int nroDeRegistros, flag_legrava;
    arq = fopen("data/usuarios.dat", "r");

    if (arq == NULL)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tARQUIVO USUARIOS.DAT INEXISTENTE!\n\n");
    }

    fseek(arq, 0L, SEEK_END);
    int size = ftell(arq);
    nroDeRegistros = ftell(arq) / sizeof(REGISTRO);
    return nroDeRegistros;
}
void carregaLista(LISTA *l)
{
    REGISTRO *arq = lerArquivo();
    int i = 0;
    for (; i < quantRegistro(); i++)
    {
        inserirElemListaOrd(l, arq[i]);
    }
}
void exibirLista(LISTA *l)
{
    int cont = 0;
    PONT end = l->inicio;
    system("cls");
    printf("\n\t#\tNOME\t\t\t\t\t\t\t\tPRONTUÁRIO");
    printf("\n=================================================================================================");
    while (end != NULL)
    {
        cont++;
        printf("\n\t%02d\t%-50s\t\t%-10s", cont, end->reg.nomeUsuario, end->reg.prontuario);
        end = end->prox;
    }
    printf("\n");
}
void inicializarLista(LISTA *l)
{
    l->inicio = NULL;
    carregaLista(l);
}

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
void buscaPorProntuario(LISTA *lis)
{
    char prontuario[11];
    printf("\n\tDigite o prontuário que deseja PESQUISAR: ");
    fflush(stdin);
    gets(prontuario);
    PONT p = buscaSequencialPront(lis, prontuario, &lis->inicio);
    if (p != NULL)
    {	
        printf("\n\tNOME: %s\n", p->reg.nomeUsuario);
        printf("\tPRONTUÁRIO: %s\n", p->reg.prontuario);
    }
    else
        printf("\n\tUsuário [%s] NÃO localizado!\n", prontuario);
}
void insereNaLista(LISTA *l)
{
    REGISTRO elem;
    elem = oqueInserir();
	if(strcmp (elem.nomeUsuario,"") == 0 || strcmp (elem.prontuario, "") == 0){
		printf("\n\tERRO ao inserir o prontuário!\n");
		return; 
	}
    printf("\n\tVai inserir o usuário [%s] [%s]\n", elem.prontuario, elem.nomeUsuario);
    getch();
    if (inserirElemListaOrd(l, elem) == true)
    {
        printf("\n\tO prontuário [%s] foi inserido com sucesso.\n", elem.prontuario);
    }
    else
        printf("\n\tERRO ao inserir o prontuário [%s]!\n", elem.prontuario);
}

REGISTRO oqueInserir()
{
    REGISTRO reg;
    printf("\n\tNOME DO USUÁRIO      : ");
    fflush(stdin);
    gets(reg.nomeUsuario);
    printf("\n\tPRONTUARIO DO USUÁRIO: ");
    fflush(stdin);
    gets(reg.prontuario);
    return reg;
}

bool excluirElemLista(LISTA *lis, char *pront)
{
    PONT ant, i;
    i = buscaSequencialPront(lis, pront, &ant);
    if (i == NULL)
        return false;
    if (ant == NULL)
        lis->inicio = i->prox;
    else
        ant->prox = i->prox;
    free(i);
    return true;
    free(i);
    return true;
}

void excluiDaLista(LISTA *l)
{
    REGISTRO elem;
    elem = oqueExcluir();
    if(strcmp (elem.prontuario, "") == 0){
		printf("\n\tERRO ao excluir o prontuário!\n");
		return; 
	}
    printf("\n\tVai excluir o usuário [%s]\n", elem.prontuario);
    getch();
    if (excluirElemLista(l, elem.prontuario) == true)
    {
        printf("\n\tO prontuário [%s] foi excluido com sucesso.\n", elem.prontuario);
    }
    else
        printf("\n\tERRO ao excluir o prontuário [%s]!\n", elem.prontuario);
}
REGISTRO oqueExcluir()
{
    REGISTRO reg;
    printf("\n\tDigite o Prontuário que deseja EXCLUIR:");
    fflush(stdin);
    gets(reg.prontuario);
    return reg;
}

REGISTRO *convertToArray(LISTA *l)
{
    REGISTRO *vet;
    vet = (REGISTRO *)malloc(tamanhoLista(l) * sizeof(REGISTRO));
    PONT end = l->inicio;
    int taml = 0;
    while (end != NULL)
    {
        vet[taml] = end->reg;
        taml++;
        end = end->prox;
    }
    return vet;
}

int salvaArquivo(LISTA *l)
{
    FILE *arq;
    int flag_legrava;
    REGISTRO *vet = convertToArray(l);
    
    arq = fopen("data/usuarios.dat", "w");
    flag_legrava = fwrite(vet, tamanhoLista(l) * sizeof(REGISTRO), 1, arq);
    if (flag_legrava != 1)
    {
        system("mode con:cols=75 lines=10");
        system("cls");
        system("color 0c");
        printf("\n\n\tERRO DE GRAVAÇÃO NO ARQUIVO USUARIOS.DAT");
        getch();
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    else
        printf("\n\n\tARQUIVO SALVO COM SUCESSO\n");

    return flag_legrava;
}
