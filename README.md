# Library Management System (C)

A **console-based Library Management System** developed in **C** as a **first-semester academic project**.  
This project demonstrates fundamental programming concepts such as **file handling, structures, and menu-driven programming**.

---

## Features

- Add new books to the library
- Display list of available books
- Remove books using Book ID
- Issue books to students
- View issued books list
- Return issued books
- Persistent data storage using text files

---

## Technologies Used

- C Programming Language
- File Handling (`.txt` files)
- Structures
- Standard C Libraries

---

## How the System Works

- Book details are stored in `books.txt`
- Issued book records are stored in `issue.txt`
- Each book has a unique ID to avoid duplication
- Issuing a book removes it from the available books list
- Returning a book adds it back to the library
- Temporary files are used to safely update records

---

## File Structure

Library_Management_System_C/
│
├── main.c
├── books.txt (created at runtime)
├── issue.txt (created at runtime)
└── temp.txt (temporary file)



## How to Run the Program

1. Clone the repository:
   ```bash
 git clone https://github.com/your-username/Library_Management_System_C.git
 
2. Navigate to the project folder:
   cd Library_Management_System_C

3.Compile the program:
  gcc main.c -o library

4.Run the executable:
./library

##What I Learned:

-Designing a menu-driven console application

-Working with structures to model real-world entities

-Using file handling for data persistence

-Implementing issue and return logic

-Managing records using temporary files

Implementing issue and return logic

Managing records using temporary files

##Future Improvements:

-Add user authentication (Admin / Student)

-Replace text files with a database

-Implement search and filter options

-Create a GUI or web-based version

-Improve input validation and error handling










