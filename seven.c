#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_SIZE 100
#define AUTHOR_SIZE 100

struct Book 
{
	int id;
	char title[TITLE_SIZE];
	char author[AUTHOR_SIZE];
	int issued;
};

struct Book books[MAX_BOOKS];
int bookCount = 0;

void clearInput(void) 
{
	int character;

	while ((character = getchar()) != '\n' && character != EOF) 
    {
	}
}

int findBook(int id) 
{
	int index;

	for (index = 0; index < bookCount; index++) 
    {
		if (books[index].id == id) 
        {
			return index;
		}
	}

	return -1;
}

void addBook(void) 
{
	struct Book book;

	if (bookCount >= MAX_BOOKS) 
    {
		printf("Library is full.\n");
		return;
	}

	printf("Enter book ID: ");
	if (scanf("%d", &book.id) != 1) 
    {
		printf("Invalid ID.\n");
		clearInput();
		return;
	}
	clearInput();

	if (findBook(book.id) != -1) 
    {
		printf("Book ID already exists.\n");
		return;
	}

	printf("Enter book title: ");
	fgets(book.title, TITLE_SIZE, stdin);
	book.title[strcspn(book.title, "\n")] = '\0';

	printf("Enter author name: ");
	fgets(book.author, AUTHOR_SIZE, stdin);
	book.author[strcspn(book.author, "\n")] = '\0';

	book.issued = 0;
	books[bookCount] = book;
	bookCount++;
	printf("Book added successfully.\n");
}

void displayBooks(void) 
{
	int index;

	if (bookCount == 0) 
    {
		printf("No books in the library.\n");
		return;
	}

	printf("\n%-6s %-30s %-25s %-10s\n", "ID", "Title", "Author", "Status");
	printf("------------------------------------------------------------------\n");
	for (index = 0; index < bookCount; index++) 
    {
		printf("%-6d %-30s %-25s %-10s\n",
			   books[index].id,
			   books[index].title,
			   books[index].author,
			   books[index].issued ? "Issued" : "Available");
	}
}

void searchBook(void) 

{
	char title[TITLE_SIZE];
	int index;
	int found = 0;

	clearInput();
	printf("Enter title to search: ");
	fgets(title, TITLE_SIZE, stdin);
	title[strcspn(title, "\n")] = '\0';

	for (index = 0; index < bookCount; index++) 
    {
		if (strstr(books[index].title, title) != NULL) 
        {
			printf("ID: %d | Title: %s | Author: %s | Status: %s\n",
				   books[index].id,
				   books[index].title,
				   books[index].author,
				   books[index].issued ? "Issued" : "Available");
			found = 1;
		}
	}

	if (!found) 
    {
		printf("Book not found.\n");
	}
}

void changeBookStatus(int issued) 
{
	int id;
	int index;

	printf("Enter book ID: ");
	if (scanf("%d", &id) != 1) 
    {
		printf("Invalid ID.\n");
		clearInput();
		return;
	}

	index = findBook(id);
	if (index == -1) 
    {
		printf("Book not found.\n");
	} else if (books[index].issued == issued) 
    {
		printf("Book is already %s.\n", issued ? "issued" : "available");
	} 
     else 
    {
		books[index].issued = issued;
		printf("Book %s successfully.\n", issued ? "issued" : "returned");
	}
}

int main(void) 
{
	int choice;

	do 
    {
		printf("\n===== Library Management System =====\n");
		printf("1. Add book\n");
		printf("2. Display all books\n");
		printf("3. Search book\n");
		printf("4. Issue book\n");
		printf("5. Return book\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");

		if (scanf("%d", &choice) != 1) {
			printf("Please enter a number from 1 to 6.\n");
			clearInput();
			continue;
		}

		switch (choice) 
        {
			case 1:
				addBook();
				break;
			case 2:
				displayBooks();
				break;
			case 3:
				searchBook();
				break;
			case 4:
				changeBookStatus(1);
				break;
			case 5:
				changeBookStatus(0);
				break;
			case 6:
				printf("Thank you for using the system.\n");
				break;
			default:
				printf("Invalid choice.\n");
		}
	} 
    
    while (choice != 6);
    return 0;
}
