#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_SIZE 50
#define COURSE_SIZE 50
#define DATA_FILE "students.dat"

typedef struct {
	int roll_number;
	char name[NAME_SIZE];
	int age;
	char course[COURSE_SIZE];
	float marks;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void remove_newline(char text[])
{
	text[strcspn(text, "\n")] = '\0';
}

void read_text(char message[], char text[], int size)
{
	printf("%s", message);
	fgets(text, size, stdin);
	remove_newline(text);
}

int read_number(char message[])
{
	char input[30];
	int number;
	char extra;

	while (1) 
    {
		read_text(message, input, sizeof(input));
		if (sscanf(input, "%d %c", &number, &extra) == 1)
        {
			return number;
		}
		printf("Please enter a valid number.\n");
	}
}

float read_marks(void)
{
	char input[30];
	float marks;
	char extra;

	while (1) 
    {
		read_text("Enter marks (0-100): ", input, sizeof(input));
		if (sscanf(input, "%f %c", &marks, &extra) == 1 &&
			marks >= 0 && marks <= 100) 
        {
			return marks;
		}
		printf("Marks must be between 0 and 100.\n");
	}
}

void save_students(void)
{
	FILE *file = fopen(DATA_FILE, "wb");

	if (file == NULL)
    {
		printf("Unable to save student data.\n");
		return;
	}
	fwrite(&student_count, sizeof(student_count), 1, file);
	fwrite(students, sizeof(Student), student_count, file);
	fclose(file);
}

void load_students(void)
{
	FILE *file = fopen(DATA_FILE, "rb");

	if (file == NULL) 
    {
		return;
	}
	fread(&student_count, sizeof(student_count), 1, file);
	if (student_count < 0 || student_count > MAX_STUDENTS) 
    {
		student_count = 0;
		fclose(file);
		return;
	}
	fread(students, sizeof(Student), student_count, file);
	fclose(file);
}

int find_student(int roll_number)
{
	int index;

	for (index = 0; index < student_count; index++) 
    {
		if (students[index].roll_number == roll_number) 
        {
			return index;
		}
	}
	return -1;
}

void add_student(void)
{
	Student student;

	if (student_count >= MAX_STUDENTS) 
    {
		printf("The database is full.\n");
		return;
	}
	student.roll_number = read_number("Enter roll number: ");
	if (find_student(student.roll_number) != -1) 
    {
		printf("That roll number already exists.\n");
		return;
	}
	read_text("Enter name: ", student.name, NAME_SIZE);
	student.age = read_number("Enter age: ");
	read_text("Enter course: ", student.course, COURSE_SIZE);
	student.marks = read_marks();

	students[student_count] = student;
	student_count++;
	save_students();
	printf("Student added successfully.\n");
}

void display_students(void)
{
	int index;

	if (student_count == 0) 
    {
		printf("No student records found.\n");
		return;
	}
	printf("\n%-10s %-20s %-8s %-20s %-8s\n",
		"Roll No.", "Name", "Age", "Course", "Marks");
	printf("----------------------------------------------------------------\n");
	for (index = 0; index < student_count; index++) 
    {
		printf("%-10d %-20.20s %-8d %-20.20s %-8.2f\n",
			students[index].roll_number,
			students[index].name,
			students[index].age,
			students[index].course,
			students[index].marks);
	}
}

void search_student(void)
{
	int roll_number = read_number("Enter roll number to search: ");
	int index = find_student(roll_number);

	if (index == -1) 
    {
		printf("Student not found.\n");
		return;
	}
	printf("\nRoll number: %d\n", students[index].roll_number);
	printf("Name: %s\n", students[index].name);
	printf("Age: %d\n", students[index].age);
	printf("Course: %s\n", students[index].course);
	printf("Marks: %.2f\n", students[index].marks);
}

void update_student(void)
{
	int roll_number = read_number("Enter roll number to update: ");
	int index = find_student(roll_number);

	if (index == -1) 
    {
		printf("Student not found.\n");
		return;
	}
	read_text("Enter new name: ", students[index].name, NAME_SIZE);
	students[index].age = read_number("Enter new age: ");
	read_text("Enter new course: ", students[index].course, COURSE_SIZE);
	students[index].marks = read_marks();
	save_students();
	printf("Student updated successfully.\n");
}

void delete_student(void)
{
	int roll_number = read_number("Enter roll number to delete: ");
	int index = find_student(roll_number);
	int next;

	if (index == -1) 
    {
		printf("Student not found.\n");
		return;
	}
	for (next = index; next < student_count - 1; next++) 
    {
		students[next] = students[next + 1];
	}
	student_count--;
	save_students();
	printf("Student deleted successfully.\n");
}

void show_menu(void)
{
	printf("\n===== Student Database System =====\n");
	printf("1. Add student\n");
	printf("2. Display all students\n");
	printf("3. Search student\n");
	printf("4. Update student\n");
	printf("5. Delete student\n");
	printf("6. Exit\n");
}

int main(void)
{
	int choice;

	load_students();
	while (1)
    {
		show_menu();
		choice = read_number("Enter your choice: ");

		switch (choice) 
        {
		case 1:
			add_student();
			break;
		case 2:
			display_students();
			break;
		case 3:
			search_student();
			break;
		case 4:
			update_student();
			break;
		case 5:
			delete_student();
			break;
		case 6:
			printf("Thank you for using the Student Database System.\n");
			return 0;
		default:
			printf("Invalid choice. Please choose 1 to 6.\n");
		}
	}
}
