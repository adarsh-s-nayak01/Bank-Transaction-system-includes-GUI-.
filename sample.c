#include <stdio.h>
#include<string.h>
#include "server.h"

void input(int *p,float *f)
{
    char ch;
    fflush(stdin);
    printf("Enter Full name:\n");
    scanf("%[^\n]",&user.acc_name);
    fflush(stdin);
    printf("Enter your account number: \n");
    scanf("%s",&user.acc_no);
    fflush(stdin);
    printf("Enter the IFSC code: \n");
    scanf("%s",&user.IFSC);
    fflush(stdin);
    printf("Enter your current account balance: \n");
    scanf("%f",f);
    fflush(stdin);
    printf("Do you have an existing UPI handler?[Y/N]:\n");
    fflush(stdin);
    scanf("%c",&ch);
    fflush(stdin);
    if((ch=='Y'||ch=='y'))
    {
        printf("Enter your UPI ID:\n");
        scanf("%s",&user.upi_id);
        fflush(stdin);
        printf("Enter your UPI Pin:\n");
        scanf("%d",p);
        fflush(stdin);
    }
    else if((ch=='N'||ch=='n'))
    {
        printf("Choose the UPI handler you wish to register with:\n1.Google pay\n2.PhonePe\n3.Paytm\nEnter your choice(1,2 or 3): ");
        scanf("%c",&ch);
        fflush(stdin);
        if(ch=='1')
        {
            char email[30];
            printf("Enter your email ID:\n");
            scanf("%s",&email);
            fflush(stdin);
            printf("Set your UPI pin (6-digit number):\n");
            scanf("%d",p);
            fflush(stdin);
            char gpay[]="@gpay";
            char *a=strtok(email,"@");
            strcat(a,gpay);
            strcpy(user.upi_id,a); 
        }
        else if(ch=='2')
        {
            printf("Enter your phone number(10 digits):\n");
            scanf("%s",&user.upi_id);
            fflush(stdin);
            printf("Set your UPI pin (6-digit number):\n");
            scanf("%d",p);
            fflush(stdin);
            char Ppe[]="@PhonePe";
            strcat(user.upi_id,Ppe);
        }
        else if(ch=='3')
        {
            printf("Enter your phone number(10 digits):\n");
            scanf("%s",&user.upi_id);
            fflush(stdin);
            printf("Set your UPI pin (6-digit number):\n");
            scanf("%d",p);
            fflush(stdin);
            char Ptm[]="@Paytm";
            strcat(user.upi_id,Ptm);
        }
        else
            printf("Invalid input, try again");
        
    }
    else
        printf("Invalid input!!, try again with proper inputs");

}    



void display(float f)
{
    printf("Name : %s\n",user.acc_name);
    printf("Account Number : %s\n",user.acc_no);
    printf("IFSC Code : %s\n",user.IFSC);
    printf("Balance : %.2f\n",f);
    printf("UPI ID : %s\n",user.upi_id);
}

void neft_user(float *p)
{
    fflush(stdin);
    printf("Enter Name of recepient:\n");
    scanf("%[^\n]",&neft.rec_acc_name);
    fflush(stdin);
    printf("Enter recepient account number: \n");
    scanf("%[^\n]",&neft.rec_acc_no);
    fflush(stdin);
    printf("Enter recepient IFSC code: \n");
    scanf("%[^\n]",&neft.rec_IFSC);
    fflush(stdin);
    printf("Enter the amount to transfer through NEFT:\n");
    scanf("%f",&neft.amt);
    fflush(stdin);
    *p-= neft.amt;
    printf("An amount of Rs.%.2f has been DEBITED from your A/C %s\nto recepient %s (A/C %s),\nYour available Balance is Rs.%.2f",neft.amt,user.acc_no,neft.rec_acc_name,neft.rec_acc_no,*p);
}

void upi_transfer(float *p)
{
    printf("Enter the amount to transfer through UPI:\n");
    scanf("%f",&DEBCRED.upi_amt);
    fflush(stdin);
    *p-=DEBCRED.upi_amt;
    printf("An amount of Rs.%.2f has been DEBITED from your A/C %s\nto recepient %s (UPI ID %s),\nYour available Balance is Rs.%.2f",DEBCRED.upi_amt,user.acc_no,DEBCRED.rec_acc_name,DEBCRED.rec_upi_id,*p);

}
int findKey(int p)
{
    int sum=0,pin=p;
    for(int i=0;i<6;i++)
    {
        sum=sum+(pin%10);
        pin/=10;
    }
    int key=(sum/10)+1;
    return key;
}

void encrypt(int key)
{
    
    int i;
    char ch;
    for (i = 0; user.acc_name[i] != '\0'; i++)
    {
        ch =  user.acc_name[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
             user.acc_name[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
             user.acc_name[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch+key;
            if(ch>'9')
            {
                ch=ch-'9'+'0'-1;
            }
            user.acc_name[i]= ch;
        }
        else
        {
            ch=ch-1;
            user.acc_name[i]= ch;
        }    
    }
    for (i = 0; user.acc_no[i] != '\0'; i++)//2
    {
        ch =  user.acc_no[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
             user.acc_no[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
             user.acc_no[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch+key;
            if(ch>'9')
            {
                ch=ch-'9'+'0'-1;
            }
            user.acc_no[i]= ch;
        }
        else
        {
            ch=ch-1;
            user.acc_no[i]= ch;
        }    
    } 
    for (i = 0; user.IFSC[i] != '\0'; i++)//3
    {
        ch =  user.IFSC[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
             user.IFSC[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
             user.IFSC[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch+key;
            if(ch>'9')
            {
                ch=ch-'9'+'0'-1;
            }
            user.IFSC[i]= ch;
        }
        else
        {
            ch=ch-1;
            user.IFSC[i]= ch;
        }    
    } 
   
    for (i = 0; user.upi_id[i] != '\0'; i++)//5
    {
        ch =  user.upi_id[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
             user.upi_id[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
             user.upi_id[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch+key;
            if(ch>'9')
            {
                ch=ch-'9'+'0'-1;
            }
            user.upi_id[i]= ch;
        }
        else
        {
            ch=ch-1;
            user.upi_id[i]= ch;
        }    
    }
    
}



void decrypt(int key)
{
    
    int i;
    char ch;
    for (i = 0; user.acc_name[i] != '\0'; i++)
    {
        ch =  user.acc_name[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
             user.acc_name[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
             user.acc_name[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch-key;
            if(ch<'0')
            {
                ch=ch+'9'-'0'+1;
            }
            user.acc_name[i]= ch;
        }
        else
        {
            ch=ch+1;
            user.acc_name[i]= ch;
        }    
    }
    for (i = 0; user.acc_no[i] != '\0'; i++)//2
    {
        ch =  user.acc_no[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
             user.acc_no[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
             user.acc_no[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch-key;
            if(ch<'0')
            {
                ch=ch+'9'-'0'+1;
            }
            user.acc_no[i]= ch;
        }
        else
        {
            ch=ch+1;
            user.acc_no[i]= ch;
        }    
    } 
    for (i = 0; user.IFSC[i] != '\0'; i++)//3
    {
        ch =  user.IFSC[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
             user.IFSC[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
             user.IFSC[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch-key;
            if(ch<'0')
            {
                ch=ch+'9'-'0'+1;
            }
            user.IFSC[i]= ch;
        }
        else
        {
            ch=ch+1;
            user.IFSC[i]= ch;
        }    
    } 
   
    for (i = 0; user.upi_id[i] != '\0'; i++)//5
    {
        ch =  user.upi_id[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z'- 'a' + 1;
            }
             user.upi_id[i]= ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
             user.upi_id[i]= ch;
        }
        else if(ch>='0'&& ch<='9')
        {
            ch=ch-key;
            if(ch<'0')
            {
                ch=ch+'9'-'0'+1;
            }
            user.upi_id[i]= ch;
        }
        else
        {
            ch=ch+1;
            user.upi_id[i]= ch;
        }    
    }
    
}
