#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"car.h"

int main()
{
   // returnCarUi();getch();
    int i,type,k,choice,result;
    User *usr;
      gotoxy(25,10);
  textcolor(YELLOW);
  printf("WELCOME TO CAR RENTAL SYSTEM");
  gotoxy(20,13);
  textcolor(LIGHTGREEN);
  printf("* RENT A CAR AND GO WHERE EVER YOU WISH *");
  getch();
  textcolor(YELLOW);
  addAdmin();

  while(1)
  {
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,8);
    textcolor(GREEN);
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    gotoxy(1,18);
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    gotoxy(32,10);
    textcolor(YELLOW);
    printf("1. Admin");
    gotoxy(32,12);
    printf("2. Employee");
    gotoxy(32,14);
    printf("3. Exit");
    gotoxy(32,16);
    printf("Enter your choice: ");

    do
    {
        textcolor(WHITE);
        scanf("%d",&type);
        if(type==1)
        {
           do
           {
               usr=getInput();
               if(usr==NULL)
                break;
               else
                k=checkUserExist(*usr,"admin");

           }while(k==0);

           if(k==-1)
            break;

           if(k==1)
           {
               while(1)
               {
                   clrscr();
                   choice=adminMenu();
                   if(choice==7)
                    break;
                   switch(choice)
                   {
                   case 1: clrscr();

                           addEmployee();
                           break;
                   case 2:
                          clrscr();
                          addCarDetails();
                          break;
                   case 3:
                          clrscr();
                          viewEmployee();
                          break;
                   case 4:
                         clrscr();
                         showCarDetails();
                         break;
                   case 5:
                          clrscr();
                          result=deleteEmp();
                          gotoxy(15,14);
                          if(result==0)
                          {
                              textcolor(LIGHTRED);
                              printf("RECORD NOT FOUND!");
                              getch();
                          }
                          else if(result==1)
                          {
                              textcolor(LIGHTGREEN);
                              printf("Record Deleted Successfully");


                          }
                          else if(result==2)
                          {
                              textcolor(LIGHTRED);
                              printf("Error in deletion");

                          }
                          gotoxy(1,16);
                          textcolor(WHITE);
                          printf("Press any key to go back to main menu");
                          getch();
                          break;
                   case 6:
                          clrscr();
                         result=deleteCarModel();
                          gotoxy(15,14);
                          if(result==0)
                          {
                              textcolor(LIGHTRED);
                              printf("RECORD NOT FOUND!");
                          }
                          else if(result==1)
                          {
                              textcolor(LIGHTGREEN);
                              printf("Record Deleted Successfully");

                          }
                          else if(result==2)
                          {
                              textcolor(LIGHTRED);
                              printf("Error in deletion");
                          }
                          gotoxy(1,16);
                          textcolor(WHITE);
                          printf("Press any key to go back to main menu");
                          getch();
                          break;
                   default: break;

                   }

                   }

               }


        }
        else if(type==2)
        {

           do
           {
               usr=getInput();
               if(usr==NULL)
                break;
               else
                k=checkUserExist(*usr,"emp");

           }while(k==0);

           if(k==-1)
            break;
           if(k==1)
           {
               while(1)
               {
                   clrscr();
                   choice=empMenu();
                   if(choice==6)
                    break;
                   switch(choice)
                   {
                   case 1:
                        clrscr();
                        int rentres=rentCar();
                        if(rentres==-2)
                        {
                            gotoxy(35,9);
                            textcolor(LIGHTRED);
                            printf("Sorry! all cars are booked try later");
                            getch();
                        }
                        else if(rentres==0)
                        {
                            gotoxy(27,18);
                            textcolor(LIGHTRED);
                            printf("you did not choose a car");
                            getch();
                        }

                        break;
                   case 2:
                       clrscr();
                       bookedCarDetails();
                       break;
                   case 3:
                       clrscr();
                       availableCarDetails();
                       break;
                   case 4:
                       clrscr();
                       showCarDetails();
                       break;
                   case 5:
                        clrscr();
                        int r;
                         result=returnCarUi();
                          gotoxy(15,14);
                          if(result==0)
                          {
                              textcolor(LIGHTRED);
                              printf("RECORD NOT FOUND!");getch();
                              break;
                          }

                           else if(result==1)
                          {
                              textcolor(LIGHTGREEN);
                              printf("Car Returned  Successfully");

                          }
                          else if(result==-2)
                          {
                              textcolor(LIGHTRED);
                              printf("Error in deletion");
                          }
                          gotoxy(1,16);
                          textcolor(WHITE);
                          printf("Press any key to go back to main menu");
                          getch();
                          break;
                   default:
                    break;

                   }
               }

           }

        }
        else if(type==3)
        {
            clrscr();
            textcolor(GREEN);
            gotoxy(30,12);
            printf("Thank you using the app");
            getch();
            exit(0);
        }
        else
        {

            textcolor(RED);
            gotoxy(30,20);
            printf("Invalid choice");
            getch();
            gotoxy(30,20);
            printf("\t\t\t\t\t");
            gotoxy(51,16);
            printf("\t\t");
            textcolor(WHITE);
            gotoxy(51,16);
        }
        break;
    }while(1);


  }


    return 0;
}
