#include "head_1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function to create a new employee node and add it to the linked list
void LL_maker_employee(int id, const char name[], const char position[], const char password[]) {
    Employee *new_employee = (Employee *)malloc(sizeof(Employee));
    if (new_employee == NULL) {
        printf("Memory allocation failed for new employee.\n");
        return;
    }
    new_employee->id = id;
    strcpy(new_employee->name, name);
    strcpy(new_employee->position, position);
    strcpy(new_employee->password, password);
    new_employee->link = NULL;

    // Add to the linked list
    if (head_employee == NULL) {
        head_employee = new_employee; // If the list is empty
    }
    else {
        Employee *current = head_employee;
        while (current->link != NULL) {
            current = current->link; // Traverse to the end of the list
        }
        current->link = new_employee; // Add the new employee at the end
    }
}

// Function to load employee data from a CSV file into the linked list
int load_employees_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not read file %s.\n", filename);
        return 0;
    }

    char line[256];
    int first_line = 1; // To skip the header line
    while (fgets(line, sizeof(line), file)) {
        if (first_line) {
            first_line = 0; // Skip header
            continue;
        }

        int id;
        char name[50], position[30], password[20];

        // Parse the line
        sscanf(line, "%d,%49[^,],%29[^,],%19s", &id, name, position, password);

        // Add to linked list
        LL_maker_employee(id, name, position, password);
    }

    fclose(file);
    return 1;
}

// Function to save employee data from the linked list to a CSV file
void save_employees_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not write on file %s.\n", filename);
        return;
    }

    // Write header
    fprintf(file, "ID,Name,Position,Password\n");

    // Write each employee's details
    Employee *current = head_employee;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s\n",
                current->id, current->name, current->position, current->password);
        current = current->link;
    }

    fclose(file);
    printf("Employee data saved to %s successfully.\n", filename);
}

// Function to check employee credentials
int check_employee_credentials(int id, const char *password) {
    Employee *current = head_employee;
    while (current != NULL) {
        if (current->id == id && strcmp(current->password, password) == 0) {
            return 1; // Credentials are valid
        }
        else if (current->id == id){
            printf("Wrong Password!\n");
            return 0;
        }
        current = current->link;
    }
    printf("Wrong ID\n");
    return 0; // Credentials are invalid
}

// Function to add an employee if the ID is not already used
int add_employee(int id, const char *name, const char *position, const char *password) {
    // Check if the ID is already used
    Employee *current = head_employee;
    while (current != NULL) {
        if (current->id == id) {
            printf("Employee ID %d is already in use.\n", id);
            return 0; // ID already used
        }
        current = current->link;
    }

    // If ID is not used, add the employee
    LL_maker_employee(id, name, position, password);
    printf("Succesfully Registered Employee\n");
    return 1; // Employee added successfully
}

void free_employee_list() {
    Employee *current = head_employee;
    Employee *next;

    while (current != NULL) {
        next = current->link; // Store the next node
        free(current);        // Free the current node
        current = next;      // Move to the next node
    }

    head_employee = NULL; // Set the head to NULL after freeing
}

// Function to delete an employee
void delete_employee_by_id(const int id) {
    Employee *current = head_employee;
    Employee *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                // The employee to delete is the head
                head_employee = current->link;
            }
            else {
                // Bypass the current node
                previous->link = current->link;
            }
            free(current); // Free the memory for the deleted car
            printf("Employee with ID %d deleted Successfully.\n", id);
            return;
        }
        previous = current;
        current = current->link;
    }
    printf("Employee with ID %d not found for deletion.\n", id);
}
