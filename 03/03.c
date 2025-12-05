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
int find_voltage_part1(char* number) {
    int len = strlen(number);
    int first_index = 0;
    //printf("Beginning Number: %c, length: %i\n", number[first_index],len);

    for (int i = 1;i<len-1;i++){
        //printf("i: %d, number: %c\n",i, number[i]);
        if (number[i] > number[first_index]){
            first_index = i;
            //printf("First Index: %d\n", first_index);
        }
    }
    //printf("First Number: %c\n", number[first_index]);
    int second_index = first_index+1;
    for (int j = second_index; j < len; j++){
        if ( number[j]> number[second_index]){
            second_index = j;
        }
    }
    //printf("Second Number: %c\n", number[second_index]);
    char result_str[3];
    result_str[0]=number[first_index];
    result_str[1]=number[second_index];
    result_str[3]='\0';
    //printf("result: %s\n",result_str);
    return atoi(result_str);
}

long find_voltage_part2(char* number) {
    int len = strlen(number);
    //printf("len: %d",len);
    char testnumber[] = "000000000000";

    //printf("Beginning Number: %c, length: %i\n", number[first_index],len);
    int start = 0;
    int len_testnumber = 0;
    for (int i = 0;i<12;i++){
        int remaining = 12 - len_testnumber;
        int end = len - remaining;
        int max_in_window = 0;
        int max_in_window_index = start;
        //printf("Remaining: %d, start: %d, end: %d\n max: %d, index: %d\n",remaining,start,end,max_in_window,max_in_window_index);
        for (int j = start; j<=end;j++){
            if (max_in_window < (number[j] - '0')){
                max_in_window = (number[j]-'0');
                max_in_window_index = j;
            } 
        }
        testnumber[i] = (char) max_in_window + '0';
        len_testnumber++;
        start = max_in_window_index+1;
    }
    //printf("Testnumber: %s",testnumber);
    char *endptr;
    long final_voltage = strtol(testnumber,&endptr,10);
    //printf("Final Voltage %ld\n", final_voltage);
    //getchar();
    return final_voltage;
}


int main(void)
{
    int num_lines = 0;
    char **output = file_lines("file.txt", &num_lines);
    
    // Game variables
    long result = 0;
    for (int i = 0; i < num_lines; i++) {
        output[i][strlen(output[i])-1] = '\0';
        //printf("Output: %s\n",output[i]);
        long voltage = find_voltage_part2(output[i]);
        printf("Final voltage: %ld\n", voltage);
        result = result + voltage;

        //printf("Result after %s: %ld \n", output[i], result);
        //getchar();
        
    }
    printf("Final Result: %ld\n", result);
}
