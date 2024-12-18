#include "head_1.h"

char adm_key[30] = "ADMIN"; // Define the admin key
int current_user = 0; // Define current_user
int current_employee = 0; // Define current_employee
RentedCar *head_rented_cars = NULL; // Define head_rented_cars
Car *head_car=NULL;
User *head_user=NULL;
Employee *head_employee=NULL;

// Entry point of the program
int main(){
    // Load data from CSV files into linked lists
    if (!load_cars_from_file(CAR_FILE_NAME)) {
        printf("Failed to load cars from file.\n");
        return 1; // Exit the program with an error code
    }
    if (!load_users_from_file(USER_FILE_NAME)) {
        printf("Failed to load users from file.\n");
        return 1; // Exit the program with an error code
    }
    if (!load_employees_from_file(EMPLOYEE_FILE_NAME)) {
        printf("Failed to load employees from file.\n");
        return 1; // Exit the program with an error code
    }
    if (!read_rented_cars_from_csv(RENTED_CARS_FILE_NAME)) {
        printf("Failed to load rented cars from file.\n");
        return 1; // Exit the program with an error code
    }


    printf("WELCOME TO THE CAR RENTAL SYSTEM!\n");

    // Display the main menu
    printf("Entering Main Menu...\n");
    MainMenu();

    // Save data back to CSV files before exiting
    save_cars_to_file(CAR_FILE_NAME);
    save_users_to_file(USER_FILE_NAME);
    save_employees_to_file(EMPLOYEE_FILE_NAME);
    write_rented_cars_to_csv(RENTED_CARS_FILE_NAME);

    // Free all linked list memory
    free_car_list();
    free_user_list();
    free_employee_list();
    free_rented_car_list();

    printf("\n");
    printf("THANK YOU FOR USING THE CAR RENTAL SYSTEM! GOODBYE!\n");
    return 0;
}
// Main menu implementation
void MainMenu(){
     
    while (1) {
         
        int choice;
        printf("=======================");
        printf("\nMain Menu:\n");
        printf("1. User Login\n");
        printf("2. Employee Login\n");
        printf("3. Exit\n");
        printf("=======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                userLogin();
                break;
            case 2:
                employeeLogin();
                break;
            case 3:
                return;  // Exit the menu loop
            default:
                printf("Invalid Choice. Enter 1/2/3.\n");
        }
    }
}


void userLogin(){
     
    while(1){
        if(current_user!=0){
            printf("\n=====================================\n");
            printf("\n==============USER PAGE===============\n");
            printf("1. See/Rent Cars\n");
            printf("2. Log Out and Back to Main Menu\n");
            printf("3. Log In to a Different Account\n");
            printf("=====================================\n");
            int choice_2;
            printf("Enter choice: ");
            scanf("%d", &choice_2);

            switch (choice_2){
            case 1:
                car_showing();
                break;
            case 2:
                current_user=0;
                return;
            case 3:
                current_user=0;
                break;
            default:
                printf("Enter a Number from 1 to 3\n");
            }
        }
        else{
            printf("\n=====================================");
            printf("\n------------ USER LOGIN ------------\n");
            printf("1. Log In\n");
            printf("2. Sign Up\n");
            printf("3. Back to Main Menu\n");
            printf("=====================================\n");
            int choice;
            printf("Enter choice (1/2/3): ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter E-Mail Address: ");
                    char emai[30];
                    scanf("%s",emai);

                    printf("Enter Password: ");
                    char passw[30];
                    scanf("%s",passw);

                    int x = check_user_credentials(emai, passw);
                    if(x==1){
                        current_user=1;
                        printf("Successfully Logged In!\n");
                        break;
                    }
                    break;
                case 2:
                    printf("Enter Mobile Number: ");
                    long int r_mob;
                    scanf("%ld",&r_mob);

                    printf("Enter Username (max 30 characters): ");
                    char r_username[30];
                    scanf("%s",r_username);

                    printf("Enter E-Mail Address: ");
                    char r_emai[30];
                    scanf("%s",r_emai);

                    printf("Enter Password (max 30 characters): ");
                    char r_passw[30];
                    scanf("%s",r_passw);

                    printf("RE-ENTER Password: ");
                    char re_passw[30];
                    scanf("%s",re_passw);
                    int r_x=0;
                    if(strcmp(re_passw,r_passw) == 0){
                        r_x = add_user(r_mob , r_username , r_emai , r_passw);
                    }
                    else{
                        printf("User not added. Try Again!\n");
                    }
                    break;
                case 3:
                    return;
                default:
                    printf("Invalid Choice. Enter 1/2/3.\n");                      
            }
        }
    }
}

void employeeLogin(){
     
    while(1){
        if(current_employee!=0){
            printf("\n=====================================\n");
            printf("\n============EMPLOYEE PAGE===========\n");
            printf("1. Edit Cars\n");
            printf("2. Manage Users\n");
            printf("3. Log In to Another Employee\n");
            printf("4. See Cars\n");
            printf("5. Log Out\n");
            printf("=====================================\n");
            int choice_2;
            printf("Enter choice: ");
            scanf("%d", &choice_2);

            switch (choice_2){
            case 1:
                car_editor();
                break;
            case 2:
                manage_users();
                break;
            case 3:
                current_employee=0;
                break;
            case 4:
                print_cars();
                break;
            case 5:
                current_employee=0;
                return;
            default:
                printf("Enter a Number from 1 to 5.");
            }
        }
        else{
            printf("\n=====================================");
            printf("\n----------- EMPLOYEE LOGIN -----------\n");
            printf("1. Log In Employee\n");
            printf("2. Register New Employee\n");
            printf("3. Back to Main Menu\n");
            printf("=====================================\n");
            int choice;
            printf("Enter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter Employee ID: ");
                    int emp_id;
                    scanf("%d",&emp_id);

                    printf("Enter Password: ");
                    char emp_passw[30];
                    scanf("%s",emp_passw);

                    int x = check_employee_credentials(emp_id, emp_passw);
                    if(x==1){
                        //strcpy(current_employee,emp_id);
                        current_employee=1;
                        printf("Employee Logged In!\n");
                    }
                    break;
                case 2:
                    printf("ENTER ADMIN KEY: ");
                    char adk[30];
                    scanf("%s",adk);
                    if(strcmp(adk,adm_key)==0){
                        printf("Enter Employee ID: ");
                        int emp_id_2;
                        scanf("%d",&emp_id_2);

                        printf("Enter Name: ");
                        char name_2[30];
                        scanf("%s",name_2);

                        printf("Enter Position: ");
                        char position[30];
                        scanf("%s",position);

                        printf("Enter Password (max 30 characters): ");
                        char emp_passw_2[30];
                        scanf("%s",emp_passw_2);

                        int x_2=0;

                        printf("RE-ENTER Password: ");
                        char re_passw_2[30];
                        scanf("%s",re_passw_2);
                        if(strcmp(emp_passw_2,re_passw_2)==0    ){
                            x_2 = add_employee(emp_id_2,name_2,position,emp_passw_2);
                            printf("Employee Added Successfully!\n");
                            save_employees_to_file(EMPLOYEE_FILE_NAME);
                            break;
                        }
                        else{
                            printf("Employee Not added. Try Again!\n");
                            break;
                        }
                    }
                    else{
                        printf("WRONG KEY ENTERED! Try Again!\n");
                    }
                    break;
                case 3:
                    return;
                default:
                    printf("Invalid choice. Enter 1/2/3.\n");
            }
        }
    }
}

void car_showing(){
     
    while(1){
        printf("\n=====================================");
        printf("\n--------------- CARS ----------------\n");
        printf("1. See All Cars\n");
        printf("2. Sort Cars\n");
        printf("3. Rent a Car\n");
        printf("4. Back to User Page\n");
        printf("=====================================\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_cars();
                break;
            case 2:
                sort_cars();
                break;
            case 3:
                char car_code[10];
                printf("CODE of car to rent: ");
                scanf("%s", car_code); 
                rent_car(car_code);
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Enter 1/2/3/4.\n");

        }
    }
}

void car_showing_employee(){  
     
    while(1){
        printf("\n=====================================");
        printf("\n--------------- CARS ----------------\n");
        printf("1. See All Cars\n");
        printf("2. Sort Cars\n");
        printf("3. Edit Cars\n");
        printf("4. Back to Log in Page\n");
        printf("=====================================\n");
        int choice;
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_cars();
                break;
            case 2:
                sort_cars();
                break;
            case 3:
                car_editor();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Enter 1/2/3/4.\n");
        }
    }
}

void car_editor(){     
    while(1){        
        printf("\n=====================================");
        printf("\n------------ CAR EDITOR -------------\n");
        printf("1. Edit Car Details\n");
        printf("2. Delete Car\n");
        printf("3. Add Car\n");
        printf("4. Back to Employee Page\n");
        printf("=====================================\n");
        int choice;
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                char car_code_1[30];
                printf("Enter Car Code: ");
                scanf("%s",car_code_1);
                edit_car_by_car_code(car_code_1);
                break;
            case 2:
                char car_code_2[30];
                printf("Enter Car Code: ");
                scanf("%s",car_code_2);
                delete_car_by_car_code(car_code_2);
                break;
            case 3:
                add_car();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Enter 1/2/3/4.\n"); 
        }
    }
}

void manage_users(){
     
    while(1){
            printf("\n=====================================");
            printf("\n----------- USER MANAGER ------------\n");
            printf("1. See all Users\n");
            printf("2. Remove User from Database\n");
            printf("3. See all Rented Cars\n");
            printf("4. Contact User\n");
            printf("5. Back to Employee Page\n");
            printf("=====================================\n");
            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);         

            switch (choice) {
                case 1:
                    see_all_users();
                    break;
                case 2:
                    char email[40];
                    printf("Enter the User Email to Delete: ");
                    scanf("%s",email);
                    remove_user(email);
                    break;
                case 3:
                    printRentedCars();
                    break;
                case 4:
                    contact_user();
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid Choice. Enter a number from 1 to 5.\n");
        }
    }
}