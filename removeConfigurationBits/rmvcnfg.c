#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Insuficient arguments\n");
        printf("Must provide input and output file names and a target string\n");
        return 0;
    }

    FILE *A = fopen(argv[1], "r");
    if(errno){
        printf("Failed to open file \"%s\"", argv[1]);
        return 0;
    }
    FILE *B = fopen(argv[2], "w");
    if(errno){
        printf("Failed to open file \"%s\"", argv[2]);
        return 0;
    }
    
    printf("Modifying file \"%s\" into \"%s\"\nRemoving string \"%s\"", argv[1], argv[2], argv[3]);

    char *targetLine = argv[3];
    int targetLineLength = 0;
    for(int i = 0; targetLine[i] != '\0'; i++){
        targetLineLength++;
    }
    char *currentLine = malloc(sizeof(char)*targetLineLength);
    char c;

    int p = 0;
    int sequenceFlag = 0;
    int continueFlag = 0;
    int ignoreNewLineFlag = 0;

    while(!feof(A)){
        c = fgetc(A);

        if(p < targetLineLength && c != EOF){
            currentLine[p++] = c;
            if(p == targetLineLength){
                continueFlag = 1;
                sequenceFlag = 1;
                ignoreNewLineFlag = 1;
                for(int i = 0; i < p; i++){
                    if(currentLine[i] != targetLine[i]){
                        sequenceFlag = 0;
                        ignoreNewLineFlag = 0;
                    }
                }
                if(sequenceFlag == 0){
                    for(int i = 0; i < p; i++){
                        fprintf(B, "%c", currentLine[i]);
                    }
                }
            }
        }
        if(continueFlag == 1){
            continueFlag = 0;
            continue;
        }

        if(c == '\n'){
            if(ignoreNewLineFlag == 1){
                p = 0;
                continue;
            }
            if(p < targetLineLength){
                for(int i = 0; i < p; i++){
                    fprintf(B, "%c", currentLine[i]);
                }
            } else{
                fprintf(B, "\n");
            }
            p = 0;
        } else if(c == EOF){
            if(p < targetLineLength){
                for(int i = 0; i < p; i++){
                    fprintf(B, "%c", currentLine[i]);
                }
            }
        } else if(p == targetLineLength){
            fprintf(B, "%c", c);
        }

        ignoreNewLineFlag = 0;
    }

    free(currentLine);
    int cl = fclose(A);
    cl = fclose(B);
    return 0;
}