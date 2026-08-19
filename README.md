# Student Management System

A console-based Student Management System developed using C++ and MySQL. The application provides basic CRUD operations for managing student records through a command-line interface.

## Features

* Add Student
* Search Student by Roll Number
* Update Student CGPA
* Delete Student
* View and manage student records using MySQL
* CRUD operations
* Object-Oriented Programming
* Input validation

## Technologies

* C++
* MySQL
* MySQL C API (`libmysql`)
* Object-Oriented Programming
* SQL
* VS Code
* MinGW-w64

## Database

The application uses MySQL for persistent data storage.

### Database

```sql
student_management
```

### Table

```text
students
├── id
├── name
├── roll_no
└── cgpa
```

## Project Structure

```text
Student_Management_System/
│
├── main.cpp
├── .gitignore
└── README.md
```

> `config.h` contains local database credentials and is excluded from Git using `.gitignore`.

## How to Run

### 1. Install MySQL

Make sure MySQL Server is installed and running.

Create the database and table:

```sql
CREATE DATABASE student_management;

USE student_management;

CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    roll_no VARCHAR(50) UNIQUE NOT NULL,
    cgpa FLOAT NOT NULL
);
```

### 2. Configure Database Credentials

Create a local `config.h` file containing your MySQL password.

This file is intentionally excluded from GitHub using `.gitignore`.

### 3. Compile

Using MinGW:

```bash
g++ main.cpp -I"C:\Program Files\MySQL\MySQL Server 8.0\include" -L"C:\Program Files\MySQL\MySQL Server 8.0\lib" -lmysql -o student_management.exe
```

### 4. Run

```bash
student_management.exe
```

Make sure `libmysql.dll` is available in the same directory as the executable.

## CRUD Operations

| Operation      | SQL      |
| -------------- | -------- |
| Add Student    | `INSERT` |
| Search Student | `SELECT` |
| Update Student | `UPDATE` |
| Delete Student | `DELETE` |
