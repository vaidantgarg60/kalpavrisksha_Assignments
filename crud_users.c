#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void addUser();
void displayUsers();
void updateUser();
void deleteUser();

int main() {
    int choice;

    while (1) {
        printf("\n--- User Management System ---\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User by ID\n");
        printf("4. Delete User by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addUser() {
    User newUser;
    FILE *file;

    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }

    printf("\nEnter User ID: ");
    scanf("%d", &newUser.id);
    printf("Enter User Name: ");
    scanf("%s", newUser.name);
    printf("Enter User Age: ");
    scanf("%d", &newUser.age);

    fprintf(file, "%d %s %d\n", newUser.id, newUser.name, newUser.age);
    
    fclose(file);
    printf("User added successfully!\n");
}

void displayUsers() {
    User user;
    FILE *file;

    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No users found or file does not exist.\n");
        return;
    }

    printf("\n--- List of All Users ---\n");
    printf("ID\tName\t\tAge\n");
    printf("----------------------------------\n");

    while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        printf("%d\t%s\t\t%d\n", user.id, user.name, user.age);
    }
    
    fclose(file);
}

void updateUser() {
    int targetId, found = 0;
    User user;
    FILE *file, *tempFile;

    printf("\nEnter the ID of the user to update: ");
    scanf("%d", &targetId);

    file = fopen(FILENAME, "r");
    tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error: Could not open files.\n");
        return;
    }

    while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == targetId) {
            found = 1;
            printf("Enter new name for user ID %d: ", targetId);
            scanf("%s", user.name);
            printf("Enter new age for user ID %d: ", targetId);
            scanf("%d", &user.age);
        }
        fprintf(tempFile, "%d %s %d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("User updated successfully!\n");
    } else {
        printf("User with ID %d not found.\n", targetId);
    }
}

void deleteUser() {
    int targetId, found = 0;
    User user;
    FILE *file, *tempFile;

    printf("\nEnter the ID of the user to delete: ");
    scanf("%d", &targetId);

    file = fopen(FILENAME, "r");
    tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error: Could not open files.\n");
        return;
    }

    while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == targetId) {
            found = 1;
        } else {
            fprintf(tempFile, "%d %s %d\n", user.id, user.name, user.age);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("User deleted successfully!\n");
    } else {
        printf("User with ID %d not found.\n", targetId);
    }
}