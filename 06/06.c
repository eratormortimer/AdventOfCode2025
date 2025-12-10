#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
char extract_single_char(char* str) {
    if (!str) return '\0';

    for (size_t i =0; i<strlen(str);i++){
        if (str[i] == ' '){
            continue;
        }
        return str[i];
    }
    return '\0';
}
size_t find_end_from_current_line_positon(char* input_line,size_t* current_line_positon){
    size_t rtn =0;
    int finished_number =0;
    int found_first_non_space =0;
    printf("TEST\n");
    for (size_t i = *current_line_positon;i<strlen(input_line);i++){
        printf("Char: %c",input_line[i]);
        while (input_line[i]==' ' && !found_first_non_space ){
            i++;
        }
        if (input_line[i] != ' '){
            if (finished_number){
                rtn = i-1;
                return rtn;
            } else {
                found_first_non_space =1;
                continue;
            }
        }else{
            finished_number =1;
            continue;
        }
    }
    return strlen(input_line)+1;
}
// void check_endposition_aganist_other_lines(char** input,int num_lines,size_t* end_position){
//     for (size_t i =1;i<num_lines-1;i++){

//     }
// }
void substring(char *src, char *dest, size_t start, size_t end) {
    size_t j = 0;
    printf("parameters: %s, %s, %ld, %ld\n",src,dest,start,end);
    for (size_t i = start; i < end && src[i] != '\0'; i++) {
        dest[j++] = src[i];
    }
    dest[j] = '\0';
    printf("Substring %s\n",dest);
}

long get_line_number(char** input, int num_lines,size_t* current_line_positon){
    long rtn = 0;
    size_t end_position = find_end_from_current_line_positon(input[num_lines-1],current_line_positon);
    //check_endposition_aganist_other_lines(input,num_lines,&end_position);
    printf("Line goes from %zu to %ld\n",*current_line_positon,end_position);
    char sign_array[16];
    memset(sign_array, 0, 16);
    substring(input[num_lines-1],sign_array,*current_line_positon,end_position);
    printf("Sign %s\n",sign_array);
    char sign = extract_single_char(sign_array);
    for (size_t i = 0;i<num_lines-1;i++){
        char *endptr;
        char number[16];
        memset(number, 0, 16);
        substring(input[i],number,*current_line_positon,end_position);
        long num = strtol(number, &endptr, 10);
        if (num == 0){
            continue;
        }
        printf("Number Char %s and long %ld\n",number,num);
        if (num==3599){
            getchar();
        }
        if (rtn == 0){
            rtn = num;
        } else {
            printf("Sign %c\n",sign);
            if (sign == '+') {
                printf("rtn %ld, num %ld\n",rtn,num);
                rtn = rtn + num;
            } else if (sign == '-') 
            {
                rtn = rtn - num;
            }else if (sign == '*')
            {
                rtn = rtn * num;
            }else if (sign == '/')
            {
                rtn = rtn / num;
            }else  {
                printf("Sign %s not valid\n",sign);
            }
        }
        printf("rtn: %ld\n",rtn);
        
    }
    *current_line_positon = end_position;
    return rtn;
}

long get_column_number(char** input, int num_lines,size_t* current_line_positon){
    long rtn = 0;
    size_t end_position = find_end_from_current_line_positon(input[num_lines-1],current_line_positon);
    //check_endposition_aganist_other_lines(input,num_lines,&end_position);
    printf("Line goes from %zu to %ld\n",*current_line_positon,end_position);
    char sign_array[16];
    memset(sign_array, 0, 16);
    substring(input[num_lines-1],sign_array,*current_line_positon,end_position);
    printf("Sign %s\n",sign_array);
    char sign = extract_single_char(sign_array);
    for (size_t i = *current_line_positon; i<end_position;i++){
        char number[16];
        memset(number, 0, 16);
        for (size_t j =0;j<num_lines-1;j++){
            number[j] = input[j][i];
        }
        number[num_lines-1] = '\0';
        char *endptr;
        long num = strtol(number, &endptr, 10);
        printf("Number Char %s and long %ld\n",number,num);
        if (rtn == 0){
            rtn = num;
        } else {
            printf("Sign %c\n",sign);
            if (sign == '+') {
                printf("rtn %ld, num %ld\n",rtn,num);
                rtn = rtn + num;
            } else if (sign == '-') 
            {
                rtn = rtn - num;
            }else if (sign == '*')
            {
                rtn = rtn * num;
            }else if (sign == '/')
            {
                rtn = rtn / num;
            }else  {
                printf("Sign %c not valid\n",sign);
            }
        }
    }
    *current_line_positon = end_position;
    return rtn;
}

int main(void)
{
    int num_lines = 0;
    char **output = file_lines("file.txt", &num_lines);
    
    // Game variables
    long result = 0;
    for (int i = 0; i < num_lines; i++) {
        output[i][strlen(output[i])-1] = '\0';
        
    }
    printf("TEST\n");
    size_t current_line_position = 0;
    while (current_line_position < strlen(output[0])){
        result = result + get_column_number(output,num_lines,&current_line_position);
        printf("result: %ld\n",result);
        //getchar();
    }
    printf("Final Result: %ld\n", result);
}
