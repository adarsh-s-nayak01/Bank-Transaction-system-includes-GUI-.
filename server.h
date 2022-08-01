struct acc_details{
    char acc_name[60];
    char acc_no[11];
    char IFSC[11];
    char upi_id[40];
 
}user;

    
struct NEFT{
    char rec_IFSC[11];
    int rec_acc_no[11];
    char rec_acc_name[60];
    float amt;
}neft;

struct debcred{
    char rec_upi_id[40];
    char rec_acc_name[60];
    float upi_amt;
}DEBCRED;

void input(int *p,float *f);
void display(float);
void neft_user(float *p);
void encrypt(int key);
int findKey(int );
void upi_transfer(float *p);
void decrypt(int key);