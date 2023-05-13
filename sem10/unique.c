#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

struct node *create_node(char *word){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->word = (char*)malloc(strlen(word) + 1);
    strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(struct node *node, char *word){
    if (strcmp(word, node->word) == 0){
        node->count++;
        return;
    }
    if (strcmp(word, node->word) < 0){
        if (node->left == NULL) {
            node->left = create_node(word);
        } else {
            insert(node->left, word);
        }
    } else {
        if (node->right == NULL) {
            node->right = create_node(word);
        } else {
            insert(node->right, word);
        }
    }
}

void in_order_traversal(struct node *node, char *order) {
    if (node == NULL) {
        return;
    }
    if (strcmp(order, "ASC") == 0) {
        in_order_traversal(node->left, order);
        printf("%s - %d\n", node->word, node->count);
        in_order_traversal(node->right, order);
    } else if (strcmp(order, "DESC") == 0) {
        in_order_traversal(node->right, order);
        printf("%s - %d\n", node->word, node->count);
        in_order_traversal(node->left, order);
    } else {
        in_order_traversal(node->left, order);
        printf("%s - %d\n", node->word, node->count);
        in_order_traversal(node->right, order);
    }
}

int main(int argc, char *argv[]) {
    struct node *root = NULL;
    char *filename, *order;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Please provide a file name as command line argument.");
        return 1;
    }
    if (argc > 2) {
        order = argv[2];
        if (strcmp(order, "ASC") != 0 && strcmp(order, "DESC") != 0) {
            printf("Invalid sorting order provided. Please use ASC or DESC.\n");
            return 1;
        }
    } else {
        order = "ASC";
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    char word[100];
    while (fscanf(fp, "%s", word) != EOF) {
        if (root == NULL) {
            root = create_node(word);
        } else {
            insert(root, word);
        }
    }
    fclose(fp);

    in_order_traversal(root, order);
    return 0;
}
