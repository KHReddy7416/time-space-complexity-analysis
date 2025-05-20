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

    // Measure compilation time
    clock_t compile_start = clock();
    int compile_status = system("gcc temp_program.c -o temp_program");
    clock_t compile_end = clock();

    if (compile_status != 0) {
        printf("Compilation failed.\n");
        return;
    }

    double compile_time = (double)(compile_end - compile_start) / CLOCKS_PER_SEC;
    printf("Time taken for compilation: %f seconds\n", compile_time);

    // Measure execution time
    clock_t exec_start = clock();
    #ifdef _WIN32
        int run_status = system("temp_program.exe");  // For Windows
    #else
        int run_status = system("./temp_program");    // For Linux/Unix-based systems
    #endif
    clock_t exec_end = clock();

    if (run_status != 0) {
        printf("Execution failed.\n");
        return;
    }

    double exec_time = (double)(exec_end - exec_start) / CLOCKS_PER_SEC;
    printf("Time taken for execution: %f seconds\n", exec_time);

    // Cleanup
    remove("temp_program.c");
    #ifdef _WIN32
        remove("temp_program.exe");  // For Windows
    #else
        remove("temp_program");  // For Linux/Unix-based systems
    #endif
}

int main() {
    run_code();
    return 0;
}
