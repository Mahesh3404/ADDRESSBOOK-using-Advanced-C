#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validate.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m" 
#define SPL     "\033[1;35m"
#define RESET   "\033[0m"

void listContacts(AddressBook *addressBook,int sortChoice) 
{
    // Sort contacts based on the chosen criteria
    if (sortChoice == 1) {
        // Sort by Name
        for (int i = 0; i < addressBook->contactCount - 1; i++) {
            for (int j = i + 1; j < addressBook->contactCount; j++) {
                if (strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    }
    else if (sortChoice == 2) {
        // Sort by Phone Number
        for (int i = 0; i < addressBook->contactCount - 1; i++) {
            for (int j = i + 1; j < addressBook->contactCount; j++) {
                if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0) {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    } 
    else if (sortChoice == 3) {
        // Sort by Email ID
        for (int i = 0; i < addressBook->contactCount - 1; i++) {
            for (int j = i + 1; j < addressBook->contactCount; j++) {
                if (strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email) > 0) {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    }
    getchar();
    if(addressBook->contactCount==0)//if no contacts present in address book printing message
    {
        printf(GREEN"No contacts to display.The address book is empty.\n"RESET);
        return;
    }
    printf(BLUE"%-3s%15.12s%20.12s%20.12s\n"RESET,"S.No","Contact Name","Phone Number","Email ID");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%3d. ",i+1);
        printf("  %-19s ",addressBook->contacts[i].name);
        printf("%-18s ",addressBook->contacts[i].phone);
        printf("%-20s",addressBook->contacts[i].email);
        printf("\n");
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file    
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];                       //declaration of name variable
    getchar();
    do                                   //loop to validate name input
    {   
        printf("Enter Name: ");          //prompt message for name
        scanf("%[^\n]",name);            //read name from user
        getchar();                       //to read new line character
        //validate_name(name);             //function call to validate name
        if(!validate_name(name))
        {
            //printing invalid name message
            printf(RED"Invalid Name! Please enter name with alphabets\n"RESET);
        }
    }while(!validate_name(name));        //continue loop until valid name is entered
    
    char phone[15];                      //declaration of phone variable
    int ret;
    do
    { 
        printf("Enter Phone Number: ");  //prompt message for phone number
        scanf("%[^\n]",phone);           //read phone number from user
        getchar();    
        ret=validate_phone(phone);           //to read new line character
        if(!ret)       //function call to validate phone number
        {
            //printing invalid message
            printf(RED"Invalid Phone number! Please enter 10 digit phone number\n"RESET);
        }
        else
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,phone)==0)
                {
                    printf(YELLOW"Phone number already exists! Please enter a unique phone number\n"RESET);
                    ret=0;
                }
            }
        }
    }while(!ret);      //continue loop until valid phone number is entered

    char mail[50];                      //declaration of email variable
    int res;
    do
    {
        printf("Enter mail Id: ");      //prompt message for email id
        scanf("%[^\n]",mail);           //read email id from user
        getchar();                       //to read new line character
        res=validate_mail(mail);           //function call to validate email id
        if(res==0)
        {
            //printing invalid message 
            printf(RED"Invalid Email ID! Enter a valid mail Id!\n"RESET);
        }
        else
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].email,mail)==0)
                {
                    printf(YELLOW"Email ID already exists! Please enter a unique email ID\n"RESET);
                    res=0;
                }
            }
        }
    } while(res==0);     //continue loop until valid email is entered
    printf(GREEN"Contact Created Successfully✅"RESET);
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
    addressBook->contactCount++;          //Increment of contact count after adding contact
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int num;    //variable declaration for choice
    char searchName[50];    //variable declaration for search name
    char searchPhone[15];   //variable declaration for search phone number
    char searchMail[50];    //variable declaration for search mail ID
    do
    {
        printf(SPL"1. Name\n2. Phone Number\n3. Email ID\n4. Exit to main menu\n"RESET);     //displaying search options
        printf("Enter the serial number by which you want to search the contact: ");    //prompt message for choice
        scanf("%d",&num);   //reading choice from user
        getchar();      //to read new line character
        switch (num)    //switch case for choice
        {
            //search by name
            case 1:
            {
                do
                {
                    printf("Enter the name to be searched: ");  //prompt message for search name
                    scanf("%[^\n]",searchName);      //reading search name from user
                    getchar();      //to read new line
                    //validate search name
                    if(validate_name(searchName))    
                    {
                        int flag=0,ind=1;
                        //Outer Loop to search the contact 
                        for(int i=0;i<addressBook->contactCount;i++)    
                        {
                            if(strcmp(searchName,addressBook->contacts[i].name)==0)
                            {
                                printf(GREEN"Contact %d\n"RESET,ind++);
                                printf("Name: %s\n",addressBook->contacts[i].name);
                                printf("Phone Number: %s\n",addressBook->contacts[i].phone);
                                printf("Email Address: %s\n",addressBook->contacts[i].email);
                                flag++;
                            }
                        }
                        //if contact not found print
                        if(flag==0)
                        {
                            printf(GREEN"No contact Found\n"RESET);
                        }
                    }
                    //if name is not valid
                    else
                    {
                        //printing invalid name message
                        printf(RED"Invalid Name! please enter name with alphabets\n"RESET);
                    }
                }while(!validate_name(searchName));   //continue loop until valid name is entered
            }
            break;
            //search by phone number
            case 2:
            {
                do
                {
                    printf("Enter the Phone Number to be searched: "); //prompt message for search Phone number
                    scanf("%[^\n]",searchPhone); //Reading input from user
                    getchar();  // to read a new line character
                    validate_phone(searchPhone);  //Phone number validation
                    if(validate_phone(searchPhone))
                    {
                        int flag=0,ret;
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(addressBook->contacts[i].phone,searchPhone)==0) //comparing phone number in the contact list
                            {
                                flag=1; // if found changing flag
                                ret=i; // storing index of contact
                            }
                        }
                        if(flag==1)
                        {
                            printf(GREEN"Contact Found: \n"RESET); //printing contact details
                            printf("Name: %s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                        }
                        if(flag==0) //if no contact found
                        {
                            printf(GREEN"No Contact Found in the contact list\n"RESET);
                        }
                    }
                    // if entered phone number is not valid printing error message
                    else
                    {
                        printf(RED"Invalid Phone Number! Please enter 10 digit phone number\n"RESET);
                    }
                } while (!validate_phone(searchPhone)); //continue loop untill phone number is entered
            }
            break;
            //search by mail ID
            case 3:
            {
                int m;
                do
                {
                    printf("Enter the Email ID to be searched: "); //prompt message for search email id
                    scanf("%[^\n]",searchMail);  //to read input from user
                    getchar(); // to read new line character
                    m=validate_mail(searchMail); //validate email
                    if(m)
                    {
                        int flag=0,ret;
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(addressBook->contacts[i].email,searchMail)==0) // comparing user mail with contact list
                            {
                                flag=1; //if found change flag
                                ret=i; //store index of contact
                            }
                        }
                        if(flag==1) //if contact present in list
                        {
                            printf(GREEN"Contact Found: \n"RESET); //printing contact details
                            printf("Name: %s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                        }
                        if(flag==0) //if contact not found
                        {
                            printf(GREEN"Contact Not Found with this Phone Number\n"RESET);  
                        }
                    }
                    //if entered email id is not valid printing error message
                    else
                    {
                        printf(RED"Invalid Email ID! Please enter a valid email ID\n"RESET);
                    }
                }while(!m); //continue loop until mail ID is entered
            }
            break;
            //Exit from search
            case 4:
            {
                break;
            }
            //If invalid choice is entered printing error message
            default:
            {
                printf(YELLOW"Invalid Choice! Please enter a valid choice\n"RESET);
            }
        }
    }while(num!=4); //continue loop until user wants to exit
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    do
    {
        printf(SPL"Edit By:\n1. Name:\n2. Phone Number:\n3. Email Id:\n4. Exit to main menu\n"RESET);
        printf("Enter the choice you want to edit: ");//prompt message for choosing the edit menu
        scanf("%d",&choice); // read input from user
        getchar(); // to read a new line character
        switch (choice)
        {
            //Edit by name
            case 1:
            {
                char oldName[50]; //Declaration of saerching name
                char newName[50]; //Declaration of editing new name
                int flag=0;
                do
                {
                    printf("Enter the name of the contact you want to edit: ");
                    scanf("%[^\n]",oldName); //Read the name from user to search in list
                    getchar(); //to read new line character
                    if(validate_name(oldName)) // validating searching name
                    {
                        //Run a loop upto contactCount
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            //Comparing searched name in the contact list
                            if(strcmp(oldName,addressBook->contacts[i].name)==0)
                            {
                                //incrementing flag variable
                                flag++;
                            }
                        }
                    }
                    else
                    {
                        printf(RED"Invalid Name! please enter name with alphabets\n"RESET);
                    }
                }while(!validate_name(oldName));//validating seached name
                //if no contact found in list printing message
                if(flag==0)
                {
                    printf(GREEN"No contact found with this name in the contact list\n"RESET);
                    break;
                }
                //Only if one contact found
                if(flag==1)
                {
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        //Comparing searched name in contact list
                        if(strcmp(oldName,addressBook->contacts[i].name)==0)
                        {
                            printf(GREEN"Contact found:\n"RESET);
                            printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            break;
                        }
                    }
                    do
                    {
                        printf("Enter the New Name: ");
                        scanf("%[^\n]",newName);//Read editing name from user
                        getchar(); // to read a new line character
                        if(validate_name(newName)) // Validating new name
                        {
                            //Run a loop upto contactCount
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                //Compare old name in contact list
                                if(strcmp(oldName,addressBook->contacts[i].name)==0)
                                {
                                    //editing new name in the place of old name
                                    strcpy(addressBook->contacts[i].name,newName);
                                    printf(GREEN"Contact Edited Successfully✅\n"RESET);
                                    break;
                                }
                            }
                            break;
                        }
                        //New name is not valid printing error message
                        else
                        {
                            printf(RED"Invalid Name! please enter name with alphabets\n"RESET);
                        }
                    }while(!validate_name(newName));//Loop continues until new name is vaidated
                }
                //Contact list having more than one contacts with searched name
                else
                {
                    printf(GREEN"Multiple contacts found with this name.\n"RESET"Please specify the index of the contact to edit\n");
                    int match[100];//Temporary array to duplicates of contacts
                    int count=0; //Counting duplicates
                    //Loop up to contact count
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        //comparing searched name in contact list
                        if(strcmp(oldName,addressBook->contacts[i].name)==0)
                        {
                            //printing duplicate contacts
                            printf("%d. ",count+1);
                            printf("Name :%s |",addressBook->contacts[i].name);
                            printf("Phone Number: %s |",addressBook->contacts[i].phone);
                            printf("Email ID: %s\n",addressBook->contacts[i].email);
                            match[count]=i; //storing duplicates into array
                            count++;//Incrementing duplicates count
                        }
                    }
                    //to choose which contact should be edited
                    int subchoice; // declaring variable
                    printf("Enter Index: "); //prompt message
                    scanf("%d",&subchoice); //Reading index from user
                    getchar(); // to read a new line character
                    //Checking entered number is in between or not
                    if(subchoice<1 || subchoice>addressBook->contactCount)
                    {
                        printf(RED"Invalid Index Selected\033[0m\n");
                        break;
                    }
                    //to store index of original contact which user want to be edited
                    int ind=match[subchoice-1];
                    do
                    {
                        printf("Enter the New Name: ");
                        scanf("%[^\n]",newName); //read new name from user
                        getchar(); // to read new line character
                        if(validate_name(newName)) // validating new name
                        {
                            //editing the new name in that place
                            strcpy(addressBook->contacts[ind].name,newName);
                            printf(GREEN"Contact Edited Successfully✅\n"RESET);
                            break;
                        }
                        //new name is not valid printig error message
                        else
                        {
                            printf(RED"Invalid Name! please enter name with alphabets\n"RESET);
                        }
                    }while(!validate_name(newName));//validating new name
                }
            break;
            }
            //Edit by phone number   
            case 2:
            {
                //declaration
                char oldPhone[15];
                char newPhone[15];
                do
                {
                    printf("Enter the phone number of the contact you want to edit: ");
                    scanf("%[^\n]",oldPhone); // reading old phone number from user
                    getchar(); // to read a new line character
                    int flag=0;
                    if(validate_phone(oldPhone))//Validating entered phone number
                    {
                        //Run a loop untill contact count
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            //comparing old number in the contact list
                            if(strcmp(addressBook->contacts[i].phone,oldPhone)==0)
                            {
                                flag++;//incrementing contact count
                                printf(GREEN"Contact found with entered Phone Number:\n"RESET);
                                printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                do
                                {
                                    printf("Enter the new phone number: ");
                                    scanf("%[^\n]",newPhone); // to read a new phone number from user
                                    getchar(); // to read a new line character
                                    if(validate_phone(newPhone)) // Validating new phone number 
                                    {
                                        //editing the new phone number in the old phone number
                                        strcpy(addressBook->contacts[i].phone,newPhone);
                                        printf(GREEN"Contact phone number Edited successfully✅\n"RESET);
                                        break;
                                    }
                                    //new number is not valid printing error message 
                                    else
                                    {
                                        printf(RED"Invalid Phone number! Please enter 10 digit phone number\n"RESET);
                                    }
                                }while(!validate_phone(newPhone));//Loop will run untill new phone number is valid
                            }
                        }
                        //if no contact found in contact list printing error message
                        if(flag==0)
                        {
                            printf(GREEN"No contact found with this phone number in the contact list\n"RESET);
                            break;
                        }
                    }
                    //old phone number is not valid printing error message
                    else
                    {
                        printf(RED"Invalid Phone number! Please enter 10 digit phone number\n"RESET);
                    }
                }while(!validate_phone(oldPhone)); //Loop will run untill the old phone number is valid
            }
            break;
            //search by Email ID;
            case 3:
            {
                char oldMail[50];
                char newMail[50];
                int ret;
                do
                {
                    printf("Enter the Email ID of the contact you want to edit: ");
                    scanf("%[^\n]",oldMail); // to read old email from user
                    getchar(); // to read a new line character
                    int flag=0;
                    ret=validate_mail(oldMail); // validating email 
                    if(ret) // Email is valid
                    {
                        //run a loop untill contact count
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            //comparing old Email in the conatct list
                            if(strcmp(addressBook->contacts[i].email,oldMail)==0)
                            {
                                flag++;//incrementing flag 
                                printf(GREEN"Contact found with enter Email ID:\n"RESET);
                                printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

                                int res;
                                do
                                {
                                    printf("Enter the new Email ID: ");
                                    scanf("%[^\n]",newMail); //Reading new Email from user
                                    getchar();//to read new line character
                                    res=validate_mail(newMail); // Validating new Email
                                    if(res)
                                    {
                                        //Editing new Email in place of Old Email
                                        strcpy(addressBook->contacts[i].email,newMail);
                                        printf(GREEN"Contact Email ID Edited successfully✅\n"RESET);
                                        break;
                                    }
                                    //New Email is not valid printing error message
                                    else
                                    {
                                        printf(RED"Invalid Email ID! Please enter a valid Email ID\n"RESET);
                                    }
                                }while(!res); //Loop will run untill New Email is valid
                            }
                        }
                        //if no contact found printing prompt message
                        if(flag==0)
                        {
                            printf(GREEN"No contact found with this mail ID in the conatact list\n"RESET);
                            break;
                        }
                    }
                    //old Email is not valid printing error message
                    else
                    {
                        printf(RED"Invalid Email ID! Please enter a valid Email ID\n"RESET);
                    }
                }while(!ret);//loop will untill old Email is valid
            break;
            }
            //to return to main menu
            case 4:
            {
                break;
            }
            default:
            {
                printf(RED"Invalid Choice! Please enter a valid choice\n"RESET);
            }
        }
    }while(choice!=4);//continue the loop until 4 is entered
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char delName[50];
    char delPhone[15];
    char delmail[50];
    
    int choice;
    do
    {
        printf(SPL"Delete By:\n1. Name:\n2. Phone Number:\n3. Email Id:\n4. Exit to main menu \n"RESET);//menu for deleting contact
        printf("Enter the choice you want to edit: "); //prompt to enter the input
        scanf("%d",&choice);//Read choice from user
        getchar();//to read a new line character
        switch (choice)
        {
            //Delete by name
            case 1:
            {
                do
                {
                    printf("Enter the name of the contact to be deleted: ");
                    scanf("%[^\n]",delName);//Read a name from user
                    getchar();// to read a new line character
                    if(!validate_name(delName))//validating name
                    {
                        //if name is not valid printing error message
                        printf(RED"Invalid Name! Please enter name with alphabets\n"RESET);
                    }
                }while(!validate_name(delName));//Run a loop until name is valid
                int count=0;
                for(int i=0;i<addressBook->contactCount;i++)//run a loop upto contact count
                {
                    //Comparing entered name in the contact list
                    if(strcmp(delName,addressBook->contacts[i].name)==0)
                    {
                        count++;//contact found incrementing count
                        printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
                //No contact found in the contact list
                if(count==0)
                {
                    printf(GREEN"No contact found with this name in the contact list\n"RESET);
                }
                //Only one contact found
                if(count==1)
                {
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        if(strcmp(addressBook->contacts[i].name,delName)==0)//cpmparing
                        {
                            printf(GREEN"Contact found\n"RESET);
                            //swapping the contact list into the deleted place
                            for(int j=i;j<addressBook->contactCount-1;j++)
                            { 
                                addressBook->contacts[j]=addressBook->contacts[j+1];
                            }
                            addressBook->contactCount--;//decreasing contact count
                            printf(GREEN"Above displayed contact Deleted Successfully✅\n"RESET);
                            break;
                        }
                    }
                }
                //more than one contact found in contact list
                else
                {
                    printf(GREEN"Multiple contacts found with this name.\n"RESET"Please specify Phone Number or Email ID to identify the contact.\n");
                    printf("1. Phone Number \n2. Email ID\nEnter your choice: ");//asking user to choose using they want to delete
                    int ch;
                    scanf("%d",&ch);//Read the choosing option from user
                    getchar();//to read a new line character
                    switch(ch)
                    {
                        //delete by phone number
                        case 1:
                        {
                            printf("Enter Phone Number: ");
                            scanf("%[^\n]",delPhone);//Read phone number from user
                            getchar();//to read a new line character
                            int flag=0;
                            for(int i=0;i<addressBook->contactCount;i++)//run a loop until contact count
                            {
                                //comparing entered and phone number is present in same index 
                                if(strcmp(addressBook->contacts[i].name,delName)==0 && strcmp(addressBook->contacts[i].phone,delPhone)==0)
                                {
                                    flag=1;
                                    printf(GREEN"Contact found:\n"RESET);
                                    printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

                                    for(int j=i;j<addressBook->contactCount-1;j++)//swapping contact list
                                    {
                                        addressBook->contacts[j]=addressBook->contacts[j+1];
                                    }
                                    addressBook->contactCount--;//decrementing contact count
                                    printf(GREEN"Above displayed contact Deleted Successfully✅\n"RESET);
                                    break;
                                }
                            }
                            if(flag==0)//no contact found in that list printing message
                            {
                                printf(GREEN"No contact found with this Phone Number for the given name in the contact list\n"RESET);
                            }
                            break;
                        }
                        //delete by Email ID
                        case 2:
                        {
                            printf("Enter Email ID: ");
                            scanf("%[^\n]",delmail);//Read email from user
                            getchar();//to read a new line character
                            int flag=0;
                            for(int i=0;i<addressBook->contactCount;i++)//run a loop upto contact count
                            {
                                //comparing name and Email and deleting
                                if(strcmp(addressBook->contacts[i].name,delName)==0 && strcmp(addressBook->contacts[i].email,delmail)==0)
                                {
                                    flag=1;
                                    printf(GREEN"Contact found:\n"RESET);
                                    printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

                                    for(int j=i;j<addressBook->contactCount-1;j++)//swapping the contact list
                                    {
                                        addressBook->contacts[j]=addressBook->contacts[j+1];
                                    }
                                    addressBook->contactCount--;//decrementing contact count
                                    printf(GREEN"Above displayed contact Deleted Successfully✅\n"RESET);
                                    break;
                                }
                            }
                            //no contact found printing message
                            if(flag==0)
                            {
                                printf(GREEN"No contact found with this Email ID for the given name in the contact list\n"RESET);
                            }
                            break;
                        }
                        default:
                        {
                            printf(RED"Invalid Choice! Please enter a valid choice\n"RESET);
                        }
                    }
                }
            break;
            }
            //delete by phone number
            case 2:
            {
                do
                {
                    printf("Enter the Phone Number of the contact to be deleted: ");
                    scanf("%[^\n]",delPhone);//reading phone number from user
                    getchar();//to read a new line character
                    if(!validate_phone(delPhone))//validating phone number
                    {
                        printf(RED"Invalid Phone number! Please enter 10 digit phone number\n"RESET);//invalid message
                    }
                }while(!validate_phone(delPhone));//loop will run until the phone number is valid
                int flag=0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    //comparing the phone number in the contact list
                    if(strcmp(addressBook->contacts[i].phone,delPhone)==0)
                    {
                        flag=1;
                        printf(GREEN"Contact found:\n"RESET);
                        printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        for(int j=i;j<addressBook->contactCount-1;j++)//swapping the contact list in delted place
                        {
                            addressBook->contacts[j]=addressBook->contacts[j+1];
                        }
                        addressBook->contactCount--;//decrementing contact count
                        printf(GREEN"Above displayed contact Deleted Successfully✅\n"RESET);
                        break;
                    }
                }
                //no contact found printing message
                if(flag==0)
                {
                    printf(GREEN"No contact found with this phone number in the contact list\n"RESET);
                }
            }
            break;
            //delete by Email ID
            case 3:
            {
                do
                {
                    printf("Enter the Email ID of the contact to be deleted: ");
                    scanf("%[^\n]",delmail); //Read email from user
                    getchar(); //to read a new line character
                    if(!validate_mail(delmail)) //Validate email
                    {
                        printf(RED"Invalid Email ID! Please enter a valid Email ID\n"RESET); //invalid message
                    }
                }while(!validate_mail(delmail));//loop will run until email is valid
                int flag=0;
                for(int i=0;i<addressBook->contactCount;i++) //loop upto contact count
                {
                    if(strcmp(addressBook->contacts[i].email,delmail)==0) //comparing email in contact list
                    {
                        flag=1;
                        printf(GREEN"Contact found:\n"RESET);
                        printf("Name :%s\nPhone Number: %s\nEmail ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        for(int j=i;j<addressBook->contactCount-1;j++) //swapping contact list in deleted place
                        {
                            addressBook->contacts[j]=addressBook->contacts[j+1];
                        }
                        addressBook->contactCount--;//decrementing contact count
                        printf(GREEN"Above displayed contact Deleted Successfully✅\n"RESET);
                        break;
                    }
                }
                //no contact found printing message
                if(flag==0)
                {
                    printf(GREEN"No contact found with this Email ID in the contact list\n"RESET);
                }
            break;
            }
            case 4:
            {
                break;
            }
            default:
            {
                printf(RED"Invalid Choice! Please enter a valid choice\n"RESET);
            }
        }
    }while(choice!=4);//continue loop until user wants to exit
}