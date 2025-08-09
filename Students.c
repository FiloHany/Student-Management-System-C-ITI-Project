#include <stdio.h>
#include <stdlib.h>
#include "students.h"
#include "STD_Types.h"

u8 no_students; // Global variable to store the number of students

// Function: idExists
// Description: Checks if a student ID already exists in the array of students.
// Parameters:
//    - ptr: Pointer to the array of students.
//    - count1: Number of students currently stored.
//    - idToCheck: The student ID to check for uniqueness.
// Returns: 1 if ID exists, 0 otherwise.
u8 idExists(Student *ptr, u8 count1, u8 idToCheck)
{
    for (u8 i = 0; i < count1; i++)
    {
        if (ptr[i].ID == idToCheck)
        {
            return 1; // ID already exists
        }
    }
    return 0; // ID does not exist
}

// Function: inputStudent
// Description: Inputs multiple students' information from the user and stores it in memory.
// Parameters:
//    - ptr: Double pointer to the array of students, used to allocate and modify the array.
// Side Effects:
//    - Asks for user input and can exit the program if memory allocation fails.
void inputStudent(Student **ptr)
{
    // Asking user how many students they want to enter
    printf("How many students do you want to enter? ");
    scanf("%d", &no_students);

    // Allocate memory based on the number of students
    *ptr = (Student *)malloc(no_students * sizeof(Student));
    if (*ptr == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (u8 i = 0; i < no_students; i++)
    {
        printf("Please enter the name of student %d: ", i + 1);
        scanf("%s", (*ptr)[i].name);

        u8 newID;
        u8 idUnique;
        do
        {
            printf("Please enter the ID of student %d: ", i + 1);
            scanf("%d", &newID);

            idUnique = !idExists(*ptr, i, newID); // Check if the ID is unique
            if (!idUnique)
            {
                printf("ID %d is already taken. Please enter a different ID.\n", newID);
            }
        } while (!idUnique);

        (*ptr)[i].ID = newID;

        printf("Please enter grades for 5 subjects for student %d:\n", i + 1);
        for (u8 j = 0; j < 5; j++)
        {
            printf("Grade for subject %d: ", j + 1);
            scanf("%f", &(*ptr)[i].grades[j]);
        }

        // Printing student information
        printf("The information of student %d:\n", i + 1);
        printf("Name: %s\n", (*ptr)[i].name);
        printf("ID: %d\n", (*ptr)[i].ID);
        printf("Grades: ");
        for (u8 j = 0; j < 5; j++)
        {
            printf("%.1f ", (*ptr)[i].grades[j]);
        }
        printf("\n");
    }
}


// Function: AVG
// Description: Calculates and displays the average grade for each student.
// Parameters:
//    - ptr: Pointer to the array of students.
// Side Effects:
//    - Prints the average of grades to the standard output.
void AVG(Student *ptr)
{
    if (no_students > 0)
    {
        for (u8 i = 0; i < no_students; i++)
        {
            f32 sum = 0.0;
            for (u8 j = 0; j < 5; j++)
            {
                // Sum of the grades
                sum += ptr[i].grades[j];
            }
            // Calculate the average
            ptr[i].avg = sum / 5.0;
            printf("The average for student %d %s is: %.1f\n", i + 1, ptr[i].name, ptr[i].avg);
        }
    }
    else
    {
        printf("There are no students to display.\n");
    }
}

// Function: passing
// Description: Determines if each student is passing or failing based on average grades.
// Parameters:
//    - ptr: Pointer to the array of students.
// Side Effects:
//    - Updates each student's pass/fail status and prints it.
void passing(Student *ptr)
{
    if (no_students > 0)
    {
        for (u8 i = 0; i < no_students; i++)
        {
            u8 *s; // Declare a pointer to hold the status string

            // Determine the status string based on the average using an if-else condition
            if (ptr[i].avg >= 50.0)
            {
                s = "Pass";
            }
            else
            {
                s = "Fail";
            }

            // Initialize j to start copying from the beginning of the status string
            u8 j = 0;

            // Copy the status string into the student's status array
            while (s[j] != '\0')
            {
                ptr[i].status[j] = s[j];
                j++;
            }
            ptr[i].status[j] = '\0'; // Null-terminate the status string

            // Print the status
            printf("The status of student %d (%s) is: %s\n", i + 1, ptr[i].name, ptr[i].status);
        }
    }
    else
    {
        printf("There are no students to display.\n");
    }
}


// Function: Display
// Description: Displays all students' detailed information.
// Parameters:
//    - ptr: Pointer to the array of students.
// Side Effects:
//    - Prints detailed student information to the standard output.
void Display(Student *ptr)
{
    if (no_students > 0)
    {
        for (u8 i = 0; i < no_students; i++)
        {
            printf("Student %d:\n", i + 1);
            printf("Name: %s\n", ptr[i].name);
            printf("ID: %d\n", ptr[i].ID);
            printf("Grades: ");
            for (u8 j = 0; j < 5; j++)
            {
                printf("%.1f ", ptr[i].grades[j]);
            }
            printf("\nAverage: %.2f\n", ptr[i].avg);
            printf("Status: %s\n", ptr[i].status);
            printf("\n");
        }
    }
    else
    {
        printf("There are no students to display.\n");
    }
}

// Function: Search
// Description: Searches for a student by ID and displays their information if found.
// Parameters:
//    - ptr: Pointer to the array of students.
//    - ID: The ID of the student to search for.
// Side Effects:
//    - Prints the found student's details or a not-found message.
void Search(Student *ptr, u8 ID)
{
    for (u8 i = 0; i < no_students; i++)
    {
        if (ID == ptr[i].ID)
        {
            printf("Student %d:\n", i + 1);
            printf("Name: %s\n", ptr[i].name);
            printf("ID: %d\n", ptr[i].ID);
            printf("Grades: ");
            for (u8 j = 0; j < 5; j++)
            {
                printf("%.1f ", ptr[i].grades[j]);
            }
            printf("\nAverage: %.2f\n", ptr[i].avg);
            printf("Status: %s\n", ptr[i].status);
            printf("\n");
            return; // Exit the function after displaying the found student's details
        }
    }

    // If the loop completes without finding a match
    printf("Student with ID %d not found.\n", ID);
}

// Function: Update
// Description: Updates information for a specific student identified by ID.
// Parameters:
//    - ptr: Pointer to the array of students.
//    - ID: The ID of the student to update.
// Side Effects:
//    - Modifies and potentially overwrites student details. Recalculates average and status.
void Update(Student *ptr, u8 ID)
{
    for (u8 i = 0; i < no_students; i++)
    {
        if (ID == ptr[i].ID)
        {
            printf("Updating information for student ID %d\n", ID);
            printf("Enter new name for student: ");
            scanf("%s", ptr[i].name);
            printf("Enter new ID for student: ");
            scanf("%d", &ptr[i].ID);
            printf("Enter new grades for 5 subjects:\n");
            for (u8 j = 0; j < 5; j++)
            {
                printf("Grade for subject %d: ", j + 1);
                scanf("%f", &ptr[i].grades[j]);
            }

            printf("Student information updated successfully.\n");
            return;
        }
    }

    // If no student with the given ID was found
    printf("Student with ID %d not found.\n", ID);
}

// Function: Delete
// Description: Deletes a student's record from the array based on the provided ID.
// Parameters:
//    - ptr: Double pointer to the array of students to allow modification of the pointer itself.
//    - ID: The ID of the student to delete.
// Side Effects:
//    - Potentially reduces the size of the allocated memory and modifies the array of students.

void Delete(Student **ptr, u8 ID)
{
    u8 found = 0;

    for (u8 i = 0; i < no_students; i++)
    {
        if ((*ptr)[i].ID == ID)
        {
            found = 1;
            // Shift all subsequent students one position back
            for (u8 j = i; j < no_students - 1; j++)
            {
                (*ptr)[j] = (*ptr)[j + 1];
            }
            no_students--; // Reduce the student count
            *ptr = realloc(*ptr, no_students * sizeof(Student)); // Reallocate memory
            if (*ptr == NULL && no_students > 0)
            {
                printf("Memory reallocation failed.\n");
                exit(1);
            }
            printf("Student with ID %d deleted successfully.\n", ID);
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", ID);
    }
}

// Function: Menu
// Description: Provides a menu-driven interface to manage students' records.
// Side Effects:
//    - Continuously displays a menu and responds to user inputs until exit is selected.
void Menu(void)
{
    u8 options = 0;
    u8 ID = 0;
    Student *students = NULL; // Start with a NULL pointer

    for (;;)
    {
        printf("1. Add a Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for a Student by ID\n");
        printf("4. Update a Student's Record\n");
        printf("5. Delete a Student's Record\n");
        printf("6. Exit\n");
        printf("Choose your option, please: ");
        scanf("%d", &options);
        switch (options)
        {
        case 1:
            printf("Enter details of a new student\n");
            inputStudent(&students);
            printf("#########################################\n");
            printf("Calculate the average\n");
            AVG(students);
            printf("#########################################\n");
            printf("Determine the pass/fail status\n");
            passing(students);
            printf("#########################################\n");
            break;
        case 2:
            printf("#########################################\n");
            printf("Display Students\n");
            Display(students);
            printf("#########################################\n");
            break;
        case 3:
            printf("#########################################\n");
            printf("Search Students\n");
            printf("#########################################\n");
            printf("Please enter the ID of the student you want to show: ");
            scanf("%d", &ID);
            Search(students, ID);
            printf("#########################################\n");
            break;
        case 4:
            printf("#########################################\n");
            printf("Update Students\n");
            printf("#########################################\n");
            printf("Please enter the ID of the student you want to update: ");
            scanf("%d", &ID);
            Update(students, ID);
            printf("#########################################\n");
            break;
        case 5:
            printf("#########################################\n");
            printf("Delete Student Record\n");
            printf("#########################################\n");
            printf("Please enter the ID of the student you want to delete: ");
            scanf("%d", &ID);
            Delete(&students, ID);
            printf("#########################################\n");
            break;
        case 6:
            free(students); // Free the allocated memory before exiting
            exit(0);
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}
