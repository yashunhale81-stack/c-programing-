#include <stdio.h>
#include <string.h>
#define MAX_ACCOUNTS 100
#define NAME_LENGTH 50

typedef struct
{
	int account_number;
	char name[NAME_LENGTH];
	double balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

void clear_input(void)
{
	int character;

	while ((character = getchar()) != '\n' && character != EOF)
	{
	}
}

int find_account(int account_number)
{
	int i;

	for (i = 0; i < account_count; i++)
	{
		if (accounts[i].account_number == account_number)
		{
			return i;
		}
	}

	return -1;
}

void create_account(void)
{
	Account new_account;

	if (account_count == MAX_ACCOUNTS)
	{
		printf("\nThe bank cannot create any more accounts.\n");
		return;
	}

	printf("\nEnter account number: ");
	if (scanf("%d", &new_account.account_number) != 1)
	{
		printf("Invalid account number.\n");
		clear_input();
		return;
	}

	if (find_account(new_account.account_number) != -1)
	{
		printf("An account with that number already exists.\n");
		clear_input();
		return;
	}

	clear_input();
	printf("Enter account holder name: ");
	if (fgets(new_account.name, NAME_LENGTH, stdin) == NULL)
	{
		printf("Could not read the name.\n");
		return;
	}
	new_account.name[strcspn(new_account.name, "\n")] = '\0';

	printf("Enter opening balance: ");
	if (scanf("%lf", &new_account.balance) != 1 || new_account.balance < 0)
	{
		printf("Opening balance must be zero or greater.\n");
		clear_input();
		return;
	}

	accounts[account_count] = new_account;
	account_count++;
	printf("Account created successfully.\n");
}

void deposit_money(void)
{
	int account_number;
	int index;
	double amount;

	printf("\nEnter account number: ");
	if (scanf("%d", &account_number) != 1)
	{
		printf("Invalid account number.\n");
		clear_input();
		return;
	}

	index = find_account(account_number);
	if (index == -1)
	{
		printf("Account not found.\n");
		return;
	}

	printf("Enter deposit amount: ");
	if (scanf("%lf", &amount) != 1 || amount <= 0)
	{
		printf("Deposit amount must be greater than zero.\n");
		clear_input();
		return;
	}

	accounts[index].balance += amount;
	printf("Deposit successful. New balance: %.2f\n", accounts[index].balance);
}

void withdraw_money(void)
{
	int account_number;
	int index;
	double amount;

	printf("\nEnter account number: ");
	if (scanf("%d", &account_number) != 1)
	{
		printf("Invalid account number.\n");
		clear_input();
		return;
	}

	index = find_account(account_number);
	if (index == -1)
	{
		printf("Account not found.\n");
		return;
	}

	printf("Enter withdrawal amount: ");
	if (scanf("%lf", &amount) != 1 || amount <= 0)
	{
		printf("Withdrawal amount must be greater than zero.\n");
		clear_input();
		return;
	}
	if (amount > accounts[index].balance)
	{
		printf("Insufficient balance.\n");
		return;
	}

	accounts[index].balance -= amount;
	printf("Withdrawal successful. New balance: %.2f\n", accounts[index].balance);
}

void show_account(void)
{
	int account_number;
	int index;

	printf("\nEnter account number: ");
	if (scanf("%d", &account_number) != 1)
	{
		printf("Invalid account number.\n");
		clear_input();
		return;
	}

	index = find_account(account_number);
	if (index == -1)
	{
		printf("Account not found.\n");
		return;
	}

	printf("\nAccount number: %d\n", accounts[index].account_number);
	printf("Account holder: %s\n", accounts[index].name);
	printf("Balance: %.2f\n", accounts[index].balance);
}

void show_all_accounts(void)
{
	int i;

	if (account_count == 0)
	{
		printf("\nNo accounts have been created yet.\n");
		return;
	}

	printf("\n%-15s %-25s %s\n", "Account Number", "Account Holder", "Balance");
	printf("------------------------------------------------------------\n");
	for (i = 0; i < account_count; i++)
	{
		printf("%-15d %-25s %.2f\n",
			   accounts[i].account_number,
			   accounts[i].name,
			   accounts[i].balance);
	}
}

int main(void)
{
	int choice;

	do
	{
		printf("\n========== BANKING SYSTEM ==========\n");
		printf("1. Create account\n");
		printf("2. Deposit money\n");
		printf("3. Withdraw money\n");
		printf("4. Check account details\n");
		printf("5. Show all accounts\n");
		printf("6. Exit\n");
		printf("Choose an option: ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Please enter a number from 1 to 6.\n");
			clear_input();
			continue;
		}

		switch (choice)
		{
			case 1:
				create_account();
				break;
			case 2:
				deposit_money();
				break;
			case 3:
				withdraw_money();
				break;
			case 4:
				show_account();
				break;
			case 5:
				show_all_accounts();
				break;
			case 6:
				printf("Thank you for using the Banking System.\n");
				break;
			default:
				printf("Invalid option. Please choose 1 to 6.\n");
		}
	} 
    while (choice != 6);
    return 0;
}
