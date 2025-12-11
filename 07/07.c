#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINES 5000

typedef struct 
{
    long* tachyons;
    size_t size;
    
    void (*add)(struct line_tachyon *, long);
} line_tachyon;

void tachyon_add(line_tachyon *lt, long value) {
    lt->tachyons[value]++;
}

char** file_lines(char filename[], int* file_length)
{
    char* line = NULL;
    char **output = calloc(MAX_LINES, sizeof(char*));
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        exit(EXIT_FAILURE);
    }

    int num_lines = 0;
    ssize_t read;
    size_t len = 0;
    while ((read = getline(&line, &len, fptr)) != -1) {
        output[num_lines] = strdup(line);
        num_lines++;
    }

    fclose(fptr);
    free(line);
    *file_length = num_lines;
    return output;
}
line_tachyon create_line_tachyon(size_t size){
    line_tachyon line;
    line.size = size;
    line.tachyons = calloc(sizeof(long),size);
    for (size_t i =0; i<size;i++){
        line.tachyons[i] =0;
    }
    line.add = tachyon_add;
    return line;
}

int check_if_number_in_array(long* array, size_t size, long number){
    for (size_t i = 0; i<size;i++){
        if (array[i] == number){
            return 1;
        }
    }
    return 0;
}

// int calculate_splits_in_line(char** input, int num_lines, size_t current_line_num, line_tachyon* current_tachyons, line_tachyon* next_tachyons){
//     int splits =0;
//     for (size_t tachyon_pos_index = 0; tachyon_pos_index < current_tachyons->current_end_pointer; tachyon_pos_index++){
//         if (input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]] == '.'){
//             next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index];
//             next_tachyons->current_end_pointer++;
//         }else if (input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]] == '^')
//         {   
//             if (current_tachyons->tachyons[tachyon_pos_index] > 0 && input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]-1] == '.' ){
//                 splits++;
//                 input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]-1] = '|';
//                 next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index]-1;
//                 next_tachyons->current_end_pointer++;
//             }
//             if (current_tachyons->tachyons[tachyon_pos_index] < strlen(input[current_line_num]) && input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]+1] == '.' ){
//                 splits++;
//                 input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]+1] = '|';
//                 next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index]+1;
//                 next_tachyons->current_end_pointer++;
//             }

//         }
        
//     }
//     return splits;
// }

// int calculate_splitters_hit(char** input, int num_lines, size_t current_line_num, line_tachyon* current_tachyons, line_tachyon* next_tachyons){
//     int splits =0;
//     for (size_t tachyon_pos_index = 0; tachyon_pos_index < current_tachyons->current_end_pointer; tachyon_pos_index++){
//         if (input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]] == '.'){
            
//             next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index];
//             next_tachyons->current_end_pointer++;
//         }else if (input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]] == '^')
//         {   
//             if (current_tachyons->tachyons[tachyon_pos_index] > 0 && input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]-1] == '.' ){
                
                
//                 next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index]-1;
//                 next_tachyons->current_end_pointer++;
//             }
//             if (current_tachyons->tachyons[tachyon_pos_index] < strlen(input[current_line_num]) && input[current_line_num][current_tachyons->tachyons[tachyon_pos_index]+1] == '.' ){
                
//                 next_tachyons->tachyons[next_tachyons->current_end_pointer] = current_tachyons->tachyons[tachyon_pos_index]+1;
//                 next_tachyons->current_end_pointer++;
//             }

//         }
        
//     }
//     return splits;
// }
void calculate_time_paths(char** input, int num_lines, size_t current_line_num, line_tachyon* current_tachyons, line_tachyon* next_tachyons){
    for (size_t tachyon_pos_index = 0; tachyon_pos_index < current_tachyons->size; tachyon_pos_index++){
        if (input[current_line_num][tachyon_pos_index] == '.') {
            next_tachyons->tachyons[tachyon_pos_index] = next_tachyons->tachyons[tachyon_pos_index] + current_tachyons->tachyons[tachyon_pos_index];
        } else if (input[current_line_num][tachyon_pos_index] == '^')
        {
            if (tachyon_pos_index > 0 && input[current_line_num][tachyon_pos_index-1] == '.' ){
                next_tachyons->tachyons[tachyon_pos_index-1] = next_tachyons->tachyons[tachyon_pos_index-1] + current_tachyons->tachyons[tachyon_pos_index];
            }
            if (tachyon_pos_index <  strlen(input[current_line_num]) && input[current_line_num][tachyon_pos_index+1] == '.' ){
                next_tachyons->tachyons[tachyon_pos_index+1] = next_tachyons->tachyons[tachyon_pos_index+1] + current_tachyons->tachyons[tachyon_pos_index];
            }
        }
        

    }
}


int main(void)
{
    int num_lines = 0;
    char** output = file_lines("file.txt", &num_lines);
    long result =0;
    for (int i = 0; i < num_lines; i++) {
        size_t len = strlen(output[i]);
        if (len > 0 && output[i][len - 1] == '\n'){
            output[i][len - 1] = '\0';
        }
    }
    printf("TEST 1\n");
    size_t max_tachyons = strlen(output[0]);
    line_tachyon tachyon_store[num_lines];
    tachyon_store[0] = create_line_tachyon(max_tachyons);
    printf("TEST 2\n");
    for (size_t i =0; i<strlen(output[0]);i++){
        if (output[0][i] == 'S'){
            tachyon_store[0].add(&tachyon_store[0],i); 
        }
    }
    printf("TEST 2\n");
    printf("Tachyon 0: %ld,%ld\n",tachyon_store[0].tachyons[0],tachyon_store[0].size);
    for (size_t i = 1;i<num_lines;i++){
        tachyon_store[i] = create_line_tachyon(max_tachyons);
        calculate_time_paths(output,num_lines,i,&tachyon_store[i-1],&tachyon_store[i]);
        //printf("Current tachyons:");
        //for (size_t j = 0;j<tachyon_store[i].current_end_pointer;j++){
            //printf("%ld, ",tachyon_store[i].tachyons[j]);
        //}
        for (size_t j = 0;j<tachyon_store[i].size;j++){
            printf("%ld, ",tachyon_store[i].tachyons[j]);
    
    }
    printf("\n");
    }
    for (size_t j = 0;j<tachyon_store[num_lines-1].size;j++){
        printf("%ld, ",tachyon_store[num_lines-1].tachyons[j]);
        result = result + tachyon_store[num_lines-1].tachyons[j];
    }
    printf("\n");
    printf("Final Result: %ld\n", result);

    return 0;
}