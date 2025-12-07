#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINES   5000
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))


char** file_lines(char filename[], int* file_length)
{
    char* line = NULL;
    char **output = calloc(MAX_LINES, sizeof(char*));
    // Open a file in read mode
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        exit(EXIT_FAILURE);
    }
        
    int num_lines = 0;
    ssize_t read;
    size_t len = 0;
    while ((read = getline(&line, &len, fptr)) != -1) {
        output[num_lines] = line;
        num_lines++;
        line = NULL;
    }

    fclose(fptr);
    if (line)
        free(line);
    *file_length = num_lines; 
    return output;

}

char** solve_adjacency(char** input, int height){
    char** matrix = calloc(height , sizeof(char*));
    int width = strlen(input[0]);
    for (size_t i = 0;i<height;i++){
        matrix[i] = malloc(strlen(input[i]) + 1);
        for (size_t j = 0; j<=width; j++){
            if (input[i][j] == '@' || (input[i][j] >= '0' && input[i][j] <= '9')) {
                matrix[i][j] ='0';
            } else {
                matrix[i][j] = input[i][j];
            }
        }
        //printf("%s\n",matrix[i]);
    }
    //printf("height %d, width %d\n",height,width);
    for (int i = 0;i<height;i++){
        for (int j = 0; j<width; j++){
            if (matrix[i][j]=='.'){
                continue;
            }
            int count = 0;
            for (int k = i -1; k<=i+1;k++){
                if (k < 0 || k>= height){
                        //printf("skipped k %d\n",k);
                        continue;
                }
                for (int l = j-1;l<=j+1;l++){
                    if (l < 0 || l>= width){
                        //printf("skipped l%d\n",l);
                        continue;
                    }
                    if (matrix[k][l] != '.' && (i!=k || j!=l)) {
                        //printf("Found on %d %d\n",k,l);
                        count++;
                    }

                }
            }
            matrix[i][j]=count + '0';
        }
        //printf("%s\n",matrix[i]);
    }
    return matrix;
}
long get_accessible_paperrolls(char** matrix,int num_lines){
    long count = 0;
    //printf("Length %d\n",num_lines);
    for (int i=0; i<num_lines;i++){
        //printf("%s\n",matrix[i]);
        //printf("strlen %d\n",strlen(matrix[i]));
        for (int j=0; j<strlen(matrix[i]);j++){
            //printf("TEST %c\n",matrix[i][j]);
        
            if (matrix[i][j] != '.' &&  (matrix[i][j] -'0') <4){
                count++;
            }
        }
    }
    return count;
}
void remove_paperrolls(char** matrix, int num_lines){
    for (int i=0; i<num_lines;i++){
        //printf("%s\n",matrix[i]);
        //printf("strlen %d\n",strlen(matrix[i]));
        for (int j=0; j<strlen(matrix[i]);j++){
            //printf("TEST %c\n",matrix[i][j]);
        
            if (matrix[i][j] != '.' &&  (matrix[i][j] -'0') <4){
                matrix[i][j] = '.';
            }
        }
    }
}

int main(void)
{
    int num_lines = 0;
    char **output = file_lines("file.txt", &num_lines);
    printf("TEST\n");
    // Game variables
    for (int i = 0; i < num_lines; i++) {
        printf("output: %s",output[i]);
        printf("LEN: %d, %d\n",LEN(output[i]),strlen(output[i]));
        if (strlen(output[i]) != 0){
            output[i][strlen(output[i])-1] = '\0';
        }
        printf("output: %s\n",output[i]);
    }
    long result = 0;
    long count = 1;
    char** matrix = solve_adjacency(output,num_lines);
    while (count !=0){
        count = get_accessible_paperrolls(matrix,num_lines);
        remove_paperrolls(matrix,num_lines);
        matrix = solve_adjacency(matrix,num_lines);
        result = count + result;
    }
    printf("Final Result: %ld\n", result);
}
