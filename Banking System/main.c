#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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
int accSize = 0;

void printWelcome();
int isDataEmpty();
void readData();
void updateData();
void freeData();

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

    updateData();
    freeData();

    return 0;
}

void freeData()
{
    for (int i = 0; i < accSize; ++i) {
        free(accPtr[i].name);
        free(accPtr[i].surname);
        free(accPtr[i].address);
        free(accPtr[i].id);
    }

    free(accPtr);
}

void updateData()
{
    FILE* data;
    data = fopen("data.txt", "w");
    char line[MAX_LINE];

    for (int i = 0; i < accSize; ++i) {
        sprintf(line, "%d", accPtr[i].number);
        fprintf(data, "%s\n", line);
        fprintf(data, "%s", accPtr[i].name);
        fprintf(data, "%s", accPtr[i].surname);
        fprintf(data, "%s", accPtr[i].address);
        fprintf(data, "%s", accPtr[i].id);
        sprintf(line, "%d", accPtr[i].regularBalance);
        fprintf(data, "%s\n", line);
        sprintf(line, "%d", accPtr[i].savingsBalance);
        fprintf(data, "%s\n\n", line);
    }

    fclose(data);
}

void readData()
{
    FILE* data;
    data = fopen("data.txt", "r");

    Account acc;
    char line[MAX_LINE];
    char* s;

    while (1) {
        
        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);
        
        if (s == NULL) {
            break;
        }

        acc.number = atoi(line);

        if (acc.number <= 0) {
            break;
        }

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.name = malloc(strlen(line) * sizeof(char));
        strcpy(acc.name, line);

        for (int i = 0; acc.name[i] != '\n' && acc.name[i] != '\0'; ++i) {
            if (!isalpha(acc.name[i]) && !isspace(acc.name[i])) {
                break;
            }
        }

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.surname = malloc(strlen(line) * sizeof(char));
        strcpy(acc.surname, line);

        for (int i = 0; acc.surname[i] != '\n' && acc.surname[i] != '\0'; ++i) {
            if (!isalpha(acc.surname[i]) && !isspace(acc.surname[i])) {
                break;
            }
        }

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.address = malloc(strlen(line) * sizeof(char));
        strcpy(acc.address, line);

        for (int i = 0; acc.address[i] != '\n' && acc.address[i] != '\0'; ++i) {
            if (!isalpha(acc.address[i]) && !isspace(acc.address[i]) && !isdigit(acc.address[i])) {
                break;
            }
        }

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.id = malloc(strlen(line) * sizeof(char));
        strcpy(acc.id, line);

        if (strlen(acc.id) != 12) {
            break;
        }

        for (int i = 0; acc.id[i] != '\n' && acc.id[i] != '\0'; ++i) {
            if (!isdigit(acc.id[i])) {
                break;
            }
        }

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.regularBalance = atoi(line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while (line[0] == '\n' && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.savingsBalance = atoi(line);

        accSize++;

        if (accSize == 1) {
            accPtr = malloc(sizeof(Account));
            *accPtr = acc;
        }
        else {
            accPtr = realloc(accPtr, accSize * sizeof(Account));
            accPtr[accSize - 1] = acc;
        }
    }

    fclose(data);
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
