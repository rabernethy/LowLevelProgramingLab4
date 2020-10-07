/* encrypt.c, written by Russell Abernethy */
/* | Assignment: Lab4 | Due: 10/19/2020 | */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void make_random_key(int len, char* key);
void encrypt(char* clear_file, char* key_file, char* cipher_file);
void decrypt(char* key_file, char* cipher_file, char* message_file);

char* read_file(int len, char name[]);
void write_file(int len, char* str, char* file_name);

int main() {
    // File names for program.
    char* clear_file = "input.txt";
    char* key_file = "key.txt";
    char* cipher_file = "cipher.txt";
    char* message_file = "message.txt";

    // Main loop.
    while (1) {
        int choice = -1;

        printf("Encrypt a file: 1\n");
        printf("Decrypt a file: 2\n");
        printf("Exit:           3\n");
        printf("Enter a choice: ");
        
        // Sentinal loop.
        while(choice != 1 || choice != 2 || choice != 3) {
            scanf("%d", &choice);
            if(choice != 1 || choice != 2 || choice != 3) {
                printf("\nSorry try again.\n");
                printf("Encrypt a file: 1\n");
                printf("Decrypt a file: 2\n");
                printf("Exit:           3\n");
                printf("Enter a choice: ");
            }
        }
        if(choice == 1)
            encrypt(clear_file,key_file,cipher_file);
        else if(choice == 2)
            decrypt(key_file,cipher_file,message_file);
        else if(choice==3)
            exit(0);
    }

}

void make_random_key(int len, char* key) {
    // Seed random with time.
    srand(time(NULL));
    // Add random keys to the array.
    int i;
    for(i = 0; i < len; i++) {
        key[i] = (char)(rand() % 256);
        // Replace EOF with -2.
        if(key[i] == -1)
            key[i] -=1;
        // Replace NULL with 1.
        if(key[i] == 0)
            key[i]++;
    }
    key[i] = '\0';
}

void encrypt(char* clear_file, char* key_file, char* cipher_file) {
    // Declerations.
    char* clear = read_file(0,clear_file);
    char* cipher = (char *)(malloc((strlen(clear))*sizeof(char)));
    char* rand_key = (char *)(malloc((strlen(clear))*sizeof(char)));
    make_random_key(strlen(clear),rand_key);

    // Encrypt the input text by XORing the clear string with the key string.
    int i;
    for(i = 0; i < strlen(clear); i++) 
        cipher[i] = clear[i] ^ rand_key[i];
    cipher[i] = '\0';

    // Write the keys and cipher to files.
    write_file(strlen(clear), rand_key, key_file);
    write_file(strlen(clear), cipher, cipher_file);

    // Free used memory
    free(rand_key);
    free(cipher);
    free(clear);
}

void decrypt(char* key_file, char* cipher_file, char* message_file) {
    // Declerations.
    char* rand_key = read_file(0, key_file);
    char* cipher = read_file(strlen(rand_key),cipher_file);
    char* message = (char*)(malloc((strlen(rand_key))*sizeof(char)));
    
    // Decrypt the cipher text by XORing the cipher string with the 
    int i;
    for(i = 0; i < strlen(rand_key); i++)
        message[i] = cipher[i] ^ rand_key[i];
    message[i] = '\0';

    // Write the decrypted string to a file.
    write_file(0,message, message_file);

    // Free used memory.
    free(message);
    free(rand_key);
    free(cipher);
}

char* read_file(int len, char name[]) {

    // Open the file and check that it was sucessful.
    FILE *fp = fopen(name,"r");
    if(fp == NULL) {
        printf("The file cannot be opened.\n");
        exit(0);
    }

    // Calculate the size of the file.
    if(len == 0) {
        while(getc(fp) != EOF)
            len++;
    }


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
    for (i = 0; i < len; i++) {
        read_array[i] = getc(fp);
    }
    read_array[i] = '\0';

    // Close the file.
    fclose(fp);

    return read_array;
}

void write_file(int len, char* str, char* file_name) {
    
    // Open the file for writing and check that it was sucessful.
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL) {
        printf("File cannot be opened.\n");
        exit(0);
    }

    int i = 0;
    if(len <= 0) {
        // Write the string to file
        for(i = 0; i < strlen(str); i++)
            putc(str[i], fp);
    } else {
        // Write len of the string to file.
        for(i = 0; i < len; i++)
            putc(str[i], fp);
    }

    //Close the file.
    fclose(fp);
}