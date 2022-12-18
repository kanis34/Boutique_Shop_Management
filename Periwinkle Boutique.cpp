#include <windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>

//File
FILE *fp;

//structures
struct registration_credentials
{
    int id;
    char first_name[50];
    char last_name[50];
    char username[50];
    char user_email[50];
    char password[8];
};

struct login_credentials
{
    char uname[50];
    char password[50];
};

struct product
{
    char attire_user[50]; //women, teenage girl, baby girl
    char usage_time[50]; //summer, winter, party, wedding
    char product_id[50];
    char products_name[50];
    float product_price;
};

struct invoice_product_amount
{
    char products_name[50];
    float product_price;
    int product_quantity;
};

struct customer_invoice
{
    char customer_mobile[20];
    char customer_name[50];
    char date[50];
    int num_of_products;
    struct invoice_product_amount ipa[10];
};


//functions
void welcome_message();
void employee_registration(FILE **fp);
void login_portal_design();
void STORE_OWNER_WELCOME_MODULE();
void STORE_OWNER_TASK_MODULE();
void STORE_MANAGER_WELCOME_MODULE();
void STORE_MANAGER_TASK_MODULE();
void view_registerted_employee(FILE **fp);
void delete_registerted_employee(FILE **file1, FILE **file2);
int update_employee_details(FILE **file1, FILE **file2);
void add_products();
void view_products();
void STORE_EMPLOYEE_WELCOME_MODULE();
void STORE_EMPLOYEE_TASK_MODULE();
void generate_invoice();
void view_Invoice();

//main function
int main()
{
    system("COLOR 5E");
    welcome_message();
    login_portal_design();

    return 0;
}

//function's body
//------------------------------------------void welcome_message()------------------------------------------------
void welcome_message()
{
    printf("\t\t\t\t\t***************WELCOME***************");
    printf("\n");
    printf("\t\t\t\t\t\tPERIWINKLE BOUTIQUE");
    printf("\n\n\n");
}

//----------------------------------------void employee_registration(FILE **fp)------------------------------------
void employee_registration(FILE **fp)
{
    int num,i;
    struct registration_credentials *registr;

    printf("\n");
    printf("\t\tEnter how many number of employees you want to register for: ");
    scanf("%d", &num);

    registr = (registration_credentials*)calloc(num, sizeof(registration_credentials));

    for(i=0; i<num; i++)
    {
        printf("\n");
        printf("\t\tEnter Id: ");
        scanf("%d",&registr[i].id);
        fgetc(stdin);

        printf("\n");
        printf("\t\tEnter First Name: ");
        fgets(registr[i].first_name,50,stdin);
        registr[i].first_name[strlen(registr[i].first_name)-1] = 0;

        printf("\n");
        printf("\t\tEnter Last Name: ");
        fgets(registr[i].last_name,50,stdin);
        registr[i].last_name[strlen(registr[i].last_name)-1] = 0;

        printf("\n");
        printf("\t\tEnter User Name: ");
        fgets(registr[i].username,50,stdin);
        registr[i].username[strlen(registr[i].username)-1] = 0;

        printf("\n");
        printf("\t\tEnter Email: ");
        fgets(registr[i].user_email,50,stdin);
        registr[i].user_email[strlen(registr[i].user_email)-1] = 0;

        printf("\n");
        printf("\t\tEnter Password: ");
        fgets(registr[i].password,50,stdin);
        registr[i].password[strlen(registr[i].password)-1] = 0;

        fwrite(&registr[i], sizeof(struct registration_credentials), 1, *fp);
    }

    if(*fp==NULL)
    {
        printf("File does not exist");
    }

    fclose(*fp);
}

//-----------------------------------------void view_registerted_employee(FILE **fp)----------------------------------------------
void view_registerted_employee(FILE **fp)
{
    struct registration_credentials registr;

    printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\tid\tfirst_name\tlast_name\tusername\tuser_email\tpassword\n");
    printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while(fread(&registr, sizeof(struct registration_credentials), 1, *fp))
    {
        printf("\t\t%d\t  %s\t\t  %s\t\t  %s\t\t %s\t\t%s\n", registr.id, registr.first_name, registr.last_name, registr.username, registr.user_email, registr.password);
    }
    fclose(*fp);
}

//-----------------------------------------------void login_portal_design()--------------------------------------------
void login_portal_design()
{
    FILE *file;
    struct registration_credentials registr;
    struct login_credentials logs;
    char uname[50], pass[8];
    int found =0;

    int i;
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n");
    printf("\t\t\t\t\t|\t       LOGIN  \t\t |");
    printf("\n");
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\n\n");

    printf("\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n");
    printf("\t\t\t\t|\t\t\t\t\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t  1. STORE OWNER\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t\t\t\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t  2. STORE MANAGER\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t\t\t\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t  3. STORE EMPLOYEE\t\t  |");
    printf("\n");
    printf("\t\t\t\t|\t\t\t\t\t\t  |");
    printf("\n");
    printf("\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\n");
    printf("\t\tWant to login as: ");
    scanf("%d",&i);

    if(i == 1)
    {
        fgetc(stdin);
        FILE *fp;
        fp = fopen("owner_login_info.dat","w");

        struct login_credentials owner = {"KANIS","1234"};

        fwrite(&owner, sizeof(login_credentials), 1, fp);
        fclose(fp);

        fp = fopen("owner_login_info.dat","r");

        if(fp==NULL)
        {
            printf("File does not found");
        }
        printf("\n");
        printf("\t\tEnter user name: ");
        fgets(uname,50,stdin);
        uname[strlen(uname)-1] = 0;

        printf("\n");
        printf("\t\tEnter password: ");
        fgets(pass,50,stdin);
        pass[strlen(pass)-1] = 0;

        while(fread(&logs,sizeof(struct login_credentials),1,fp))
        {
            if(!strcmp(uname, logs.uname) && !strcmp(pass, logs.password))
            {
                printf("\nuname = %s and reg_uname = %s", uname, registr.username);
                printf("\npass= %s and reg_pass = %s", pass, registr.password);
                found = 1;
                system("cls");
                welcome_message();
                STORE_OWNER_WELCOME_MODULE();
                STORE_OWNER_TASK_MODULE();
            }
        }
        fclose(fp);
    }
    else if(i == 2)
    {
        FILE *fp;
        fgetc(stdin);
        fp = fopen("manager_register.dat","r");

        if(fp==NULL)
        {
            printf("File does not found");
        }

        printf("\n");
        printf("\t\tEnter user name: ");
        fgets(uname,50,stdin);
        uname[strlen(uname)-1] = 0;

        printf("\n");
        printf("\t\tEnter password: ");
        fgets(pass,50,stdin);
        pass[strlen(pass)-1] = 0;

        while(fread(&registr,sizeof(struct registration_credentials),1,fp))
        {
            if(!strcmp(uname, registr.username) && !strcmp(pass, registr.password))
            {
                printf("\nuname = %s and reg_uname = %s", uname, registr.username);
                printf("\npass= %s and reg_pass = %s", pass, registr.password);
                system("cls");
                welcome_message();
                STORE_MANAGER_WELCOME_MODULE();
                STORE_MANAGER_TASK_MODULE();

            }
        }
        fclose(fp);
    }

    else if(i ==3)
    {
        FILE *fp;
        fgetc(stdin);
        fp = fopen("employee_register.dat","r");

        if(fp==NULL)
        {
            printf("File does not found");
        }
        printf("\n");
        printf("\t\tEnter user name: ");
        fgets(uname,50,stdin);
        uname[strlen(uname)-1] = 0;

        printf("\n");
        printf("\t\tEnter password: ");
        fgets(pass,50,stdin);
        pass[strlen(pass)-1] = 0;

        while(fread(&registr,sizeof(struct registration_credentials),1,fp))
        {
            if(!strcmp(uname, registr.username) && !strcmp(pass, registr.password))
            {
                printf("\nuname = %s and reg_uname = %s", uname, registr.username);
                printf("\npass= %s and reg_pass = %s", pass, registr.password);
                system("cls");
                welcome_message();
                STORE_EMPLOYEE_WELCOME_MODULE();
                STORE_EMPLOYEE_TASK_MODULE();

            }
        }
        fclose(fp);

    }
    else
    {
        printf("Invalid login try!");
    }
}
//------------------------------------------------void STORE_OWNER_WELCOME_MODULE()-----------------------------------------

void STORE_OWNER_WELCOME_MODULE()
{
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n");
    printf("\t\t\t\t\t|      LOGIN AS STORE OWNER\t |");
    printf("\n");
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\n\n");

    printf("\t\t\t\t\t 1. Registration of Manager");
    printf("\n");
    printf("\t\t\t\t\t 2. Delete Manager");
    printf("\n");
    printf("\t\t\t\t\t 3. View Manager Details");
    printf("\n");
    printf("\t\t\t\t\t 4. Update/Modify Manager Details");
    printf("\n");
    printf("\t\t\t\t\t 5. View Employee Details");
    printf("\n");
    printf("\t\t\t\t\t 0. Exit");
    printf("\n");
}

//-----------------------------------------------void STORE_OWNER_TASK_MODULE()--------------------------------------------
void STORE_OWNER_TASK_MODULE()
{
    int option;
    do
    {
        printf("\n\tEnter any option: ");
        scanf("%d",&option);
        if(option==0)
        {
            exit(0);
        }
        else if(option==1)
        {
            system("cls");
            STORE_OWNER_WELCOME_MODULE();
            FILE *mg_reg;
            mg_reg = fopen("manager_register.dat","a+");
            employee_registration(&mg_reg);

        }
        else if(option==2)
        {
            system("cls");
            STORE_OWNER_WELCOME_MODULE();
            FILE *fp1, *fp2;
            fp1 = fopen("manager_register.dat","r");
            fp2 = fopen("manager_register_new.dat","w");
            delete_registerted_employee(&fp1,&fp2);
            remove("manager_register.dat");
            rename("manager_register_new.dat","manager_register.dat");
        }
        else if(option==3)
        {
            system("cls");
            STORE_OWNER_WELCOME_MODULE();
            FILE *fp;
            fp = fopen("manager_register.dat","r");
            view_registerted_employee(&fp);
        }
        else if(option==4)
        {
            FILE *fp1, *fp2;
            struct registration_credentials registr1;
            fp1 = fopen("manager_register.dat","r");
            fp2 = fopen("manager_register_new.dat","w");
            system("cls");
            STORE_OWNER_WELCOME_MODULE();
            int found = update_employee_details(&fp1,&fp2);
            if(found==1)
            {
                fp2 = fopen("manager_register_new.dat","r");
                fp1 = fopen("manager_register.dat","w");

                while(fread(&registr1,sizeof(struct registration_credentials),1,fp2))
                {
                    fwrite(&registr1,sizeof(struct registration_credentials),1,fp1);
                }

                fclose(fp1);
                fclose(fp2);
            }

            if(found==0)
            {
                printf("Id doesn't found");
            }
        }
        else if(option==5)
        {
            system("cls");
            STORE_OWNER_WELCOME_MODULE();
            FILE *fp;
            fp = fopen("employee_register.dat","r");
            view_registerted_employee(&fp);
        }
    }
    while(option!=0);
}

//-------------------------------void STORE_MANAGER_WELCOME_MODULE()--------------------------------------------------
void STORE_MANAGER_WELCOME_MODULE()
{
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n");
    printf("\t\t\t\t\t|      LOGIN AS STORE MANAGER\t |");
    printf("\n");
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\n\n");

    printf("\t\t\t\t\t 1. Registration of Employee");
    printf("\n");
    printf("\t\t\t\t\t 2. Delete Employee");
    printf("\n");
    printf("\t\t\t\t\t 3. View Employee Details");
    printf("\n");
    printf("\t\t\t\t\t 4. Update/Modify Employee Details");
    printf("\n");
    printf("\t\t\t\t\t 5. Add Products");
    printf("\n");
    printf("\t\t\t\t\t 6. View Product");
    printf("\n");
    printf("\t\t\t\t\t 0. Exit");
    printf("\n");
}

//------------------------------------------------void STORE_MANAGER_TASK_MODULE()--------------------------------------------
void STORE_MANAGER_TASK_MODULE()
{
    int option;
    do
    {
        printf("\n\tEnter any option: ");
        scanf("%d",&option);
        if(option==0)
        {
            exit(0);
        }
        else if(option==1)
        {
            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            FILE *emp_reg;
            emp_reg = fopen("employee_register.dat","a+");
            employee_registration(&emp_reg);
        }
        else if(option==2)
        {
            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            FILE *fp1, *fp2;
            fp1 = fopen("employee_register.dat","r");
            fp2= fopen("employee_register_new.dat","w");
            delete_registerted_employee(&fp1,&fp2);
            remove("employee_register.dat");
            rename("employee_register_new.dat","employee_register.dat");
        }
        else if(option==3)
        {
            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            FILE *fp;
            fp = fopen("employee_register.dat","r");
            view_registerted_employee(&fp);
        }
        else if(option==4)
        {
            FILE *fp1, *fp2;
            struct registration_credentials registr1;
            fp1 = fopen("employee_register.dat","r");
            fp2 = fopen("employee_register_new.dat","w");

            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            int found = update_employee_details(&fp1,&fp2);
            if(found==1)
            {
                fp2 = fopen("employee_register_new.dat","r");
                fp1 = fopen("employee_register.dat","w");

                while(fread(&registr1,sizeof(struct registration_credentials),1,fp2))
                {
                    fwrite(&registr1,sizeof(struct registration_credentials),1,fp1);
                }

                fclose(fp1);
                fclose(fp2);
            }

            if(found==0)
            {
                printf("Id doesn't found");
            }
        }
        else if(option==5)
        {
            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            add_products();
        }
        else if(option==6)
        {
            system("cls");
            STORE_MANAGER_WELCOME_MODULE();
            view_products();
        }

        else
        {
            printf("\t\t\tPlease enter a valid option!\n");
        }
    }
    while(option!=0);
}

//-----------------------------------void delete_registerted_employee(FILE **file1, FILE **file2)---------------------
void delete_registerted_employee(FILE **file1, FILE **file2)
{
    struct registration_credentials registr;
    char uname[50], pass[8];
    int found = 0;

    if(file1==NULL)
    {
        printf("File does not found");
    }

    fgetc(stdin);
    printf("\n");
    printf("\tEnter user name: ");
    fgets(uname,50,stdin);
    uname[strlen(uname)-1] = 0;

    printf("\n");
    printf("\tEnter password: ");
    fgets(pass,50,stdin);
    pass[strlen(pass)-1] = 0;


    while(fread(&registr,sizeof(struct registration_credentials),1,*file1))
    {
        if(strcmp(uname, registr.username)==0 && strcmp(pass, registr.password)==0)
        {
            found = 1;
        }
        else
        {
            fwrite(&registr,sizeof(struct registration_credentials),1,*file2);
        }

    }
    if(found == 1)
    {
        printf("\n\t\t\tRecord deleted successfully");
    }
    else
    {
        printf("\n\t\t\tSuch userName doesn't exist.");
    }

    fclose(*file1);
    fclose(*file2);
}

//-----------------------------int update_employee_details(FILE **file1, FILE **file2)--------------------------------
int update_employee_details(FILE **file1, FILE **file2)
{
    struct registration_credentials registr1;

    int empId, found = 0;
    char uname[50];
    char consent1;

    if(*file1==NULL)
    {
        printf("File does not found");
    }

    fgetc(stdin);

    printf("\n");
    printf("\tEnter id: ");
    scanf("%d",&empId);
    fgetc(stdin);


    while(fread(&registr1,sizeof(struct registration_credentials),1,*file1))
    {
        if(registr1.id == empId)
        {
            found = 1;
            printf("\t\tUpdate email?(press 'e')\n");
            printf("\t\tUpdate password?(press 'p')\n");
            printf("\t\tUpdate email & password?(press 'b')\n\n");
            printf("\t\t   Enter you choice: ");
            scanf("%c",&consent1);

            if(consent1 == 'e')
            {
                fgetc(stdin);
                printf("\n");
                printf("\t\tUpdate Email: ");
                fgets(registr1.user_email,50,stdin);
                registr1.user_email[strlen(registr1.user_email)-1] = 0;
            }

            else if(consent1 == 'p')
            {
                fgetc(stdin);
                printf("\n");
                printf("\t\tUpdate Password: ");
                fgets(registr1.password,50,stdin);
                registr1.password[strlen(registr1.password)-1] = 0;
            }
            else
            {
                fgetc(stdin);
                printf("\n");
                printf("\t\tUpdate Email: ");
                fgets(registr1.user_email,50,stdin);
                registr1.user_email[strlen(registr1.user_email)-1] = 0;

                printf("\t\tUpdate Password: ");
                fgets(registr1.password,50,stdin);
                registr1.password[strlen(registr1.password)-1] = 0;
            }
        }
        fwrite(&registr1,sizeof(struct registration_credentials),1,*file2);
    }

    fclose(*file1);
    fclose(*file2);
    return found;
}

//------------------------------------------void add_products()-------------------------------
void add_products()
{
    struct product *prod;
    int num,i;

    FILE *fp;
    fp = fopen("product_database.dat","a+");

    printf("\n");
    printf("\t\tHow many products you want to enter: ");
    scanf("%d", &num);

    prod = (product*)calloc(num, sizeof(product));

    for(i=0; i<num; i++)
    {
        printf("\n");
        fgetc(stdin);
        printf("\t\tEnter Attire User: ");
        fgets(prod[i].attire_user,50,stdin);
        prod[i].attire_user[strlen(prod[i].attire_user)-1]=0;

        printf("\n");
        printf("\t\tEnter Usage Time: ");
        fgets(prod[i].usage_time, 50, stdin);
        prod[i].usage_time[strlen(prod[i].usage_time)-1]=0;

        printf("\n");
        printf("\t\tEnter Product Id: ");
        fgets(prod[i].product_id,50,stdin);
        prod[i].product_id[strlen(prod[i].product_id)-1]=0;

        printf("\n");
        printf("\t\tEnter Product Name: ");
        fgets(prod[i].products_name, 50, stdin);
        prod[i].products_name[strlen(prod[i].products_name)-1]=0;

        printf("\n");
        printf("\t\tEnter Product Price: ");
        scanf("%f",&prod[i].product_price);

        fwrite(&prod[i], sizeof(struct product), 1, fp);
    }

    printf("\n\t\t\tProduct added successfully!");
    fclose(fp);
}

void view_products()
{
    struct product prod;
    int i;
    FILE *fp;
    fp = fopen("product_database.dat","r");
    printf("\n\n\t\t Attire_User\tUsage_Time\tProduct_Id\tProduct_Name\tProduct_Price\n");
    printf("\t\t----------------------------------------------------------------------------------------------------");
    while(fread(&prod, sizeof(struct product),1, fp))
    {
        printf("\n\t\t%s\t\t%s\t\t%s\t\t%s\t\t %f\n", prod.attire_user, prod.usage_time, prod.product_id,prod.products_name, prod.product_price);
    }
    fclose(fp);
}

//----------------------------------void STORE_EMPLOYEE_WELCOME_MODULE()----------------------------------
void STORE_EMPLOYEE_WELCOME_MODULE()
{
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n");
    printf("\t\t\t\t\t|      LOGIN AS STORE EMPLOYEE\t |");
    printf("\n");
    printf("\t\t\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\n\n");

    printf("\t\t\t\t\t 1. Generate Invoice");
    printf("\n");
    printf("\t\t\t\t\t 2. Show Invoices");
    printf("\n");
    printf("\t\t\t\t\t 0. Exit");
    printf("\n");
}

void STORE_EMPLOYEE_TASK_MODULE()
{
    int option;
    do
    {
        printf("\n\tEnter any option: ");
        scanf("%d",&option);
        if(option==0)
        {
            exit(0);
        }
        else if(option==1)
        {
            system("cls");
            welcome_message();
            STORE_EMPLOYEE_WELCOME_MODULE();
            generate_invoice();
        }
        else if(option==2)
        {
            system("cls");
            welcome_message();
            STORE_EMPLOYEE_WELCOME_MODULE();
            view_Invoice();
        }
    }
    while(option!=0);
}

void generate_invoice()
{
    struct customer_invoice invoice;
    struct product prod_strct;
    FILE *fp, *prod_file;
    int found = 0;
    int num,num_of_products, i;
    float total = 0.0, discount = 0.0;
    char check_mobile_no[20];

    fp = fopen("invoices.dat","a");

    fgetc(stdin);
    printf("\n");
    printf("\t\tEnter Customer Mobile no: ");  //char customer_mobile[20]
    fgets(invoice.customer_mobile, 20, stdin);
    invoice.customer_mobile[strlen(invoice.customer_mobile)-1]=0;

    printf("\n");
    printf("\t\tEnter Customer Name: ");  //char customer_name[50]
    fgets(invoice.customer_name, 50, stdin);
    invoice.customer_name[strlen(invoice.customer_name)-1]=0;

    strcpy(invoice.date,__DATE__);  //char date[50]

    printf("\t\tEnter how many products do you want: ");
    scanf("%d", &num);
    invoice.num_of_products = num;

    for(i=0; i<num; i++)
    {
        char prod_id[50] = {};
        printf("\n\t\tEnter product id to check: ");
        scanf("%s",prod_id);

        prod_file = fopen("product_database.dat","r");
        while(fread(&prod_strct, sizeof(struct product),1, prod_file))
        {
            if(strcmp(prod_id,prod_strct.product_id)==0)
            {
                found = 1;
                sscanf(prod_strct.products_name, "%s", invoice.ipa[i].products_name);
                printf("\n\t\tProduct name: %s", invoice.ipa[i].products_name);
                invoice.ipa[i].product_price = prod_strct.product_price;
                printf("\n\t\tProduct price: %f", invoice.ipa[i].product_price);

                printf("\n");
                printf("\t\tEnter Product quantity: ");
                scanf("%d",&invoice.ipa[i].product_quantity);
            }
        }
        total += invoice.ipa[i].product_price * invoice.ipa[i].product_quantity;

        fwrite(&invoice, sizeof(struct customer_invoice),1, fp);

    }
    fclose(prod_file);
    printf("\n\t\tTotal is: %f", total);
    fclose(fp);


}

void view_Invoice()
{
    struct customer_invoice invoice;
    FILE *fp, * check_invoice_file;
    fp = fopen("invoices.dat","r");
    float total = 0.0;

    while(fread(&invoice, sizeof(struct customer_invoice), 1, fp))
    {
        total = 0.0;
        printf("\n");
        printf("\n\t\t*******************************************************************");
        printf("\n\t\tDate: %s",invoice.date);
        printf("\n\t\tCustomer Name: %s",invoice.customer_name);
        printf("\n\t\tMobile No: %s",invoice.customer_mobile);
        printf("\n");
        printf("\t\t*******************************************************************\n");
        for(int i=0; i<invoice.num_of_products; i++)
        {
            printf("\n\t\t\t%d. Product Name\t\t=%s", i+1, invoice.ipa[i].products_name);
            printf("\n\t\t\t   Product Price   \t=%f", invoice.ipa[i].product_price);
            printf("\n\t\t\t   Product Quantity   \t=%d", invoice.ipa[i].product_quantity);
            total+=invoice.ipa[i].product_price * invoice.ipa[i].product_quantity;
        }
        printf("\n\t\t\t-----------------------------------------");
        printf("\n\t\t\t   Total is  \t\t=%f",total);
    }

    fclose(fp);


}



