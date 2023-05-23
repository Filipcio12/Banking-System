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

void printWelcome();
long whatSize();
Account readAccount(int index);
void writeAccount(Account acc);
void overwriteAccount(Account acc, int index);
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
void makeDeposit();
void makeWithdrawal();
void makeMoneyTransfer();
void transferToSavingsAccount();
void transferFromSavingsAccount();

int main() 
{
    int choice;

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

            case 4:
                makeDeposit();
                break;

            case 5:
                makeWithdrawal();
                break;

            case 6:
                makeMoneyTransfer();
                break;

            case 7:
                transferToSavingsAccount();
                break;

            case 8:
                transferFromSavingsAccount();
                break;

            case 9:
                break;
                
            default:
                printf("\nIncorrect input.\n\n");
                break;
        }
    } while (choice != 9);

    return 0;
}

void transferFromSavingsAccount()
{
    printf("\nMaking a transfer from a savings account:\n");
    
    int index = searchAccount();

    if (index == -1) {
        return;
    }

    Account acc = readAccount(index);

    int transfer;

    while (1) {
        printf("Type in an amount of money:\n");
        
        if (scanf("%d", &transfer) == 0 || transfer < 0 ||
            transfer > acc.savingsBalance) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        acc.savingsBalance -= transfer;
        acc.regularBalance += transfer;
        printf("\nTransferred %d.\n", transfer);
        overwriteAccount(acc, index);
        printAccount(index);
        return;
    }
}

void transferToSavingsAccount()
{
    printf("\nMaking a transfer to a savings account:\n");
    
    int index = searchAccount();

    if (index == -1) {
        return;
    }

    Account acc = readAccount(index);

    int transfer;

    while (1) {
        printf("Type in an amount of money:\n");
        
        if (scanf("%d", &transfer) == 0 || transfer < 0 ||
            transfer > acc.regularBalance) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        acc.regularBalance -= transfer;
        acc.savingsBalance += transfer;
        printf("\nTransferred %d.\n", transfer);
        overwriteAccount(acc, index);
        printAccount(index);
        return;
    }
}

void makeMoneyTransfer()
{
    printf("\nMaking a money transfer:\n");

    int index1 = searchAccount();

    if (index1 == -1) {
        return;
    }

    int index2 = searchAccount();

    if (index2 == -1) {
        return;
    }

    Account acc1 = readAccount(index1);
    Account acc2 = readAccount(index2);

    int transfer;

    while (1) {
        printf("Type in an amount of money ");
        printf("to transfer from the first account to the second:\n");

        if (scanf("%d", &transfer) == 0 || transfer < 0 || 
            transfer > acc1.regularBalance) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        acc1.regularBalance -= transfer;
        acc2.regularBalance += transfer;
        printf("\nTransferred %d.\n", transfer);
        overwriteAccount(acc1, index1);
        overwriteAccount(acc2, index2);
        printAccount(index1);
        printAccount(index2);
        return;
    }
}

void makeWithdrawal()
{
    printf("\nMaking a withdrawal:\n");
    
    int index = searchAccount();

    if (index == -1) {
        return;
    }

    Account acc = readAccount(index);

    int withdrawal;

    while (1) {
        printf("Type in an amount of money:\n");
        
        if (scanf("%d", &withdrawal) == 0 || withdrawal < 0 || 
            withdrawal > acc.regularBalance) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        acc.regularBalance -= withdrawal;
        printf("\nWithdrawn %d.\n", withdrawal);
        overwriteAccount(acc, index);
        printAccount(index);
        return;
    }
}

void makeDeposit()
{
    printf("\nMaking a deposit:\n");
    
    int index = searchAccount();

    if (index == -1) {
        return;
    }

    Account acc = readAccount(index);

    int deposit;

    while (1) {
        printf("Type in an amount of money:\n");
        
        if (scanf("%d", &deposit) == 0 || deposit < 0) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        acc.regularBalance += deposit;
        printf("\nDeposited %d.\n", deposit);
        overwriteAccount(acc, index);
        printAccount(index);
        return;
    }
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
    long size = whatSize();

    if (size == 0) {
        printf("\nNo accounts to search.\n\n");
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
    long size = whatSize();
    char line[MAX_LINE];

    do {
        printf("\nType in an ID:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkID(line) == 0);

    for (int i = 0; i < size; ++i) {
        Account acc = readAccount(i);
        if (strcmp(line, acc.id) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByAddress()
{
    long size = whatSize();
    char line[MAX_LINE];

    do {
        printf("\nType in an address:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkAddress(line) == 0);

    for (int i = 0; i < size; ++i) {
        Account acc = readAccount(i);
        if (strcmp(line, acc.address) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchBySurname()
{
    long size = whatSize();
    char line[MAX_LINE];

    do {
        printf("\nType in a surname:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    for (int i = 0; i < size; ++i) {
        Account acc = readAccount(i);
        if (strcmp(line, acc.surname) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByName()
{
    long size = whatSize();
    char line[MAX_LINE];

    do {
        printf("\nType in a name:\n");
        fgets(line, MAX_LINE, stdin);
    } while (checkName(line) == 0);

    for (int i = 0; i < size; ++i) {
        Account acc = readAccount(i);
        if (strcmp(line, acc.name) == 0) { // RETURNS 0 IF STRINGS ARE THE SAME!!!
            return i;
        }
    }

    return -1;
}

int searchByNumber()
{
    long size = whatSize();
    int number;

    while (1) {
        printf("\nThere are %ld records in the database.", size);
        printf("\nType in a number from 1 to %ld:\n", size);

        if (scanf("%d", &number) == 0 || number > size || number <= 0) {
            printf("\nIncorrect input.\n");
            while (getchar()!='\n');
            continue;
        }

        return number - 1;
    }
}

void printAccount(int index) 
{
    Account acc = readAccount(index);

    printf("\nNumber:\t\t\t%d\n", acc.number);
    printf("Name:\t\t\t%s\n", acc.name);
    printf("Surname:\t\t%s\n", acc.surname);
    printf("Address:\t\t%s\n", acc.address);
    printf("ID:\t\t\t%s\n", acc.id);
    printf("Regular balance:\t%d\n", acc.regularBalance);
    printf("Savings balance:\t%d\n\n", acc.savingsBalance);
}

void listAccounts() 
{
    long size = whatSize();

    if (size == 0) {
        printf("\nNo accounts to list.\n\n");
        return;
    }

    printf("\nListing all accounts:\n");
    
    for (int i = 0; i < size; ++i) {
        printAccount(i);
    }
}

void makeAccount() 
{
    Account acc;
    char line[MAX_LINE];
	long size = whatSize();
	
    printf("\nCreating new account:\n\n");
	acc.number = size + 1;
	
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

    writeAccount(acc);

    printf("\n");
}

void overwriteAccount(Account acc, int index)
{
	FILE* data = fopen("data.bin", "wb");
	fseek(data, index * sizeof(Account), SEEK_SET);
	fwrite(&acc, sizeof(Account), 1, data);
	fclose(data);
}

void writeAccount(Account acc)
{
    FILE* data = fopen("data.bin", "ab");
    fwrite(&acc, sizeof(Account), 1, data);
    fclose(data);
}

Account readAccount(int index)
{
    FILE* data = fopen("data.bin", "rb");
    Account acc;
    fseek(data, index * sizeof(Account), SEEK_SET);
    fread(&acc, sizeof(Account), 1, data);
    fclose(data);
    return acc;
}

long whatSize() 
{
    FILE* data = fopen("data.bin", "rb");

    if (data == NULL) {
        data = fopen("data.bin", "wb");
    }

    fseek(data, 0, SEEK_END);
    long size = ftell(data) / sizeof(Account);

    fclose(data);
    return size;
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
    printf("7) Make a money transfer to a savings account.\n");
    printf("8) Make a money transfer from a savings account.\n");
    printf("9) Quit.\n\n");
}
