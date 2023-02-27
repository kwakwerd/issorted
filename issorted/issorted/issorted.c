#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBERS 100
#define INITIAL_ARRAY_SIZE 10
#define INITIAL_CAPACITY 16 
#define CHUNK_SIZE 10
#define MAX_STRING_LENGTH 100

void is_sorted(int numbers[], int num_numbers) {
    for (int i = 1; i < num_numbers; i++) {
        if (numbers[i - 1] > numbers[i]) {
            
          
            printf("element %d (%d) not sorted", i, numbers[i]);

            break;
                 // not sorted
        }
    }
    printf("sorted");// sorted

}
void is_sortedReal(double numbers[], int num_numbers) {
    for (int i = 1; i < num_numbers; i++) {
        if (numbers[i - 1] > numbers[i]) {

           
            printf("element %d (%lf) not sorted", i, numbers[i]);
            break;
            // not sorted
        }
    }
    printf("sorted");// sorted
}

void check_sortedString(char** array, int length) {
    for (int i = 1; i < length; i++) {
        if (strcmp(array[i - 1], array[i]) > 0) {
            printf("element %d (%s) not sorted", i, array[i]);

            return;
        }
           
    }
    printf("sorted");

}


int main(int argc, char* argv[])
{
    
  

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("\n======================================================");
        printf("\nusage: issorted [(-(n|i|r|s|l|h))|--help]  [filename]");
        printf("\n\n   -n      sort natural numbers");
        printf("\n   -i      sort integers numbers");
        printf("\n   -r      sort real numbers");
        printf("\n   -s      sort strings (default)");
        printf("\n   -l      sort lines ");
        printf("\n   -h      display help");
        printf("\n\n   --help      display help");
        printf("\n\n   filename      optional stream source (default is stdin");

    }



    else if (strcmp(argv[1], "-n") == 0|| strcmp(argv[1], "-i") == 0)
    {
        if (argv[2] == NULL)
        {
            int array_size = INITIAL_ARRAY_SIZE; // initial array size
            int count = 0; // number of elements currently in array
            int* array = malloc(array_size * sizeof(int)); // allocate initial array

            if (array == NULL) 
            {
                printf("Error: Failed to allocate memory for array.\n");
                return 1;
            }

            int input;
            while (scanf("%d", &input) == 1) 
            {
                if (count == array_size)
                {
                    // if array is full, double its size
                    array_size *= 2;
                    int* new_array = realloc(array, array_size * sizeof(int));


                    if (new_array == NULL) {
                        printf("Error: Failed to allocate memory for array.\n");
                        free(array);
                        return 1;
                    }

                    array = new_array;
                }

                array[count] = input;
                count++;
            }

        
            is_sorted(array, count);

        }
        else
        {

            FILE* myFile;
            char* data;
            int size = 0;

            // open input file
            myFile = fopen(argv[2], "r");
            if (myFile == NULL) {
                printf("Error opening file.\n");
                return 1;
            }

            // count number of integers in input file
            int num;
            while (fscanf(myFile, "%d", &num) == 1) {
                size++;
            }

            // allocate memory for data array
            data = (char*)malloc(size * sizeof(char));
            if (data == NULL) {
                printf("Error allocating memory.\n");
                return 1;
            }

            // read integers from input file and store in data array
            rewind(myFile);
            int i = 0;
            while (fscanf(myFile, "%c", &data[i]) == 1) {
                i++;
            }

            // close input file
            fclose(myFile);
            int num_numbers = 0;


            // check if the numbers are sorted

            is_sorted(data, size);


        }
        
    }
    else if (strcmp(argv[1], "-s") == 0|| strcmp(argv[1], "-l") == 0)
    {
        if (argv[2] == NULL)
        {
           
            char** array = NULL;
            char* buffer = NULL;
            int buffer_size = 0;
            int count = 0;
            int capacity = 1;
            int c;

            // Allocate initial memory for array and buffer
            array = (char**)malloc(capacity * sizeof(char*));
            buffer_size = 1024;
            buffer = (char*)malloc(buffer_size * sizeof(char));

            // Read strings from standard input until end-of-stream
            while ((c = getchar()) != EOF) {
                // If the buffer is full, resize it
                if (count == buffer_size - 1) {
                    buffer_size *= 2;
                    buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
                }

                // Read characters into buffer until end-of-line or buffer is full
                int i = 0;
                while (c != EOF && c != '\n') {
                    buffer[i++] = (char)c;
                    // If the buffer is full, resize it
                    if (i == buffer_size - 1) {
                        buffer_size *= 2;
                        buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
                    }
                    c = getchar();
                }
                buffer[i] = '\0';

                // Allocate memory for string and copy it into array
                array[count] = (char*)malloc((i + 1) * sizeof(char));
                strcpy(array[count], buffer);

                count++;
                // If the array is full, resize it
                if (count == capacity) {
                    capacity *= 2;
                    array = (char**)realloc(array, capacity * sizeof(char*));
                }
            }
            
            check_sortedString(array, count);
            
            for (int i = 0; i < count; i++) {
                free(array[i]);
            }
            free(array);
            free(buffer);

            
        }
    }
    else if (strcmp(argv[1], "-r") == 0)
    {
        double* array;  // pointer to dynamic array
        int size = 1;   // initial size of array
        int count = 0;  // number of elements currently in array
        double input;   // input variable for doubles

        // allocate memory for initial size of array
        array = (double*)malloc(size * sizeof(double));

        // loop until user enters EOF
        while (scanf("%lf", &input) != EOF) {
            // check if array is full and resize if necessary
            if (count == size) {
                size *= 2;
                array = (double*)realloc(array, size * sizeof(double));
            }
            // add input to array and increment count
            array[count++] = input;
        }

        is_sortedReal(array, count);

        // free dynamically allocated memory
        free(array);


        }
        return 0;

    }

