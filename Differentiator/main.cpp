#include "differ.h"

int main(int argc, char* argv[]) {
    tree diff_tree = {};
    TreeCtor(&diff_tree);

    ReadEquation(&diff_tree, argv[1]);
    simple_tree(diff_tree.Tamyr, &diff_tree.count);
    tree_dot(&diff_tree, argv[3]);

    tree derivative = Derivative(&diff_tree);

    //for (int i = 0; i < 3; i++) derivative = Derivative(&derivative);

    tree_dot(&derivative, argv[3]);

    simple_tree(derivative.Tamyr, &derivative.count);
    tree_dot(&derivative, argv[3]);

    Latex(&derivative, argv[2]);

    TreeDtor(&diff_tree);
    TreeDtor(&derivative);
}