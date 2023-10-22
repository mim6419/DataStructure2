#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
}Node;

void init(Node** head) {
    *head = (Node*)malloc(sizeof(Node));
    (*head)->data = NULL;
    (*head)->next = *head;
    (*head)->prev = *head;
}

Node* alloc_new_node(char data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void add_new_node(Node** head, const char data) {
    Node* new_node = alloc_new_node(data);
    Node* curr = *head;
    for (; curr->next != *head; curr = curr->next);
    curr->next = new_node;
    new_node->prev = curr;
    new_node->next = *head;
    (*head)->prev = new_node;
}

void add(Node** head, char data, int index) {
    Node* new_node = alloc_new_node(data);
    Node* curr = *head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next->prev = new_node;
    new_node->prev = curr;
    curr->next = new_node;

}

void delete_all(Node* head, char data) {
    Node* curr = head->next;
    while (curr != head) {
        if (curr->data == data) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        curr = curr->next;
    }
}



void print_list(Node* head) {
    Node* curr = head->next;
    if (head->next == head) {
        printf("NULL\n");
        return;
    }
    for (; curr != head; curr = curr->next) {
        printf("%c", curr->data);
    }
    printf("\n");
}

int find(Node* head, const char* data) {
    int count = strlen(data);
    int answer = 1;
    int move = 0;
    Node* curr = head->next;
    while (curr != head) {
        for (int i = 0; i < 100;  i++) {
            if (curr->data != data[0]) {
                move++;
                curr = curr->next;
                if (curr == head) {
                    for (int i = 0; i < strlen(data); i++) {
                        printf("%c", data[i]);
                    }
                    printf(" = ");
                    return 0;
                }
            }
            else if (curr->data == data[0])
                break;
        }
        for (int i = 1; i < count; i++) {
            if (curr->next->data == data[i]) {
                answer++;
                curr = curr->next;

            }
        }
        if (answer == count) {
            for (int i = 0; i < strlen(data); i++) {
                printf("%c", data[i]);
            }
            printf(" = ");
            return move;
        }
        curr = curr->next;
        move++;
        if (curr == head)
            break;
    }
    for (int i = 0; i < strlen(data); i++) {
        printf("%c", data[i]);
    }
    printf(" = ");
    return 0;
}

int find_reversed(Node* head, const char* data) {
    int count = strlen(data);
    int answer = 1;
    int move = 0;
    int length = 0;;
    Node* curr = head;
    while (curr->next != head) {
        curr = curr->next;
        length++;
    }

    curr = head->prev;
    while (curr != head) {
        for (int i = 0; i < 100; i++) {
            if (curr->data != data[0]) {
                move++;
                curr = curr->prev;
                if (curr == head) {
                    for (int i = 0; i < strlen(data); i++) {
                        printf("%c", data[i]);
                    }
                    printf(" = ");
                    return 0;
                }
            }
            else if (curr->data == data[0])
                break;
        }
        for (int i = 1; i < count; i++) {
            if (curr->prev->data == data[i]) {
                answer++;
                curr = curr->prev;
            }
        }
        if (answer == count) {
            for (int i = 0; i < strlen(data); i++) {
                printf("%c", data[i]);
            }
            printf(" = ");
            return length - (move + count) ;
        }
        curr = curr->prev;
        move++;
        if(curr == head)
            break;
    }
    for (int i = 0; i < strlen(data); i++) {
        printf("%c", data[i]);
    }
    printf(" = ");
    return 0;
}

int main(int argc, char* argv[]) {
    Node* head;
    init(&head);
    add_new_node(&head, 'a');
    add_new_node(&head, 'p');
    add_new_node(&head, 'p');
    add_new_node(&head, 'l');
    add_new_node(&head, 'e');
    add_new_node(&head, 'c');
    add_new_node(&head, 'a');
    add_new_node(&head, 'r');
    add_new_node(&head, 'r');
    add_new_node(&head, 'o');
    add_new_node(&head, 't');
    add_new_node(&head, 'b');
    add_new_node(&head, 'a');
    add_new_node(&head, 'n');
    add_new_node(&head, 'a');
    add_new_node(&head, 'n');
    add_new_node(&head, 'a');
    print_list(head);

    delete_all(head, 'p');
    delete_all(head, 'a');
    print_list(head);
    delete_all(head, 'n');

    add(&head, 'a', 0);
    add(&head, 'p', 1);
    add(&head, 'p', 1);
    add(&head, 'a', 6);

    print_list(head);
    
    int index = find(head, "carrot");
    if (index != 0) {
        printf("TRUE, idx = %d\n", index);
    }
    else
        printf("FALSE\n");

    int idx = find_reversed(head, "car");
    
    if (idx != 0) {
        printf("TRUE, idx = %d\n", idx);
    }
    else
        printf("FALSE\n");
    return 0;
}

