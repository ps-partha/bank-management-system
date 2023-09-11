#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int total = 0, amount, password, ac_nm, ID = 0, loc=0, sl = 1,ws=1,ts=1;
int choice;
int Account_n, found = 0, pin, i;
int depos[50][10], withdrawals[50][10], tuitio_fees[50][10], Loan[50][10], total_loan[50][10];

struct Account
{
    char first_name[20];
    char last_name[20];
    char Phone[10];
    char NID[20];
    int id;
    int pin;
    char city[20];
    char address[50];
};
struct Account_Balance
{
    long int Balance[100];
};
struct university_data
{
    int university_option;
    long int total_fee;
    int per_semester;
} university_data;

int yes_no, ac_number, pin;
int find = 0;
struct Account_Balance balance;
struct Account info;
struct university_data university_data;
FILE *fp;
struct Account info;

void Deposits();
void Tuitio_fees();
void Loan_management();
void history();
void Withdrawals();
void Account_detells();
void Create_Account();
void Account_info();
void login();
void Ac_Manu();
void bankhead();
void Delete();
void Home();
void  clrscr();

void  clrscr(){
    system("cls");
}
// --------------------- Deposits -------------------------
void Deposits(loc)
{
    int Deposits;
    printf("Enter your Deposits amount :");
    scanf("%d", &Deposits);
    depos[loc][sl] = Deposits;
    sl++;
    balance.Balance[loc] = balance.Balance[loc] + Deposits;
    printf("Deposits successfuly\n");
    printf("Now your total balance %ld\n\n", balance.Balance[loc]);
    printf("Press any key to continue.......");
    getch();
}

//----------------------- Tution Fees -----------------------------

void Tuitio_fees(loc)
{
    printf("\n[1] Dhaka International university\n[2] Green International university\n[3] United International University\n\n");
    printf("Enter university name (1 to 3):");
    scanf("%d", &university_data.university_option);
    if (university_data.university_option == 1)
    {
        printf("\n-----------------------------------------------------------\n");
        printf("Dhaka International university\n\n");
        printf("Enter your Total Tuitio fees :");
        scanf("%ld", &university_data.total_fee);
        university_data.per_semester = university_data.total_fee / 12;
        tuitio_fees[loc][ts]= university_data.per_semester;
        ts++;
        if (university_data.per_semester <= balance.Balance[loc])
        {
            printf("Your per semester tution fees are %d\n", university_data.per_semester);
            balance.Balance[loc] = balance.Balance[loc] - university_data.per_semester;
            printf("Tution fee done successfuly \n");
        }
        else
        {
            printf("\nInsufficient balance\n");
        }
    }
}
void Loan_management(loc)
{
    int loanAmont,yn;
    printf("Enter your loan amount :");
    scanf("%d", &loanAmont);
    Loan[loc][1] = Loan[loc][1] + loanAmont;
    printf("Load successfuly\n");
}

void history(loc){
    int dsum=0,wsum=0,fsum=0;
    for ( i = 1; i <= sl; i++)
    {
        dsum = dsum + depos[loc][i];
    }
    for (i = 1; i <= ws; i++)
    {
        wsum = wsum + withdrawals[loc][i];
    }
    for ( i = 1; i <= ts; i++)
    {
        fsum = fsum + tuitio_fees[loc][i];
    }
    printf("\nTotal Deposits : %d \n",dsum);
    printf("Total Withdrawals : %d \n",wsum);
    printf("Total Tuitio fees : %d \n",fsum);  
}






//-------------------------- Withdrawals -----------------------------
void Withdrawals(loc)
{
    int yn;
    printf("Enter you Withdrawal amount :");
    scanf("%d", &amount);
    withdrawals[loc][ws] = amount;
    ws++;
    if (amount > balance.Balance[loc])
    {
        printf("\nInsufficient balance\n");
        printf("You want to loan? (1 or 0) :");
        scanf("%d", &yn);
        if (yn == 1)
        {
            Loan_management(loc);
        }
    }
    else
    {
        balance.Balance[loc] = balance.Balance[loc] - amount;
        total = balance.Balance[loc];
        printf("Withdrawals successfuly\n");
        printf("Now acount balence is %d\n", total);
    }
}
//----------------------- Create account -----------------------------

void Create_Account()
{
    FILE *fp, *fp3;
    clrscr();
    bankhead();
    int temAC;
    fp = fopen("information.txt", "a");
    fp3 = fopen("information.txt", "r");


    printf("\n<<======= Create Account =============>>\n");
    printf("\nEnter Your First Name   : ");
    scanf("%s", &info.first_name);
    printf("Enter Your Last Name    : ");
    scanf("%s", &info.last_name);
    printf("Enter Your Phone Number : ");
    scanf("%s", &info.Phone);
    printf("Enter Your NID Number   : ");
    scanf("%s", &info.NID);
    printf("Enter Your Account Pin (must be integer)  : ");
    scanf("%d", &info.pin);
    printf("Enter Your City         : ");
    scanf("%s", &info.city);
    printf("Enter Your Address      : ");
    scanf("%s", &info.address);
    ID = ID + 1;
    balance.Balance[ID] = 500;
    info.id = ID;
    
    if (fp == NULL)
    {
        fprintf(stderr, "can't open file");
    }
    else
    {
        clrscr();
        bankhead();
        printf("\n\nAccount Created successfuly\n");
        printf("Your Account Number is %d \n\n", info.id);
    }
    fwrite(&info, sizeof(struct Account), 1, fp);
    fclose(fp);
    Home();
}
// ------------------------- Account Detells -----------------------
void Account_detells(ac_number, pin)
{
    fp = fopen("information.txt", "r");
    while (fread(&info, sizeof(struct Account), 1, fp) > 0)
    {
        if (info.id == Account_n && info.pin == pin)
        {
            found = 1;
            printf("\n===========================================\n\n");
            printf("Account Number        : %d\n", info.id);
            printf("Account Holder Name   : %s %s\n", info.first_name, info.last_name);
            printf("Total Balance         : %ld\n", balance.Balance[info.id]);
            printf("Total Loan            : %d\n", Loan[info.id][1]);
            printf("\n===========================================\n");
        }
    }
    if (found == 0)
    {
        printf("\n\nRecord not found\n");
    }
    fclose(fp);
}

void Account_info()
{
    fp = fopen("information.txt", "r");
    printf("Enter your account number :");
    scanf("%d", &Account_n);
    printf("Enter your account PIN :");
    scanf("%d", &pin);
    while (fread(&info, sizeof(struct Account), 1, fp) > 0)
    {
        if (info.id == Account_n && info.pin == pin)
        {
            found = 1;
            printf("\n===========================================\n\n");
            printf("Account Number      : %d\n", info.id);
            printf("Account Holder Name : %s %s\n", info.first_name, info.last_name);
            printf("Phone Number        : %s\n", info.Phone);
            printf("NID Number          : %s\n", info.Phone);
            printf("City                : %s\n", info.city);
            printf("Account PIN         : %d\n", info.pin);
            printf("Address             : %s\n", info.address);
            printf("Total Balance       : %ld\n", balance.Balance[info.id]);
            printf("\n===========================================\n");
        }
    }
    if (found == 0)
    {
        printf("\n\nRecord not found\n\n");
    }
    fclose(fp);
}
// --------------------- Account Delete ---------------------------
void Delete()
{
    struct Account info;
    FILE *fp, *fp1;
    int ac_num, found = 0;
    fp = fopen("information.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Enter the Account number(delete) : ");
    scanf("%d", &ac_num);
    if (fp == NULL)
    {
        fprintf(stderr, "can't open file\n");
        exit(0);
    }
    while (fread(&info, sizeof(struct Account), 1, fp))
    {
        if (info.id == ac_num)
        {

            found = 1;
        }
        else
        {
            fwrite(&info, sizeof(struct Account), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    if (!found)
    {
        printf("\nAccount not found!\n");
    }
    if (found)
    {
        remove("information.txt");
        rename("temp.txt", "information.txt");
        printf("\nAccount deleted succesfully\n");
    }
}

// ===================== Main Function ====================
void main()
{
    clrscr();
    bankhead();
    Home();
}
void bankhead()
{
    printf("\n\n\t\t\t\t\t\t*=========================================*");
    printf("\n\t\t\t\t\t\t|           Welcome to our Bank           |\n");
    printf("\t\t\t\t\t\t*=========================================*\n\n");
}

// --------------- Bank Home --------------------------

void Home()
{
    while (1)
    {
        printf("[1] Login\n");
        printf("[2] Create Account\n");
        printf("[3] Search Account\n");
        printf("[4] Delete Account\n");
        printf("[5] Exit\n");
        printf("\n\nEnter Your option (1 to 5):");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            clrscr();
            login();
            break;
        case 2:
            clrscr();
            Create_Account();
            break;
        case 3:
            Account_info();
            printf("Press any key to continue.......");
            getch();
            clrscr();
            bankhead();
            Home();
            break;
        case 4:
            Delete();
            printf("Press any key to continue.......");
            getch();
            clrscr();
            bankhead();
            Home();
            break;
        case 5:
            remove("information.txt");
            exit(0);
        default:
            clrscr();
            bankhead();
            printf("Enter a valid number!\n\n");
            Home();
        }
    }
    getch();
}
void Ac_Manu(char fn[20], char ln[20])
{
    clrscr();
    printf("\n\n");
    printf("\t\t\t\t\t|========================================|\n");
    printf("\t\t\t\t\t     Welcome to our bank %s %s \n", fn, ln);
    printf("\t\t\t\t\t|========================================|\n\n\n");
    printf("[1] Home\n");
    printf("[2] Loan management\n");
    printf("[3] Withdrawals\n");
    printf("[4] Deposits\n");
    printf("[5] Account details\n");
    printf("[6] Tuition fees\n");
    printf("[7] Transaction history\n");
    printf("[8] Logout\n\n");
}
void login()
{
    FILE *fp;
    struct Account info;
    fp = fopen("information.txt", "r");
    char ans;
    bankhead();
    printf("\nPlease enter your Account number :");
    scanf("%d", &Account_n);
    printf("Enter Your Account PIN : ");
    scanf("%d", &pin);
    while (fread(&info, sizeof(struct Account), 1, fp) > 0)
    {
        if (info.id == Account_n && info.pin == pin)
        {
            found = 1;
            Ac_Manu(info.first_name, info.last_name);
            while (1)
            {
                loc = info.id;
                ac_nm = info.id;
                pin = info.pin;
                printf("Enter your option (1 to 8):");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    clrscr();
                    bankhead();
                    Home();
                    break;
                case 2:
                    Loan_management(loc);
                    printf("Press any key to continue.......");
                    getch();
                    clrscr();
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 3:
                    Withdrawals(loc);
                    printf("Press any key to continue.......");
                    getch();
                    clrscr();
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 4:
                    Deposits(loc);
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 5:
                    Account_detells(ac_nm, pin);
                    printf("Press any key to continue.......");
                    getch();
                    clrscr();
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 6:
                    Tuitio_fees(loc);
                    printf("Press any key to continue.......");
                    getch();
                    clrscr();
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 7:
                    history(loc);
                    printf("\nPress any key to continue.......");
                    getch();
                    clrscr();
                    Ac_Manu(info.first_name, info.last_name);
                    break;
                case 8:
                    clrscr();
                    bankhead();
                    Home();
                    break;
                default:
                    printf("Enter a valid number!\n\n");
                    break;
                }
            }
        }
    }
    if (found == 0)
    {
        printf("\nAccount not found!\n\n");
    }
    fclose(fp);
    getch();
}
