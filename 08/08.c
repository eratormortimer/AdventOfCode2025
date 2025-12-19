#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINES 5000

typedef struct 
{
    long x,y,z;
    long circut;
    void (*add)(struct line_tachyon *, long);
} line_tachyon;


line_tachyon create_line_tachyon(long x, long y, long z){
    line_tachyon line;
    line.x =x;
    line.y =y;
    line.z=z;
    line.circut = 0;
    return line;
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


double get_tachyon_distance(line_tachyon* tachyon_1, line_tachyon* tachyon_2){
    long x_dis = abs(tachyon_1->x - tachyon_2->x); 
    long y_dis = abs(tachyon_1->y - tachyon_2->y);
    long z_dis = abs(tachyon_1->z - tachyon_2->z);
    double distance = sqrt(pow(x_dis,2) + pow(y_dis,2) + pow(z_dis,2));
    return distance;
}


line_tachyon* get_closest_tachyon(line_tachyon** tachyons, size_t size, line_tachyon line){
    double shortest_distance = -1;
    size_t index_of_shortest = 0;
    for (size_t i =0; i< size; i++){
        if (tachyons[i]==&line){
            continue;
        }
        double distance = get_tachyon_distance(tachyons[i],&line);
        if (distance < shortest_distance || shortest_distance == -1) {
            shortest_distance = distance;
            index_of_shortest =i;
        } 
    }
    return tachyons[index_of_shortest];
}

int set_circuts(line_tachyon* line, line_tachyon* match,long circut_number) {
    if (line->circut==0 && match->circut==0){
        line->circut=circut_number;
        match->circut=circut_number;
        return 1;
    }else if (line->circut==0){
        line->circut=match->circut;
        return 0;
    }else if (match->circut==0){
        match->circut = line->circut;
        return 0;
    }
    return 0; 
}

line_tachyon* get_coordinates(char* line){
    char saveptr;
    char *endptr;
    char* range = strtok_r(line, ",", &saveptr);
    line_tachyon tachyon = create_line_tachyon(strtol(range,&endptr,10),strtol(strok_r(NULL, ",",&saveptr),&endptr,10),strtol(strok_r(NULL, ",",&saveptr),&endptr,10));
    return &tachyon;
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
    struct line_tachyon** tachyons = calloc(num_lines, sizeof *tachyons);
    long* circuits = calloc(num_lines, sizeof *circuits);
    long current_circut = 1;
    for (size_t i = 0; i < num_lines;i++){
        line_tachyon* tachyon = get_coordinates(output[i]);
        tachyons[i]=tachyon;
    }
    for (size_t i = 0; i < 10;i++){

    }
    printf("Final Result: %ld\n", result);

    return 0;
}