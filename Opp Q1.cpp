#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;


class Person {
protected:
    string name;
    int age;
    string address;

public:
    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", Address: " << address << endl;
    }
};

class Student : public Person {
private:
    string studentID;
    unordered_map<string, int> grades; 

public:
    Student(string n, int a, string addr, string id) 
        : Person(n, a, addr), studentID(id) {}

    void assignGrade(string subject, int grade) {
        grades[subject] = grade;
    }

    double calculateGPA() {
        if (grades.empty()) return 0.0;
        double total = 0.0;
        for (auto &grade : grades) {
            total += grade.second;
        }
        return total / grades.size();
    }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Student ID: " << studentID << ", GPA: " 
             << fixed << setprecision(2) << calculateGPA() << endl;
    }
};


class Payable {
public:
    virtual double calculateSalary() = 0;
};


class Teacher : public Person, public Payable {
private:
    string teacherID;
    string subject;
    int classesTaught;
    double ratePerClass;

public:
    Teacher(string n, int a, string addr, string id, string sub, int classes, double rate) 
        : Person(n, a, addr), teacherID(id), subject(sub), classesTaught(classes), ratePerClass(rate) {}

    void assignGrade(Student &student, string subject, int grade) {
        student.assignGrade(subject, grade);
    }

    double calculateSalary() override {
        return classesTaught * ratePerClass;
    }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Teacher ID: " << teacherID << ", Subject: " << subject 
             << ", Salary: " << calculateSalary() << endl;
    }
};


int main() {
    Teacher teacher("Alice", 35, "123 Street", "T001", "Math", 10, 50.0);
    Student student1("Bob", 16, "456 Avenue", "S001");
    Student student2("Charlie", 17, "789 Boulevard", "S002");

    
    teacher.assignGrade(student1, "Math", 85);
    teacher.assignGrade(student2, "Math", 90);

    
    cout << "Teacher Details:" << endl;
    teacher.displayDetails();

    cout << "\nStudent Details:" << endl;
    student1.displayDetails();
    student2.displayDetails();

    return 0;
}

