### CAR RENTAL SYSTEM
This Car Rental System is a comprehensive command-line-based application designed to manage a car rental company's operations. 
The system allows customers to rent cars, employees to manage the car database, and provides administrative controls for managing users, employees, and rented cars. 
The project uses CSV files for data storage, ensuring persistence, and linked lists for dynamic data manipulation during runtime.

### Project Structure
The project is divided into five separate C files for modularity and better organization:

1. **`cars.c`**  
   - Contains all functions related to car management, including adding, deleting, editing, and searching cars.  
   - Implements sorting and saving/loading car data from CSV files.

2. **`C_rented_cars.c`**  
   - Manages functions for renting cars and handling rented car data.  
   - Includes reading and writing rented car data to CSV files.

3. **`C_user.c`**  
   - Handles user-related functionalities like login, registration, and managing user data.  
   - Includes functions for validating credentials and displaying user details.

4. **`C_employee.c`**  
   - Contains functions for employee management, including login, adding, deleting, and modifying employee records.

5. **`C_main.c`**  
   - Serves as the entry point of the program.  
   - Manages the main menu and coordinates function calls from other modules.

### Instructions
1. **Pre-Requisites:**
   - Install a C compiler (e.g., GCC).
   - Ensure the required CSV files (`cars_data.csv`, `employee_data.csv`, `user_data.csv`, and `rented_cars.csv`) are in the same directory as the program.

2. **Steps to Compile and Run:**
   - Open a terminal or command prompt in the project directory.
   - Compile the program using the following command:  
    
    gcc -o car_rental C_employee.c C_main.c C_rented_cars.c C_user.c cars.c
     
   - Run the program using:  

    ./car_rental

3. **Program Flow:**
   - Choose between User Login, Employee Login, or Admin Login from the Main Menu.
   - Follow the prompts for specific operations such as renting a car, managing data, or viewing reports.

### Features
- **Car Management:** Add, edit, delete, search, and view car records and also view the car recod based on filters which displayes the cars in a sorted order.
- **User Management:** User registration, login, and rental history tracking, deleting data of user.
- **Employee Management:** Employee login, addition, deletion, and modification.
- **Rented Car Tracking:** Renting cars and viewing rental records.
- **Data Persistence:** All data is stored in CSV files for future use.