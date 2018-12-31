#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNotVerified(char *arr, char letter, int n) {
    int i = 0;

    while(i < n && arr[i] != letter) i++;
    return i == n;
}

void validateWord(char *str, int *check3, int *check2) {
    int i, j, n = 0, count, check2Already = 0, check3Already = 0;
    char table[27] = "";

    for (i = 0; i < strlen(str) - 1; i++) {
        
        if (isNotVerified(table, str[i], n)) {
            count = 1;

            for (j = i + 1; j < strlen(str); j ++) {
                if (str[j] == str[i]) count++;
            }

            switch (count) {
                case 2:
                    if (!check2Already){
                        *check2 += 1;
                        check2Already = 1;
                    }
                    break;
                
                case 3:
                    if (!check3Already){
                        *check3 += 1;
                        check3Already = 1;
                    }
                    break;
                
                default:
                    break;
            }
            
            table[n++] = str[i];
        }
    }
}

typedef struct node {
    char text[30];
    struct node *next;
} Node;

typedef struct list {
    Node *root;
    unsigned short length;
} List;

// List constructor

List* newList() {
    List *list = (List *) malloc(sizeof(List));
    list->root = NULL;
    list->length = 0; 
    return list;
}

void addToList(List *list, char *str) {
    Node *node = (Node *) malloc(sizeof(Node));
    strcpy(node->text, str);
    node->next = NULL;
    
    Node *auxList = list->root;
    
    if (list->root == NULL) list->root = node;
    else {
        while (auxList->next != NULL) auxList = auxList->next;
        auxList->next = node;
    }

    list->length++;
}

void removeFromList(List *list, Node *node) {
    Node *auxNode = list->root;

    if (!list->length) return; // La lista está vacía

    if (auxNode = node) {
        list->root = auxNode->next;
        free(node);
    } else {
        while (auxNode->next != node) auxNode = auxNode->next;
        auxNode->next = node->next;

        free(node);
    }

    list->length--;
}

/*
    Description: this function return true if only ONE character is different comparing 2 strings
    @params:
    char *str1, String 1 different of NULL
    char *str2, String 2 different of NULL
    int len     Length of strings
*/

int compareStrings(char *str1, char *str2, int len) {
    int counter = 0;

    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) counter++;
    }

    return counter == 1;
}

void printCoincidence(char *str1, char *str2) {
    unsigned short len = strlen(str1), i;
    printf("Frase de coincidencia: \n");
    for (i = 0; i < len; i++)
        if (str1[i] == str2[i]) printf("%c", str1[i]);
        
    printf("\n");
}

int main() {
    int checkTwo = 0, checkThree = 0, n = 0, i;
    char str[30], auxStr[30];
    Node *auxCompNode;
    List *list = newList();
    FILE * fp;

    fp = fopen("day2/input.txt", "r");

    if (fp != NULL) {
        while(!feof(fp)) {
            fscanf(fp, "%s", str);
            addToList(list, str);
            n++;
            // validateWord(str, &checkThree, &checkTwo);
            // free(str);
        }
    }

    printf("Escaneados un total de %d strings\n\n", n);

    // printf("\nEn total se repiten %d letras dos veces y %d letras 3 veces. La checksum es %d\n\n", checkTwo, checkThree, checkThree * checkTwo);

    fclose(fp);

    while (list->length > 2) {
        strcpy(auxStr, list->root->text);

        auxCompNode = list->root->next;

        while (auxCompNode != NULL && !compareStrings(auxStr, auxCompNode->text, strlen(auxStr))) auxCompNode = auxCompNode->next;

        if (auxCompNode != NULL) {
            // Se encontraron dos strings que difieren solo en un caracter
            printCoincidence(auxCompNode->text, auxStr);
            break;
        } else {
            removeFromList(list, list->root);
        }

    }

    // printf("Strings finales: %s y %s\n", list->root->text, list->root->next->text);

    system("PAUSE");

    return 0;
}
