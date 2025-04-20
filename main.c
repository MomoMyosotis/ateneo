#include "implements.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// 180 righe

void Print_Menu() {
	printf("\nHere's the menu:\n");

	// Uscita
	printf(" 0. Exit.\n");

	// Gestione studenti
	printf("\n--- Student Management ---\n");
	printf(" 1. Enter a new student.\n");
	printf(" 2. View the list of students.\n");
	printf(" 3. Search for a student.\n");
	printf(" 4. Remove a student.\n");
	printf(" 5. Change a student's data.\n");
	printf(" 6. View the data of a student.\n");

	// Gestione corsi
	printf("\n--- Course Management ---\n");
	printf(" 7. Add a new score.\n");
	printf(" 8. View who got the highest AVG.\n");
	printf(" 9. View the results of a certain course.\n");
	printf(" 10. Create a course.\n");
	printf(" 11. Change course's info.\n");
	printf(" 12. View the list of all courses.\n");
	printf(" 13. View the data of a course.\n");
	printf(" 14. Search for a course.\n");
	printf(" 15. Remove a course.\n");

	// Gestione major
	printf("\n--- Major Management ---\n");
	printf(" 16. Create a major.\n");
	printf(" 17. Change major's info.\n");
	printf(" 18. View the list of all majors.\n");
	printf(" 19. View the data of a major.\n");
	printf(" 20. Search for a major.\n");
	printf(" 21. Remove a major.\n");

	// Placeholder
	printf("\n--- Space Holders ---\n");
	printf(" 22. SPACE HOLDER.\n");
	printf(" 23. SPACE HOLDER.\n");
	printf(" 24. SPACE HOLDER.\n");
}

int main() {
    int choice;
    int counter = 0;

    printf("\nWelcome ROOT, what are you here for?");


    do {
        Print_Menu();
        printf("\nOption: ");
        if (scanf("%i", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the buffer
            continue;
        }

        counter++;

        switch (choice) {
            // Gestione studenti
        case 1:
            printf("\nYou choose to enter a new student.\n");
            REGISTER('s');
            break;
        case 2:
            printf("\nYou choose to view the list of students.\n");
            LIST('s');
            break;
        case 3:
            printf("\nYou choose to search for a student.\n");
            SEARCH('s');
            break;
        case 4:
            printf("\nYou choose to remove a student.\n");
            RM('s');
            break;
        case 5:
            printf("\nYou choose to change a student's data.\n");
            C_DATA('s');
            break;
        case 6:
            printf("\nYou choose to view a student's info.\n");
            SEARCH('s');
            break;

            // Gestione corsi
        case 7:
            printf("\nYou choose to add a new score.\n");
            Score('n');
            break;
        case 8:
            printf("\nYou choose to see the student with the highest AVG score.\n");
            Score('a');
            break;
        case 9:
            printf("\nYou choose to view the results of a certain course.\n");
            Score('c');
            break;
        case 10:
            printf("\nYou choose to create a course.\n");
            REGISTER('c');
            break;
        case 11:
            printf("\nYou choose to change the course's info.\n");
            C_DATA('c');
            break;
        case 12:
            printf("\nYou choose to view the list of all courses.\n");
            LIST('c');
            break;
        case 13:
            printf("\nYou choose to view a course's info.\n");
            SEARCH('c');
            break;
        case 14:
            printf("\nYou choose to search for a course.\n");
            SEARCH('c');
            break;
        case 15:
            printf("\nYou choose to remove a course.\n");
            RM('c');
            break;

            // Gestione major
        case 16:
            printf("\nYou choose to create a major.\n");
            REGISTER('m');
            break;
        case 17:
            printf("\nYou choose to change the major's info.\n");
            C_DATA('m');
            break;
        case 18:
            printf("\nYou choose to view the list of all majors.\n");
            LIST('m');
            break;
        case 19:
            printf("\nYou choose to view a major's info.\n");
            SEARCH('m');
            break;
        case 20:
            printf("\nYou choose to search for a major.\n");
            SEARCH('m');
            break;
        case 21:
            printf("\nYou choose to remove a major.\n");
            RM('m');
            break;

            // Uscita
        case 0:
            printf("\nYou choose to terminate the program.\n");
            return 0;
            break;

        default:
            printf("\nSorry, but %i is an invalid input.\n", choice);
            printf("%i attempts left.\n", 5 - counter);
            if (counter > 4) {
                printf("\nYou just used your last attempt, terminating program.\n");
                system("cls");
                return 0;
            }
            break;
        }
    } while (choice != 0);

    return 0;
}
// last line