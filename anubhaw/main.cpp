#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Course {
public:
    int id;
    string name;
    int credits;

    Course(int id, string name, int credits)
        : id(id), name(name), credits(credits) {}

    void display() const {
        cout << "Course ID: " << id << " | Name: " << name << " | Credits: " << credits << endl;
    }
};

class Student {
public:
    int id;
    string name;
    vector<int> enrolledCourses;

    Student(int id, string name)
        : id(id), name(name) {}

    void enroll(int courseId) {
        enrolledCourses.push_back(courseId);
    }

    void display() const {
        cout << "Student ID: " << id << " | Name: " << name << endl;
        if (enrolledCourses.empty()) {
            cout << "  No enrolled courses.\n";
        } else {
            cout << "  Enrolled in courses: ";
            for (int c : enrolledCourses)
                cout << c << " ";
            cout << endl;
        }
    }
};

class University {
private:
    vector<Student> students;
    vector<Course> courses;
    int studentCounter = 1;
    int courseCounter = 100;

public:
    void addStudent() {
        string name;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        students.emplace_back(studentCounter++, name);
        cout << "Student added successfully!\n";
    }

    void addCourse() {
        string name;
        int credits;
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter course credits: ";
        cin >> credits;
        courses.emplace_back(courseCounter++, name, credits);
        cout << "Course added successfully!\n";
    }

    void enrollStudent() {
        int sid, cid;
        cout << "Enter Student ID: ";
        cin >> sid;
        cout << "Enter Course ID: ";
        cin >> cid;

        auto sIt = find_if(students.begin(), students.end(), [sid](const Student &s) { return s.id == sid; });
        auto cIt = find_if(courses.begin(), courses.end(), [cid](const Course &c) { return c.id == cid; });

        if (sIt != students.end() && cIt != courses.end()) {
            sIt->enroll(cid);
            cout << "Enrollment successful!\n";
        } else {
            cout << "Invalid student or course ID.\n";
        }
    }

    void showStudents() const {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }
        for (const auto &s : students)
            s.display();
    }

    void showCourses() const {
        if (courses.empty()) {
            cout << "No courses available.\n";
            return;
        }
        for (const auto &c : courses)
            c.display();
    }

    void menu() {
        int choice;
        do {
            cout << "\n===== University Management System =====\n";
            cout << "1. Add Student\n";
            cout << "2. Add Course\n";
            cout << "3. Enroll Student in Course\n";
            cout << "4. Show All Students\n";
            cout << "5. Show All Courses\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: addCourse(); break;
                case 3: enrollStudent(); break;
                case 4: showStudents(); break;
                case 5: showCourses(); break;
                case 0: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    University uni;
    uni.menu();
    return 0;
}