#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left, *right;
    int height;
} Node;

Node *newNode(int value) {
    Node *aux = malloc(sizeof(Node));
    aux->value = value;
    aux->left = aux->right = NULL;
    aux->height = 1;
    return aux;
}

int getHeight(Node *node) {
    if (node == NULL) return -1;
    return node->height;
}

int getBalanceFactor(Node *node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

int getMax(int right, int left) {
    return (right > left) ? right : left;
}

Node *rotateLeft(Node *node) {
    Node *right_child = node->right;
    Node *left_right_child = right_child->left;

    right_child->left = node;
    node->right = left_right_child;

    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    right_child->height = getMax(getHeight(right_child->left), getHeight(right_child->right)) + 1;

    return right_child;
}

Node *rotateRight(Node *node) {
    Node *left_child = node->left;
    Node *right_left_child = left_child->right;

    left_child->right = node;
    node->left = right_left_child;

    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    left_child->height = getMax(getHeight(left_child->left), getHeight(left_child->right)) + 1;

    return left_child;
}

Node *reorganizeTree(Node *root, int value) {
    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalanceFactor(root);

    // LEFT LEFT CASE
    if (balance > 1 && value < root->left->value) return rotateRight(root);

    // RIGHT RIGHT CASE
    if (balance < -1 && value > root->right->value) return rotateLeft(root);

    // LEFT RIGHT CASE
    if (balance > 1 && value > root->left->value) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RIGHT LEFT CASE
    if (balance < -1 && value < root->right->value) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node *insertNode(Node *root, int value) {
    if (root == NULL) return newNode(value);
    else if (value < root->value) root->left = insertNode(root->left, value);
    else if (value > root->value) root->right = insertNode(root->right, value);
    else return root;

    return reorganizeTree(root, value);
}

int printIndex(Node *root, int main_root_data, int index, int value){
    if (root != NULL) {
        index = printIndex(root->left, main_root_data, index, value);
        index++;
        
        if (root->value == value){
            printf("%d\n", index);
            return -1;
        }
        if (index == 0) return -1;
        index = printIndex(root->right, main_root_data, index, value);
        if (root->value == main_root_data) printf("Data tidak ada\n");
    }

    return index;
}

int main() {
    int amount_queries, main_root_data;
    int query_type, value, index;
    Node *root = NULL;

    scanf("%d", &amount_queries);

    while (amount_queries--){
        scanf("%d", &query_type);
        scanf("%d", &value);

        if (query_type == 1) {
            root = insertNode(root, value);
            main_root_data = root->value;
            continue;
        }
        index = 0;
        printIndex(root, main_root_data, index, value);
    }
    return 0;
}
