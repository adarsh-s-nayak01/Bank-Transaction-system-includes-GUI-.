#include <stdio.h>
#include "server.h"


int main()
{
    int upi_pin=0;
    float balance=0.0;
    FILE *fp;
    char cfile[]="Data.csv";
    printf("*************\\WELCOME TO SECURE FINANCE AGENCY//*************\n");
    printf("Please Enter the required information to get started :\n");
    input(&upi_pin,&balance);

    fp=fopen(cfile,"w+");
    fprintf(fp,"Service,Customer name,Account number,IFSC code,Account balance,UPI handler,UPI Pin");

    int key=findKey(upi_pin);

    encrypt(key);

    fprintf(fp,"\n%s,%s,%s,%s,%.2f,%s,%d","Creation",user.acc_name,user.acc_no,user.IFSC,balance,user.upi_id,upi_pin); 

    decrypt(key);

    printf("Services :\n");
    printf("1.NEFT\n2.UPI Transfer\n3.Balance Enquiry\n4.Change UPI Pin\n5.Display details\n6.Exit\nEnter the option(1,2,3,4,5 or 6): \n");
    char c;
    scanf("%c",&c);
    fflush(stdin);

    if(c=='1')
    {
        neft_user(&balance);
        encrypt(key);
        fprintf(fp,"\n%s,%s,%s,%s,%.2f,%s,%d","NEFT",user.acc_name,user.acc_no,user.IFSC,balance,user.upi_id,upi_pin);
    }
    else if(c=='2')
    {
        printf("Enter the recepient UPI ID :\n");
        scanf("%[^\n]",&DEBCRED.rec_upi_id);
        fflush(stdin);
        printf("Enter the recepient Name :\n");
        scanf("%[^\n]",&DEBCRED.rec_acc_name);
        fflush(stdin);
        upi_transfer(&balance);
        encrypt(key);
        fprintf(fp,"\n%s,%s,%s,%s,%.2f,%s,%d","UPI Transfer",user.acc_name,user.acc_no,user.IFSC,balance,user.upi_id,upi_pin);
    }
    else if(c=='3')
    {
        printf("Balance is %.2f",balance);
    }
    else if(c=='4')
    {
        int check;
        printf("Enter your current UPI Pin :\n");
        scanf("%d",&check);
        if(upi_pin==check)
        {
            printf("Enter NEW UPI Pin : \n");
            scanf("%d",&upi_pin);
            printf("Re-enter new UPI Pin :\n");
            scanf("%d",&check);
            if(upi_pin==check)
            {
                printf("UPI Pin successfully changed!\n");
            }
            else
                printf("ERROR: Pin doesn't match!!\n");    
        }
        else
            printf("ERROR: Invalid UPI pin!\n");
        encrypt(key);
        fprintf(fp,"\n%s,%s,%s,%s,%.2f,%s,%d","UPI Pin change",user.acc_name,user.acc_no,user.IFSC,balance,user.upi_id,upi_pin);    
    }
    else if(c=='5')
    {
        display(balance);
        encrypt(key);
        fprintf(fp,"\n%s,%s,%s,%s,%.2f,%s,%d","Display Details",user.acc_name,user.acc_no,user.IFSC,balance,user.upi_id,upi_pin);
    }
    else if(c=='6')
    {
        printf("Thank you for using our services!");
        return 0;
    }
    else
        printf("Invalid input!\n");

    fclose(fp);
    
    return 0;
}