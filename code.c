/* .==========================================================
   STUDENT ATTENDANCE ANALYSER
   B.Tech CSE, Semester I - C Programming Project

   Rule:  75% attendance or more  ->  ELIGIBLE
          below 75% attendance    ->  NOT ELIGIBLE
   ========================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50                /* maximum number of students */

int roll[MAX];                /* roll numbers */
char name[MAX][20];           /* names (up to 19 letters) */
int present[MAX];             /* classes attended by each student */
int n = 0;                    /* number of students added */
int total = 0;                /* number of classes held */


/* ---------- safe input functions ---------- */

/* Reads one full line typed by the user and removes the Enter at the end.
   If there is no more input, the program ends politely. */
void read_line(char *s, int size)
{
    int c;

    if (fgets(s, size, stdin) == NULL) {
        printf("\nNo more input. Program ended.\n");
        exit(0);
    }
    if (strchr(s, '\n') == NULL) {            /* line was too long */
        while ((c = getchar()) != '\n' && c != EOF)
            ;                                 /* throw away the extra part */
    }
    s[strcspn(s, "\r\n")] = '\0';
}

/* Reads a whole number (at most 9 digits).
   Returns -1 if the user typed something that is not a number. */
int read_number(void)
{
    char line[100];
    int x;
    char extra;

    read_line(line, sizeof(line));
    if (strlen(line) > 9)
        return -1;
    if (sscanf(line, "%d %c", &x, &extra) != 1)   /* number only, nothing after it */
        return -1;
    return x;
}


/* ---------- the three features ---------- */

void add_student(void)
{
    int i, r;

    if (n >= MAX) {
        printf("The class is full (maximum %d students).\n", MAX);
        return;
    }

    printf("Enter roll number: ");
    r = read_number();
    if (r <= 0) {
        printf("Invalid roll number. Please type a positive number.\n");
        return;
    }
    for (i = 0; i < n; i++) {
        if (roll[i] == r) {
            printf("This roll number already exists.\n");
            return;
        }
    }

    printf("Enter name: ");
    read_line(name[n], 20);                   /* longer names are cut to 19 letters */
    if (name[n][0] == '\0') {
        printf("Name cannot be empty.\n");
        return;
    }

    roll[n] = r;
    present[n] = 0;
    n++;

    printf("Student added.\n");
    if (total > 0)
        printf("Note: this student is counted absent in the %d earlier class(es).\n", total);
}

void mark_attendance(void)
{
    char line[100], ch;
    int i;

    if (n == 0) {
        printf("Please add students first.\n");
        return;
    }

    printf("Class number %d. Type P for present or A for absent.\n", total + 1);
    for (i = 0; i < n; i++) {
        do {
            printf("%d %s : ", roll[i], name[i]);
            read_line(line, sizeof(line));
            ch = line[0];
            if (ch >= 'a' && ch <= 'z')
                ch = ch - 'a' + 'A';          /* small letter to capital letter */
            if (ch != 'P' && ch != 'A')
                printf("Please type only P or A.\n");
        } while (ch != 'P' && ch != 'A');

        if (ch == 'P')
            present[i]++;
    }
    total++;
    printf("Attendance saved.\n");
}

void show_report(void)
{
    int i, eligible = 0;
    float percent;

    if (n == 0) {
        printf("No students added yet.\n");
        return;
    }
    if (total == 0) {
        printf("No attendance marked yet.\n");
        return;
    }

    printf("\nEligibility rule: 75%% attendance or more\n");
    printf("Classes held: %d\n\n", total);
    printf("%-10s %-20s %-8s %-6s %-8s %s\n",
           "Roll", "Name", "Present", "Total", "Percent", "Status");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        percent = present[i] * 100.0 / total;
        printf("%-10d %-20s %-8d %-6d %5.1f%%   ",
               roll[i], name[i], present[i], total, percent);

        if (percent >= 75) {
            printf("ELIGIBLE\n");
            eligible++;
        } else {
            printf("NOT ELIGIBLE\n");
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("Eligible: %d    Not eligible: %d\n", eligible, n - eligible);
}


/* ---------- main function ---------- */

int main(void)
{
    int choice;

    do {
        printf("\n===== ATTENDANCE ANALYSER =====\n");
        printf("1. Add student\n");
        printf("2. Mark attendance\n");
        printf("3. View report\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        choice = read_number();

        if (choice == 1)
            add_student();
        else if (choice == 2)
            mark_attendance();
        else if (choice == 3)
            show_report();
        else if (choice != 0)
            printf("Wrong choice. Please enter 0, 1, 2 or 3.\n");
    } while (choice != 0);

    printf("Thank you!\n");
    return 0;
}
