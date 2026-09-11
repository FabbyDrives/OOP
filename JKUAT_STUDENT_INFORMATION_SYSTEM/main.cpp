#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class User {
protected:
    string username, password, name;

public:
    User(string u = "", string p = "", string n = "")
        : username(u), password(p), name(n) {}

    bool login(const string &u, const string &p) {
        return username == u && password == p;
    }

    string getName() { return name; }
};

class Unit {
    string code, unitName;

public:
    Unit(string c = "", string n = "") : code(c), unitName(n) {}

    string getCode() { return code; }
    string getName() { return unitName; }

    void display() {
        cout << code << " - " << unitName << endl;
    }
};

class Student : public User {
    string registrationNumber;
    vector<Unit> registeredUnits;
    vector<string> notes, assignments, cats;
    double grade = 0, examMark = 0;

    // Prints a numbered list, or a fallback message if it's empty.
    void printList(const string &title, const vector<string> &items) {
        cout << "\n===== " << title << " =====\n";
        if (items.empty()) {
            cout << "Nothing here yet.\n";
            return;
        }
        for (size_t i = 0; i < items.size(); i++)
            cout << i + 1 << ". " << items[i] << endl;
    }

public:
    Student(string reg = "", string u = "", string p = "", string n = "")
        : User(u, p, n), registrationNumber(reg) {}

    void registerUnit(const Unit &unit) {
        registeredUnits.push_back(unit);
        cout << "Unit registered successfully.\n";
    }

    void viewUnits() {
        cout << "\n===== REGISTERED UNITS =====\n";
        if (registeredUnits.empty()) {
            cout << "No units registered.\n";
            return;
        }
        for (auto &u : registeredUnits)
            u.display();
    }

    void addNote(const string &note) { notes.push_back(note); }
    void viewNotes() { printList("LEARNING MATERIALS", notes); }

    void addAssignment(const string &a) { assignments.push_back(a); }
    void viewAssignments() { printList("ASSIGNMENTS", assignments); }

    void addCAT(const string &c) { cats.push_back(c); }
    void viewCATs() { printList("CATS", cats); }

    void setGrade(double g) { grade = g; }
    void setExamMark(double e) { examMark = e; }

    void viewResults() {
        cout << "\n===== STUDENT RESULTS =====\n";
        cout << "CAT/Assignment Grade: " << grade << endl;
        cout << "Examination Mark: " << examMark << endl;
    }

    string getRegNo() { return registrationNumber; }
};

class Lecturer : public User {
    string staffNumber;

    // Reads a full line of input for a given prompt.
    string promptLine(const string &label) {
        string value;
        cout << label;
        cin.ignore();
        getline(cin, value);
        return value;
    }

public:
    Lecturer(string staff = "", string u = "", string p = "", string n = "")
        : User(u, p, n), staffNumber(staff) {}

    void uploadNotes(Student &student) {
        student.addNote(promptLine("Enter name of notes: "));
        cout << "Notes uploaded successfully.\n";
    }

    void uploadAssignment(Student &student) {
        student.addAssignment(promptLine("Enter assignment title: "));
        cout << "Assignment uploaded successfully.\n";
    }

    void uploadCAT(Student &student) {
        student.addCAT(promptLine("Enter CAT title: "));
        cout << "CAT uploaded successfully.\n";
    }

    void gradeStudent(Student &student) {
        double mark;
        cout << "Enter assignment/CAT grade: ";
        cin >> mark;
        student.setGrade(mark);
        cout << "Student graded successfully.\n";
    }

    void enterExamMarks(Student &student) {
        double mark;
        cout << "Enter examination mark: ";
        cin >> mark;
        student.setExamMark(mark);
        cout << "Examination mark entered successfully.\n";
    }
};

class Administrator : public User {
public:
    Administrator(string u = "", string p = "", string n = "")
        : User(u, p, n) {}

    void manageStudents()  { cout << "\nAdministrator can add, update and remove students.\n"; }
    void manageLecturers() { cout << "\nAdministrator can add, update and remove lecturers.\n"; }
    void manageUnits()     { cout << "\nAdministrator can add, update and remove units.\n"; }
    void manageAccounts()  { cout << "\nAdministrator can manage system accounts.\n"; }
};

void saveStudent(Student &student) {
    ofstream file("students.txt", ios::app);
    if (file.is_open())
        file << student.getRegNo() << endl;
}

void studentMenu(Student &student) {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       STUDENT PORTAL / LMS\n";
        cout << "====================================\n";
        cout << "1. Register Units\n";
        cout << "2. View Registered Units\n";
        cout << "3. Access Notes\n";
        cout << "4. View Assignments\n";
        cout << "5. Attempt CATs\n";
        cout << "6. View Grades\n";
        cout << "7. View Examination Results\n";
        cout << "8. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string code, name;
            cout << "\nEnter Unit Code: ";
            cin >> code;
            cout << "Enter Unit Name: ";
            cin.ignore();
            getline(cin, name);
            student.registerUnit(Unit(code, name));
            break;
        }
        case 2: student.viewUnits(); break;
        case 3: student.viewNotes(); break;
        case 4: student.viewAssignments(); break;
        case 5:
            student.viewCATs();
            cout << "\nCAT attempted successfully (demo).\n";
            break;
        case 6:
        case 7: student.viewResults(); break;
        case 8: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 8);
}

void lecturerMenu(Lecturer &lecturer, Student &student) {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "          LECTURER MODULE\n";
        cout << "====================================\n";
        cout << "1. Upload Notes\n";
        cout << "2. Upload Assignment\n";
        cout << "3. Upload CAT\n";
        cout << "4. Grade Assignment/CAT\n";
        cout << "5. Enter Examination Marks\n";
        cout << "6. View Student Units\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: lecturer.uploadNotes(student); break;
        case 2: lecturer.uploadAssignment(student); break;
        case 3: lecturer.uploadCAT(student); break;
        case 4: lecturer.gradeStudent(student); break;
        case 5: lecturer.enterExamMarks(student); break;
        case 6: student.viewUnits(); break;
        case 7: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 7);
}

void adminMenu(Administrator &admin) {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       ADMINISTRATOR MODULE\n";
        cout << "====================================\n";
        cout << "1. Manage Students\n";
        cout << "2. Manage Lecturers\n";
        cout << "3. Manage Units\n";
        cout << "4. Manage User Accounts\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: admin.manageStudents(); break;
        case 2: admin.manageLecturers(); break;
        case 3: admin.manageUnits(); break;
        case 4: admin.manageAccounts(); break;
        case 5: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}

int main() {
    // Demo accounts
    Student student("SCT121-0470/2025", "student", "1234", "Fabius Kamau");
    Lecturer lecturer("LEC001", "lecturer", "1234", "Demo Lecturer");
    Administrator admin("admin", "1234", "System Administrator");

    // Sample learning materials
    student.addNote("Introduction to Object Oriented Programming");
    student.addAssignment("OOP Assignment 1");
    student.addCAT("OOP CAT 1");

    int choice;

    do {
        cout << "\n\n============================================\n";
        cout << "   JKUAT STUDENT INFORMATION SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Student Login\n";
        cout << "2. Lecturer Login\n";
        cout << "3. Administrator Login\n";
        cout << "4. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        string username, password;

        switch (choice) {
        case 1:
            cout << "\n===== STUDENT LOGIN =====\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            if (student.login(username, password)) {
                cout << "\nLogin successful! Welcome " << student.getName() << "!\n";
                studentMenu(student);
            } else {
                cout << "Invalid username or password.\n";
            }
            break;

        case 2:
            cout << "\n===== LECTURER LOGIN =====\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            if (lecturer.login(username, password)) {
                cout << "\nLogin successful! Welcome " << lecturer.getName() << "!\n";
                lecturerMenu(lecturer, student);
            } else {
                cout << "Invalid username or password.\n";
            }
            break;

        case 3:
            cout << "\n===== ADMINISTRATOR LOGIN =====\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            if (admin.login(username, password)) {
                cout << "\nLogin successful! Welcome " << admin.getName() << "!\n";
                adminMenu(admin);
            } else {
                cout << "Invalid username or password.\n";
            }
            break;

        case 4:
            cout << "\nThank you for using JKUAT Student Information System.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
