#include <stdio.h>
#include <string.h>
#define MAX_RESERVATIONS 100
#define NAME_LENGTH 50

typedef struct
{
	int number;
	char name[40];
	char source[30];
	char destination[30];
	int available_seats;
} Train;

typedef struct
{
	int pnr;
	char passenger_name[NAME_LENGTH];
	int age;
	int train_number;
	char train_name[40];
	char source[30];
	char destination[30];
} Reservation;

Train trains[] =
{
	{101, "Morning Express", "Delhi", "Mumbai", 50},
	{202, "Coastal Express", "Chennai", "Bengaluru", 40},
	{303, "City Intercity", "Kolkata", "Patna", 60}
};

Reservation reservations[MAX_RESERVATIONS];
int reservation_count = 0;
int next_pnr = 1001;

void clear_input(void)
{
	int character;

	while ((character = getchar()) != '\n' && character != EOF)
	{
	}
}

void read_text(char text[], int size)
{
	if (fgets(text, size, stdin) != NULL)
	{
		text[strcspn(text, "\n")] = '\0';
	}
}

int find_train(int train_number)
{
	int train_count = sizeof(trains) / sizeof(trains[0]);
	int i;

	for (i = 0; i < train_count; i++)
	{
		if (trains[i].number == train_number)
		{
			return i;
		}
	}

	return -1;
}

int find_reservation(int pnr)
{
	int i;

	for (i = 0; i < reservation_count; i++)
	{
		if (reservations[i].pnr == pnr)
		{
			return i;
		}
	}

	return -1;
}

void show_trains(void)
{
	int train_count = sizeof(trains) / sizeof(trains[0]);
	int i;

	printf("\n%-8s %-22s %-15s %-15s %s\n",
		   "Number", "Train Name", "From", "To", "Seats");
	printf("---------------------------------------------------------------------\n");
	for (i = 0; i < train_count; i++)
	{
		printf("%-8d %-22s %-15s %-15s %d\n",
			   trains[i].number,
			   trains[i].name,
			   trains[i].source,
			   trains[i].destination,
			   trains[i].available_seats);
	}
}

void reserve_ticket(void)
{
	int train_number;
	int train_index;
	Reservation reservation;

	if (reservation_count == MAX_RESERVATIONS)
	{
		printf("\nThe reservation system is full.\n");
		return;
	}

	show_trains();
	printf("\nEnter train number: ");
	if (scanf("%d", &train_number) != 1)
	{
		printf("Invalid train number.\n");
		clear_input();
		return;
	}

	train_index = find_train(train_number);
	if (train_index == -1)
	{
		printf("Train not found.\n");
		return;
	}
	if (trains[train_index].available_seats == 0)
	{
		printf("No seats are available on this train.\n");
		return;
	}

	clear_input();
	printf("Enter passenger name: ");
	read_text(reservation.passenger_name, NAME_LENGTH);

	printf("Enter passenger age: ");
	if (scanf("%d", &reservation.age) != 1 || reservation.age <= 0)
	{
		printf("Age must be greater than zero.\n");
		clear_input();
		return;
	}

	reservation.pnr = next_pnr;
	next_pnr++;
	reservation.train_number = trains[train_index].number;
	strcpy(reservation.train_name, trains[train_index].name);
	strcpy(reservation.source, trains[train_index].source);
	strcpy(reservation.destination, trains[train_index].destination);
	reservations[reservation_count] = reservation;
	reservation_count++;
	trains[train_index].available_seats--;

	printf("\nTicket reserved successfully.\n");
	printf("Your PNR number is: %d\n", reservation.pnr);
}

void display_reservation(const Reservation *reservation)
{
	printf("\nPNR: %d\n", reservation->pnr);
	printf("Passenger: %s\n", reservation->passenger_name);
	printf("Age: %d\n", reservation->age);
	printf("Train: %d - %s\n", reservation->train_number, reservation->train_name);
	printf("Route: %s to %s\n", reservation->source, reservation->destination);
}

void view_reservation(void)
{
	int pnr;
	int index;

	printf("\nEnter PNR number: ");
	if (scanf("%d", &pnr) != 1)
	{
		printf("Invalid PNR number.\n");
		clear_input();
		return;
	}

	index = find_reservation(pnr);
	if (index == -1)
	{
		printf("Reservation not found.\n");
		return;
	}

	display_reservation(&reservations[index]);
}

void view_all_reservations(void)
{
	int i;

	if (reservation_count == 0)
	{
		printf("\nNo reservations found.\n");
		return;
	}

	for (i = 0; i < reservation_count; i++)
	{
		display_reservation(&reservations[i]);
	}
}

void cancel_ticket(void)
{
	int pnr;
	int index;
	int train_index;
	int i;

	printf("\nEnter PNR number to cancel: ");
	if (scanf("%d", &pnr) != 1)
	{
		printf("Invalid PNR number.\n");
		clear_input();
		return;
	}

	index = find_reservation(pnr);
	if (index == -1)
	{
		printf("Reservation not found.\n");
		return;
	}

	train_index = find_train(reservations[index].train_number);
	if (train_index != -1)
	{
		trains[train_index].available_seats++;
	}

	for (i = index; i < reservation_count - 1; i++)
	{
		reservations[i] = reservations[i + 1];
	}
	reservation_count--;
	printf("Ticket cancelled successfully.\n");
}

int main(void)
{
	int choice;

	do
	{
		printf("\n========== RAILWAY RESERVATION SYSTEM ==========\n");
		printf("1. Show trains\n");
		printf("2. Reserve ticket\n");
		printf("3. View reservation by PNR\n");
		printf("4. View all reservations\n");
		printf("5. Cancel ticket\n");
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
				show_trains();
				break;
			case 2:
				reserve_ticket();
				break;
			case 3:
				view_reservation();
				break;
			case 4:
				view_all_reservations();
				break;
			case 5:
				cancel_ticket();
				break;
			case 6:
				printf("Thank you for using the Railway Reservation System.\n");
				break;
			default:
				printf("Invalid option. Please choose 1 to 6.\n");
		}
	} while (choice != 6);

	return 0;
}
