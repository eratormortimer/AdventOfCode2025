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
int mod(int a, int b) {
    int r = a % b;
    if (r < 0) r += (b > 0 ? b : -b);
    return r;
}

int main(void)
{
    int num_lines = 0;
    char **output = file_lines("file.txt", &num_lines);
    
    // Game variables
    int rotation = 50;
    int num_of_times_zero = 0;
    for (int i = 0; i < num_lines; i++) {
        printf("Line: %s", output[i]);
        char direction = output[i][0];
        printf("direction: %c", direction);
        int change = atoi(&output[i][1]);
        if (direction == 'R') {
            rotation = rotation + change;
            num_of_times_zero = num_of_times_zero + rotation/100;
        } else {
            rotation = rotation - change;
            if (rotation < 0){
                
                    num_of_times_zero = num_of_times_zero + abs(rotation)/100 +1;
                if (abs(rotation) == change){
                    num_of_times_zero--;
                } 
            } else if (rotation == 0)
            {
                num_of_times_zero++;
            }
            
        }
        rotation = mod(rotation, 100);

        printf("\nRotation after %s: %d \n", output[i], rotation);
        printf("Number of times Zero: %d \n", num_of_times_zero);
        //getchar();
    }
    printf("Number of times Zero: %d", num_of_times_zero);
}
