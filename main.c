#include "usuario.h"
#include "gondola.h"

int menuPrincipal();

int main()
{

    setlocale(LC_ALL, "Portuguese");
    //login();
    return menuPrincipal();
}

int menuPrincipal()
{
 
    
    
    LISTA lis;
    GONDOLA gon;
    inicializarLista(&lis);
    inicializarGondola(&gon);
    carregaGondula(&gon);
    //produtoDefault(&gon);
    //cadastroDefault();
    char opc, opc2;

    do
    {
        system("cls");
        system("color 1F");
        printf("\n    __    __ ___  __              __   __  __    __       __         __   __   __    "
               "\n   (_  | (_   |  |_  |\\/|  /\\    / _  |_  |__)  |_  |\\ | /   |  /\\  |  \\ /  \\ |__)   "
               "\n   __) | __)  |  |__ |  | /--\\   \\__) |__ |  \\  |__ | \\| \\__ | /--\\ |__/ \\__/ |  \\   "
               "\n         __   __    __       __   __  __        __  __    __       __   __   "
               "\n        |  \\ |_    (_  /  \\ |__) |_  |__) |\\/| |_  |__)  /    /\\  |  \\ /  \\         "
               "\n        |__/ |__   __) \\__/ |    |__ | \\  |  | |__ |  \\  \\__ /--\\ |__/ \\__/         \n");
        printf("\n\t\t\t\t__________________________");
        printf("\n\t\t\t\t|    MENU DE OPÇÕES:     |");
        printf("\n\t\t\t\t|========================|");
        printf("\n\t\t\t\t|1. Abastecer  Gôndolas  |");
        printf("\n\t\t\t\t|2. Caixa/PVD            |");
        printf("\n\t\t\t\t|3. Entregas a domicílio |");
        printf("\n\t\t\t\t|4. Gerenciar Usuários   |");
        printf("\n\t\t\t\t|5. Relogar              |");
        printf("\n\t\t\t\t|0. Sair                 |");
        printf("\n\t\t\t\t|________________________|");
        printf("\n\t\t\t\t Escolha:");
        fflush(stdin);
        opc = getche();
        system("cls");

        switch (opc)
        {
        case '1':
        	abastecerGondolas(&gon);
            break;
        case '2':
            system("color 4F");
            printf("\n\t\tCAIXAS/PVD:  ");
            printf("\n=================================================");
            printf("\n\n Em desenvolvimento...");
            break;
        case '3':
            system("color 4F");
            printf("\n\t\tENTREGAS A DOMICÍLIO:  ");
            printf("\n===========================================================");
            printf("\n\n Em desenvolvimento...");
            break;
        case '4':
            gerenciarUsuarios(&lis);
            break;
        case '5':
        	main();
            break;
        case '0':
            printf("\n\n\tPrograma Finalizado com sucesso!\n");
            exit(1);
            break;
        default:
            printf("\n\n\tOpção Inválida...");
            break;
        }
        fflush(stdin);
        opc = getche();
    } while (opc != 'N' && opc != 'n');
    return 0;
}
