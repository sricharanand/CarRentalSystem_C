#include "head_1.h"

void LL_maker_rented_cars(char user_name[], char user_contact[], char user_email[], char car_code[], char rental_date[], char return_date[]) {
    RentedCar *new_rental = (RentedCar *)malloc(sizeof(RentedCar));
    if (new_rental == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Copy data into the new node
    strcpy(new_rental->user_name, user_name);
    strcpy(new_rental->user_contact, user_contact);
    strcpy(new_rental->user_email, user_email);
    strcpy(new_rental->car_code, car_code);
    strcpy(new_rental->rental_date, rental_date);
    strcpy(new_rental->return_date, return_date);
    new_rental->link = head_rented_cars; // Insert at the beginning
    head_rented_cars = new_rental; // Update head to point to the new node
}

void rent_car(const char car_code[]) {
    if (car_code == NULL) {
        printf("Car Code cannot be empty!\n");
        return;
    }
    Car *current = head_car;
    while (current) {
        if (strcmp(current->car_code, car_code) == 0) {
            if (strcmp(current->availability, "Available") == 0) {
                char car_c[30];
                strcpy(car_c,car_code);
                char user_name[50];
                char user_contact[15];
                char user_email[50];
                char rental_date[20];
                char return_date[20];

                printf("Enter User Name: ");
                getchar();
                fgets(user_name, sizeof(user_name), stdin);
                user_name[strcspn(user_name, "\n")] = '\0'; // Remove newline character

                printf("Enter User Contact: ");
                fgets(user_contact, sizeof(user_contact), stdin);
                user_contact[strcspn(user_contact, "\n")] = '\0'; // Remove newline character

                printf("Enter User Email: ");
                fgets(user_email, sizeof(user_email), stdin);
                user_email[strcspn(user_email, "\n")] = '\0'; // Remove newline character

                printf("Enter Rental Date (YYYY-MM-DD): ");
                fgets(rental_date, sizeof(rental_date), stdin);
                rental_date[strcspn(rental_date, "\n")] = '\0'; // Remove newline character

                printf("Enter Return Date (YYYY-MM-DD): ");
                fgets(return_date, sizeof(return_date), stdin);
                return_date[strcspn(return_date, "\n")] = '\0'; // Remove newline character

                payment_qr();
                // Add the rental information to the linked list
                LL_maker_rented_cars(user_name, user_contact, user_email, car_c, rental_date, return_date);
                strcpy(current->availability,"Not_Available");
                printf("Car Rented Successfully!\n");
                save_cars_to_file(RENTED_CARS_FILE_NAME);
                return;
            }
            else{
                printf("Car is currently NOT Available!\n");
                break;
            }
        }
        current = current->link;
    }
    printf("Car with Code %s NOT found.\n", car_code);
}

void write_rented_cars_to_csv(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could NOT write on the file.\n");
        return;
    }

    // Write header
    fprintf(file, "User Name,User Phone Number,User Email,Car Code,Rental Date,Return Date\n");

    RentedCar *current = head_rented_cars;
    while (current != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n",
                current->user_name,
                current->user_contact,
                current->user_email,
                current->car_code,
                current->rental_date,
                current->return_date);
        current = current->link;
    }

    fclose(file);
    printf("Rented Cars Data Written to %s Successfully!\n", filename);
    return;
}

int read_rented_cars_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not read Rented Cars\n");
        return 0;
    }

    char line[256]; // Buffer to hold each line from the file

    int first_line = 1; // For Header line

    while (fgets(line, sizeof(line), file)) {
        if (first_line) {
            first_line = 0; // Skip header
            continue;
        }
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = 0;

        // Split the line into tokens (comma separated). 
        char user_name[50], user_contact[15], user_email[50], car_code[20], rental_date[20], return_date[20];
        sscanf(line, "%49[^,],%14[^,],%49[^,],%19[^,],%19[^,],%19[^,]",
               user_name, user_contact, user_email, car_code, rental_date, return_date);

        // Add the rented car details to the linked list
        LL_maker_rented_cars(user_name, user_contact, user_email, car_code, rental_date, return_date);
    }

    fclose(file);
    printf("Rented Cars Data Loaded Successfully!\n");
    return 1;
}

void payment_qr(){
    srand(time(0)); // Seed the random number generator for randomness
    for(int i=1;i<=24;i++){
        for(int j=1;j<=24;j++){
            if(i==1 || i==24 || j==1 || j==24){
                printf("@@");
            }
            else if((i>=17 && i <=22 && j>=17 && j<=22)){
                if((rand() % 2) == 0){
                    printf("  ");
                }
                else{
                    printf("@@");
                }
            }
            else if(((i==3 || i==8 || i==17 || i==22) && j>=3 && j<=8) || ((i==3 || i==8 || i==17 || i==22) && j<=22 && j>=17)){
                printf("@@");
            }
            else if(((j==3 || j==8 || j==17 || j==22) && i>=3 && i<=8) || ((j==3 || j==8 || j==17 || j==22) && i<=22 && i>=17)){
                printf("@@");
            }
            else if((i==5 || i==6 || i==19 || i==20) && (j==5 || j==6 || j==19 || j==20)){
                printf("@@");
            }
            else {
                if ((rand() % 2) == 0 && (((i>9 && i<16) || (j > 9 && j < 16)) && i>=3 && j>=3 && i<=22 && j<=22)) {
                    printf("@@");
                } 
                else {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    char a;
    printf("Click Enter\n");
    scanf("%c",&a);
}

void free_rented_car_list() {
    if (head_rented_cars == NULL) {
        // printf("The Car List is already empty.\n");
        return;
    }

    RentedCar *current = head_rented_cars;
    RentedCar *next;

    while (current != NULL) {
        next = current->link; // Store the next node
        free(current);        // Free the current node
        current = next;      // Move to the next node
    }

    head_rented_cars = NULL; // Set the head to NULL after freeing
    // printf("All rented cars have been successfully freed from the list.\n");
}

void printRentedCars() {
    RentedCar *current = head_rented_cars; // Start from the head of the list
    if (current == NULL) {
        printf("No Cars have been rented yet.\n");
        return;
    }
    printf("\nRented Cars:\n");
    while (current != NULL) {
        printf("User Name: %s\n", current->user_name);
        printf("User Contact: %s\n", current->user_contact);
        printf("User Email: %s\n", current->user_email);
        printf("Car Code: %s\n", current->car_code);
        printf("Rental Date: %s\n", current->rental_date);
        printf("Return Date: %s\n", current->return_date);
        printf("-----------------------------\n");
        current = current->link; // Move to the next rented car
    }
}