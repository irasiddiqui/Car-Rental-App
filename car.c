#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"conio2.h"
#include"car.h"

void addAdmin()
{
    FILE *fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        User u[2]={{"admin","test","Ravi"},{"super","demo","ashu"}};
        fwrite(u,sizeof(u),1,fp);
    }


}
User* getInput()
{
    int i;
    clrscr();
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(32,5);
    textcolor(LIGHTRED);
    printf("* LOGIN PANEL *");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);
    for(i=1;i<=80;i++)
         printf("%c",247);
    gotoxy(1,15);
    for(i=1;i<=80;i++)
         printf("%c",247);
    gotoxy(60,8);
    textcolor(WHITE);
    printf("PRESS 0 to EXIT");
    gotoxy(25,10);
    textcolor(LIGHTCYAN);
    printf("Enter Userid :");
    textcolor(WHITE);
    static User u;
    fflush(stdin);
    fgets(u.userid,20,stdin);
    char *pos;
    pos=strchr(u.userid,'\n');
    if(pos!=NULL)
    {
        *pos='\0';
    }
    if(strcmp(u.userid,"0")==0)
    {
        gotoxy(30,17);
        textcolor(LIGHTRED);
        printf("Login Cancelled");
        getch();
        return NULL;
    }
    gotoxy(25,11);
    textcolor(LIGHTCYAN);
    printf("Enter Password :");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        u.pwd[i]=getch();
        if(u.pwd[i]==13)
             break;
        else if(u.pwd[i]==127||u.pwd[i]==8)
        {
            i--;
            printf("\b \b");
            continue;
        }
        printf("*");
        i++;
    }
    u.pwd[i]='\0';
        if(strcmp(u.pwd,"0")==0)
        {
            gotoxy(30,17);
            textcolor(LIGHTRED);
            printf("Login Cancelled");
            getch();
            textcolor(YELLOW);
            return NULL;
        }

   return &u;

}

int checkUserExist(User u,char *usertype)
{
    if(strlen(u.userid)==0||strlen(u.pwd)==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Both fields are mandatory. Try Again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t");
        return 0;
    }
    FILE *fp;
    if(strcmp(usertype,"admin")==0)
        fp=fopen("admin.bin","rb");
    else
        fp=fopen("emp.bin","rb");
    if(fp==NULL)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Can not open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t");
        return -1;
    }
    int found=0;
    User user;
    while(fread(&user,sizeof(user),1,fp)==1)
    {

        if(strcmp(user.userid,u.userid)==0&&strcmp(user.pwd,u.pwd)==0)
        {
            found=1;
            break;
        }

    }
    if(found==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Ivalid Userid/Pwd Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t");
        return 0;
    }
    else
    {
        gotoxy(28,20);
        textcolor(GREEN);
        printf("Login Successfull");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t");
    }

    fclose(fp);
    return 1;
}

int adminMenu()
{
    int i,choice;
    gotoxy(32,2);
    textcolor(LIGHTRED);
    printf("CAR RENTAL SYSTEM");
    gotoxy(35,6);
    textcolor(GREEN);
    printf("ADMIN MENU\n");
    for(i=1;i<=80;i++)
      printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Add Employee");
     gotoxy(32,9);
    printf("2. Add Car Details");
     gotoxy(32,10);
    printf("3. Show Employee");
     gotoxy(32,11);
    printf("4. Show Car Details");
     gotoxy(32,12);
    printf("5. Delete Employee");
     gotoxy(32,13);
    printf("6. Delete Car Details");
     gotoxy(32,14);
    printf("7. Exit");

    gotoxy(32,16);
    printf("Enter Choioce :");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}

void addEmployee()
{
    char empid[20]={"Emp-"};
    char temp[20];
    char choice;
    User u;
    FILE *fp;
    char *pos;
    fp=fopen("emp.bin","ab+");
    if(fp==NULL)
    {
        printf("wait");
        getch();
        return;
    }
    fseek(fp,0,SEEK_END);
    int total_rec=ftell(fp)/sizeof(User);//to find the total number of records in the file
    if(total_rec!=0)
    {

        fseek(fp,-60,SEEK_END);
        fread(temp,sizeof(temp),1,fp);

        pos=strchr(temp,'-');
        total_rec=atoi(pos+1);
    }
    total_rec++;
    sprintf(temp,"%d",total_rec);// to copy integer to a string
    strcat(empid,temp);
    strcpy(u.userid,empid);
    fseek(fp,0,SEEK_END);
    do
    {
        clrscr();
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL SYSTEM\n");
        textcolor(LIGHTGREEN);
        int i;
        for(i=1;i<=80;i++)
            printf("~");
        gotoxy(25,5);
        textcolor(WHITE);
        printf("**** ADD EMPLOYEE DETAILS ****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter  Employee Name:");
        textcolor(WHITE);
        fflush(stdin);
        fgets(u.name,20,stdin);

        pos=strchr(u.name,'\n');
        if(pos!=NULL)
           *pos='\0';   //this search enter key and replace it with null character,
                       //when name is less than given size
        textcolor(YELLOW);
        printf("Enter Employee Pwd:");
        textcolor(WHITE);
        fflush(stdin);
        fgets(u.pwd,20,stdin);
        pos=strchr(u.pwd,'\n');
        if(pos!=NULL)
           *pos='\0';
        fwrite(&u,sizeof(User),1,fp);

        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ADDED SUCCESSFULLY\n");
        printf("Employee ID is :- %s",u.userid);
        getch();
        gotoxy(1,20);
        textcolor(LIGHTRED);
        printf("Do you want to add more Employee (Y/N):");

        textcolor(WHITE);
        fflush(stdin);
        scanf(" %c",&choice);
        if(choice=='N'||choice=='n')
            break;

        total_rec++;
        sprintf(u.userid,"Emp-%d",total_rec);

    }while(1);

    fclose(fp);

}
 void addCarDetails()

 {
     Car c;
     char choice;
     FILE *fp=fopen("Car.bin","ab+");
     fseek(fp,0,SEEK_END);
     int total_rec=ftell(fp)/sizeof(Car);

    /* if(total_rec!=0)
     {
         fseek(fp,-66,SEEK_END);
         fread(&c,sizeof(c),1,fp);
         total_rec=c.car_id;
         printf("\%d",total_rec);getch();
     }
      */
     c.car_id=++total_rec;
     fseek(fp,0,SEEK_END);
     do
     {
         clrscr();
         gotoxy(32,2);
         textcolor(LIGHTRED);
         printf("CAR RENTAL SYSTEM\n");
         int i;
         textcolor(LIGHTGREEN);
         for(i=1;i<=80;i++)
            printf("~");
         gotoxy(25,5);
         textcolor(WHITE);
         printf("**** ADD CAR DETAILS ****");
         gotoxy(1,8);
         textcolor(YELLOW);
         printf("Enter Car Model:");
         textcolor(WHITE);
         fflush(stdin);
         fgets(c.car_name,20,stdin);
         char *pos;
         pos=strchr(c.car_name,'\n');
         if(pos!=NULL)
           *pos='\0';
         textcolor(YELLOW);
         printf("Enter Car Capacity:");
         textcolor(WHITE);
         scanf("%d",&c.capacity);
          textcolor(YELLOW);
         printf("Enter Car Count:");
         textcolor(WHITE);
         scanf("%d",&c.car_count);
          textcolor(YELLOW);
         printf("Enter Car price for a day:");
         textcolor(WHITE);
         scanf("%d",&c.price);
         fwrite(&c,sizeof(c),1,fp);
         gotoxy(32,15);
         textcolor(LIGHTGREEN);
         printf("Car Added Successfully");
         printf("\n Car ID is :%d",c.car_id);
         getch();
         gotoxy(1,20);
         printf("Do You want to add more Car(Y/N)");
         textcolor(WHITE);
         fflush(stdin);
         scanf("%c",&choice);
         if(choice=='N'||choice=='n')
            break;
         total_rec++;
         c.car_id=total_rec;
         getch();
     }while(1);
     fclose(fp);

 }

 void viewEmployee()
 {
     User e;
     int i;

     gotoxy(32,1);
     textcolor(YELLOW);
     printf("CAR RENTAL SYSTEM\n");
     for(i=1;i<=80;i++)
        printf("%c",247);
     gotoxy(32,5);
     printf("* EMPLOYEE DETAILS *");
     gotoxy(1,7);
     textcolor(LIGHTGREEN);
     for(i=1;i<=80;i++)
        printf("%c",247);
     gotoxy(1,9);
     for(i=1;i<=80;i++)
        printf("%c",247);
     gotoxy(2,8);
     printf("Employee ID\t\t\tName\t\t\tPassword");
     textcolor(YELLOW);
     FILE *fp=fopen("emp.bin","rb");
     i=10;
     while(fread(&e,sizeof(e),1,fp)==1)
     {
         gotoxy(2,i);
         printf("%s",e.userid);
         gotoxy(33,i);
         printf("%s",e.name);
         gotoxy(58,i);
         printf("%s",e.pwd);
         i++;


     }
     fclose(fp);

     getch();
 }

 void showCarDetails()
 {
     int i;
     Car c;
     gotoxy(32,1);
     textcolor(YELLOW);
     printf("CAR RENTAL SYSTEM\n");
     for(i=1;i<=80;i++)
        printf("%c",247);
     gotoxy(30,5);
     printf("* ALL CAR DETAILS *");
     gotoxy(1,7);
     textcolor(LIGHTGREEN);
     for(i=1;i<=80;i++)
        printf("%c",247);
     printf("\n Car ID\t   Model\t\tCapacity\tAvailable\t Price/Day\n");
     for(i=1;i<=80;i++)
        printf("%c",247);
     FILE *fp=fopen("Car.bin","rb");
      i=12;
     while(fread(&c,sizeof(c),1,fp)==1)
     {
         gotoxy(2,i);
         printf("%d",c.car_id);
         gotoxy(12,i);
         printf("%s",c.car_name);
         gotoxy(36,i);
         printf("%d",c.capacity);
         gotoxy(53,i);
         printf("%d",c.car_count);
         gotoxy(68,i);
         printf("%d",c.price);
         i++;


     }
     fclose(fp);
     getch();

 }
int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    int i,result;
    char empid[10];
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(29,5);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<=80;i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        gotoxy(32,10);
        textcolor(LIGHTRED);
        printf("NO Employee is added yet");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb");
    if(fp2==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(32,10);
        printf(" SORRY !Can not create temp file");
        return -1;
    }
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Employee id to delete the record: ");
    textcolor(WHITE);
    scanf("%s",empid);

    User u;
    int found=0;
    while(fread(&u,sizeof(u),1,fp1)==1)
    {
        if(strcmp(u.userid,empid)!=0)
            fwrite(&u,sizeof(u),1,fp2);
        else
            found=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
        remove("temp.bin");
    else
    {
        result=remove("emp.bin");
        if(result!=0)
        {
           return 2;

        }

        result=rename("temp.bin","emp.bin");
        if(result!=0)
            return 2;
    }
    return found;


}


int deleteCarModel()
{
    int i,carid,result;
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(29,5);
    printf("* DELETE CAR RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
            printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<=80;i++)
        printf("%c",247);
    FILE *fp1=fopen("Car.bin","rb");
    if(fp1==NULL)
    {
        gotoxy(32,10);
        textcolor(LIGHTRED);
        printf("NO CAR IS ADDED YET!");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb");
    if(fp2==NULL)
    {
        gotoxy(32,10);
        textcolor(LIGHTRED);
        printf(" sorry cannot create temp file ");
        return -1;
    }
     gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter car model id to delete the record: ");
    textcolor(WHITE);
    scanf("%d",&carid);
    int found=0;
    Car c;
    while(fread(&c,sizeof(c),1,fp1)==1)
    {
        if(carid!=c.car_id)
        {

            fwrite(&c,sizeof(c),1,fp2);
        }
        else
            found=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
      else
    {
        result=remove("Car.bin");
        if(result!=0)
        {
           return 2;

        }

        result=rename("temp.bin","Car.bin");
        if(result!=0)
            return 2;
    }
    return found;
}

int empMenu()
{
    int choice,i;
    gotoxy(32,2);
    textcolor(LIGHTRED);
    printf("CAR RENTAL SYSTEM");
    gotoxy(35,6);
    textcolor(LIGHTGREEN);
    printf("EMPLOYEE MENU\n");
    for(i=1;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Rent A Car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show All Car Details");
    gotoxy(32,12);
    printf("5. Return Car");
    gotoxy(32,13);
    printf("6. Exit");
    gotoxy(32,16);
    printf("Enter Choice:");
    textcolor(WHITE);
    scanf("%d",&choice);

    return choice;

}

int selectCarModel()
{
    int choice,rowno=9;
    FILE *fp=fopen("Car.bin","rb");
    int flag;
    Car c;
    gotoxy(34,rowno);
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        if(c.car_count>0)
        {
            printf("%d \t%s\t %d",c.car_id,c.car_name,c.price);
            gotoxy(34,++rowno);
        }
    }
    gotoxy(34,rowno+2);
    printf("Enter Your Choice:");
    while(1)
    {
        flag=0;
        textcolor(WHITE);
        scanf("%d",&choice);
        rewind(fp);
        while(fread(&c,sizeof(c),1,fp)==1)
        {
            if(c.car_id==choice && c.car_count>0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        gotoxy(37,rowno+4);
        textcolor(LIGHTRED);
        printf("WRONG INPUT");
        getch();
        gotoxy(37,rowno+4);
        printf("\t\t\t\t\t");
        gotoxy(52,rowno+2);
        printf("\t ");
        gotoxy(52,rowno+2);
        textcolor(WHITE);


    }
    return 0;
}
int isValidDate(struct tm dt)
{
    if(dt.tm_year>=2021 && dt.tm_year<=2022)
    {
        if(dt.tm_mon>=1 && dt.tm_mon<=12)
        {
            if((dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon== 5 ||dt.tm_mon==7 || dt.tm_mon== 8 || dt.tm_mon== 10 || dt.tm_mon== 12) && (dt.tm_mday>=1 && dt.tm_mday<=31 ))
            {
              return 1;
            }

            else if((dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon== 9 ||dt.tm_mon==11) && (dt.tm_mday>=1 && dt.tm_mday<=30 ))
            {
               return 1;
            }
            else if ((dt.tm_mday>=1 && dt.tm_mday<=28)&& dt.tm_mon==2)
            {
                return 1;
            }
            else if((dt.tm_mday>=1 && dt.tm_mday<=29)&& ((dt.tm_year %400 ==0)|| ((dt.tm_year % 4==0)&&(dt.tm_year % 100 != 100))))
            {
            return 1;
            }
        }
        return 0;
    }
    return 0;
}
void updateCarCount(int C_id)
{
    FILE *fp=fopen("Car.bin","rb+");
    if(fp==NULL)
    {
        printf("\nFile can not be open");
        return;
    }
    Car c;

    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_id==C_id)
        {
            int x=c.car_count;
            x--;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;
        }
    }
    fclose (fp);
}

void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    Customer_car_details cc;
    int i;
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(30,5);
    //textcolor(LIGHTGREEN);
    printf("*BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(1,9);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(1,8);
    printf("Model \t Cust Name \t Pickup \t Drop \t\t S_date \t E_date");
    i=10;
    textcolor(YELLOW);

    if(fp==NULL)
    {
        gotoxy(25,10);
        textcolor(LIGHTRED);
        printf("NO BOOKING IS DONE YET");
        getch();
        return ;

    }

    while(fread(&cc,sizeof(cc),1,fp)==1)
    {
        gotoxy(1,i);
        printf("%s",getCarName(cc.car_id));

        gotoxy(13,i);
        printf("%s",cc.cust_name);

        gotoxy(27,i);
        printf("%s",cc.pick);

        gotoxy(44,i);
        printf("%s",cc.drop);

        gotoxy(58,i);
        printf("%d-%d-%d",cc.sd.tm_mday,cc.sd.tm_mon,cc.sd.tm_year);

        gotoxy(70,i);
        printf("%d-%d-%d",cc.ed.tm_mday,cc.ed.tm_mon,cc.ed.tm_year);

        i++;

    }
    fclose(fp);
    getch();

}

char* getCarName(int C_id)
{
    FILE *fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("File cannot be open");
        return NULL;
    }
    static Car c;
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_id==C_id)
        {
            break;
        }
    }
    fclose(fp);
    return c.car_name;
}
int rentCar()
{
    clrscr();
    Customer_car_details cc;
    int i;
    gotoxy(32,2);
    textcolor(LIGHTRED);
    printf("CAR RENTAL SYSTEM");
    gotoxy(35,6);
    textcolor(LIGHTGREEN);
    printf("EMPLOYEE MENU\n");
    for(i=1;i<=80;i++)
        printf("*");
    gotoxy(32,8);
    textcolor(YELLOW);
    int c=selectCarModel();
    if(c==0||c==-2)
        return c;
    cc.car_id=c;
    clrscr();
    gotoxy(35,6);
    textcolor(LIGHTGREEN);
    printf("EMPLOYEE MENU\n");
    for(i=1;i<=80;i++)
        printf("*");
    gotoxy(1,17);
    for(i=1;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.cust_name,30,stdin);
    char *pos;
    pos=strchr(cc.cust_name,'\n');
    *pos='\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter Pick up point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.pick,30,stdin);
    pos=strchr(cc.pick,'\n');
    *pos='\0';
     gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter drop point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.drop,30,stdin);
    pos=strchr(cc.drop,'\n');
    *pos='\0';
    back:
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date:");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&cc.sd.tm_mday,&cc.sd.tm_mon,&cc.sd.tm_year);
        int datevalid=isValidDate(cc.sd);
        if(datevalid==1 &&(dateCheckToday(cc.sd)==1 || dateCheckToday(cc.sd)==2))
            break;

        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("invalid date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t\t\t");
        gotoxy(44,12);
        printf("\t\t\t\t\t");
        gotoxy(44,12);
        textcolor(WHITE);

    }while(1);

     gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date:");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&cc.ed.tm_mday,&cc.ed.tm_mon,&cc.ed.tm_year);
        int datevalid=isValidDate(cc.ed);
        if(datevalid==1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date1!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t\t\t");
        gotoxy(42,13);
        printf("\t\t\t\t\t");
        gotoxy(42,13);
        textcolor(WHITE);

    }while(1);

    if(compareDate(cc.sd,cc.ed)!=1 && compareDate(cc.sd,cc.ed)!=2)
    {
          gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("End date should come after Start date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(44,12);
        printf("\t\t\t\t\t");
        gotoxy(42,13);
        printf("\t\t\t\t\t");
        goto back;
    }


    FILE *fp=fopen("customer.bin","ab");
    if(fp==NULL)
    {
        gotoxy(27,18);
        printf("Sorry File Can not be opened");
        return -1;
    }
     fwrite(&cc,sizeof(Customer_car_details),1,fp);
    gotoxy(27,18);
    textcolor(WHITE);
    printf("Booking Done ! for the car id:%d",cc.car_id);
    printf("\nPress Any key to continue");
    getch();
    fclose(fp);
    updateCarCount(cc.car_id);
    bookedCarDetails();
    return 1;

}
void availableCarDetails()
{
     int i;
     Car c;
     gotoxy(32,1);
     textcolor(YELLOW);
     printf("CAR RENTAL SYSTEM\n");
     for(i=1;i<=80;i++)
        printf("%c",247);
     gotoxy(30,5);
     printf("* AVAILABLE CAR DETAILS *");
     gotoxy(1,7);
     textcolor(LIGHTGREEN);
     for(i=1;i<=80;i++)
        printf("%c",247);
     printf("\n Car ID\t   Model\t\tCapacity\tAvailable\t Price/Day\n");
     for(i=1;i<=80;i++)
        printf("%c",247);
     FILE *fp=fopen("Car.bin","rb");
     if(fp==NULL)
     {
         gotoxy(15,10);
         textcolor(LIGHTRED);
         printf("NO CAR ADDED YET!");
         return;
     }
      i=12;
     while(fread(&c,sizeof(c),1,fp)==1)
     {
         if(c.car_count>0)
         {
            gotoxy(2,i);
            printf("%d",c.car_id);
            gotoxy(12,i);
            printf("%s",c.car_name);
            gotoxy(36,i);
            printf("%d",c.capacity);
            gotoxy(53,i);
            printf("%d",c.car_count);
            gotoxy(68,i);
            printf("%d",c.price);
            i++;
         }


     }
     fclose(fp);
     getch();
}

int dateCheckToday(struct tm p)
{
    time_t today=time(0);
    struct tm *r=localtime(&today);
    if(p.tm_year==(1900+(r->tm_year)))
    {
        if(p.tm_mon==(1+(r->tm_mon)) && p.tm_mday==r->tm_mday)
        {
           return 2;
        }
         else if(p.tm_mon >=(1+(r->tm_mon)))
        {
            if(p.tm_mday>r->tm_mday)
                return 1;
        }
    }

    else if(p.tm_year >(1900+(r->tm_year)))
    {
        if(p.tm_mon >=(1+(r->tm_mon)))
        {
            if(p.tm_mday>r->tm_mday)
                return 1;
        }
    }


    else
        return 0;


  return 0;
}
int returnCar(Customer_car_details c)
{
    int result;
    FILE *fp1=fopen("customer.bin","rb");
    if(fp1==NULL)
    {
         gotoxy(32,10);
        textcolor(LIGHTRED);
        printf(" error in delition ");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb");
    if(fp2==NULL)
    {
        gotoxy(32,10);
        textcolor(LIGHTRED);
        printf(" error in delition ");
        return -1;
    }

    int found=0;
    Customer_car_details cc;
    while(fread(&cc,sizeof(cc),1,fp1)==1)
    {
        if(c.car_id!=cc.car_id && compareDate(c.sd,cc.sd)!=2)
        {

            fwrite(&cc,sizeof(cc),1,fp2);
        }
        else
        {
           found=1;
           updateCarCount2(cc.car_id);

        }

    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
      else
    {
        result=remove("customer.bin");
        if(result!=0)
        {
           return -2;

        }

        result=rename("temp.bin","customer.bin");
        if(result!=0)
            return -2;
    }
    return found;
}
void updateCarCount2(int C_id)
{
   FILE *fp=fopen("Car.bin","rb+");
    if(fp==NULL)
    {
        printf("\nFile can not be open");
        return;
    }
    Car c;

    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_id==C_id)
        {
            int x=c.car_count;
            x++;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;
        }
    }
    fclose (fp);
}
int compareDate(struct tm start ,struct tm end)
{
    if(end.tm_year==start.tm_year && end.tm_mon==start.tm_mon && end.tm_mday==start.tm_mday)
        return 2;
   else if(end.tm_year>=start.tm_year && end.tm_mon>=start.tm_mon && end.tm_mday>start.tm_mday)
        return 1;
    else
        return 0;
}
int returnCarUi()
{
    int i,flag=0;
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(29,5);
    printf("* CAR RETURNING PORTAL *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
            printf("%c",247);

    FILE *fp=fopen("customer.bin","rb");
    if(fp==NULL)
    {
        gotoxy(32,10);
        textcolor(LIGHTRED);
        printf("NO BOOKING IS DONE YET!");
        return -1;
    }
    Customer_car_details cc,temp;
    gotoxy(5,10);
    textcolor(YELLOW);
    printf("Enter the car id :");
    textcolor(WHITE);
    scanf("%d",&cc.car_id);
     gotoxy(5,11);
    textcolor(YELLOW);
    printf("Enter starting date(DD MM YYYY):");
    textcolor(WHITE);

    do
    {
        scanf("%d %d %d",&cc.sd.tm_mday,&cc.sd.tm_mon,&cc.sd.tm_year);
        int datevalid=isValidDate(cc.sd);
        if(datevalid==1)
            break;

        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("invalid date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t\t\t");
        gotoxy(37,11);
        printf("\t\t\t\t\t");
        gotoxy(37,11);
        textcolor(WHITE);

    }while(1);

     gotoxy(5,12);
    textcolor(YELLOW);
    printf("Enter end date filled at the time of booking(DD MM YYYY):");
    textcolor(WHITE);

   do
   {
       scanf("%d %d %d",&cc.ed.tm_mday,&cc.ed.tm_mon,&cc.ed.tm_year);
        int datevalid=isValidDate(cc.ed);
        if(datevalid==1)
            break;

        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("invalid date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t\t\t");
        gotoxy(62,12);
        printf("\t\t\t\t\t");
        gotoxy(62,12);
        textcolor(WHITE);

    }while(1);
    while(fread(&temp,sizeof(temp),1,fp)==1)
    {
        if(temp.car_id==cc.car_id && compareDate(temp.sd,cc.sd)==2 && compareDate(temp.ed,cc.ed)==2)
        {
            fclose(fp);
            flag=1;
            int r=returnCar(cc);
            return r;

        }
        else if(temp.car_id==cc.car_id && compareDate(temp.sd,cc.sd)==2 && compareDate(temp.ed,cc.ed)==1)
        {
            flag=1;
            break;
        }
    }
    fclose(fp);
    if(flag==1)
    {
        gotoxy(15,16);
        textcolor(LIGHTRED);
        printf("you have crossed the date of return!");
        gotoxy(15,17);
        printf("you will be charged 1000 rupees per day as late fine!");
        flag=returnCar(cc);
        return flag;

    }

    else
        return 0;

}
