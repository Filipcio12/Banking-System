#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 50

typedef struct {
    int number;
    char name[MAX_LINE];
    char surname[MAX_LINE];
    char address[MAX_LINE];
    char id[MAX_LINE];
    int regularBalance;
    int savingsBalance;
} Account;

Account* accPtr;
int accSize = 0;

void printWelcome();
int isDataEmpty();
void readData();
void updateData();
void makeAccount();
void listAccounts();
void printAccount(int index);
int searchAccount();
int searchByNumber();
int searchByName();
int searchBySurname();
int searchByAddress();
int searchByID();

int checkName(char* line);
int checkAddress(char* line);
int checkID(char* line);

int main() 
{
    int choice;

    if (!isDataEmpty()) {
        readData();
    }

    do {
        printWelcome();

        if (scanf("%d", &choice) == 0) {
            printf("\nIncorrect input.\n\n");
            while (getchar()!='\n');
            continue;
        }

        while (getchar()!='\n');

        switch (choice) {
            case 1:
                makeAccount();
                break;

            case 2:
                listAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 8:
                break;
                
            default:
                printf("\nIncorrect input.\n\n");
                break;
        }
    } while (choice != 8);

    updateData();
    free(accPtr);

    return 0;
}

int checkName(char* line)
{
    if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' && line[strlen(line) - 2] == '\r') {
        line[strlen(line) - 1] = '\0';
        line[strlen(line) - 2] = '\0';
    }

    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    if (strlen(line) == 0) {
        return 0;
    }

    for (int i = 0; i < strlen(line); ++i) {
        if (!isalpha(line[i]) && !isblank(line[i])) {
            return 0;
        }
    }

    return 1;
}

int checkAddress(char* line)
{
    if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' && line[strlen(line) - 2] == '\r') {
        line[strlen(line) - 1] = '\0';
        line[strlen(line) - 2] = '\0';
    }

    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    if (strlen(line) == 0) {
        return 0;
    }      
    
    for (int i = 0; i < strlen(line); ++i) {
        if (!isalpha(line[i]) && !isblank(line[i]) && !isdigit(line[i])) {
            return 0;
        }
    }

    return 1;
}

int checkID(char* line)
{
    if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' && line[strlen(line) - 2] == '\r') {
        line[strlen(line) - 1] = '\0';
        line[strlen(line) - 2] = '\0';
    }

    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    if (strlen(line) != 11) {
        return 0;
    }

    for (int i = 0; i < 11; ++i) {
        if (!isdigit(line[i])) {
            return 0;
        }
    }

    return 1;
}

int searchAccount() 
{
    if (isDataEmpty()) {
        printf("\nNo accounts search.\n\n");
        return -1;
    }

    int index;
    int choice;

    do {
        printf("\nSearching for an account:\n");
        printf("How do you wish to search:\n\n");
        printf("1) By number\n");
        printf("2) By name\n");
        printf("3) By surname\n");
        printf("4) By address\n");
        printf("5) By ID\n\n");

        if (scanf("%d", &choice) == 0) {
            printf("\nIncorrect input.\n\n");
            while (getchar()!='\n');
            continue;
        }

        while (getchar()!='\n');

        switch (choice) {
            case 1:
                index = searchByNumber();
                break;

            case 2:
                index = searchByName();
                break;

            case 3:
                index = searchBySurname();
                break;
            
            case 4:
                index = searchByAddress();
                break;
            
            case 5:
                index = searchByID();
                break;
            
            default:
                printf("\nIncorrect input.\n\n");
                break;
        }
    } while (choice > 5 || choice < 1);

    if (index == -1) {
        printf("\nAccount not found.\n\n");
    }
    else {
        printAccount(index);
    }

    return index;
}

int searchByID()
{
    char line[MAX_LINE];

    do {
        printf("\nType in an ID:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkID(line) == 0);

    for (int i = 0; i < accSize; ++i) {
        if (strcmp(line, accPtr[i].id) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByAddress()
{
    char line[MAX_LINE];

    do {
        printf("\nType in an address:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkAddress(line) == 0);

    for (int i = 0; i < accSize; ++i) {
        if (strcmp(line, accPtr[i].address) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchBySurname()
{
    char line[MAX_LINE];

    do {
        printf("\nType in a surname:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    for (int i = 0; i < accSize; ++i) {
        if (strcmp(line, accPtr[i].surname) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByName()
{
    char line[MAX_LINE];

    do {
        printf("\nType in a name:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    for (int i = 0; i < accSize; ++i) {
        if (strcmp(line, accPtr[i].name) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByNumber()
{
    int number;

    while (1) {
        printf("\nThere are %d records in the database.", accSize);
        printf("\nType in a number from 1 to %d:\n", accSize);

        if (scanf("%d", &number) == 0 || number > accSize || number <= 0) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        return number - 1;
    }
}

void printAccount(int index) 
{
    printf("\nNumber:\t\t\t%d\n", accPtr[index].number);
    printf("Name:\t\t\t%s\n", accPtr[index].name);
    printf("Surname:\t\t%s\n", accPtr[index].surname);
    printf("Address:\t\t%s\n", accPtr[index].address);
    printf("ID:\t\t\t%s\n", accPtr[index].id);
    printf("Regular balance:\t%d\n", accPtr[index].regularBalance);
    printf("Savings balance:\t%d\n\n", accPtr[index].savingsBalance);
}

void listAccounts() 
{
    if (isDataEmpty()) {
        printf("\nNo accounts to list.\n\n");
        return;
    }

    printf("\nListing all accounts:\n");
    
    for (int i = 0; i < accSize; ++i) {
        printAccount(i);
    }
}

void makeAccount() 
{
    Account acc;
    char line[MAX_LINE];

    printf("\nCreating new account:\n\n");

    do {
        printf("Type in your name:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    strcpy(acc.name, line);

    do {
        printf("Type in your surname:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    strcpy(acc.surname, line);

    do {
        printf("Type in your address:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkAddress(line) == 0);

    strcpy(acc.address, line);

    do {
        printf("Type in your id number:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkID(line) == 0);

    strcpy(acc.id, line);

    printf("Type in your regular account balance:\n");
    fgets(line, MAX_LINE, stdin);
    acc.regularBalance = atoi(line);

    printf("Type in your savings account balance:\n");
    fgets(line, MAX_LINE, stdin);
    acc.savingsBalance = atoi(line);

    if (++accSize == 1) {
        accPtr = malloc(sizeof(Account));
        *accPtr = acc;
    }
    else {
        accPtr = realloc(accPtr, accSize * sizeof(Account));
        accPtr[accSize - 1] = acc;
    }

    printf("\n");
}

void updateData()
{
    FILE* data;
    data = fopen("data.txt", "w");
    char line[MAX_LINE];

    for (int i = 0; i < accSize; ++i) {
        fprintf(data, "%s\n", accPtr[i].name);
        fprintf(data, "%s\n", accPtr[i].surname);
        fprintf(data, "%s\n", accPtr[i].address);
        fprintf(data, "%s\n", accPtr[i].id);
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
        acc.number = accSize + 1;

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL || checkName(line) == 0) {
            break;
        }

        strcpy(acc.name, line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL || checkName(line) == 0) {
            break;
        }

        strcpy(acc.surname, line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL || checkAddress(line) == 0) {
            break;
        }

        strcpy(acc.address, line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL || checkID(line) == 0) {
            break;
        }

        strcpy(acc.id, line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.regularBalance = atoi(line);

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL) {
            break;
        }

        acc.savingsBalance = atoi(line);

        if (++accSize == 1) {
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
    printf("What would you like to do:\n\n");
    printf("1) Create a new account.\n");
    printf("2) List all accounts.\n");
    printf("3) Search for an account.\n");
    printf("4) Make a deposit.\n");
    printf("5) Make a withdrawal.\n");
    printf("6) Make a money transfer between accounts.\n");
    printf("7) Make a money transfer to/from savings account.\n");
    printf("8) Quit.\n\n");
}
