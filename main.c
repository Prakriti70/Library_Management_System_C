// Library Management System
// Console-based project in C
// First Semester Academic Project



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure for books
struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

// Structure for students
struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char authorName[50]; 
    char date[12];
} s;

// Function prototypes
void addBook();
void booksList();
void del();
void issueBook();
void issueList();
void returnBook();

FILE *fp;

int main() {
    int ch;
    while (1) {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add Book\n");
        printf("2. Books List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. Issued Book List\n");
        printf("6. Return Book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar();

        switch (ch) {
            case 0: exit(0);
            case 1: addBook(); break;
            case 2: booksList(); break;
            case 3: del(); break;
            case 4: issueBook(); break;
            case 5: issueList(); break;
            case 6: returnBook(); break;
            default: printf("Invalid Choice...\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }
    return 0;
}

void addBook() {
    system("cls");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(b.date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Check for duplicate ID
    int tempId;
    FILE *check = fopen("books.txt", "r");
    if (check != NULL) {
        printf("Enter book id: ");
        scanf("%d", &b.id);
        getchar();
        char tempBookName[50], tempAuthorName[50], tempDate[12];
        while (fscanf(check, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &tempId, tempBookName, tempAuthorName, tempDate) != EOF) {
            if (tempId == b.id) {
                printf("A book with this ID already exists. Please choose a different ID.\n");
                fclose(check);
                return;
            }
        }
        fclose(check);
    } else {
        printf("Enter book id: ");
        scanf("%d", &b.id);
        getchar();
    }

    printf("Enter book name: ");
    fgets(b.bookName, sizeof(b.bookName), stdin);
    b.bookName[strcspn(b.bookName, "\n")] = 0;

    printf("Enter author name: ");
    fgets(b.authorName, sizeof(b.authorName), stdin);
    b.authorName[strcspn(b.authorName, "\n")] = 0;

    fp = fopen("books.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%d|%s|%s|%s\n", b.id, b.bookName, b.authorName, b.date);
    fclose(fp);

    printf("Book Added Successfully!\n");
}

void booksList() {
    system("cls");
    printf("<== Available Books ==>\n");
    printf("%-10s %-30s %-20s %s\n", "Book ID", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books available!\n");
        return;
    }

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &b.id, b.bookName, b.authorName, b.date) != EOF) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del() {
    system("cls");
    int id, found = 0;
    printf("Enter Book ID to remove: ");
    scanf("%d", &id);
    getchar();

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *ft = fopen("temp.txt", "w");
    if (ft == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &b.id, b.bookName, b.authorName, b.date) != EOF) {
        if (b.id == id) {
            found = 1;
        } else {
            fprintf(ft, "%d|%s|%s|%s\n", b.id, b.bookName, b.authorName, b.date);
        }
    }
    fclose(fp);
    fclose(ft);

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("Book Deleted Successfully!\n");
    } else {
        remove("temp.txt");
        printf("No Book found with ID: %d\n", id);
    }
}

void issueBook() {
    system("cls");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(s.date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int found = 0;
    printf("Enter Book ID to issue: ");
    scanf("%d", &s.id);
    getchar();

    // Open the books file to check if the book exists
    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books available!\n");
        return;
    }

    // Create a temporary file to store books except the issued one
    FILE *ft = fopen("temp.txt", "w");
    if (ft == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    // Search for the book and remove it from the list
    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &b.id, b.bookName, b.authorName, b.date) != EOF) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName); // Copy book name for issuing
            strcpy(s.authorName, b.authorName); // Copy author name for issuing
            found = 1;
        } else {
            // Write other books to the temporary file
            fprintf(ft, "%d|%s|%s|%s\n", b.id, b.bookName, b.authorName, b.date);
        }
    }
    fclose(fp);
    fclose(ft);

    if (!found) {
        printf("No book found with this ID!\n");
        remove("temp.txt"); // Delete the temporary file
        return;
    }

    // Replace the original books file with the temporary file
    remove("books.txt");
    rename("temp.txt", "books.txt");

    // Now, issue the book to the student
    printf("Enter Student Name: ");
    fgets(s.sName, sizeof(s.sName), stdin);
    s.sName[strcspn(s.sName, "\n")] = 0;

    printf("Enter Student Class: ");
    fgets(s.sClass, sizeof(s.sClass), stdin);
    s.sClass[strcspn(s.sClass, "\n")] = 0;

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);
    getchar();

    // Add the issued book to the issue file
    fp = fopen("issue.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%d|%s|%s|%d|%s|%s|%s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.authorName, s.date);
    fclose(fp);

    printf("Book Issued Successfully!\n");
}

void issueList() {
    system("cls");
    printf("<== Issued Books List ==>\n");
    printf("%-10s %-30s %-20s %-10s %-30s %-20s %s\n", "S.ID", "Name", "Class", "Roll", "Book Name", "Author", "Date");

    fp = fopen("issue.txt", "r");
    if (fp == NULL) {
        printf("No books have been issued!\n");
        return;
    }

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%d|%49[^|]|%49[^|]|%11[^\n]\n", &s.id, s.sName, s.sClass, &s.sRoll, s.bookName, s.authorName, s.date) != EOF) {
        printf("%-10d %-30s %-20s %-10d %-30s %-20s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.authorName, s.date);
    }
    fclose(fp);
}

void returnBook() {
    system("cls");
    int id, found = 0;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);
    getchar();

    // Open the issue file to find the book
    fp = fopen("issue.txt", "r");
    if (fp == NULL) {
        printf("No books have been issued!\n");
        return;
    }

    // Create a temporary file to store non-returned books
    FILE *ft = fopen("temp.txt", "w");
    if (ft == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    // Search for the book and remove it from the issue list
    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%d|%49[^|]|%49[^|]|%11[^\n]\n", &s.id, s.sName, s.sClass, &s.sRoll, s.bookName, s.authorName, s.date) != EOF) {
        if (s.id == id) {
            found = 1;
            // Add the returned book back to the books file
            FILE *fb = fopen("books.txt", "a");
            if (fb == NULL) {
                printf("Error opening books file!\n");
                fclose(fp);
                fclose(ft);
                return;
            }
            fprintf(fb, "%d|%s|%s|%s\n", s.id, s.bookName, s.authorName, s.date); // Restore author name
            fclose(fb);
        } else {
            // Write other issued books to the temporary file
            fprintf(ft, "%d|%s|%s|%d|%s|%s|%s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.authorName, s.date);
        }
    }
    fclose(fp);
    fclose(ft);

    if (found) {
        // Replace the original issue file with the temporary file
        remove("issue.txt");
        rename("temp.txt", "issue.txt");
        printf("Book Returned Successfully!\n");
    } else {
        remove("temp.txt"); // Delete the temporary file
        printf("No issued book found with ID: %d\n", id);
    }
}