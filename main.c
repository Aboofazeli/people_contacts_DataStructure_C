//
//  main.c
//  DataStructure
//
//  Created by alireza aboofazeli on 2017-11-13.
//  Copyright © 2017 Ali Reza Aboofazeli. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void clearInput(void);
void addNewcontact(void);
void listAll(void);
void deletecontact(void);
void modifycontact(void);
int searchcontact(void);
int prompt(void);
int findnum (int);

typedef struct contact {
    int number;
    char name[20];
    char phone[15];
    char email[20];
    struct contact *next;
    
} Contact;
Contact *start,*currnode,*newnode;
int cnum = 0;
int main()
{
    FILE *datafile;
    char *filename = "contactdatabase.dat";
    char ch;
    start = NULL;
    datafile = fopen(filename,"r");
    
    if(datafile)
    {
        start = (struct contact *)malloc(sizeof(struct contact));
        
        currnode = start;
        while(1)
        {
            newnode = (struct contact *)malloc(sizeof(struct contact));
            fread(currnode,sizeof(struct contact),1,datafile);
            if(currnode->next == NULL)
                break;
            currnode->next = newnode;
            currnode = newnode;
        }
        fclose(datafile);
        cnum = currnode->number;
        
    }
    
    do
    {
        fflush(stdin);
        printf("\nWelcome To The Contact Database\n");
        printf("-- -----------------------------\n");
        printf("1 - Add a new contact\n");
        printf("2 - Delete contact\n");
        printf("3 - List all contacts\n");
        printf("4 - Modify contact\n");
        printf("5 - Find a contact by name\n");
        printf("-- -----------------------------\n");
        printf("Q - Save and quit\n");
        printf("\tYour choice:\n");
        scanf(" %c",&ch);
        
        switch(ch)
        {
            case '1':
                printf("Add a new contact\n");
                fflush(stdin);
                addNewcontact();
                break;
            case '2':
                printf("Delete a contact\n");
                deletecontact();
                break;
            case '3':
                printf("List all contacts\n");
                listAll();
                break;
            case '4':
                printf("Modify a contact\n");
                modifycontact();
                break;
            case '5':
                printf("Find a contact by name\n");
                searchcontact();
                break;
            case 'Q':
                printf("Save and quit\n");
            default:
                break;
        }
    }
    while(ch != 'Q');
    
    currnode = start;
    
    if(currnode == NULL)
        return(0);
    
    datafile = fopen(filename,"w");
    
    if(datafile == NULL)
    {
        printf("Error writing to %s\n",filename);
        return(1);
    }
    
    while(currnode != NULL)
    {
        fwrite(currnode,sizeof(struct contact),1,datafile);
        currnode = currnode->next;
    }
    fclose(datafile);
    return(0);
}

void addNewcontact(void)
{
    newnode = (struct contact *)malloc(sizeof(struct contact));
    
    if(start==NULL)
        start = currnode = newnode;
    
    else
    {
        currnode = start;
        
        while(currnode->next != NULL)currnode = currnode->next;
        
        currnode->next = newnode;
        currnode = newnode;
    }
   
    cnum++;
    printf("%27s: %5i\n","contact number",cnum);
    currnode->number = cnum;
    
    printf("%27s: ","Enter contact name");
    scanf("%s",currnode->name);
    printf("%27s: ","Enter contact Phone number");
    scanf("%s",currnode->phone);
    printf("%27s: ","Enter contact email");
    scanf("%s",currnode->email);
    printf("contact added!");
    
  
    currnode->next = NULL;
}

void listAll(void)
{
    if(start==NULL)
        puts("There are no contacts to display!\n");
    
    else
    {
        printf("%6s %-20s %-15s %-15s\n","Acct#","Name","Phone","Email\n");
        printf("------ -------------------- ------------- -------------------\n");
        
        currnode=start;
        do
        {
            
            printf("%6d: %-20s %-15s %-20s\n",\
                   currnode->number,\
                   currnode->name,\
                   currnode->phone,\
                   currnode->email);
           
        }
        
        while((currnode=currnode->next) != NULL);
    }
}

void deletecontact(void)
{
    int accnum;
    struct contact *prev;
    if(start==NULL)
    {
        printf("There are no contacts to delete!\n");
        return;
    }
    
    listAll();
    printf("Enter contact account number to delete: \n");
    scanf("%d",&accnum);
    currnode = start;
    
    while(currnode != NULL)
    {
        if(currnode->number == accnum)
        {
            if(currnode == start)
                start=currnode->next;
            else
                prev->next = currnode->next;
            
            free(currnode);
            printf("contact %d deleted!\n",accnum);
            return;
        }
        
        else
        {
            prev = currnode;
            currnode = currnode->next;
        }
    }
    printf("contact %d not found!\n",accnum);
}

void modifycontact(void)
{
    int accnum, result;
    if(start==NULL)
    {
        printf("There are no contacts to modify!\n");
        return;
    }
    
    listAll();
    printf("Enter contact account number to modify or change: \n");
    scanf("%d",&accnum);
    result = findnum(accnum);
    
    if( result >0 ){
        printf("Contact %d:\n",currnode->number);
        printf("Name: %s\n",currnode->name);
        if(prompt())
            scanf(" %s",currnode->name);
        printf("Phone: %s\n",currnode->phone);
        if(prompt())
            scanf(" %s",currnode->phone);
        printf("Email: %s\n",currnode->email);
        if(prompt())
            scanf(" %s",currnode->email);
        return;
    }
    printf("contact %d was not found!\n",accnum);
}

int findnum (int num)
{
    int accnum;
    accnum = num;
    currnode = start;
    while(currnode != NULL)
    {
        
        if(currnode->number == accnum)
        {
            return 1;
        }
        
        else
        {
            currnode = currnode->next;
        }
    }
    return -1;
}

int searchcontact(void)
{
    char buff[20];
    
    if(start==NULL)
    {
        printf("There are no contacts to find!\n");
        return 1;
    }
    
    printf("Enter contact name: ");
    fflush(stdin);
    scanf("%s",buff);
    
    currnode = start;
    while(currnode != NULL)
    {
        if( strcmp(currnode->name, buff) == 0 )
        {
            printf("%6s %-20s %-15s %-15s\n","Acct#","Name","Phone","Email");
           
            printf("%6d: %-20s %-15s %-20s\n",\
                   currnode->number,\
                   currnode->name,\
                   currnode->phone,\
                   currnode->email);
            
            
            return 0;
        }
        else
        {
            currnode = currnode->next;
        }
    }
    printf("contact %s was not found!\n",buff);
    return 1;
}

int prompt(void)
{
    char ch;
    fflush(stdin);
    printf("Update? (Y to update any other key to not)");
    scanf(" %c",&ch);
    
    fflush(stdin);
    if(ch == 'Y')
    {
        printf("Enter new value: ");
        return(1);
    }
    else
        return(0);
}
