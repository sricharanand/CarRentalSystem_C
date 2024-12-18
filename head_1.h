#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// File names
#define CAR_FILE_NAME "cars_data.csv"
#define EMPLOYEE_FILE_NAME "employee_data.csv"
#define USER_FILE_NAME "user_data.csv"
#define RENTED_CARS_FILE_NAME "rented_cars.csv"
// Global admin key
extern char adm_key[30];

extern int current_user;
extern int current_employee;

// ---------------------------
// Struct Definitions
// ---------------------------
typedef struct car {
    char car_cpm[30];
    char model[30];
    char car_code[30]; // Unique code for each car
    float mileage;
    int CC;
    char availability[30];
    float price_pd;
    struct car *link;
} Car;

typedef struct User {
    long int id;
    char name[50];
    char email[50];
    char password[20];
    struct User *link;
} User;

typedef struct Employee {
    int id;
    char name[50];
    char position[30];
    char password[20];
    struct Employee *link;
} Employee;

typedef struct rented_car {
    char user_name[50];       // User's name
    char user_contact[15];    // User's contact number
    char user_email[50];      // User's email
    char car_code[20];        // Car code of the rented car
    char rental_date[20];     // Date of rental
    char return_date[20];     // Expected return date
    struct rented_car *link;  // Pointer to the next rented car
} RentedCar;

// Head of the linked list for rented cars
extern RentedCar *head_rented_cars;

// Global head pointers
extern Car *head_car;
extern User *head_user;
extern Employee *head_employee;

// ---------------------------
// Car Management Functions
// ---------------------------

void LL_maker_car(const char *car_cpm, const char *model, const char *car_code, float milage, int CC, const char *availability, float price_pd);
void search_car_by_car_code(const char *car_code);
void delete_car_by_car_code(const char *car_code);
void free_car_list();
int load_cars_from_file(const char *filename);
void save_cars_to_file(const char *filename);
void edit_car_by_car_code(const char *car_code);
void print_cars();
int count_cars();
void sort_cars();
int compare_by_price_asc(const void *a, const void *b);
int compare_by_CC_desc(const void *a, const void *b);
int compare_by_milage_desc(const void *a, const void *b);
void add_car();

// ---------------------------
// User Management Functions
// ---------------------------
void LL_maker_user(long int id, const char name[], const char email[], const char password[]);
int load_users_from_file(const char *filename);
void save_users_to_file(const char *filename);
int check_user_credentials(const char *email, const char *password);
int add_user(long int id, const char *name, const char *email, const char *password);
void free_user_list();
void delete_user_by_id(const char email[]);
void manage_users();
void see_all_users();
void remove_user();
void contact_user();
void car_rented_by_user();

// ---------------------------
// Employee Management Functions
// ---------------------------
void LL_maker_employee(int id, const char name[], const char position[], const char password[]);
int load_employees_from_file(const char *filename);
void save_employees_to_file(const char *filename);
int check_employee_credentials(int id, const char *password);
int add_employee(int id, const char *name, const char *position, const char *password);
void free_employee_list();
void delete_employee_by_id(const int id);

// ---------------------------
// Car List Functions
// ---------------------------
void LL_maker_rented_cars(char user_name[], char user_contact[], char user_email[], char car_code[], char rental_date[], char return_date[]);
void rent_car();
void write_rented_cars_to_csv(const char *filename);
int read_rented_cars_from_csv(const char *filename);
void free_rented_car_list();
void printRentedCars();

// ---------------------------
// General Functions
// ---------------------------
void userLogin();
void employeeLogin();
void MainMenu();
void car_showing();
void car_editor();
void car_showing_employee();
void payment_qr();

#endif
