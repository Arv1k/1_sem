#include "akinator.h"

int main(int argc, char* argv[]) {
    printf("#---------------------#\n"
           "# Версия 0.2.0, альфа #\n"
           "# Создано Arv1k-ом    #\n"
           "#---------------------#\n\n\n");

    printf("Привет!)\n"
           "Загадай кого-нибудь или что-нибудь, а я постараюсь отгадать!\n\n"
           "Хочешь сыграть?\n"
           "# нажми [y] если хочешь и [n] если не хочешь\n");

    char ans = 0;
    scanf("\n%c", &ans);

    if (ans == 'n') {
        printf("Пока!\n");

        return 0;
    }

    else if (ans != 'y' && ans != 's') {
        printf("Неверная команда!\n");

        return 0;
    }

    printf("Начнём!)\n\n");

    tree myTree = {};
    TreeCtor(&myTree);

    FILE* enterTree = fopen(argv[1], "rb");
    assert(enterTree);

    TreeReadAkinator(&myTree, enterTree);

    assert(enterTree);
    fclose(enterTree);

    while (ans != 'q') {
        printf("Вы хотите чтобы я отгадал что-нибудь, или дал определение чего-либо?\n"
               "# отгадай [y], дай определение [s]\n");

        scanf("\n%c", &ans);

        if (ans == 'y') {
            tree_elem* pos = question(myTree.Tamyr);

            scanf("\n%c", &ans);

            if      (ans == 'y') printf("Я так и знал!)\n\n");
            else if (ans == 'n') new_member(&myTree, pos);
            else {
                printf("Неверная команда!\n");

                break;
            }
        }

        else if (ans == 's') {
            printf("Определение кого вам дать?\n");
            char buff[max_string] = "\n";

            fflush(stdin);

            while (*buff == '\n') fgets(buff, max_string, stdin);

            char* point = strchr(buff, '\n');
            *point = '\0';

            search_member(&myTree, buff);
        }

        else {
            printf("Неверная команда!\n");

            break;
        }

        printf("Хотите сыграть еще?\n"
               "# да [y], выйти [q]\n");

        scanf("\n%c", &ans);

        if (ans != 'y' && ans != 'q') {
            printf("Неверная команда!\n");

            break;
        }
    }

    printf("Пока!\n");

    FILE* outputFile = fopen(argv[1], "w");
    assert(outputFile);

    TreePrint(myTree.Tamyr, outputFile);

    assert(outputFile);
    fclose(outputFile);

    akinator_dot(&myTree, argv[2]);

    TreeDtor(&myTree);
}