#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "users.txt"
#define TEMP_FILENAME "temp.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void clear_input_buffer();
bool id_exists(int id);
void addUser();
void displayUsers();
void updateUser();
void deleteUser();

int main() {
    int choice;

    while (true) {
        printf("\n--- User Management System ---\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User by ID\n");
        printf("4. Delete User by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: addUser(); break;
            case 2: displayUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: printf("Exiting program. Goodbye!\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool id_exists(int id) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        return false;
    }
    User user;
    while (fscanf(file, "%d\n", &user.id) == 1) {
        fgets(user.name, sizeof(user.name), file);
        fscanf(file, "%d\n", &user.age);
        if (user.id == id) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void addUser() {
    User newUser;
    FILE *file;

    printf("\nEnter User ID: ");
    scanf("%d", &newUser.id);
    clear_input_buffer();

    while (id_exists(newUser.id)) {
        printf("Error: User ID %d already exists. Please enter a different ID: ", newUser.id);
        scanf("%d", &newUser.id);
        clear_input_buffer();
    }

    printf("Enter User Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;

    printf("Enter User Age: ");
    scanf("%d", &newUser.age);
    clear_input_buffer();
    
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }

    fprintf(file, "%d\n%s\n%d\n", newUser.id, newUser.name, newUser.age);
    fclose(file);
    printf("User added successfully!\n");
}

void displayUsers() {
    User user;
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("No users found or file does not exist.\n");
        return;
    }

    printf("\n--- List of All Users ---\n");
    printf("%-5s %-20s %s\n", "ID", "Name", "Age");
    printf("----------------------------------\n");

    while (fscanf(file, "%d\n", &user.id) == 1) {
        fgets(user.name, sizeof(user.name), file);
        user.name[strcspn(user.name, "\n")] = 0;
        fscanf(file, "%d\n", &user.age);
        printf("%-5d %-20s %d\n", user.id, user.name, user.age);
    }
    
    fclose(file);
}

void updateUser() {
    int targetId;
    bool found = false;
    User user;

    printf("\nEnter the ID of the user to update: ");
    scanf("%d", &targetId);
    clear_input_buffer();

    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen(TEMP_FILENAME, "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error: Could not open files.\n");
        if(file) fclose(file);
        if(tempFile) fclose(tempFile);
        return;
    }

    while (fscanf(file, "%d\n", &user.id) == 1) {
        fgets(user.name, sizeof(user.name), file);
        user.name[strcspn(user.name, "\n")] = 0;
        fscanf(file, "%d\n", &user.age);

        if (user.id == targetId) {
            found = true;
            printf("Enter new name for user ID %d: ", targetId);
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = 0;

            printf("Enter new age for user ID %d: ", targetId);
            scanf("%d", &user.age);
            clear_input_buffer();
        }
        fprintf(tempFile, "%d\n%s\n%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);

    if (found) {
        printf("User updated successfully!\n");
    } else {
        printf("User with ID %d not found.\n", targetId);
    }
}

void deleteUser() {
    int targetId;
    bool found = false;
    User user;

    printf("\nEnter the ID of the user to delete: ");
    scanf("%d", &targetId);
    clear_input_buffer();

    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen(TEMP_FILENAME, "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error: Could not open files.\n");
        if(file) fclose(file);
        if(tempFile) fclose(tempFile);
        return;
    }

    while (fscanf(file, "%d\n", &user.id) == 1) {
        fgets(user.name, sizeof(user.name), file);
        user.name[strcspn(user.name, "\n")] = 0;
        fscanf(file, "%d\n", &user.age);
        
        if (user.id == targetId) {
            found = true;
        } else {
            fprintf(tempFile, "%d\n%s\n%d\n", user.id, user.name, user.age);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);

    if (found) {
        printf("User deleted successfully!\n");
    } else {
        printf("User with ID %d not found.\n", targetId);
    }
}
