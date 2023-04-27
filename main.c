#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 50

typedef struct {
    int number;
    char* name;
    char* surname;
    char* address;
    char* id;
    int regularBalance;
    int savingsBalance;
} Account;

Account* accPtr;

void printWelcome();
int isDataEmpty();
void readData();

int main() 
{
    if (isDataEmpty() == 0) { // If data is not empty
        readData();
    }

    while (1) {
        printWelcome();

        int choice;

        if (scanf("%d", &choice) == 0) {
            printf("Incorrect input.\n\n");
            while (getchar()!='\n');
            continue;
        }

        if (choice == 1) {
            printf("\n");
            while (getchar()!='\n');
            continue;
        }
        else if (choice == 8) {
            break;
        } 
        else {
            printf("\n");
            while (getchar()!='\n');
            continue;
        }
    }
    return 0;
}

void readData()
{
    FILE* data;
    data = fopen("data.txt", "r");

    Account acc;
    char* line;

    // Number

    line = fgets(line, MAX_LINE, data);
    acc.number = atoi(line);

    if (acc.number <= 0) {
        // Incorrect data. Overwrite data.txt
        fclose(data);
        data = fopen("data.txt", "w");
        return;
    }

    line = fgets(line, MAX_LINE, data);
    acc.name = line;

    for (int i = 0; i < strlen(acc.name); ++i) {
        if (!isalpha(acc.name[i]) && !isspace(acc.name[i])) {
            // Incorrect data. Overwrite data.txt
            fclose(data);
            data = fopen("data.txt", "w");
            return;
        }
    }

    line = fgets(line, MAX_LINE, data);
    acc.surname = line;

    for (int i = 0; i < strlen(acc.surname); ++i) {
        if (!isalpha(acc.surname[i]) && !isspace(acc.surname[i])) {
            // Incorrect data. Overwrite data.txt
            fclose(data);
            data = fopen("data.txt", "w");
            return;
        }
    }

    line = fgets(line, MAX_LINE, data);
    acc.address = line;

    for (int i = 0; i < strlen(acc.address); ++i) {
        if (!isalpha(acc.address[i]) && !isspace(acc.address[i]) && isdigit(acc.address[i])) {
            // Incorrect data. Overwrite data.txt
            fclose(data);
            data = fopen("data.txt", "w");
            return;
        }
    }

    line = fgets(line, MAX_LINE, data);
    acc.id = line;

    if (strlen(acc.id) != 11) {
        fclose(data);
        data = fopen("data.txt", "w");
        return;
    }

    for (int i = 0; i < 11; ++i) {
        if (!isdigit(acc.id[i])) {
            fclose(data);
            data = fopen("data.txt", "w");
            return;
        }
    }

    line = fgets(line, MAX_LINE, data);
    acc.regularBalance = line;
}

int isDataEmpty() 
{
    FILE* data;
    data = fopen("data.txt", "r");

    if (data == NULL) {
        data = fopen("data.txt", "w");
    }

    fseek(data, 0L, SEEK_END);

    if (ftell(data) == 0) {
        fclose(data);
        return 1;
    }
    else {
        fclose(data);
        return 0;
    }
}

void printWelcome()
{
    printf("Welcome to the Banking System.\n");
    printf("What would you like to do:\n");
    printf("1) Create a new account.\n");
    printf("2) List all accounts.\n");
    printf("3) Search for an account.\n");
    printf("4) Make a deposit.\n");
    printf("5) Make a withdrawal.\n");
    printf("6) Make a money transfer between accounts.\n");
    printf("7) Make a money transfer to/from savings account.\n");
    printf("8) Quit.\n\n");
}