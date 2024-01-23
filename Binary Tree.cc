#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct tree {
    int value;
    tree * right;
    tree * left;
} tree;

tree * search(int value, tree * root) {
    if (root == NULL) {
        printf("Value not found!\n");
        return NULL;
    }
    if (root->value == value) {
        printf("Found!\n");
        return root;
    }
    if (value < root->value) {
        return search(value, root->left);
    }
    return search(value, root->right);
}

tree * removeNode(int value, tree * root) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        root->left = removeNode(value, root->left);
    } else if (value > root->value) {
        root->right = removeNode(value, root->right);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            tree * temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            tree * temp = root;
            root = root->left;
            free(temp);
        } else {
            tree * temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->value = temp->value;
            root->right = removeNode(temp->value, root->right);
        }
    }
    return root;
}

tree * initNode(int value) {
    tree * init = (tree *) malloc(sizeof(tree));
    init->value = value;
    init->right = NULL;
    init->left = NULL;
    return init;
}

tree * insert(tree * root, int value) {
    if (root == NULL) {
        root = initNode(value);
    } else if (value <= root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void printTree(tree * root, int level = 0) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "       ";
    }
    std::cout << root->value << std::endl;
    printTree(root->left, level + 1);
}

int main() {
    int level = 0;
    tree * root = NULL;
    int navigator = 0;
    int add = 0;

    while (true) {
        printf("Welcome to your Binary Search Tree! To view your tree, enter '1'. To insert a value into your tree, enter '2'. To remove an element from your tree, enter '3', to search in your tree, enter '4', and to exit, enter '5'\n");
        scanf("%d", &navigator);
        while (navigator != 1 && navigator != 2 && navigator != 3 && navigator != 4 && navigator != 5) {
            printf("You did not provide a valid option! Please try again \n");
            scanf("%d", &navigator);
        }
        if (navigator == 1) {
            if (root == NULL) {
                printf("Tree is empty! \n");
            } else {
                printf("You chose to view the Tree!\n ");
                printTree(root, level);
            }
        }
        if (navigator == 2) {
            printf("You chose to insert! Please insert the number below: \n");
            scanf("%d", &add);
            root = insert(root, add);
        }
        if (navigator == 3) {
            if (root == NULL) {
                printf("Tree is empty! \n");
            } else {
                printf("You chose to remove an element from the tree!\n ");
                printf("Enter a value!\n");
                scanf("%d", &add);
                removeNode(add, root);
            }
        }
        if(navigator == 4) {
            printf("You chose to perform a search, enter the desired value to be searched!\n");
            scanf("%d", &add);
            search(add, root);
        }
        if (navigator == 5) {
            printf("You chose to exit the Navigator! \n");
            break;
        }
    }
}
