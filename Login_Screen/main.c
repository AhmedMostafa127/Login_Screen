#include <stdio.h>
#include <stdlib.h> // exit_finction
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int menu();
void signup();
void login();
void takepassword(char pass[]);
void forgot(); // forgot pass , username
void change_password() ;
void delete_account();
void divider()
{
    for(int count =0 ; count <70 ; count++)
    {
        printf("-");
    }
    printf("\n");
}

typedef struct account
{
    char first_name[50];
    char last_name[50];
    char user_name [50];
    char phone[12];
    char gender[6] ;
    char DOB[10]; //Date of birth
    char pass[50];
}acc;

int main()
{
    while (1)
    {
        getch();
        system("cls");
        switch(menu())
        {
        case 1 :
            signup();
            break;
        case 2 :
            login();
            break;
        case 3 :
            forgot();
            break;
        case 4 :
            change_password();
            break ;
        case 5 :
            delete_account();
            break ;
        case 6 :
            exit(0);
        default :
            printf("Invalid option \n");
            break;
        }
    }


    return 0;
}

int menu()
{
    int choice_num = 0;


    printf("-------------------------------Main Menu------------------------------ \n");
    divider();
    printf("1) SIGNUP \n");
    printf("2) LOGIN \n");
    printf("3) FORGOT PASSWORD OR USERNAME \n");
    printf("4) CHANGE PASSWORD \n");
    printf("5) DELETE ACCOUNT \n");
    printf("6) EXIT \n");
    printf("Enter your choice : ");

    scanf("%i",&choice_num);
    return choice_num ;
}

void takepassword(char pass[])
{
       printf("Please Enter The Password \"Max 50 ch\": ");
       int i = 0 ;
       char ch ;
       while (1)
        {
        ch = getch();
        if(ch == 13 || i==20) //
        {
            pass[i]='\0';
            break;
        }
        else if (ch == 8)  //Backspace
        {

            if(i>0)
            {
                i--;
                printf("\b \b");
            }

        }
        else if (ch == 9)  //Tab
        {
            continue ;
        }
        else
        {
            pass[i++]=ch;
            printf("*");
        }
        }
        printf("\n");
}

void signup()
{
    system("cls");
    acc ptr_acc ;
    int gender_choice;
    char pass2[50];
    int compared_conf_pass=-1;

    printf("--------------------------------SIGNUP-------------------------------- \n");
    divider();
    printf("Creating New Account \n");
//    divider();
    printf("Please enter your first name   : ");
    scanf("%s",ptr_acc.first_name);
    fflush(stdin);
    printf("Please enter your last name    : ");
    scanf("%s",ptr_acc.last_name);
    fflush(stdin);
    printf("Please enter your user name    : ");
    scanf("%s",ptr_acc.user_name);
    fflush(stdin);
    printf("Please enter your phone number : ");
    scanf("%s",ptr_acc.phone);
    fflush(stdin);
    while (gender_choice !=1 || gender_choice != 2 )
    {
        printf("Please choose your gender : \n 1) Male \t 2) Female : ");
        scanf("%i",&gender_choice);
        if(gender_choice ==1)
        {
          strcpy(ptr_acc.gender , "Male" );
          break ;

        }
        else if ( gender_choice == 2)
        {
          strcpy(ptr_acc.gender , "Female" );
          break ;

        }
        else
        {
            printf("Please Enter Again your choice \"Male\" OR \"Female\" ONLY \n");
        }
    }

    printf("Please enter your Date of birth: ");
    scanf("%s",ptr_acc.DOB);
    fflush(stdin);
    takepassword(ptr_acc.pass);

    while (compared_conf_pass !=0 )
    {
    printf("Confirm Password :");
    scanf("%s", pass2);
    compared_conf_pass = strcmp(ptr_acc.pass,pass2);
    if ( compared_conf_pass == 0)
    {
        printf("CONGRATS !! Your Account has been created successfully \n ");
        getch();

        FILE *file_ptr = fopen("account.txt" , "w");
        fwrite(&ptr_acc , sizeof(struct account) ,1 , file_ptr);
        //fprintf(file_ptr , "Name : %s %s - User name : %s - Phone : %s - Gender : %s - Date of birth : %s - Password : %s \n",
              //  ptr_acc.first_name  ,ptr_acc.last_name  ,ptr_acc.user_name   ,ptr_acc.phone  ,ptr_acc.gender  ,ptr_acc.DOB  ,ptr_acc.pass);

        fclose(file_ptr); //9 user ,
    }
    else
    {
        printf("SORRY !! :( , Please try again to confirm your password \n ");
    }

    }
}

void login()
{
    system("cls");
    printf("--------------------------------LOG IN-------------------------------- \n");
    divider();
    char user[50] , pass[50];
    struct account my_acc;
    int compared_user = -1 ,compared_pass = -1 ;
    FILE *file_ptr = fopen("account.txt","r");
    fread(&my_acc , sizeof(struct account),1,file_ptr);



   while(compared_user != 0)
   {
       printf("Enter user name :");
       scanf("%s",user);
       compared_user = strcmp(my_acc.user_name, user);

       if (compared_user != 0)
       {
         printf("Sorry !! Please enter correct user name \n");
       }
       else
       {

           while (compared_pass != 0 )
           {
               takepassword(pass);
               compared_pass = strcmp(my_acc.pass,pass);
               if (compared_pass != 0)
                {
                    printf("Sorry !! Please enter correct Password \n");
                }
                else
                {
                     system("cls");
                     printf("------------------Welcome to your account , %s %s ------------------ \n" ,my_acc.first_name,my_acc.last_name);
                     divider();
                     printf("Name : %s %s \nUser name : %s \nPhone : %s \nGender : %s \nDate of birth : %s \nPassword : %s \n",
                            my_acc.first_name  ,my_acc.last_name  ,my_acc.user_name   ,my_acc.phone  ,my_acc.gender  ,my_acc.DOB  ,my_acc.pass);
                    divider();
                    getch();
                }

           }


       }
   }
   fclose(file_ptr);
}


void forgot()
{

    system("cls");
    printf("----------------------FORGOT PASSWORD OR USERNAME--------------------- \n");
    divider();
    struct account my_acc;
    char user[50] , pass[50] ,phone[50];
    int choice = -1,compared_user = -1 ,compared_pass = -1 , compared_phone =-1 ;
    FILE *file_ptr = fopen("account.txt","r");
    fread(&my_acc , sizeof(struct account),1,file_ptr);

    printf("1.Search by UserName \n");
    printf("2.Search by password \n");
    printf("3.Search by Phone Number \n");
    printf("4.Return to main menu \n");
    divider();
    printf("Enter your choice : ");
    scanf("%i",&choice);

    switch (choice)
    {
    case 1 :
        printf("Enter user name :");
        scanf("%s",user);
        compared_user = strcmp(user,my_acc.user_name);

       if (compared_user != 0)
       {
         printf("Sorry !! Account is not found \n");
       }
       else
       {
            printf("Account Found \n");
            printf("Name : %s %s \nUser name : %s \nPhone : %s \nGender : %s \nDate of birth : %s \nPassword : %s \n",
                            my_acc.first_name  ,my_acc.last_name  ,my_acc.user_name   ,my_acc.phone  ,my_acc.gender  ,my_acc.DOB  ,my_acc.pass);
            getch();

       }
        break;

        case 2 :
        printf("Enter password :");
        scanf("%s",pass);
        compared_user = strcmp(pass,my_acc.pass);

       if (compared_pass != 0)
       {
         printf("Sorry !! Account is not found \n");
       }
       else
       {
            printf("Account Found \n");
            printf("Name : %s %s \nUser name : %s \nPhone : %s \nGender : %s \nDate of birth : %s \nPassword : %s \n",
                            my_acc.first_name  ,my_acc.last_name  ,my_acc.user_name   ,my_acc.phone  ,my_acc.gender  ,my_acc.DOB  ,my_acc.pass);
            getch();

       }
        break;

        case 3 :
        printf("Enter phone number:");
        scanf("%s",phone);
        compared_phone = strcmp(phone,my_acc.phone);

       if (compared_phone != 0)
       {
         printf("Sorry !! Account is not found \n");
       }
       else
       {
            printf("Account Found \n");
            printf("Name : %s %s \nUser name : %s \nPhone : %s \nGender : %s \nDate of birth : %s \nPassword : %s \n",
                            my_acc.first_name  ,my_acc.last_name  ,my_acc.user_name   ,my_acc.phone  ,my_acc.gender  ,my_acc.DOB  ,my_acc.pass);
            getch();

       }
        break;


        case 4 :
            return ;
            break;

        default :
            printf("Invalid choice !!!");
            break;

    }
    fclose(file_ptr);
}

void change_password()
{

    system("cls");
    printf("----------------------------CHANGE PASSWORD--------------------------- \n");
    divider();
    int num1,num2 , compared_pass = -1;
    char pass2[50];
    srand(time(0));

    while (num1 != num2)
    {
        num1 = rand();

        printf("Random number : %i \n",num1 );
        printf("Enter above number : ");
        scanf("%i",&num2);


        if (num1 != num2)
        {
            printf("Please enter correct number \n");

        }
        else
        {
            struct account my_acc ;
            FILE *file_ptr = fopen("account.txt","r");
            fread(&my_acc , sizeof(struct account) ,1 ,file_ptr );

            printf("Please enter new password : \n");
            takepassword(my_acc.pass);

            while(compared_pass != 0)
            {
                printf("Confirm password : ");
                scanf("%s", pass2);
                compared_pass = strcmp(my_acc.pass,pass2);

                if( compared_pass != 0)
                {
                    printf("INCORRECT PASSWORD !!! \n");
                }
                else
                {
                    file_ptr = fopen("account.txt","w");
                    fwrite(&my_acc , sizeof(struct account) ,1 ,file_ptr );
                    printf("Password has been changed Successfully \n");
                    getch();
                }

            }

        fclose(file_ptr);
        }
    }


}
void delete_account()
{

    system("cls");
    printf("----------------------------DELETE ACCOUNT--------------------------- \n");
    divider();
    FILE *file_ptr = fopen("account.txt","r");
    char c = fgetc(file_ptr);
    if (c == EOF)
    {
        printf("NO Account to delelte \n");


    }
    else
    {
        printf("Are you sure [Y/N] : ") ;
        char ch = getche();
        if( ch == 'Y' || ch == 'y')
        {
            file_ptr = fopen("account.txt","w");
            fprintf(file_ptr," ");
            printf("\nACCOUNT DELELTION HAS BEEN DONE SUCCESSFULLY \n");
            getch();
        }
        else if( ch == 'N' || ch == 'n')
        {
            printf("\nACCOUNT DELELTION HAS BEEN STOPPED\n");
            getch();
        }
        else
        {
            printf("INVALID INPUT !!! \n");
        }
    }
}
