#include<stdio.h>
#include<stack>
#include<queue>
#include<stdlib.h>

using namespace std;

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node;

void pre_order_iter(Node* root) {
    if (root != NULL && root->data == 1)
        printf("[Pre order_iter]");
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    pre_order_iter(root->left);
    pre_order_iter(root->right);
}

void pre_order_recursive(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    printf("[Pre order_recursive] ");
    while (!s.empty() || curr != NULL) {
        while (curr != NULL) {
            printf("%d ", curr->data);
            if (curr->right) {
                s.push(curr->right);
            }
            curr = curr->left;
        }
        if (!s.empty()) {
            curr = s.top();
            s.pop();
        }
    }
    printf("\n");
}
int solve_sum(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->data + solve_sum(root->left) + solve_sum(root->right);
}
void get_node_sum(Node* root) {
    printf("\n[Sum] %d\n", solve_sum(root));
}


Node* alloc_new_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = data;
    return new_node;
}


void find_leafnodes(Node* root) {
    if (root != NULL && root->data == 1) {
            printf("[Leaf nodes] ");
    }
    if (root == NULL) {
        return;
    }
    if (root->right == NULL && root->left == NULL) {
        printf("%d", root->data);
    }
    find_leafnodes(root->left);
    find_leafnodes(root->right);
}

Node* make_tree() {
    Node* root = alloc_new_node(1);
    Node* n2 = alloc_new_node(2);
    Node* n3 = alloc_new_node(3);
    Node* n4 = alloc_new_node(4);
    Node* n5 = alloc_new_node(5);
    Node* n6 = alloc_new_node(6);
    Node* n7 = alloc_new_node(7);
    root->left = n2;
    root->right = n3;
    n2->left = n4;
    n3->left = n5;
    n3->right = n6;
    n5->left = n7;

    return root;
}

int main() {
    Node* root = make_tree();
    pre_order_recursive(root);
    pre_order_iter(root);
    get_node_sum(root);
    find_leafnodes(root);

    return 0;
}
