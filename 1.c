#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void run_code() {
    char code[2048];
    printf("Enter your C code (end with EOF Ctrl+Z on Windows):\n");

    size_t index = 0;
    while (fgets(code + index, sizeof(code) - index, stdin)) {
        index += strlen(code + index);
        if (index >= sizeof(code) - 1) break; 
    }

    FILE *file = fopen("temp_program.c", "w");
    if (file == NULL) {
        perror("Unable to open file for writing");
        return;
    }
    fputs(code, file);
    fclose(file);


    clock_t start_time = clock();
    int compile_status = system("gcc temp_program.c -o temp_program");
    clock_t end_time = clock();

    if (compile_status != 0) {
        printf("Compilation failed.\n");
        return;
    }

    start_time = clock();
    int run_status = system("temp_program");  
    end_time = clock();

    if (run_status != 0) {
        printf("Execution failed.\n");
        return;
    }

    double compile_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken for compilation: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    
    remove("temp_program.c");
    remove("temp_program.exe");
}

int main() {
    run_code();
    return 0;
}


