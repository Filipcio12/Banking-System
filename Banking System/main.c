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

        while (getchar()!='\n');

        if (choice == 1) {
            makeAccount();
            printf("\n");
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
    free(accPtr);

    return 0;
}

void makeAccount() 
{
    Account acc;
    char line[MAX_LINE];

    printf("\nCreating new account:\n\n");

    do {
        printf("Type in your name:\n");
        fgets(line, MAX_LINE, stdin);

        int i;
        int repeat = 0;

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i])) {
                repeat = 1;
                break;
            }

            acc.name[i] = line[i];
        }

        acc.name[i] = '\0';

        if (repeat) {
            continue;
        }

        break;

    } while(1);

    do {
        printf("Type in your surname:\n");
        fgets(line, MAX_LINE, stdin);

        int i;
        int repeat = 0;

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i])) {
                repeat = 1;
                break;
            }

            acc.surname[i] = line[i];
        }

        acc.surname[i] = '\0';

        if (repeat) {
            continue;
        }

        break;

    } while(1);

    do {
        printf("Type in your address:\n");
        fgets(line, MAX_LINE, stdin);

        int i;
        int repeat = 0;

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i]) && !isdigit(line[i])) {
                repeat = 1;
                break;
            }

            acc.address[i] = line[i];
        }

        acc.address[i] = '\0';

        if (repeat) {
            continue;
        }

        break;

    } while(1);

    do {
        printf("Type in your id number:\n");
        fgets(line, MAX_LINE, stdin);

        int i;
        int repeat = 0;

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isdigit(line[i])) {
                repeat = 1;
                break;
            }

            acc.id[i] = line[i];
        }

        acc.id[i] = '\0';

        if (repeat || strlen(acc.id) != 11) {
            continue;
        }

        break;

    } while(1);

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

        if (s == NULL) {
            break;
        }

        int i;

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i])) {
                break;
            }

            acc.name[i] = line[i];
        }

        acc.name[i] = '\0';

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL) {
            break;
        }

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i])) {
                break;
            }

            acc.surname[i] = line[i];
        }

        acc.surname[i] = '\0';

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL) {
            break;
        }

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isalpha(line[i]) && !isspace(line[i]) && !isdigit(line[i])) {
                break;
            }

            acc.address[i] = line[i];
        }

        acc.address[i] = '\0';

        do {
            s = fgets(line, MAX_LINE, data);
        } while ((line[0] == '\n' || line[0] == '\r') && s != NULL);

        if (s == NULL) {
            break;
        }

        for (i = 0; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; ++i) {
            if (!isdigit(line[i])) {
                break;
            }

            acc.id[i] = line[i];
        }

        acc.id[i] = '\0';

        if (strlen(acc.id) != 11) {
            break;
        }

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
