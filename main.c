/*
PROJECT 1 : ADDRESS BOOK
Name : T Mahesh
Date : 12-12-2025
Description about the project :
    Address Book Project is a C-based console application to manage contacts with details like Name, Phone Number, Email ID. 
It allows user to Create, Search, Edit, Delete, Save and Display contacts with proper validatioin for Name, Phone Number and Email ID.
Below are the functionalities about this project :
Create Contact : Add new contacts with Name, Phone Number and Email ID.
                 This supports creating multiple contacts with same name and unique Phone Number and Email ID.
List Contacts : Display all contacts in a formatted table.
                It sorts contacts alphabetically by name.
Search Contacts : Search for contacts by Name, Phone number and Email ID.
                  It displays all matching contact. Including multiple contacts also.
Edit Contact : Modify Name, Phone number, Email ID or all fields of contact
               It supports selecting the contact which you want to edit in the case of multiple contacts with same name.
Delete Contact : Remove contact by Name, Phone number or Email ID.
                 It supports choosing the phone number or Email ID for deletion in case of maultiple contacts with same name.
                 It automatically handles shifting of contacts in the list after deletion.
Save Contacts : Write all contacts to a file "contacts.csv" in CSV format for storing.
                It includes contact count and overwrites existing file content.
Load Contacts : Read saved contacts from "contacts.csv" at program starting.
                It restores the contact list for use.
*/
#include <stdio.h>
#include "contact.h"
#define BLUE    "\033[1;34m"
#define SPL     "\033[1;35m"
#define DIS     "\033[1;36m"
#define RESET   "\033[0m"


int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf(DIS"1. Create contact\n"RESET);
        printf(SPL"2. Search contact\n"RESET);
        printf(DIS"3. Edit contact\n"RESET);
        printf(SPL"4. Delete contact\n"RESET);
        printf(DIS"5. List all contacts\n"RESET);
    	printf(SPL"6. Save contacts\n"RESET);		
        printf(DIS"7. Exit\n"RESET);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                int sortChoice;
                printf(BLUE"Sort contacts by:"RESET"\n1. Name\n2. Phone Number\n3. Email ID\nEnter your choice: ");
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting....");
                return 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
