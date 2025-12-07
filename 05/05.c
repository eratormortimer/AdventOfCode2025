#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "uthash.h"


#define MAX_LINES   5000
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

struct fresh_hash {
    int id;            /* we'll use this field as the key */
    UT_hash_handle hh; /* makes this structure hashable */
};

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

void get_ranges_and_ids(char** input, int num_lines, char** ranges, char** ids){
    size_t divider = 0;
    for (size_t i =0;i<num_lines;i++){
        if (strlen(input[i])==0){
            divider =i;
            break;
        }
    }
    for (size_t i =0;i<divider;i++){
        ranges[i] = strdup(input[i]);
    }
    
    for (size_t i = divider+1;i<num_lines;i++){
        ids[i-divider-1]=strdup(input[i]);
    }
}
void add_ranges_to_hash(char** ranges,struct fresh_hash* ids){
    for (size_t i =0;i<LEN(ranges))
}


long find_id_exists(struct fresh_hash* ids,int id) {
    struct fresh_hash *s=NULL;

    HASH_FIND_INT( ids, &id, s );
    if (s != NULL){
        return 1;
    }
    return 0;
}

int main(void)
{
    int num_lines = 0;
    char** output = file_lines("file.txt", &num_lines);
    printf("TEST\n");
    // Game variables
    for (int i = 0; i < num_lines; i++) {
        printf("output: %s",output[i]);
        printf("LEN: %d, %d\n",LEN(output[i]),strlen(output[i]));
        if (strlen(output[i]) != 0){
            output[i][strlen(output[i])-1] = '\0';
        }
        
    }
    long result = 0;
    char** ranges = calloc(num_lines,sizeof(char*));
    char* ids = calloc(num_lines,sizeof(char));
    get_ranges_and_ids(output,num_lines,ranges,ids);
    struct fresh_hash* eatable_hash = NULL;
    add_ranges_to_hash(ranges,eatable_hash);
    for (size_t i =0;i<strlen(ids);i++){
        result = result + find_id_exists(eatable_hash,ids[i]);
    }
    printf("Final Result: %ld\n", result);
}
