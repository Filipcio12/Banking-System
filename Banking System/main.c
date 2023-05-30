#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int readAccount(Account* acc, int index);
void appendAccount(Account acc);
void overwriteAccount(Account acc, int index);
void makeAccount();
void listAccounts();
void printAccount(Account acc);
void searchAccount();
int searchByNumber();
int checkName(char* line);
int checkAddress(char* line);
int checkID(char* line);
void makeDeposit();
void makeWithdrawal();
void makeMoneyTransfer();
void transferToSavingsAccount();
void transferFromSavingsAccount();
void enterLine(char* line, char* msg, int (*check)(char*));
int cmpName(char* line, Account acc);
int cmpSurname(char* line, Account acc);
int cmpAddress(char* line, Account acc);
int cmpID(char* line, Account acc);
void searchByField(long size, char* msg, int (*check)(char*),
				   int (*cmp)(char*, Account));
int verifyAccount(Account acc, int index);
void makeBackup();
void confirmOperation();

int main()
{
	int choice;

	do {
		printWelcome();

		if (scanf("%d", &choice) == 0) {
			printf("\nIncorrect input.\n\n");
			while (getchar() != '\n')
				;
			continue;
		}

		while (getchar() != '\n')
			;

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

void confirmOperation()
{
	char line[MAX_LINE];
	do {
		printf("Do you wish to confirm the operation? (y/n):\n");
		fgets(line, MAX_LINE, stdin);
	} while (strcmp("y\n", line) && strcmp("n\n", line));

	if (!strcmp("n\n", line)) {
		if (remove("data.bin") != 0) {
			printf("Error deleting file.\n");
			return;
		}
		if (rename("backup.bin", "data.bin") != 0) {
			printf("Error renaming file.\n");
			return;
		}
		makeBackup();
	}
}

void makeBackup()
{
	FILE* data = fopen("data.bin", "rb");
	FILE* backup = fopen("backup.bin", "wb");
	if (data == NULL || backup == NULL) {
		printf("File open error.\n");
		return;
	}
	Account acc;
	while (fread(&acc, sizeof(Account), 1, data)) {
		fwrite(&acc, sizeof(Account), 1, backup);
	}

	fclose(data);
	fclose(backup);
}

int verifyAccount(Account acc, int index)
{
	if (checkName(acc.name) && checkName(acc.surname) &&
		checkAddress(acc.address) && checkID(acc.id) &&
		(index + 1) == acc.number && acc.regularBalance >= 0 &&
		acc.savingsBalance >= 0) {
		return 1;
	}

	return 0;
}

void transferFromSavingsAccount()
{
	printf("\nMaking a transfer from a savings account:\n");

	int index = searchByNumber();

	if (index == -1) {
		return;
	}

	Account acc;
	if (!readAccount(&acc, index)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc);

	double transfer;

	while (1) {
		printf("Type in an amount of money:\n");

		if (scanf("%lf", &transfer) == 0 || transfer < 0 ||
			transfer > acc.savingsBalance) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (acc.regularBalance - (int)(floor(transfer * 100)) < 0 ||
			acc.savingsBalance + (int)(floor(transfer * 100)) < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc.savingsBalance -= (int)(floor(transfer * 100));
		acc.regularBalance += (int)(floor(transfer * 100));
		printf("\nTransferred %.2f.\n", transfer);
		while (getchar() != '\n')
			;
		makeBackup();
		overwriteAccount(acc, index);
		confirmOperation();

		if (!readAccount(&acc, index)) {
			printf("Error reading the file.\n");
			return;
		}

		printAccount(acc);
		return;
	}
}

void transferToSavingsAccount()
{
	printf("\nMaking a transfer to a savings account:\n");

	int index = searchByNumber();

	if (index == -1) {
		return;
	}

	Account acc;
	if (!readAccount(&acc, index)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc);

	double transfer;

	while (1) {
		printf("Type in an amount of money:\n");

		if (scanf("%lf", &transfer) == 0 || transfer < 0 ||
			transfer > acc.regularBalance) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (acc.regularBalance - (int)(floor(transfer * 100)) < 0 ||
			acc.savingsBalance + (int)(floor(transfer * 100)) < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc.regularBalance -= (int)(floor(transfer * 100));
		acc.savingsBalance += (int)(floor(transfer * 100));
		printf("\nTransferred %.2f.\n", transfer);
		while (getchar() != '\n')
			;
		makeBackup();
		overwriteAccount(acc, index);
		confirmOperation();

		if (!readAccount(&acc, index)) {
			printf("Error reading the file.\n");
			return;
		}
		printAccount(acc);
		return;
	}
}

void makeMoneyTransfer()
{
	printf("\nMaking a money transfer:\n");

	int index1 = searchByNumber();

	if (index1 == -1) {
		return;
	}

	Account acc1;
	if (!readAccount(&acc1, index1)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc1);

	int index2 = searchByNumber();

	if (index2 == -1) {
		return;
	}

	Account acc2;
	if (!readAccount(&acc2, index2)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc2);

	double transfer;

	while (1) {
		printf("Type in an amount of money ");
		printf("to transfer from the first account to the second:\n");

		if (scanf("%lf", &transfer) == 0 || transfer < 0 ||
			transfer > acc1.regularBalance) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (acc1.regularBalance - (int)(floor(transfer * 100)) < 0 ||
			acc2.regularBalance + (int)(floor(transfer * 100)) < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc1.regularBalance -= (int)(floor(transfer * 100));
		acc2.regularBalance += (int)(floor(transfer * 100));
		printf("\nTransferred %.2f.\n", transfer);
		while (getchar() != '\n')
			;
		makeBackup();
		overwriteAccount(acc1, index1);
		overwriteAccount(acc2, index2);
		confirmOperation();

		if (!readAccount(&acc1, index1)) {
			printf("Error reading the file.\n");
			return;
		}
		if (!readAccount(&acc2, index2)) {
			printf("Error reading the file.\n");
			return;
		}
		printAccount(acc1);
		printAccount(acc2);
		return;
	}
}

void makeWithdrawal()
{
	printf("\nMaking a withdrawal:\n");

	int index = searchByNumber();

	if (index == -1) {
		return;
	}

	Account acc;
	if (!readAccount(&acc, index)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc);

	double withdrawal;

	while (1) {
		printf("Type in an amount of money:\n");

		if (scanf("%lf", &withdrawal) == 0 || withdrawal < 0 ||
			withdrawal > acc.regularBalance) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}
		if (acc.regularBalance - (int)(floor(withdrawal * 100)) < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc.regularBalance -= (int)(floor(withdrawal * 100));
		printf("\nWithdrawn %.2f.\n", withdrawal);
		while (getchar() != '\n')
			;
		makeBackup();
		overwriteAccount(acc, index);
		confirmOperation();
		if (!readAccount(&acc, index)) {
			printf("Error reading the file.\n");
			return;
		}
		printAccount(acc);
		return;
	}
}

void makeDeposit()
{
	printf("\nMaking a deposit:\n");

	int index = searchByNumber();

	if (index == -1) {
		return;
	}

	Account acc;
	if (!readAccount(&acc, index)) {
		printf("Error reading the file.\n");
		return;
	}
	printAccount(acc);

	double deposit;

	while (1) {
		printf("Type in an amount of money:\n");

		if (scanf("%lf", &deposit) == 0 || deposit < 0) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		if (acc.regularBalance + (int)(floor(deposit * 100)) < 0) {
			while (getchar() != '\n')
				;
			continue;
		}

		acc.regularBalance += (int)(floor(deposit * 100));
		printf("\nDeposited %.2f.\n", deposit);
		while (getchar() != '\n')
			;
		makeBackup();
		overwriteAccount(acc, index);
		confirmOperation();

		if (!readAccount(&acc, index)) {
			printf("Error reading the file.\n");
			return;
		}
		printAccount(acc);
		return;
	}
}

int checkName(char* line)
{
	if (line == NULL) {
		return 0;
	}
	if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' &&
		line[strlen(line) - 2] == '\r') {
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
	if (line == NULL) {
		return 0;
	}
	if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' &&
		line[strlen(line) - 2] == '\r') {
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
	if (line == NULL) {
		return 0;
	}
	if (strlen(line) > 1 && line[strlen(line) - 1] == '\n' &&
		line[strlen(line) - 2] == '\r') {
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

int cmpName(char* line, Account acc)
{
	return (strcmp(line, acc.name));
}

int cmpSurname(char* line, Account acc)
{
	return (strcmp(line, acc.surname));
}

int cmpAddress(char* line, Account acc)
{
	return (strcmp(line, acc.address));
}

int cmpID(char* line, Account acc)
{
	return (strcmp(line, acc.id));
}

void searchAccount()
{
	long size = whatSize();

	if (size == 0) {
		printf("\nNo accounts to search.\n\n");
		return;
	}

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
			while (getchar() != '\n')
				;
			continue;
		}

		while (getchar() != '\n')
			;

		int index;

		switch (choice) {
		case 1:
			index = searchByNumber();
			Account acc;
			if (!readAccount(&acc, index)) {
				printf("Error reading the file.\n");
				return;
			}
			printAccount(acc);
			break;

		case 2:
			searchByField(size, "name", &checkName, &cmpName);
			break;

		case 3:
			searchByField(size, "surname", &checkName, &cmpSurname);
			break;

		case 4:
			searchByField(size, "address", &checkAddress, &cmpAddress);
			break;

		case 5:
			searchByField(size, "ID", &checkID, &cmpID);
			break;


		default:
			printf("\nIncorrect input.\n\n");
			break;
		}
	} while (choice > 5 || choice < 1);
}

void searchByField(long size, char* msg, int (*check)(char*),
				   int (*cmp)(char*, Account))
{
	char line[MAX_LINE];
	int found = 0;
	enterLine(line, msg, check);

	for (int i = 0; i < size; ++i) {
		Account acc;
		if (!readAccount(&acc, i)) {
			printf("Error reading the file.\n");
			return;
		}
		if (!(*cmp)(line, acc)) {
			printAccount(acc);
			found = 1;
		}
	}

	if (!found) {
		printf("\nAccount not found.\n\n");
	}
}

int searchByNumber()
{
	long size = whatSize();

	if (size == 0) {
		return -1;
	}

	int number;

	while (1) {
		printf("\nThere are %ld records in the database.", size);
		printf("\nType in a number from 1 to %ld:\n", size);

		if (scanf("%d", &number) == 0 || number > size || number <= 0) {
			printf("\nIncorrect input.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		return number - 1;
	}
}

void printAccount(Account acc)
{
	printf("\nNumber:\t\t\t%d\n", acc.number);
	printf("Name:\t\t\t%s\n", acc.name);
	printf("Surname:\t\t%s\n", acc.surname);
	printf("Address:\t\t%s\n", acc.address);
	printf("ID:\t\t\t%s\n", acc.id);
	printf("Regular balance:\t%.2f\n", ((float)acc.regularBalance) / 100);
	printf("Savings balance:\t%.2f\n\n", ((float)acc.savingsBalance) / 100);
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
		Account acc;
		if (!readAccount(&acc, i)) {
			printf("Error reading the file.\n");
			return;
		}
		printAccount(acc);
	}
}

void enterLine(char* line, char* msg, int (*check)(char*))
{
	do {
		printf("Type in the %s:\n", msg);
		fgets(line, MAX_LINE, stdin);
	} while (!(*check)(line));
}

void makeAccount()
{
	Account acc;
	char line[MAX_LINE];
	long size = whatSize();

	printf("\nCreating new account:\n\n");
	acc.number = size + 1;

	enterLine(line, "name", &checkName);
	strcpy(acc.name, line);
	enterLine(line, "surname", &checkName);
	strcpy(acc.surname, line);
	enterLine(line, "address", &checkAddress);
	strcpy(acc.address, line);
	enterLine(line, "ID", &checkID);
	strcpy(acc.id, line);

	double number;

	while (1) {
		printf("Type in the regular account balance:\n");
		if (scanf("%lf", &number) == 0 || number < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc.regularBalance = (int)(number * 100);
		if (acc.regularBalance < 0) {
			continue;
		}
		break;
	}

	while (1) {
		printf("Type in the savings account balance:\n");
		if (scanf("%lf", &number) == 0 || number < 0) {
			while (getchar() != '\n')
				;
			continue;
		}
		acc.savingsBalance = (int)(number * 100);
		if (acc.savingsBalance < 0) {
			continue;
		}
		break;
	}

	while (getchar() != '\n')
		;

	makeBackup();
	appendAccount(acc);
	confirmOperation();

	printf("\n");
}

void overwriteAccount(Account acc, int index)
{
	FILE* data = fopen("data.bin", "rb+");
	if (data == NULL) {
		printf("File open error.\n");
		return;
	}
	fseek(data, index * sizeof(Account), SEEK_SET);
	fwrite(&acc, sizeof(Account), 1, data);
	fclose(data);
}

void appendAccount(Account acc)
{
	FILE* data = fopen("data.bin", "ab");
	if (data == NULL) {
		printf("File open error.\n");
		return;
	}
	fwrite(&acc, sizeof(Account), 1, data);
	fclose(data);
}

int readAccount(Account* acc, int index)
{
	FILE* data = fopen("data.bin", "rb");
	if (data == NULL) {
		return 0;
	}
	fseek(data, index * sizeof(Account), SEEK_SET);
	fread(acc, sizeof(Account), 1, data);
	fclose(data);
	return verifyAccount(*acc, index) ? 1 : 0;
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
