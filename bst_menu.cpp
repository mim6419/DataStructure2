#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<iostream>
using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* alloc_new_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->left = new_node->right = NULL;
    new_node->data = data;
    return new_node;
}

TreeNode* find_min(TreeNode* node) {
    if (node != NULL) {
        while (node->left != NULL)
            node = node->left;
    }
    return node;
}

TreeNode* insert_node(TreeNode* root, int data) {
    if (root == NULL) {
        return alloc_new_node(data);
    }
    else if (data < root->data) {
        root->left = insert_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

void level_order(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        if (curr == NULL)break;
        q.pop();
        printf("%d ", curr->data);
        if (curr->left) {
            q.push(curr->left);
        }
        if (curr->right) {
            q.push(curr->right);
        }
    }
}
int search_node(TreeNode* root, int target, int count) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == target) {
        return count + 1;
    }
    else if (target < root->data) {
        return search_node(root->left, target, count + 1);
    }
    else {
        return search_node(root->right, target, count + 1);
    }
}

int do_free(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int count = 0;
    while (!q.empty()) {
        TreeNode* curr = q.front();
        if (curr == NULL)break;
        q.pop();
        printf("%d free, ", curr->data);
        count++;
        if (curr->left) {
            q.push(curr->left);
        }
        if (curr->right) {
            q.push(curr->right);
        }
    }
    free(root);
    return count;
}

TreeNode* delete_node(TreeNode* root, int data) {
    if (root != NULL) {
        if (root->data == data) {
            if (root->left == NULL && root->right == NULL) {
                free(root);
                return NULL;
            }
            else {
                if (root->left == NULL) {
                    TreeNode* temp = root->right;
                    free(root);
                    return temp;
                }
                if (root->right == NULL) {
                    TreeNode* temp = root->left;
                    free(root);
                    return temp;
                }
                TreeNode* temp = find_min(root->right);
                root->data = temp->data;
                root->right = delete_node(root->right, temp->data);
            }
        }
        else {
            if (data < root->data) {
                root->left = delete_node(root->left, data);
            }
            else {
                root->right = delete_node(root->right, data);
            }
        }
    }
    return root;
}

int main() {
    int input;
    TreeNode* root = NULL;
    while (true) {
        printf("1. 입력\n");
        printf("2. 탐색\n");
        printf("3. Level Order\n");
        printf("4. 삭제\n");
        printf("5. 종료\n");
        printf("번호를 넣으시세요: ");
        scanf("%d", &input);
        switch (input) {
            case 1:
                while (true) {
                    int data;
                    printf("입력 (종료는 -1) : ");
                    scanf("%d", &data);
                    if (data == -1)
                        break;
                    root = insert_node(root, data);
                }
                break;
            case 2:
                int target;
                int count;
                printf("탐색할 노드? : ");
                scanf("%d", &target);
            
                count = search_node(root, target, 0);
                if (count == 0) {
                    printf("%d은 존재하지 않습니다\n\n", target);
                    break;
                }
                else {
                    printf("%d 은 %d회 탐색으로 발견\n\n", target, count);
                    break;
                }
            case 3:
                printf("[Level]\n");
                level_order(root);
                printf("\n");
                break;
            case 4:
                int dNode;
                printf("삭제할 노드를 입력하세요: ");
                scanf("%d", &dNode);
                root = delete_node(root, dNode);
                printf("%d 삭제 ", dNode);
                level_order(root);
                printf("\n\n");
                break;
            case 5:
                int cnt = do_free(root);
                printf("\n총 %d개의 노드가 free됨.", cnt);
                exit(0);
        }
    }
    return 0;
}