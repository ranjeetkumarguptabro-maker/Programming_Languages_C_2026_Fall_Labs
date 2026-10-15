
/*
 * Name: Ranjeet Kumar
 * Surname: Gupta
 * Student ID: 251ADB005
 *
 * Task 4: Binary file I/O (Bonus)
 * Week 5 - Files & Modular Programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int save_student_binary(const Student *s, const char *filename);
int load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");

    if (save_student_binary(&s1, bin_file) != 0) {
        perror(bin_file);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(txt_file, "w");

    if (fp == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }

    int result = fprintf(fp, "%s %d %.2f\n",
                         s1.name, s1.age, s1.gpa);

    int close_result = fclose(fp);

    if (result < 0 || close_result != 0) {
        fprintf(stderr, "Failed to write text file.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");

    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Failed to load binary student.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    long text_size = file_size(txt_file);
    long binary_size = file_size(bin_file);

    if (text_size < 0 || binary_size < 0) {
        fprintf(stderr, "Failed to determine file size.\n");
        return EXIT_FAILURE;
    }

    printf("Text file size: %ld bytes\n", text_size);
    printf("Binary file size: %ld bytes\n", binary_size);

    return EXIT_SUCCESS;
}

int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        return -1;
    }

    size_t written = fwrite(s, sizeof(Student), 1, fp);
    int close_result = fclose(fp);

    return (written == 1 && close_result == 0) ? 0 : -1;
}

int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    size_t read_count = fread(out, sizeof(Student), 1, fp);
    int close_result = fclose(fp);

    return (read_count == 1 && close_result == 0) ? 0 : -1;
}

long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);

    if (size < 0) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        return -1;
    }

    return size;
}
