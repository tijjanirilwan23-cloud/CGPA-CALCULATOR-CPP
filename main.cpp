#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>   // Added for Input Validation

using namespace std;

int getGradePoint(char grade) {
    grade = toupper(grade);
    switch (grade) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'E': return 1;
        case 'F': return 0;
        default: return -1;
    }
}

string getClassOfDegree(double cgpa) {
    if (cgpa >= 4.50) return "First Class Honours";
    if (cgpa >= 3.50) return "Second Class Honours (Upper Division)";
    if (cgpa >= 2.40) return "Second Class Honours (Lower Division)";
    if (cgpa >= 1.50) return "Third Class Honours";
    if (cgpa >= 1.00) return "Pass";
    return "Fail / Probation";
}

// Helper function to safely handle integer inputs
int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            return value;
        }
        cout << "Invalid input! Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

struct Course {
    string code;
    int units;
    char grade;
    int points;
};

int main() {
    cout << "=========================================\n";
    cout << " CGPA CALCULATOR FOR NIGERIAN STUDENT \n";
    cout << "=========================================\n\n";

    int totalSemesters = getValidIntInput("Enter the number of completed semesters: ");

    int cumulativeUnits = 0;
    int cumulativeQualityPoints = 0;

    for (int sem = 1; sem <= totalSemesters; ++sem) {
        cout << "\n-----------------------------------------\n";
        cout << "SEMESTER " << sem << "\n";
        cout << "-----------------------------------------\n";
        
        int numCourses = getValidIntInput("Enter number of courses taken in semester " + to_string(sem) + ": ");

        int semesterUnits = 0;
        int semesterQualityPoints = 0;

        for (int i = 0; i < numCourses; ++i) {
            Course course;
            cout << "\nCourse " << (i + 1) << " Code (e.g., GST101): ";
            cin >> course.code;

            course.units = getValidIntInput("Course Credit Units (e.g., 2, 3, 6): ");

            while (true) {
                cout << "Grade Obtained (A, B, C, D, E, F): ";
                cin >> course.grade;
                
                int pt = getGradePoint(course.grade);
                if (pt != -1) {
                    course.points = pt;
                    break;
                }
                cout << "Invalid grade entered! Please enter A, B, C, D, E, or F.\n";
            }

            int courseQualityPoint = course.units * course.points;
            semesterUnits += course.units;
            semesterQualityPoints += courseQualityPoint;
        }

        double gpa = (semesterUnits == 0) ? 0.0 : (double)semesterQualityPoints / semesterUnits;
        cout << fixed << setprecision(2);
        cout << "\n>>> Semester " << sem << " GPA: " << gpa << " <<<\n";

        cumulativeUnits += semesterUnits;
        cumulativeQualityPoints += semesterQualityPoints;
    }

    double cgpa = (cumulativeUnits == 0) ? 0.0 : (double)cumulativeQualityPoints / cumulativeUnits;

    cout << "\n=========================================\n";
    cout << "              FINAL RESULT               \n";
    cout << "=========================================\n";
    cout << fixed << setprecision(2);
    cout << "Total Credit Units Taken : " << cumulativeUnits << "\n";
    cout << "Total Quality Points     : " << cumulativeQualityPoints << "\n";
    cout << "Final CGPA              : " << cgpa << " / 5.00\n";
    cout << "Class of Degree         : " << getClassOfDegree(cgpa) << "\n";
    cout << "=========================================\n";

    
    return 0;
}