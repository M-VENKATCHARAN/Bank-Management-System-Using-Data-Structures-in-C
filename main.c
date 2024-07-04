#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<ctype.h>

typedef struct ACCOUNT
{
    int account_number;
    char acct_holder_name[50];
    float balance;
    struct ACCOUNT* l;
    struct ACCOUNT* r;
} acct;

int acct_number()
{
    srand(time(NULL)); // Seed the random number generator only once at the beginning
  int acctnum = rand() % 900000 + 100000;
    return acctnum;
}

acct* check(acct *head, int key) 
{

  acct *cur = head;
  while (cur != NULL) 
  {
    if (cur->account_number == key)
    {
       return cur;
    } 
    else 
    {
      cur = cur->r;
    }
  }

  return NULL;
}


void insert(acct** root, acct* temp)
{
    acct* new_acc = (acct*)malloc(sizeof(acct));
    new_acc->account_number = temp->account_number;
    strcpy(new_acc->acct_holder_name, temp->acct_holder_name);  // Copy the account holder name
    new_acc->balance = temp->balance;
    new_acc->l = NULL;
    new_acc->r = NULL;

    if (*root == NULL)
    {
        *root = new_acc;
    }
    else
    {
        acct* cur = *root;
        while (cur != NULL)
        {
            if (temp->account_number < cur->account_number)
            {
                if (cur->l == NULL)
                {
                    cur->l = new_acc;
                    new_acc->r = cur;
                    break;
                }
                cur = cur->l;
            }
            else
            {
                if (cur->r == NULL)
                {
                    cur->r = new_acc;
                    new_acc->l = cur;
                    break;
                }
                cur = cur->r;
            }
        }
    }
}

acct* create_acct(acct* root)
{
    acct* temp = (acct*)malloc(sizeof(acct));
    if (temp == NULL)
    {
        printf("Please try to create the account again\n");
        return root;
    }

    temp->balance = 0.0;
    temp->l = NULL;
    temp->r = NULL;

    printf("Enter Your Name: ");
    scanf("%s", temp->acct_holder_name);
    for(int i=0;i<strlen(temp->acct_holder_name);i++)
    {
        if(!(isalpha(temp->acct_holder_name[i])))
            {
                printf(" Enter a valid Name: ");
                scanf("%s",temp->acct_holder_name);
                i=0;
                continue;
            }
    }   

    // Generate a unique account number
    temp->account_number = acct_number();

    // Use the corrected insert function to maintain order
    insert(&root, temp);

    printf("Thank you for creating an account\n");
    printf("Name: %s\nAccount number: %d\nAccount has been created\n", temp->acct_holder_name, temp->account_number);

    return root;
}




void deposit(acct* root, int acct_num, float money)
{
    acct* cur = check(root, acct_num);
    if (cur != NULL)
    {
        cur->balance += money;
        printf("Successfully added %.2f amount in the account number %d\n", money, acct_num);
    }
    else
    {
        printf("Could not find the bank account. Please try again later.\n");
    }
}

void check_balance(acct* root, int acct_num)
{
    acct* cur = check(root, acct_num);
    if (cur != NULL)
    {
        printf("Account holder name: %s\nAccount number: %d\nBalance: %.2f\n", cur->acct_holder_name, cur->account_number, cur->balance);
    }
    else
    {
        printf("Could not find the account. Please try again.\n");
    }
}

void delete_account(acct* root, int acct_num) 
{
    
  acct*node=check(root,acct_num);

  if(node!=NULL)
  {
  if (node->l == NULL) {
    root = node->r;
    if (root != NULL) {
      root->l = NULL;
    }
  } else {
    
    node->l->r = node->r;
    if (node->r != NULL) {
      node->r->l = node->l;
    }
  }

  free(node);
    
        printf("Account number %d has been deleted.\n", acct_num);
    } 
    else 
    {
        printf("Could not find the account. Please try again.\n");
    }
}

int main()
{
    
    int user_acct_num = 0;
    int user_acct_num1 = 0, user_acct_num2 = 0;
    float amt = 0;
    acct* root = NULL;

    while (1)
    {
        int ch;
        printf("\tWelcome to our Bank\nWe request you to choose one of the following functions\n\n");
        printf("1. Create\n2. Deposit\n3. Check balance\n4. Delete account\n5. Exit\n \n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch)
        {
        case 1:
            root = create_acct(root);
            break;
        case 2:
            printf("Enter your account number: ");
            scanf("%d", &user_acct_num);
            printf("Enter the amount to deposit in the account: ");
            scanf("%f", &amt);
            deposit(root, user_acct_num, amt);
            break;
        case 3:
            printf("Enter your account number: ");
            scanf("%d", &user_acct_num);
            check_balance(root, user_acct_num);
            break;
       
        case 4:
            printf("Enter your account number: ");
            scanf("%d", &user_acct_num);
            delete_account(root,user_acct_num);
            break;
        case 5:
            printf("Thank you for visiting our bank. Have a nice day.\n");
            exit(0);
        default:
            printf("Please try again.\n");
            continue;
        }
    }
    return 0;
}