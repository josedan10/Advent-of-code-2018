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

    printf("\nMy cadena: %s\n", str);

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
                        printf("Se repite %c dos veces.\n", str[i]);
                    }
                    break;
                
                case 3:
                    if (!check3Already){
                        *check3 += 1;
                        check3Already = 1;
                        printf("Se repite %c tres veces.\n", str[i]);
                    }
                    break;
                
                default:
                    break;
            }
            
            table[n++] = str[i];
        }
    }
}

int main()
{
    int checkTwo = 0, checkThree = 0, n = 0;
    char str[30];
    FILE * fp;

    fp = fopen("day2/input.txt", "r");

    if (fp != NULL) {
        while(!feof(fp)) {
            printf("\n===================Fila: %d\n", ++n);
            fscanf(fp, "%s", str);
            validateWord(str, &checkThree, &checkTwo);
        }
    }

    printf("\nEn total se repiten %d letras dos veces y %d letras 3 veces. La checksum es %d\n\n", checkTwo, checkThree, checkThree * checkTwo);

    fclose(fp);

    system("PAUSE");

    return 0;
}
