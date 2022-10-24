#define TARGET_LINE_LENGTH 17

#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *A = fopen("teste.txt", "r");
    FILE *B = fopen("newTest.txt", "w");
    char targetLine[] = ":0300000040DF07D7";
    char l[TARGET_LINE_LENGTH];
    char c;
    int p = 0;
    int checking = 0;
    int ignoreEOL = 0;
    while (!feof(A)){
        c = fgetc(A);
        if(p < TARGET_LINE_LENGTH){
            l[p++] = c;
            if(p == TARGET_LINE_LENGTH){
                int f = 1;
                for(int j = 0; j < TARGET_LINE_LENGTH; j++){
                    if(targetLine[j] != l[j]){
                        f = 0;
                    }
                }
                if(f==0){
                    printf("sequence not detected\n");
                    for(int i = 0; i < TARGET_LINE_LENGTH; i++){
                        fprintf(B, "%c", l[i]);
                    }
                } else{
                    printf("sequence detected\n");
                    ignoreEOL = 1;
                }
                checking = 1;
            }
        }
        if(checking == 1){
            printf("checking done\n");
            checking = 0;
            continue;
        }
        if(c == '\n' || feof(A)){
            if(c == '\n'){
                printf("new line\n");
                if(ignoreEOL == 1){
                    ignoreEOL = 0;
                    p = 0;
                    printf("new line ignored\n");
                    continue;
                }
                if(p < TARGET_LINE_LENGTH){
                    printf("printing array\n");
                    for(int i = 0; i < p; i++){
                        fprintf(B, "%c", l[i]);
                        printf("%d ", (int)l[i]);
                    }
                    printf("\n");
                } else{
                    fprintf(B, "\n");
                }
            } else{
                printf("eof\n");
                if(p < TARGET_LINE_LENGTH){
                    p--;
                    printf("printing array %d\n", p);
                    for(int i = 0; i < p; i++){
                        fprintf(B, "%c", l[i]);
                        printf("%d ", (int)l[i]);
                    }
                }
            }
            p = 0;
        } else if(p == 18){
            fprintf(B, "%c", c);
            printf("printing %c \n", c);
        }
        ignoreEOL = 0;
    }
    int cl = fclose(A);
    cl = fclose(B);
}