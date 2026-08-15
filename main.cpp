#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

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

    ofstream out("Student.txt", ios::app);

    if(!out){
        cout<<"Error: Student file could not be opened!"<<endl;
        return;
    }

    out<< s.getName() << " : "<< s.getRollNo()<< " : "<< s.getCgpa()<< endl;

    if(out.fail()){
        cout<<"Error: Student could not be added!"<<endl;
        out.close();
        return;
    }

    cout<< "student added!"<<endl;
    out.close();
}

void searchStudent(){
    string rollNo;

    cout<< "Enter Roll number of student: "<<endl;
    cin.ignore();
    getline(cin, rollNo);

    ifstream in("Student.txt");

    if(!in){
        cout<<"Error: Student file could not be opened!"<<endl;
        return;
    }

    string line;
    bool found = false;

    while(getline(in, line)){
        if(line.find(rollNo)!=string::npos){
            found = true;
            cout<< line << endl;
            break;
        }
    }

    if(!found){
        cout<< "Student not found"<<endl;
    }

    in.close();
}

void updateStudent(){
    cout<< "Enter roll no. of student to be updated: "<<endl;

    string rollNo;
    cin.ignore();
    getline(cin, rollNo);

    ifstream in("Student.txt");

    if(!in){
        cout<<"Error: Student file could not be opened!"<<endl;
        return;
    }

    bool found = false;
    ofstream out("temp.txt");

    if(!out){
        cout<<"Error: Temporary file could not be created!"<<endl;
        in.close();
        return;
    }

    string line;

    while(getline(in, line)){
        if(line.find(rollNo)!=string::npos){
            found = true;

            cout << "Enter new cgpa: "<<endl;
            float cgpa;
            cin>> cgpa;

            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Invalid CGPA!"<<endl;
                out.close();
                in.close();
                remove("temp.txt");
                return;
            }

            string CGPA = to_string(cgpa);
            line.replace(line.find_last_of(':')+2, string::npos, CGPA);

            cout<< "Updated Successfully"<<endl;
        }

        out<< line<< endl;
    }

    if(!found){
        cout<< "Student not found"<<endl;
        out.close();
        in.close();
        remove("temp.txt");
        return;
    }

    out.close();
    in.close();

    if(remove("Student.txt") != 0){
        cout<<"Error: Could not remove Student.txt"<<endl;
        remove("temp.txt");
        return;
    }

    if(rename("temp.txt", "Student.txt") != 0){
        cout<<"Error: Could not rename temporary file!"<<endl;
        return;
    }
}

void deleteStudent(){
    string rollNo;

    cout<< "Enter Roll number of student to be deleted: "<<endl;
    cin.ignore();
    getline(cin, rollNo);

    ifstream in("Student.txt");

    if(!in){
        cout<<"Error: Student file could not be opened!"<<endl;
        return;
    }

    string line;
    bool found = false;

    ofstream out("temp.txt");

    if(!out){
        cout<<"Error: Temporary file could not be created!"<<endl;
        in.close();
        return;
    }

    while(getline(in, line)){
        if(line.find(rollNo)!=string::npos){
            found = true;
            cout<< line <<" successfully deleted"<<endl;
            continue;
        }

        out<< line<< endl;
    }

    if(!found){
        cout<< "Student not found"<<endl;
        out.close();
        in.close();
        remove("temp.txt");
        return;
    }

    out.close();
    in.close();

    if(remove("Student.txt") != 0){
        cout<<"Error: Could not remove Student.txt"<<endl;
        remove("temp.txt");
        return;
    }

    if(rename("temp.txt", "Student.txt") != 0){
        cout<<"Error: Could not rename temporary file!"<<endl;
        return;
    }
}

int main(){
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

    return 0;
}