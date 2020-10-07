/* read_write.c written by Russell Abernethy */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(char name[]);
void write_file(char* str, int len);

int main() {
    // Name of the input file.
    char file_name[] = "input.txt";

    // Create a string by reading a file.
    char *string = read_file(file_name);
    printf("%s\n", string);

    // Write the file to an output file.
    write_file(string, strlen(string));

    // Free alocated memory.
    free(string);
}

char* read_file(char name[]) {

    // Open the file and check that it was sucessful.
    FILE *fp = fopen(name,"r");
    if(fp == NULL) {
        printf("The file cannot be opened.\n");
        exit(0);
    }

    // Calculate the size of the file.
    int len = 0;
    while(getc(fp) != EOF)
        len++;

    // Allocate memory for the string.
    char *read_array;
    read_array = (char *)(malloc((len+1)*sizeof(char)));
    if(read_array == NULL) {
        printf("Sufficent memory cannot be allocated.\n");
        exit(0);
    }

    // Rewind the file.
    rewind(fp);

    // Read the file's contents to the allocated string.
    int i;
    for (i = 0; i < len; i++)
        read_array[i] = getc(fp);
    read_array[i] = '\0';

    // Close the file.
    fclose(fp);

    return read_array;
}

void write_file(char* str, int len) {
    
    // Open the file for writing and check that it was sucessful.
    FILE *fp = fopen("write.txt", "w");
    if(fp == NULL) {
        printf("File cannot be opened.\n");
        exit(0);
    }

    // Write the string to file
    int i = 0;
    for(i = 0; i < strlen(str); i++)
        putc(str[i], fp);

    // Close the file.
    fclose(fp);
}