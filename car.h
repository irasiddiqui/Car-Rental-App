#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include<time.h>

struct User
{
    char userid[20];
    char pwd[20];
    char name[20];
};

struct Car
{
    int car_id;
    char car_name[50];
    int capacity;
    int car_count;
    int price;
};

struct Customer_car_details
{
    int car_id;
    char cust_name[30];
    char pick[30];
    char drop[30];
    struct tm sd;
    struct tm ed;
};

typedef struct User User;
typedef struct Car Car;
typedef struct Customer_car_details Customer_car_details;

void addAdmin();  //for inserting admin's data into file
User* getInput();  //for accepting userid and pwd and returning its address
int checkUserExist(User,char*);
int adminMenu(); // for displaying admin menu
void addEmployee();
void viewEmployee();
void addCarDetails();
void showCarDetails();
int deleteEmp();
int deleteCarModel();
int empMenu();
int selectCarModel();
int isValidDate(struct tm);
void updateCarCount(int);
void bookedCarDetails();
char* getCarName(int);
void availableCarDetails();
int rentCar();
int dateCheckToday(struct tm);
int compareDate(struct tm,struct tm);
int returnCar(Customer_car_details);
void updateCarCount2(int);
int returnCarUi();



#endif // CAR_H_INCLUDED
