#ifndef DBCOMMAND_H
#define DBCOMMAND_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

#define MAX_LINE_SIZE 1024
#define MAX_FIELD_SIZE 256
#define MAX_FIELDS 10

void add_book(uint64_t isbn, char* author, char* name, int total);
void delete_book(uint64_t isbn);
void edit_book(uint64_t isbn, char* author, char* name, int total, int available);


void add_student(char* record_book_number, char* surname, char* name, char* patronymic, char* faculcy, char* speciality);
void add_book(uint64_t isbn, char *author, char *name, int total);
void delete_student(char *record_book_number);
void edit_student(char* record_book_number, char* surname, char* name, char* patronymic, char* faculcy, char* speciality);

int check_user(char* login, char* password);

void save_db();



#endif //DBCOMMAND_H