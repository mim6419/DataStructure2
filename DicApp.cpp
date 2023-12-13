#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 50
#define MAX_MEANING_SIZE 200

typedef struct {
    char word[MAX_WORD_SIZE];
    char meanings[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode {
    element key;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* createNode(element key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

TreeNode* insert(TreeNode* root, element key) {
    if (root == NULL) {
        return createNode(key);
    }

    int cmp = strcmp(key.word, root->key.word);
    if (cmp < 0) {
        root->left = insert(root->left, key);
    }
    else if (cmp > 0) {
        root->right = insert(root->right, key);
    }

    return root;
}

element* search(TreeNode* root, char* word) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(word, root->key.word);
    if (cmp < 0) {
        return search(root->left, word);
    }
    else if (cmp > 0) {
        return search(root->right, word);
    }
    else {
        return &root->key;
    }
}

TreeNode* addDic(TreeNode* root) {
    element key;
    FILE* file = fopen("dic.txt", "a");

    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return NULL;
    }

    printf("�߰��� ���� �ܾ �Է��ϼ���: ");
    scanf("%s", key.word);

    if (search(root, key.word) != NULL) {
        printf("�̹� �ִ� �ܾ��Դϴ�.\n");
        fclose(file);
        return root;
    }

    printf("���� �Է��ϼ��� (�������� 'exit' �Է�): ");
    strcpy(key.meanings, "");  // �� �ʱ�ȭ

    int meaningNum = 1;  // �� ��ȣ
    while (1) {
        char meaning[MAX_MEANING_SIZE];
        scanf("%s", meaning);
        if (strcmp(meaning, "exit") == 0) {
            break;
        }
        // �� �߰�
        strcat(key.meanings, " (");
        char numStr[2];
        sprintf(numStr, "%d", meaningNum);
        strcat(key.meanings, numStr);
        strcat(key.meanings, ") ");
        strcat(key.meanings, " / ");
        strcat(key.meanings, meaning);
        meaningNum++;
    }

    fprintf(file, "\n%s:%s", key.word, key.meanings);

    // Ʈ������ �߰�
    root = insert(root, key);
    return root;
    fclose(file);
}

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

TreeNode* treeInit(TreeNode* root) {
    element key;
    FILE* file = fopen("dic.txt", "r");
    if (file == NULL)
        return NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* token = strtok(line, ":");
        if (token) {
            strcpy(key.word, token);
        }
        token = strtok(NULL, "");
        if (token) {
            strcpy(key.meanings, token);
        }
        root = insert(root, key);
    }

    fclose(file);
    return root;
}

void searchWord(TreeNode* root) {
    while (true) {
        char searchWord[MAX_WORD_SIZE];
        printf("�ܾ �˻��ϼ��� (�����Ϸ��� 'exit' �Է�): ");
        scanf("%s", searchWord);

        if (strcmp(searchWord, "exit") == 0) {
            break;
        }
        element* result = search(root, searchWord);
        if (result != NULL) {
            printf("%s : %s\n", result->word, result->meanings);
        }
        else {
            printf("�ܾ ã�� �� �����ϴ�.\n");
        }
    }
}

void searchMeaningInTree(TreeNode* root, const char* searchMeaning) {
    if (root != NULL) {
        // ���� ����Ʈ������ �˻�
        searchMeaningInTree(root->left, searchMeaning);

        // ���� ��忡�� ���� �˻�
        char* meanings = root->key.meanings;
        char* meaningToken = strtok(meanings, " / ");
        while (meaningToken != NULL) {
            // �� �濡 ���� �˻�
            if (strstr(meaningToken, searchMeaning) != NULL) {
                printf("%s : %s\n", root->key.word, meanings);
                break;
            }
            meaningToken = strtok(NULL, " / ");
        }

        // ������ ����Ʈ������ �˻�
        searchMeaningInTree(root->right, searchMeaning);
    }
}


void searchMeaning(TreeNode* root) {
    while (true) {
        char searchWord[MAX_WORD_SIZE];
        printf("���� �˻��ϼ��� (�����Ϸ��� 'exit' �Է�): ");
        scanf("%s", searchWord);

        if (strcmp(searchWord, "exit") == 0) {
            break;
        }
        searchMeaningInTree(root, searchWord);
    }
}


void printMenu() {
    printf("------------------Menu---------------\n");
    printf("1.�ܾ��߰�\n");
    printf("2.Leaf Node ���\n");
    printf("3.�ܾ� ��ȸ\n");
    printf("4.�ܾ� ����\n");
    printf("5.����\n");
    printf("-------------------------------------\n");
}

int main() {
    TreeNode* root = NULL;
    element key;
    root = treeInit(root);
    int input;
    while (true) {
        printMenu();
        printf("��ȣ�� �Է��ϼ���:");
        scanf("%d", &input);
        switch (input) {
            case 1:
                root = addDic(root);
                break;
            case 2:
                break;
            case 3:
                searchWord(root);
                break;
            case 4:
                searchMeaning(root);
                break;
            case 5:
                printf("�����մϴ�\n");
                freeTree(root);
                return 0;
            default:
                break;
        }
    }
    return 0;
}
