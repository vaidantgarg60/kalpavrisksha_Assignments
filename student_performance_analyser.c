/**
 * @file student_analyzer.c
 * @brief A program to analyze student performance based on marks in three subjects.
 */

#include <stdio.h>

#define NUM_SUBJECTS 3
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

// A structure to hold all information related to a single student.

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    int marks[NUM_SUBJECTS];
    int totalMarks;
    float averageMarks;
    char grade;
};

// --- Function Prototypes ---

int calculateTotal(int marks[]);
float calculateAverage(int total);
char assignGrade(float average);
void printPerformancePattern(char grade);
void printRollNumbersRecursive(int current, int total);

int main() {

    struct Student students[MAX_STUDENTS];
    int numStudents;

    printf("Enter the number of students (1-100): ");
    scanf("%d", &numStudents);

    // Input validation
    if (numStudents < 1 || numStudents > 100) {
        printf("Invalid number of students. Please run again with a number between 1 and 100.\n");
        return 1;
    }

    printf("Enter student details (RollNo Name Marks1 Marks2 Marks3):\n");
    for (int i = 0; i < numStudents; i++) {
        scanf("%d %s %d %d %d",
              &students[i].rollNumber,
              students[i].name,
              &students[i].marks[0],
              &students[i].marks[1],
              &students[i].marks[2]);
    }

    printf("\n--- Student Performance Analysis ---\n");

    for (int i = 0; i < numStudents; i++) {
       
        students[i].totalMarks = calculateTotal(students[i].marks);
        students[i].averageMarks = calculateAverage(students[i].totalMarks);
        students[i].grade = assignGrade(students[i].averageMarks);

        // Displaying the results for each student
        printf("Roll: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Total: %d\n", students[i].totalMarks);
        printf("Average: %.2f\n", students[i].averageMarks); 
        printf("Grade: %c\n", students[i].grade);


        if (students[i].grade == 'F') {
            printf("\n");
            continue;
        }

        printPerformancePattern(students[i].grade);
        printf("\n\n"); 
    }
    
    printf("------------------------------------\n");
    printf("List of Roll Numbers (via recursion): ");
    printRollNumbersRecursive(1, numStudents);
    printf("\n");

    return 0;
}

/**
 * @brief Calculates the total marks for a student.
 * @param marks An array containing marks for all subjects.
 * @return The sum of all marks.
 */
int calculateTotal(int marks[]) {
    int total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        total += marks[i]; 
    }
    return total;
}

/**
 * @brief Calculates the average marks.
 * @param total The total marks obtained.
 * @return The average marks as a float.
 */
float calculateAverage(int total) {
    return (float)total / NUM_SUBJECTS;
}

/**
 * @brief Assigns a grade based on the average marks.
 * @param average The average marks of the student.
 * @return The character grade ('A', 'B', 'C', 'D', 'F').
 */
char assignGrade(float average) {
    if (average >= 85) {
        return 'A';
    } else if (average >= 70) {
        return 'B';
    } else if (average >= 50) {
        return 'C';
    } else if (average >= 35) {
        return 'D';
    } else {
        return 'F';
    }
}

/**
 * @brief Prints a performance pattern of stars based on the grade.
 * @param grade The grade of the student.
 */
void printPerformancePattern(char grade) {
    int starCount = 0;
    switch (grade) {
        case 'A':
            starCount = 5;
            break;
        case 'B':
            starCount = 4;
            break;
        case 'C':
            starCount = 3;
            break;
        case 'D':
            starCount = 2;
            break;
        default:
            starCount = 0; 
            break;
    }

    printf("Performance: ");
    for (int i = 0; i < starCount; i++) {
        printf("*");
    }
}

/**
 * @brief Prints roll numbers from 1 to N using recursion.
 * @param current The current roll number to print.
 * @param total The total number of students.
 */
void printRollNumbersRecursive(int current, int total) {
   
    if (current > total) {
        return;
    }

    printf("%d ", current);
    printRollNumbersRecursive(current + 1, total); // The recursive call
}
