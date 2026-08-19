#include <iostream>
#include <string>
#include "config.h"
#include <windows.h>
#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysql.h"

using namespace std;

class student{
    private:
    string name;
    string rollNo;
    float cgpa;

    public:
    student(): name(""), rollNo(""), cgpa(0.0){
    }

    void setName(string name){
        this->name = name;
    }
    void setRollNo(string rollNo){
        this->rollNo = rollNo;
    }
    void setCgpa(float cgpa){
        this->cgpa = cgpa;
    }

    string getName(){
        return name;
    }
    string getRollNo(){
        return rollNo;
    }
    float getCgpa(){
        return cgpa;
    }
};

MYSQL* conn;

bool connectDatabase() {

    conn = mysql_init(NULL);

    if (conn == NULL) {
        cout << "MySQL initialization failed!" << endl;
        return false;
    }

    conn = mysql_real_connect(
        conn,
        "localhost",
        "root",
        DB_PASSWORD,
        "student_management",
        3306,
        NULL,
        0
    );

    if (conn == NULL) {
        cout << "Database connection failed!" << endl;
        cout << mysql_error(conn) << endl;
        return false;
    }

    cout << "Database connected successfully!" << endl;

    return true;
}

void addStudent(student s){
    string name, rollNo;
    float cgpa;

    cout<< "Enter Name: "<<endl;
    cin.ignore();
    getline(cin, name);
    s.setName(name);

    cout<< "Enter roll number: "<<endl;
    getline(cin, rollNo);
    s.setRollNo(rollNo);

    cout<<"Enter cgpa: "<<endl;
    cin>>cgpa;

    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Invalid CGPA!"<<endl;
        return;
    }

    s.setCgpa(cgpa);

    string query = "INSERT INTO students (name, roll_no, cgpa) VALUES ('" + s.getName() + "', '" + s.getRollNo() + "', " + to_string(s.getCgpa()) + ")";

    if(mysql_query(conn, query.c_str()) != 0) {
        cout << "Error: Student could not be added!" << endl;
        cout << mysql_error(conn) << endl;
        return;
    }

    cout << "Student added successfully!" << endl;
}

void searchStudent() {

    string rollNo;

    cout << "Enter Roll number of student: " << endl;
    cin.ignore();
    getline(cin, rollNo);

    string query =
        "SELECT id, name, roll_no, cgpa "
        "FROM students "
        "WHERE roll_no = '" + rollNo + "'";

    if (mysql_query(conn, query.c_str()) != 0) {
        cout << "Error while searching student!" << endl;
        cout << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL) {
        cout << "Error retrieving result!" << endl;
        cout << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row != NULL) {

        cout << "\nStudent Found!" << endl;
        cout << "ID: " << row[0] << endl;
        cout << "Name: " << row[1] << endl;
        cout << "Roll No: " << row[2] << endl;
        cout << "CGPA: " << row[3] << endl;

    }
    else {
        cout << "Student not found!" << endl;
    }

    mysql_free_result(result);
}

 
void updateStudent() {

    string rollNo;

    cout << "Enter roll no. of student to be updated: " << endl;
    cin.ignore();
    getline(cin, rollNo);

    float cgpa;

    cout << "Enter new CGPA: " << endl;
    cin >> cgpa;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid CGPA!" << endl;
        return;
    }

    string query =
        "UPDATE students "
        "SET cgpa = " + to_string(cgpa) +
        " WHERE roll_no = '" + rollNo + "'";

    if (mysql_query(conn, query.c_str()) != 0) {

        cout << "Error while updating student!" << endl;
        cout << mysql_error(conn) << endl;

        return;
    }

    if (mysql_affected_rows(conn) == 0) {
        cout << "Student not found!" << endl;
    }
    else {
        cout << "Student updated successfully!" << endl;
    }
}
void deleteStudent() {

    string rollNo;

    cout << "Enter Roll number of student to be deleted: " << endl;
    cin.ignore();
    getline(cin, rollNo);

    string query =
        "DELETE FROM students "
        "WHERE roll_no = '" + rollNo + "'";

    if (mysql_query(conn, query.c_str()) != 0) {

        cout << "Error while deleting student!" << endl;
        cout << mysql_error(conn) << endl;

        return;
    }

    if (mysql_affected_rows(conn) == 0) {
        cout << "Student not found!" << endl;
    }
    else {
        cout << "Student deleted successfully!" << endl;
    }
}

int main(){

    if (!connectDatabase()) {
        return 1;
    }

    student s;
    bool exit = false;

    while(!exit){
        system("cls");

        cout << "Welcome To Student Management System" << endl;
        cout << "************************************" << endl;
        cout << "1.Add Student." << endl;
        cout << "2.Search Student." << endl;
        cout << "3.Update Student." << endl;
        cout << "4.Delete Student." <<endl;
        cout << "5.Exit" <<endl;
        cout << "Enter Choice: ";

        int val;
        cin >> val;

        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Invalid choice!"<<endl;
            Sleep(2000);
            continue;
        }

        if(val == 1){
            system("cls");
            addStudent(s);
            Sleep(4000);
        }
        else if(val == 2){
            system("cls");
            searchStudent();
            Sleep(4000);
        }
        else if(val == 3){
            system("cls");
            updateStudent();
            Sleep(4000);
        }
        else if(val == 4){
            system("cls");
            deleteStudent();
            Sleep(4000);
        }
        else if(val == 5){
            system("cls");
            cout<< "Exiting Program"<<endl;
            exit = true;
            Sleep(2000);
        }
        else{
            cout<<"Invalid choice!"<<endl;
            Sleep(2000);
        }
    }
    mysql_close(conn);
    return 0;
}
