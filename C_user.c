#include "head_1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function to create a new user node and add it to the linked list
void LL_maker_user(long int id, const char name[], const char email[], const char password[]) {
    User *new_user = (User  *)malloc(sizeof(User));
    if (new_user == NULL) {
        printf("Memory allocation failed for new user.\n");
        return;
    }
    new_user->id = id;
    strcpy(new_user->name, name);
    strcpy(new_user->email, email);
    strcpy(new_user->password, password);
    new_user->link = NULL;

    // Add to the linked list
    if (head_user == NULL) {
        head_user = new_user; // If the list is empty
    }
    else {
        User *current = head_user;
        while (current->link != NULL) {
            current = current->link; // Traverse to the end of the list
        }
        current->link = new_user; // Add the new user at the end
    }
    return;
}

// Function to load users from the CSV file into the linked list
int load_users_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not Read %s.\n", filename);
        return 0;
    }

    char line[256];
    int first_line = 1; // For Header line
    while (fgets(line, sizeof(line), file)) {
        if (first_line) {
            first_line = 0; // Skip header
            continue;
        }

        long int id;
        char name[50], email[50], password[20];


        // Parse the line (a long double, 50 char strings till commas, 19 char string)
        sscanf(line, "%ld,%49[^,],%49[^,],%19s", &id, name, email, password);

        // Add to linked list
        LL_maker_user(id, name, email, password);
    }

    fclose(file);
    return 1;
}

// Function to save users from the linked list to the CSV file
void save_users_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not Write on %s.\n", filename);
        return;
    }

    // Write header
    fprintf(file, "Phone Number,Name,E-Mail,Password\n");

    // Write each user's details
    User *current = head_user;
    while (current != NULL) {
        fprintf(file, "%ld,%s,%s,%s\n",
                current->id, current->name, current->email, current->password);
        current = current->link;
    }

    fclose(file);
    printf("User data saved to %s successfully.\n", filename);
}

// Function to check user credentials during login
int check_user_credentials(const char *email, const char *password) {
    User *current = head_user;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0) {
            return 1; // Credentials are valid
        }
        else if(strcmp(current->email, email) == 0){
            printf("Password Incorrect\n");
            return 0;
        }
        current = current->link;
    }
    printf("E-Mail Not Registered\n");
    return 0;
}

// Function to add a new user to the linked list
int add_user(long int id, const char *name, const char *email, const char *password) {
    // Check if the email is already used
    User *current = head_user;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            printf("E-Mail %s is already Used.\n", email);
            return 0; // Email already used
        }
        current = current->link;
    }

    // If email is not used, add the user
    LL_maker_user(id, name, email, password);
    printf("Successfully Signed Up\n");
    return 1; // User added successfully
}

void free_user_list() {
    User *current = head_user;
    User *next;

    while (current != NULL) {
        next = current->link; // Store the next node
        free(current);        // Free the current node
        current = next;      // Move to the next node
    }
    head_user = NULL; // Set the head to NULL after freeing
}

void delete_user_by_id(const char email[]) {
    User *current = head_user;
    User *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            if (previous == NULL) {
                // The user to delete is the head
                head_user = current->link;
            }
            else {
                // Bypass the current node
                previous->link = current->link;
            }
            free(current);
            printf("User with ID %s Deleted Successfully.\n", email);
            return;
        }
        previous = current;
        current = current->link;
    }
    printf("User with ID %s NOT found for deletion.\n", email);
}

void see_all_users() {
    User *current = head_user;
    while (current != NULL) {
        printf("Phone Number: %ld\n", current->id);
        printf("Name: %s\n", current->name);
        printf("Email: %s\n", current->email);
        printf("--------------------\n");
        current = current->link;
    }
}

void remove_user(const char *email) {
    User *current = head_user;
    User *previous = NULL;
    
    // Traverse the linked list to find the user with the specified email
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) { // Email matches
            if (previous == NULL) {
                // The user to delete is the head of the list
                head_user = current->link; // Update head to the next user
            }
            else {
                // Bypass the current user
                previous->link = current->link;
            }
            free(current); // Free the memory allocated for the user
            printf("User with Email '%s' has been deleted.\n", email);
            return;
        }
        previous = current; // Move to the next user
        current = current->link;
    }
    // If we reach here, the user was not found
    printf("User with Email '%s' not found.\n", email);
}

void car_rented_by_user(const char *email) {
    RentedCar *current_rented_car = head_rented_cars;
    while (current_rented_car != NULL) {
        if (strcmp(current_rented_car->user_email, email) == 0) { // Email matches
            printf("Rented Car Details:\n");
            printf("User Name: %s\n", current_rented_car->user_name);
            printf("User Contact: %s\n", current_rented_car->user_contact);
            printf("User Email: %s\n", current_rented_car->user_email);
            printf("Car Code: %s\n", current_rented_car->car_code);
            printf("Rental Date: %s\n", current_rented_car->rental_date);
            printf("Return Date: %s\n", current_rented_car->return_date);
            printf("============================================\n");

            // Find and print the car details
            Car *current_car = head_car;
            while (current_car != NULL) {
                if (strcmp(current_car->car_code, current_rented_car->car_code) == 0) { // Car code matches
                    printf("Car Details:\n");
                    printf("Car Company: %s\n", current_car->car_cpm);
                    printf("Model: %s\n", current_car->model);
                    printf("Car Code: %s\n", current_car->car_code);
                    printf("Mileage: %.2f\n", current_car->mileage);
                    printf("CC: %d\n", current_car->CC);
                    printf("Availability: %s\n", current_car->availability);
                    printf("Price per Day: %.2f\n", current_car->price_pd);
                    printf("--------------------\n");
                    return; // Exit the function after finding the car details
                }
                current_car = current_car->link;
            }
            printf("Car not found with code '%s'\n", current_rented_car->car_code);
            return; // Exit the function if the car is not found
        }
        current_rented_car = current_rented_car->link;
    }
    printf("User with E-Mail '%s' has NO rented cars.\n", email);
}

void contact_user() {
    char email[50]; // Buffer to hold the user's email

    // Prompt the user to enter their email
    printf("Enter the E-Mail of the user to contact: ");
    scanf("%49s", email); // Read the email input safely

    // Simulate contacting the user
    printf("Attempting to contact user at E-Mail: %s\n", email);
    printf("Contacting...\n");
    // Simulate successful contact
    printf("Successfully contacted User!");
}
