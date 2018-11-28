#include "akinator.h"

int main() {
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

    FILE* enterTree = fopen("../enterTree", "rb");
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

            if      (ans == 'y') printf("Я так и знал!)\n");
            else if (ans == 'n') new_member(&myTree, pos);
            else {
                printf("Неверная команда!\n");

                break;
            }
        }

        else if (ans == 's') {
            printf("Определение кого вам дать?\n");
            char buff[max_string] = {};

            scanf("\n%[^\n]", buff);
            search_member(&myTree, buff);
        }

        else {
            printf("Неверная команда!\n");

            break;
        }

        printf("Хотите сыграть еще?\n"
               "# да [y], выйти [q]\n");

        scanf("\n%c", &ans);
    }

    printf("Пока!\n");

    FILE* outputFile = fopen("../enterTree", "w");
    assert(outputFile);

    TreePrint(myTree.Tamyr, outputFile);

    assert(outputFile);
    fclose(outputFile);

    TreeDtor(&myTree);
}