#include "db_command.h"

/// @brief added book to db
/// @param isbn ISBN-code
/// @param author 
/// @param name 
/// @param total total value of books
void add_book(uint64_t isbn, char* author, char* name, int total) {

}

/// @brief delete book by ISBN from db
/// @param isbn ISBN-code
void delete_book(uint64_t isbn) {

}

/// @brief edid book by ISBN
/// @param isbn ISBN-code for searh
/// @param author new author or NULL to skip
/// @param name new name or NULL to skip
/// @param total new total value of books or NULL to skip
/// @param available new available value or NULL to skip
void edit_book(uint64_t isbn, char* author, char* name, int total, int available) {

}




/// @brief added student to db
/// @param record_book_number 
/// @param surname фамилия
/// @param name имя
/// @param patronymic отчество
/// @param faculcy like "ИУ"
/// @param speciality 
void add_student(char* record_book_number, char* surname, char* name, char* patronymic, char* faculcy, char* speciality) {

}

/// @brief delete student by record book number fron db
/// @param record_book_number 
void delete_student(char* record_book_number) {

}

/// @brief edit studend by record book number
/// @param record_book_number for searh
/// @param surname фамилия (new or NULL to skip)
/// @param name имя (new or NULL to skip)
/// @param patronymic отчество (new or NULL to skip)
/// @param faculcy like "ИУ" (new or NULL to skip)
/// @param speciality (new or NULL to skip)
void edit_student(char* record_book_number, char* surname, char* name, char* patronymic, char* faculcy, char* speciality) {

}


int check_user(char* login, char* password) {
    char line[MAX_LINE_SIZE];
    char field[MAX_FIELD_SIZE];
    char *token;
    char *rest;
    int field_count;
    int i;

    FILE* fp = fopen("users.csv", "r");
    if (fp == NULL) {
        printf("Error opening file users.csv\n");
        return 1;
    }

    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Parse fields from line
        rest = line;
        field_count = 0;
        while ((token = strtok_r(rest, ";", &rest)) != NULL && field_count < MAX_FIELDS) {
            strcpy(field, token);
            if (field_count == 0 && !strcmp(field, login)) break;
            else if(field_count == 1 && !strcmp(field, password)) break;
            else {
                fclose(fp);
                return 1;
            }
            printf("right");
            field_count++;
        }
    }
    printf("wrong");
    fclose(fp);
    return 0;
}


/// @brief save all db's
void save_db() {

}