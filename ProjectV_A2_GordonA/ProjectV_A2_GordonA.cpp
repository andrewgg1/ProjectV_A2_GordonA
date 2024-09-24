/*
 *	FILE		: ProjectV_A2_GordonA.cpp
 *	PROJECT		: Project V: Student Data Processing
 *	AUTHOR		: Andrew Gordon
 *	DATE		: Sept. 23, 2024
 *	DESCRIPTION	:
 *	This program reads student data from a file and stores it in a vector of STUDENT_DATA structs.
 *  The program supports different modes (pre-release, release, and debug) to handle variations in the input data.
 *  In pre-release mode, the program reads additional email addresses for each student.
 *  The program also includes debug mode to print each line of the input file for debugging purposes.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// STUDENT_DATA struct to contain data of each student
struct STUDENT_DATA {
	string firstName;
	string lastName;
	string emailAddress;
};

int main()
{
	// vector to store student data
	vector<STUDENT_DATA> studentData;
	string studentDataLine;

	#ifdef PRE_RELEASE
		cout << "Running in pre-release mode." << endl;
		ifstream studentDataFile("StudentData_Emails.txt");
	#else
		ifstream studentDataFile("StudentData.txt");
		cout << "Running in standard mode." << endl;
	#endif

	// open the student data file
	if (!studentDataFile.is_open()) {
		cerr << "Failed to open the Student Data file." << endl;
		return 1;
	}

	while (getline(studentDataFile, studentDataLine)) {
		// print each line, only if in debug mode
		#ifdef _DEBUG
				cout << studentDataLine << endl;
		#endif // DEBUG

		// find the index of the first comma
		size_t firstCommaIndex = string::npos;
		firstCommaIndex = studentDataLine.find(',');

		if (firstCommaIndex != string::npos) {
			// create new STUDENT_DATA struct
			STUDENT_DATA newStudent;		

			// if in pre-release mode, extract and save the email address
			#ifdef PRE_RELEASE
				// extract email address
				size_t secondCommaIndex = string::npos;
				secondCommaIndex = studentDataLine.find(',', firstCommaIndex + 1);
				newStudent.emailAddress = studentDataLine.substr(secondCommaIndex + 1);
				// get first name
				newStudent.firstName = studentDataLine.substr(firstCommaIndex + 2, secondCommaIndex - firstCommaIndex - 2);
			#else
				// get first name from line, no email address
				newStudent.firstName = studentDataLine.substr(firstCommaIndex + 2);
			#endif

			// get last name, save to struct
			newStudent.lastName = studentDataLine.substr(0, firstCommaIndex);			

			// push the student struct into the vector of students
			studentData.push_back(newStudent);
		}
	}

	// close the student data file
	studentDataFile.close();

	return 0;
}
