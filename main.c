#include "common.h"
#include "usuario.h"
#include "gondola.h"

int main()
{
    char opc, opc2;
    setlocale(LC_ALL, "Portuguese");

    do
    {
        system("color f5");
        system("cls");

        printf("\n    __    __ ___  __              __   __  __    __       __         __   __   __    "
               "\n   (_  | (_   |  |_  |\\/|  /\\    / _  |_  |__)  |_  |\\ | /   |  /\\  |  \\ /  \\ |__)   "
               "\n   __) | __)  |  |__ |  | /--\\   \\__) |__ |  \\  |__ | \\| \\__ | /--\\ |__/ \\__/ |  \\   "
               "\n         __   __    __       __   __  __        __  __    __       __   __   "
               "\n        |  \\ |_    (_  /  \\ |__) |_  |__) |\\/| |_  |__)  /    /\\  |  \\ /  \\         "
               "\n        |__/ |__   __) \\__/ |    |__ | \   |  | |__ |  \\  \\__ /--\\ |__/ \\__/         ");
        printf("\n\n                            __________________________");
        printf("\n                            |    MENU DE OPÇÕES:     |");
        printf("\n                            |========================|");
        printf("\n                            |1. Abastecer  Gôndolas  |");
        printf("\n                            |2. Caixa/PVD            |");
        printf("\n                            |3. Entregas a domicílio |");
        printf("\n                            |4. Gerenciar Usuários   |");
        printf("\n                            |0. Sair                 |");
        printf("\n                            |________________________|");
        printf("\n                             Escolha:");
        fflush(stdin);
        opc = getche();
        system("cls");

        switch (opc)
        {
        case '1':
            abastecerGondolas();
            break;
        case '2':
            printf("\n          CAIXAS/PVD:  ");
            printf("\n---------------------------------------");
            printf("\n    Em desenvolvimento...");
            fflush(stdin);
            scanf("%c", &opc2);
            printf("\n-> Pressione qualquer tecla para VOLTAR...\n");
            break;
        case '3':
            printf("\n          ENTREGAS A DOMICÍLIO:  ");
            printf("\n---------------------------------------");
            printf("\n    Em desenvolvimento...");
            fflush(stdin);
            scanf("%c", &opc2);
            printf("\n-> Pressione qualquer tecla para VOLTAR...\n");
            break;
        case '4':
            gerenciarUsuarios();
            break;
        case '0':
            printf("\n    Programa Finalizado com Sucesso!\n");
            printf("\n-> Pressione qualquer tecla para SAIR...\n");
            exit(1);
            break;
        default:
            printf("\n\n    Opção Invalida...");
            printf("\n-> Pressione qualquer tecla para VOLTAR...\n");
            break;
        }
        fflush(stdin);
        opc = getche();
    } while (opc != 'N' && opc != 'n');
    return 0;
}
