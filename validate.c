#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "validate.h"

#define RED     "\033[1;31m"
#define RESET   "\033[0m"

int validate_name(char *name) //function to validate name
{
    int flag=1;
    for(int i=0; name[i]!='\0';i++) //loop until null character
    {
        if (name[i]>='A' && name[i]<='Z' || name[i]>='a' && name[i]<='z' || name[i]==' ') //checking for alphabets and space
        {
            flag=1;
        }
        else
        {
            flag=0;
            break;
        }
    }
    return flag;
}
int validate_phone(char *phone)//function to validate phone number
{
    int count=0;
    for(int i=0;phone[i]!='\0';i++) //loop until null character
    {
        if(phone[i]>='0' && phone[i]<='9') //checking for digits
        {
            count++;
        }
        else
        {
            return 0;
        }
    }
    if(count==10)//checking for 10 digits
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int validate_mail(char *mail) //function to validate email ID
{
    int len=0;
    if(mail[0]=='@')//checking if mail starts with @
    {
        printf(RED"Mail should not start with '@'\n"RESET);
        return 0;
    }
    for(int i=0;mail[i]!='\0';i++)//calculating length of mail
    {
        len++;
    }
    int at_position=-1,dot_position=-1;
    for(int i=0;mail[i]!='\0';i++)//loop until null character
    {
        if(mail[i]==' ')//checking for spaces
        {
            printf(RED"Mail does not contain spaces\n"RESET);
            return 0;
        }
        if(mail[i]>='A' && mail[i]<='Z')//checking for uppercase letters
        {
            printf(RED"Mail should not contain uppercase letters\n"RESET);
            return 0;
        }
        if(mail[i]=='@')//checking for @ position
        {
            at_position=i;
        }
        if(mail[i]=='.')//checking for . position
        {
            dot_position=i;
        }
    }
    if(at_position==-1 || dot_position==-1 || at_position>dot_position)//validating positions of @ and .
    {
        printf(RED"Mail should contain @ and . in correct positions\n"RESET);
        return 0;
    }
    if(dot_position==len-1)//checking if mail ends with .
    {
        printf(RED"Mail should not end with '.'\n"RESET);
        return 0;
    }
    char val[]="gmail.com";//validating domain name
    int i=at_position+1,j=0;
    while(val[j])//loop until end of domain name
    {
        if(mail[i]!=val[j])//comparing domain name
        {
            printf(RED"Invalid mail domain! It should be @gmail.com\n"RESET);
            return 0;
        }
        i++;
        j++;
    }
    if(mail[i]!='\0')//checking for characters after domain name
    {
        printf(RED"Email should not contain characters after domain name\n"RESET);
        return 0;
    }
    return 1;
}