// ProjectV_A2_GordonA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// STUDENT_DATA struct to contain data of each student
struct STUDENT_DATA {
    string firstName;
    string lastName;
};

int main()
{
    // vector to store student data
    vector<STUDENT_DATA> studentData;
    string studentDataLine;

    // open the student data file
    ifstream studentDataFile("StudentData.txt");
    if (!studentDataFile.is_open()) {
        cerr << "Failed to open the Student Data file." << endl;
        return 1;
    }

    while (getline(studentDataFile, studentDataLine)) {
        // find the index of the comma
        size_t commaIndex = studentDataLine.find(',');
        if (commaIndex != string::npos) {
            // create new STUDENT_DATA struct
            STUDENT_DATA newStudent;

            // get the first and last names, save to struct
            newStudent.lastName = studentDataLine.substr(0, commaIndex);;
            newStudent.firstName = studentDataLine.substr(commaIndex + 2); // +2 to skip ", "

            // push the student struct into the vector of students
            studentData.push_back(newStudent);
        }
    }

    // close the student data file
    studentDataFile.close();

    return 0;
}
