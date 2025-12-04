#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_LINES   5000


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

char *read_first_line(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return NULL;

    char *line = NULL;
    size_t len = 0;

    ssize_t read = getline(&line, &len, fp);
    fclose(fp);

    if (read == -1) {      // empty file or read error
        free(line);
        return NULL;
    }

    // remove trailing newline
    line[strcspn(line, "\n")] = '\0';

    return line;           // caller must free()
}

long check_if_valid_part_1(long buffer) {
    char number[20];
    sprintf(number, "%ld", buffer);
    long len = strlen(number);
    if (len % 2 != 0){
        return 0;
    }
    char first_half[len/2 + 1];
    char second_half[len/2 + 1];
    strncpy(first_half, number, len/2);
    first_half[len/2] = '\0';
    strncpy(second_half, number+len/2, len/2);
    second_half[len/2] = '\0';
    //printf("first half: %s, second: %s\n", first_half, second_half);
    if (strcmp(first_half, second_half)){
        return 0;
    }
    //printf("first half: %s, second: %s\n", first_half, second_half);
    //getchar();
    return 1;
}

long check_if_valid_part_2(long buffer) {
    char number[20];
    sprintf(number, "%ld", buffer);
    long len = strlen(number);
    for (int i = 1; i<=len/2; i++){
        if (len % i == 0){
            int j = 0;
            //printf("i: %d\n",i);
            while (j + i < len){
                int k = j+i;
                //printf("j: %d, k; %d\n",j,k);
                //printf("number[j]: %c, number[k]: %c\n",number[j],number[k]);
                if (number[j] != number[k]){
                    goto next_intervall;
                }
                j++;
            }
            //printf("VALID: %s\n",number);
            return 1;
        }
        next_intervall: continue;
    }
    return 0;
}

int main(void)
{
    int num_lines = 0;
    char *output = read_first_line("file.txt");
    printf("Test\n");
    if (!output) {
        printf("Failed to read first line.\n");
        return 1;
    }
    char *saveptr1, *saveptr2;

    long result = 0;
    printf("Line: %s\n", output);
    // size_t len = sizeof(output[0]);
    // char* line_copy = malloc(len+1);
    // memcpy(line_copy, output[0], len);
    // line_copy[len] = '\0';  

    char* range = strtok_r(output, ",", &saveptr1);
    printf("Range: %s\n", range);
    while(range != NULL) {
        char *endptr;
        long i = strtol(strtok_r(range, "-", &saveptr2),&endptr,10);
        long j = strtol(strtok_r(NULL, "-", &saveptr2),&endptr,10);
        
        for (i; i<=j; i++){
            //printf("i: %ld, j: %ld\n",i,j);
            //printf("valid: %d\n", check_if_valid(i));
            if (check_if_valid_part_2(i)) {
                result = result + i;
                //printf("Result: %ld, i: %ld\n", result, i);
            }
            //printf("Initial Result: %d\n", result);
        }
        printf("Initial Result: %ld\n", result);
        //getchar();
        range = strtok_r(NULL, ",", &saveptr1);
        printf("Range: %s\n", range);
        
    }
    printf("Result: %ld\n", result);
}