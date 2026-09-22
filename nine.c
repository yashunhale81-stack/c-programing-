#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LENGTH 50
#define TEXT_LENGTH 80

typedef struct
{
	int id;
	char name[NAME_LENGTH];
	int age;
	char gender[15];
	char disease[TEXT_LENGTH];
	char doctor[NAME_LENGTH];
} Patient;

Patient patients[MAX_PATIENTS];
int patient_count = 0;

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

int find_patient(int id)
{
	int i;

	for (i = 0; i < patient_count; i++)
	{
		if (patients[i].id == id)
		{
			return i;
		}
	}

	return -1;
}

void add_patient(void)
{
	Patient patient;

	if (patient_count == MAX_PATIENTS)
	{
		printf("\nThe hospital has reached its patient limit.\n");
		return;
	}

	printf("\nEnter patient ID: ");
	if (scanf("%d", &patient.id) != 1 || patient.id <= 0)
	{
		printf("Patient ID must be a positive number.\n");
		clear_input();
		return;
	}

	if (find_patient(patient.id) != -1)
	{
		printf("A patient with that ID already exists.\n");
		clear_input();
		return;
	}

	clear_input();
	printf("Enter patient name: ");
	read_text(patient.name, NAME_LENGTH);

	printf("Enter age: ");
	if (scanf("%d", &patient.age) != 1 || patient.age < 0)
	{
		printf("Age must be zero or greater.\n");
		clear_input();
		return;
	}

	clear_input();
	printf("Enter gender: ");
	read_text(patient.gender, sizeof(patient.gender));

	printf("Enter disease or reason for visit: ");
	read_text(patient.disease, TEXT_LENGTH);

	printf("Enter doctor name: ");
	read_text(patient.doctor, NAME_LENGTH);

	patients[patient_count] = patient;
	patient_count++;
	printf("Patient added successfully.\n");
}

void display_patient(const Patient *patient)
{
	printf("\nPatient ID: %d\n", patient->id);
	printf("Name: %s\n", patient->name);
	printf("Age: %d\n", patient->age);
	printf("Gender: %s\n", patient->gender);
	printf("Disease: %s\n", patient->disease);
	printf("Doctor: %s\n", patient->doctor);
}

void view_all_patients(void)
{
	int i;

	if (patient_count == 0)
	{
		printf("\nNo patient records found.\n");
		return;
	}

	printf("\n%-10s %-25s %-6s %-20s %-20s\n",
		   "ID", "Name", "Age", "Disease", "Doctor");
	printf("-------------------------------------------------------------------------------\n");
	for (i = 0; i < patient_count; i++)
	{
		printf("%-10d %-25s %-6d %-20s %-20s\n",
			   patients[i].id,
			   patients[i].name,
			   patients[i].age,
			   patients[i].disease,
			   patients[i].doctor);
	}
}

void search_patient(void)
{
	int id;
	int index;

	printf("\nEnter patient ID to search: ");
	if (scanf("%d", &id) != 1)
	{
		printf("Invalid patient ID.\n");
		clear_input();
		return;
	}

	index = find_patient(id);
	if (index == -1)
	{
		printf("Patient not found.\n");
		return;
	}

	display_patient(&patients[index]);
}

void update_disease(void)
{
	int id;
	int index;

	printf("\nEnter patient ID: ");
	if (scanf("%d", &id) != 1)
	{
		printf("Invalid patient ID.\n");
		clear_input();
		return;
	}

	index = find_patient(id);
	if (index == -1)
	{
		printf("Patient not found.\n");
		return;
	}

	clear_input();
	printf("Enter updated disease or treatment details: ");
	read_text(patients[index].disease, TEXT_LENGTH);
	printf("Patient record updated successfully.\n");
}

void discharge_patient(void)
{
	int id;
	int index;
	int i;

	printf("\nEnter patient ID to discharge: ");
	if (scanf("%d", &id) != 1)
	{
		printf("Invalid patient ID.\n");
		clear_input();
		return;
	}

	index = find_patient(id);
	if (index == -1)
	{
		printf("Patient not found.\n");
		return;
	}

	for (i = index; i < patient_count - 1; i++)
	{
		patients[i] = patients[i + 1];
	}
	patient_count--;
	printf("Patient discharged successfully.\n");
}

int main(void)
{
	int choice;

	do
	{
		printf("\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n");
		printf("1. Add patient\n");
		printf("2. View all patients\n");
		printf("3. Search patient\n");
		printf("4. Update patient disease\n");
		printf("5. Discharge patient\n");
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
				add_patient();
				break;
			case 2:
				view_all_patients();
				break;
			case 3:
				search_patient();
				break;
			case 4:
				update_disease();
				break;
			case 5:
				discharge_patient();
				break;
			case 6:
				printf("Thank you for using the Hospital Management System.\n");
				break;
			default:
				printf("Invalid option. Please choose 1 to 6.\n");
		}
	} 
    while (choice != 6);
    return 0;
}
