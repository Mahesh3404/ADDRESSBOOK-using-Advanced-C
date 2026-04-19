#include <stdio.h>
#include "file.h"
#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"


void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr; //file pointer declaration
    if((fptr=fopen("contact.csv","w"))==NULL) //opening file in write mode
    {
        fprintf(stderr,"The contact.csv file is not opened\n");//error message if file not opened
        return;
    }
    fprintf(fptr,"%d\n",addressBook->contactCount); //writing contact count to file
    for(int i=0;i<addressBook->contactCount;i++) //loop to write each contact to file
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr); //closing the file

    printf(GREEN"Contacts saved successfully✅\n"RESET);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr; //file pointer declaration
    if((fptr=fopen("contact.csv","r"))==NULL)//opening file in read mode
    {
        fprintf(stderr,"The contact.csv file not opened\n");//error message if file not opened
        return;
    }
    if(fscanf(fptr,"%d\n",&addressBook->contactCount)!=1)//reading contact count from file
    {
        addressBook->contactCount=0;//if no contact count present setting it to 0
        fclose(fptr);//closing the file
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++) //loop to read each contact from file
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);//closing the file
    
}
