#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>
#include<iostream>

using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

void in_order(TreeNode* root) {
    stack<TreeNode*> s;
    while (1) {
        for (; root != NULL; root = root->left) {
            s.push(root);
        }
        if(!s.empty())
            root = s.top();
        if (root == NULL)break;
        printf("%d", root->data);
        s.pop();
        root = root->right;
    }
}

void pre_order(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* curr = root;
    while (!s.empty() || curr != NULL) {
        while (curr != NULL) {
            printf("%d", curr->data);
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
}

void post_order(TreeNode* root) {
    if (root == NULL)
        return;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    TreeNode* node;
    while (!s1.empty()) {
        node = s1.top();
        s2.push(node);
        s1.pop();
        if (node->left) {
            s1.push(node->left);
        }
        if (node->right) {
            s1.push(node->right);
        }
    }
    while (!s2.empty()) {
        node = s2.top();
        s2.pop();
        printf("%d", node->data);
    }
}

void postorder(TreeNode* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d", root->data);
}

void inorder(TreeNode* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d", root->data);
    inorder(root->right);
}

void preorder(TreeNode* root) {
    if (root == NULL)
        return;
    printf("%d", root->data);
    preorder(root->left);
    preorder(root->right);
}

void level_order(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        if (curr == NULL)break;
        q.pop();
        printf("%d", curr->data);
        if (curr->left) {
            q.push(curr->left);
        }
        if (curr->right) {
            q.push(curr->right);
        }
    }
}
void levelOrderTraversalRightToLeft(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    // 큐를 사용하여 레벨 순회
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        cout << current->data;

        if (current->right) {
            q.push(current->right);
        }
        if (current->left) {
            q.push(current->left);
        }
    }
}

TreeNode* findLowestCommonAncestor(TreeNode* root, TreeNode* node1, TreeNode* node2) {
    if (root == NULL) {
        return NULL; // 트리가 비어있는 경우
    }

    if (node1->data < root->data && node2->data < root->data) {
        return findLowestCommonAncestor(root->left, node1, node2);
    }
    else if (node1->data > root->data && node2->data > root->data) {
        return findLowestCommonAncestor(root->right, node1, node2);
    }
    else {
        return root; // node1과 node2가 root의 서로 다른 하위 트리에 있는 경우
    }
}

int main() {
    TreeNode n1 = { 4, NULL, NULL };
    TreeNode n2 = { 5, NULL, NULL };
    TreeNode n6 = { 7, NULL, NULL };
    TreeNode n3 = { 2, &n1, &n6 };
    TreeNode n4 = { 3, &n2, NULL };
    TreeNode n5 = { 1, &n3, &n4 };

    TreeNode* root = &n5;
    //inorder(root);
    in_order(root);
    printf("\n");
    preorder(root);
    printf("\n");
    pre_order(root);
    printf("\n");
    postorder(root);
    printf("\n");
    post_order(root);
    printf("\n");
    level_order(root);
    printf("\n");
    levelOrderTraversalRightToLeft(root);
}
