// Student Result Management System (simple version)
// Unique feature: Scholarship Predictor (scholarship based on marks + attendance)
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

const double MAX_MARKS = 20;   // marks are out of 20 (change to 100 if needed)

// Reads a number safely: repeats until the input is valid and inside [low, high]
double readNumber(string message, double low, double high) {
    double value;
    while (true) {
        cout << message;
        if (cin >> value && value >= low && value <= high) {
            return value;
        }
        if (cin.eof()) exit(0);          // input ended, stop the program
        cout << "Invalid input! Enter a number between " << low << " and " << high << ".\n";
        cin.clear();                     // clear the error state
        cin.ignore(1000, '\n');          // throw away the bad input
    }
}

// Base class
class Person {
protected:
    string name;
public:
    Person(string n) { name = n; }
    string getName() { return name; }
};

// Student class inherits from Person
class Student : public Person {
private:
    string id;           // string, because a UID can contain letters (e.g. 25BCD10200)
    double marks[3];     // marks in 3 subjects (out of 20)
    double attendance;   // attendance in percent
public:
    // Parameterized constructor
    Student(string i, string n, double m1, double m2, double m3, double att) : Person(n) {
        id = i;
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        attendance = att;
    }

    string getId() { return id; }

    double percentage() {
        // total marks divided by the maximum possible total, as a percentage
        return (marks[0] + marks[1] + marks[2]) / (3 * MAX_MARKS) * 100;
    }

    char grade() {
        double p = percentage();
        if (p >= 80) return 'A';
        if (p >= 60) return 'B';
        if (p >= 40) return 'C';
        return 'F';
    }

    // UNIQUE FEATURE: scholarship percentage based on marks and attendance
    int scholarship() {
        double p = percentage();
        if (p >= 90 && attendance >= 85) return 100;
        if (p >= 80 && attendance >= 80) return 50;
        if (p >= 70 && attendance >= 75) return 25;
        return 0;
    }

    void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Average: " << percentage() * MAX_MARKS / 100 << "/20"
             << " | Percentage: " << percentage() << "%"
             << " | Grade: " << grade()
             << " | Scholarship: " << scholarship() << "%" << endl;
    }
};

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n===== Student Result Management System =====\n";
        cout << "1. Add student\n";
        cout << "2. Show all students\n";
        cout << "3. Search student by ID\n";
        cout << "0. Exit\n";
        choice = (int)readNumber("Enter choice: ", 0, 3);

        if (choice == 1) {
            string id, name;
            cout << "Enter ID: ";
            cin >> id;

            // do not allow two students with the same ID
            bool exists = false;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].getId() == id) exists = true;
            }
            if (exists) {
                cout << "This ID already exists!\n";
                continue;
            }

            cout << "Enter name: ";
            cin >> ws;               // skip the leftover newline
            getline(cin, name);      // name can contain spaces

            double m1 = readNumber("Enter marks of subject 1 (0-20): ", 0, MAX_MARKS);
            double m2 = readNumber("Enter marks of subject 2 (0-20): ", 0, MAX_MARKS);
            double m3 = readNumber("Enter marks of subject 3 (0-20): ", 0, MAX_MARKS);
            double att = readNumber("Enter attendance % (0-100): ", 0, 100);

            students.push_back(Student(id, name, m1, m2, m3, att));
            cout << "Student added successfully!\n";
        }
        else if (choice == 2) {
            if (students.empty()) cout << "No records found.\n";
            for (size_t i = 0; i < students.size(); i++)
                students[i].display();
        }
        else if (choice == 3) {
            string id;
            bool found = false;
            cout << "Enter ID to search: ";
            cin >> id;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].getId() == id) {
                    students[i].display();
                    found = true;
                }
            }
            if (!found) cout << "Student not found.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}