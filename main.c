#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

struct books{
    long int accNo;
    char bookName[500];
    char authorName[500];
    char publisher[500];
    char date[12];
}book;

struct student{
    long int sacNo;
    char studName[50];
    char rollNo[10];
    char bookName[500];
    char date[12];
}stud;

FILE *fp;

int main()
{
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =          SIMPLE LIBRARY SYSTEM            =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");

    int i=0;
    int ch;
    char dummy;

    while(1)
    {
            printf("1.Add Book to library\n");
            printf("2.Display library Book list\n");
            printf("3.Remove book\n");
            printf("4.Issue book\n");
            printf("5.Issued books list\n");
            printf("0.Exit\n\n");

            printf("Enter Your Choice:");
            scanf("%d",&ch);

     switch(ch)
        {
            case 0: exit(0);

            case 1:addBook();
                    break;

            case 2:bookList();
                    break;

            case 3:removeBook();
                    break;

            case 4:issueBook();
                    break;

            case 5:issueList();
                    break;

            default:printf("No such choice....\n\n");

            }
     printf("\nEnter any key to continue: ");
     fflush(stdin);
     getch();
     scanf("%c",&dummy);

    }

    return 0;
}

void addBook(){

    char date[12];
    char dummy;
    time_t t=time(NULL);
    struct tm tm =*localtime(&t);
    sprintf(date,"%02d/%02d/%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    strcpy(book.date,date);

    fp=fopen("books.txt","ab");

    printf("\nEnter book number:  ");
    scanf("%ld",&book.accNo);
    scanf("%c",&dummy);
    printf("\nEnter the book name:  ");
    scanf("%[^\n]",book.bookName);
    scanf("%c",&dummy);

    printf("\nEnter the author's name: ");
    scanf("%[^\n]",book.authorName);
    scanf("%c",&dummy);

    printf("\nEnter the publisher name:  ");
    scanf("%[^\n]",book.publisher);


    printf("Book added successfully\n\n");

    fwrite(&book,sizeof(book),1,fp);
    fclose(fp);

}

void bookList(){

    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-20s %-40s %-30s %s\n\n", "Book no", "Book Name", "Author", "Publisher");

    fp = fopen("books.txt", "rb");
    while(fread(&book, sizeof(book), 1, fp) == 1){
        printf("%ld\t\t%s\t\t\t\t%s\t\t\t%s\n", book.accNo, book.bookName, book.authorName, book.publisher);
    }

    fclose(fp);
}


void removeBook(){
    int no, f=0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book number to remove: ");
    scanf("%ld", &stud.sacNo);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("editBook.txt", "ab");

    while(fread(&book, sizeof(book), 1, fp) == 1){
        if(stud.sacNo == book.accNo){
            f=1;
        }else{
            fwrite(&book, sizeof(book), 1, ft);
        }
    }

    if(f==1){
        printf("\n\n Book Deleted Successfully");
    }else{
        printf("\n\n Book not found in record");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("books.txt", "editBook.txt");

}

void issueBook(){

    char Date[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(Date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(stud.date, Date);

    int f=0;

    system("cls");
    printf("<== Issue Books ==>\n\n");
    printf("Enter Book number to issue: ");
    scanf("%d", &stud.sacNo);

    fp = fopen("books.txt", "rb");

    while(fread(&book, sizeof(book), 1, fp) == 1){
        if(book.accNo == stud.sacNo){
            strcpy(stud.bookName, book.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("Invalid book id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(stud.studName);

    printf("Enter Student Roll no: ");
    fflush(stdin);
    gets(stud.rollNo);

    printf("Enter book name: ");
    fflush(stdin);
    gets(stud.bookName);

    printf("Book Issued Successfully\n\n");

    fwrite(&stud, sizeof(stud), 1, fp);
    fclose(fp);
}

void issueList(){
    system("cls");
    printf("<== Book Issue List ==>\n\n");

   printf("sacNo\t\tstudent name\t\tstudent roll no\t\tbook name\n\n");

    fp = fopen("issue.txt", "rb");
    while(fread(&stud, sizeof(stud), 1, fp) == 1)
    {
        printf("%ld\t\t%s\t\t%s\t\t\t%s\t\t\n", stud.sacNo, stud.studName, stud.rollNo, stud.bookName);

    }
        fclose(fp);
}
