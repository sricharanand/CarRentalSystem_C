#include "head_1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function to create a new car node and add it to the linked list
void LL_maker_car(const char *car_cpm, const char *model, const char *car_code, float mileage, int CC, const char *availability, float price_pd) {
    // Allocate memory for a new car node
    Car *new_car = (Car *)malloc(sizeof(Car));
    if (new_car == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Copy the provided data into the new car node
    // strncpy(s1, s2, n) copies n chars from s2 to s1.
    strncpy(new_car->car_cpm, car_cpm, sizeof(new_car->car_cpm) - 1);
    new_car->car_cpm[sizeof(new_car->car_cpm) - 1] = '\0'; // Ensure null-termination

    strncpy(new_car->model, model, sizeof(new_car->model) - 1);
    new_car->model[sizeof(new_car->model) - 1] = '\0'; // Ensure null-termination

    strncpy(new_car->car_code, car_code, sizeof(new_car->car_code) - 1);
    new_car->car_code[sizeof(new_car->car_code) - 1] = '\0'; // Ensure null-termination

    new_car->mileage = mileage;
    new_car->CC = CC;
    strncpy(new_car->availability, availability, sizeof(new_car->availability) - 1);
    new_car->availability[sizeof(new_car->availability) - 1] = '\0'; // Ensure null-termination

    new_car->price_pd = price_pd;
    new_car->link = NULL; // Initialize the link pointer to NULL

    // Add the new car to the linked list
    if (head_car == NULL) {
        head_car = new_car; // If the list is empty, set the new car as the head
    }
    else {
        Car *current = head_car;
        while (current->link != NULL) {
            current = current->link; // Traverse to the end of the list
        }
        current->link = new_car; // Add the new car at the end
    }
}


// Function to add a new car to the linked list
void add_car() {
    char car_cmp[50];
    char model[50];
    char car_code[20];
    float mileage;
    int CC;
    char availability[20];
    float price_pd;

    printf("Enter Car Company: ");
    scanf(" %[^\n]", car_cmp); // Read string with spaces
    printf("Enter Car Model: ");
    scanf(" %[^\n]", model); // Read string with spaces
    printf("Enter Car Code: ");
    scanf("%s", car_code);
    printf("Enter Car Mileage: ");
    scanf("%f", &mileage);
    printf("Enter Engine capacity (CC): ");
    scanf("%d", &CC);
    printf("Enter Availability (Available/Not Available): ");
    scanf("%s", availability);
    printf("Enter Price per Day: ");
    scanf("%f", &price_pd);

    // Add the new car to the linked list
    LL_maker_car(car_cmp, model, car_code, mileage, CC, availability, price_pd);
    printf("Car Added Successfully!\n");
}

int load_cars_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s for reading.\n", filename);
        return 0;
    }

    char line[256];
    int first_line = 1; // To skip the header line
    while (fgets(line, sizeof(line), file)) {
        if (first_line) {
            first_line = 0; // Skip header
            continue;
        }

        char car_cpm[30], model[30], car_code[30], availability[30];
        float mileage, price_pd;
        int CC;

        // Parse the line
        if (sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%f",
                   car_cpm, model, car_code, &mileage, &CC, availability, &price_pd) == 7) {
            // Add to linked list
            LL_maker_car(car_cpm, model, car_code, mileage, CC, availability, price_pd);
        }
        else {
            printf("Error Parsing Line: %s", line);
        }
    }

    fclose(file);
    return 1;
}

// Function to write car data from the linked list to a CSV file
void save_cars_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not write to file %s.\n", filename);
        return;
    }

    // Write header
    fprintf(file, "Car Company,Model,Car Code,Mileage,CC,Availability,Price Per Day\n");

    // Write each car's details
    Car *current = head_car; // Use the correct type for the pointer
    if (current == NULL) {
        printf("No Cars to Save!\n");
    }
    else {
        while (current != NULL) {
            fprintf(file, "%s,%s,%s,%.2f,%d,%s,%.2f\n",
                    current->car_cpm, current->model, current->car_code,
                    current->mileage, current->CC, current->availability, current->price_pd);
            current = current->link;
        }
    }

    fclose(file);
    printf("Car data Saved to %s Successfully.\n", filename);
}

// Function to search for a car by car_code
void search_car_by_car_code(const char *car_code) {
    if (car_code == NULL) {
        printf("Car code cannot be NULL.\n");
        return;
    }

    Car *current = head_car;
    while (current) {
        if (strcmp(current->car_code, car_code) == 0) {
            // Print car details if found
            printf("Car Found!\n");
            printf("Car Company: %s\n", current->car_cpm);
            printf("Model: %s\n", current->model);
            printf("Car Code: %s\n", current->car_code);
            printf("Mileage: %.2f\n", current->mileage);
            printf("CC: %d\n", current->CC);
            printf("Availability: %s\n", current->availability);
            printf("Price Per Day: %.2f\n", current->price_pd);
            return;
        }
        current = current->link;
    }

    printf("Car with Code %s Not Found.\n", car_code);
}

// Function to delete a car by car_code
void delete_car_by_car_code(const char *car_code) {
    if (car_code == NULL) {
        printf("Car code cannot be Empty!\n");
        return;
    }

    Car *current = head_car;
    Car *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->car_code, car_code) == 0) {
            if (previous == NULL) {
                // The car to delete is the head
                head_car = current->link;
            }
            else {
                // Bypass the current node
                previous->link = current->link;
            }
            free(current); // Free the memory for the deleted car
            printf("Car with code %s deleted successfully.\n", car_code);
            return;
        }
        previous = current;
        current = current->link;
    }
    printf("Car with code %s not found for Deletion.\n", car_code);
}

// Function to free the entire linked list of cars
void free_car_list() {
    if (head_car == NULL) {
        printf("The car list is already Empty!\n");
        return;
    }

    Car *current = head_car;
    Car *next;

    while (current != NULL) {
        next = current->link; // Store the next node
        free(current);        // Free the current node
        current = next;      // Move to the next node
    }

    head_car = NULL; // Set the head to NULL after freeing
}

// Function to edit car data by its car_code
void edit_car_by_car_code(const char *car_code) {
    Car *current = head_car;

    while (current != NULL) {
        if (strcmp(current->car_code, car_code) == 0) {
            printf("Editing car with car_code: %s\n", car_code);
            printf("Current details:\n");
            printf("Car Company: %s, Model: %s, Mileage: %.2f, CC: %d, Availability: %s, Price: %.2f\n",
                   current->car_cpm, current->model, current->mileage, current->CC, current->availability, current->price_pd);

            // Prompt for new values
            printf("Enter new Car Company (or press Enter to keep current): ");
            char new_car_cpm[30];
            getchar();
            fgets(new_car_cpm, sizeof(new_car_cpm), stdin);
            if (new_car_cpm[0] != '\n') {
                new_car_cpm[strcspn(new_car_cpm, "\n")] = 0; // Remove newline character
                strncpy(current->car_cpm, new_car_cpm, sizeof(current->car_cpm) - 1);
                current->car_cpm[sizeof(current->car_cpm) - 1] = '\0'; // Ensure null termination
            }

            printf("Enter new Model (or press Enter to keep current): ");
            char new_model[30];
            fgets(new_model, sizeof(new_model), stdin);
            if (new_model[0] != '\n') {
                new_model[strcspn(new_model, "\n")] = 0; // Remove newline character
                strncpy(current->model, new_model, sizeof(current->model) - 1);
                current->model[sizeof(current->model) - 1] = '\0'; // Ensure null termination
            }

            printf("Enter new Mileage (or press Enter to keep current): ");
            char new_mileage[10];
            fgets(new_mileage, sizeof(new_mileage), stdin);
            if (new_mileage[0] != '\n') {
                current->mileage = atof(new_mileage);
            }

            printf("Enter new CC (or press Enter to keep current): ");
            char new_CC[10];
            fgets(new_CC, sizeof(new_CC), stdin);
            if (new_CC[0] != '\n') {
                current->CC = atoi(new_CC);
            }

            printf("Enter new Availability (or press Enter to keep current): ");
            char new_availability[30];
            fgets(new_availability, sizeof(new_availability), stdin);
            if (new_availability[0] != '\n') {
                new_availability[strcspn(new_availability, "\n")] = 0; // Remove newline character
                strncpy(current->availability, new_availability, sizeof(current->availability) - 1);
                current->availability[sizeof(current->availability) - 1] = '\0'; // Ensure null termination
            }

            printf("Enter new Price per day (or press Enter to keep current): ");
            char new_price_pd[10];
            fgets(new_price_pd, sizeof(new_price_pd), stdin);
            if (new_price_pd[0] != '\n') {
                current->price_pd = atof(new_price_pd);
            }

            printf("Car details updated successfully.\n");
            return;
        }
        current = current->link;
    }
    printf("Car with Car Code %s Not Found.\n", car_code);
}

void print_cars() {
    struct car *current = head_car;

    if (current == NULL) {
        printf("No cars available in the list.\n");
        return;
    }

    printf("Car Details:\n");
    printf("--------------------------------------------------\n");
    printf("%-30s %-30s %-30s %-10s %-10s %-30s %-10s\n",
           "Car Company", "Model", "Car Code", "Mileage", "CC", "Availability", "Price per Day");
    printf("--------------------------------------------------\n");

    while (current != NULL) {
        printf("%-30s %-30s %-30s %-10.2f %-10d %-30s %-10.2f\n",
               current->car_cpm, current->model, current->car_code,
               current->mileage, current->CC, current->availability,
               current->price_pd);
        current = current->link;
    }

    printf("--------------------------------------------------\n");
}


// Function to count the number of cars in the linked list
int count_cars() {
    int count = 0;
    struct car *current = head_car;
    while (current != NULL) {
        count++;
        current = current->link;
    }
    return count;
}

// Function to sort cars based on certain criteria
// Comparison functions
int compare_by_mileage_desc(const void *a, const void *b) {
    float mileage_a = ((Car *)a)->mileage;
    float mileage_b = ((Car *)b)->mileage;
    return (mileage_a < mileage_b) - (mileage_a > mileage_b); // Descending order
}

int compare_by_CC_desc(const void *a, const void *b) {
    int CC_a = ((Car *)a)->CC;
    int CC_b = ((Car *)b)->CC;
    return (CC_a < CC_b) - (CC_a > CC_b); // Descending order
}

int compare_by_price_asc(const void *a, const void *b) {
    float price_a = ((Car *)a)->price_pd;
    float price_b = ((Car *)b)->price_pd;
    return (price_a > price_b) - (price_a < price_b); // Ascending order
}

// Function to sort cars based on user input
void sort_cars() {
    int num_cars = count_cars();
    if (num_cars == 0) {
        printf("No Cars Available to Sort.\n");
        return;
    }

    // Create an array of cars
    Car *car_array = malloc(num_cars * sizeof(Car));
    if (car_array == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Copy data from linked list to array
    Car *current = head_car;
    for (int i = 0; i < num_cars; i++) {
        car_array[i] = *current; // Copy the car data
        current = current->link;
    }

    // Ask user for sort criteria
    int sort_choice;
    printf("1. Sort by Mileage\n");
    printf("2. Sort by CC\n");
    printf("3. Sort by Price\n");
    printf("Enter your Choice (1-3): ");
    scanf("%d", &sort_choice);
    while (getchar() != '\n'); // Clear the input buffer

    // Sort the array based on the chosen criteria
    if (sort_choice == 1) {
        // Sort by mileage in descending order (qsort sorts an array)
        qsort(car_array, num_cars, sizeof(Car), compare_by_mileage_desc);
    }
    else if (sort_choice == 2) {
        // Sort by CC in descending order
        qsort(car_array, num_cars, sizeof(Car), compare_by_CC_desc);
    } else if (sort_choice == 3) {
        // Sort by price in ascending order
        qsort(car_array, num_cars, sizeof(Car), compare_by_price_asc);
    } else {
        printf("Invalid Choice. Enter 1/2/3.\n");
        free(car_array);
        return;
    }

    // Print the sorted cars
    printf("Sorted Car Details:\n");
    printf("--------------------------------------------------\n");
    printf("%-30s %-30s %-30s %-10s %-10s %-30s %-10s\n",
           "Car Company", "Model", "Car Code", "Mileage", "CC", "Availability", "Price per Day");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < num_cars; i++) {
        printf("%-30s %-30s %-30s %-10.2f %-10d %-30s %-10.2f\n",
               car_array[i].car_cpm, car_array[i].model, car_array[i].car_code,
               car_array[i].mileage, car_array[i].CC, car_array[i].availability,
               car_array[i].price_pd);
    }

    printf("--------------------------------------------------\n");

    // Free the allocated memory
    free(car_array);
}
