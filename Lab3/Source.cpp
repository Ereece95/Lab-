#include <fstream>
#include <iostream>
#include <vector>
#include "StudentRecord.h"
#include "Grade.h"

using namespace std;
bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecord);
bool readDelimiter(string input, std::vector<string>& output, char delimiter);
void PrintGrade(StudentRecord* studentRecord, int numberOfRecords);

const float QUIZ_WEIGHT = 25;
const float MIDTERM_WEIGHT = 25;
const float FINAL_WEIGHT = 50;

int main()
{
	int numberOfRecords;
	StudentRecord studentRecord[1024];

	//Read StudentRecords
	ReadStudentRecord(studentRecord, numberOfRecords);

	//Print out read result
	cout << "There are " << numberOfRecords << " student records." << endl;


	//Calculation
	PrintGrade(studentRecord, numberOfRecords);

	cin.get();
}

void PrintGrade(StudentRecord* studentRecord, int numberOfRecords)
{
	for (int i = 0; i < numberOfRecords; i++)
	{
		float quiz_grade = ((studentRecord[i].quiz1 + studentRecord[i].quiz2) / 20.0) * QUIZ_WEIGHT;
		float midterm_grade = (studentRecord[i].midterm / 100.0) * MIDTERM_WEIGHT;
		float final_grade = (studentRecord[i].finalexam / 100.0) * FINAL_WEIGHT;

		float total_grade = (quiz_grade + midterm_grade + final_grade);


		cout << studentRecord[i].name << '\t' << total_grade << '\t';
		if (total_grade >= 90)
			cout << "A" << endl;
		else if (total_grade >= 80)
			cout << "B" << endl;
		else if (total_grade >= 70)
			cout << "C" << endl;
		else if (total_grade >= 60)
			cout << "D" << endl;
		else
			cout << "F" << endl;
	}

}

bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecords)
{
	using namespace std;
	ifstream is;
	const string INPUTFILENAME = "studentrecords.txt";
	try {
		is.open(INPUTFILENAME);

		numberOfRecords = 0;

		string readline;
		while (!is.eof())
		{
			is >> readline;
			cout << readline << endl;

			char delimiter = ',';
			std::vector<string> output;
			readDelimiter(readline, output, delimiter);

			int index = 0;
			std::vector<string>::iterator recordIterator;
			for (recordIterator = output.begin(); recordIterator != output.end(); recordIterator++)
			{
				switch (index)
				{
				case NAME:
					studentRecord[numberOfRecords].name = *recordIterator;
					break;
				case QUIZ1:
					studentRecord[numberOfRecords].quiz1 = std::stoi(*recordIterator);
					break;
				case QUIZ2:
					studentRecord[numberOfRecords].quiz2 = std::stoi(*recordIterator);
					break;
				case MIDTERM:
					studentRecord[numberOfRecords].midterm = std::stoi(*recordIterator);
					break;
				case FINALEXAM:
					studentRecord[numberOfRecords].finalexam = std::stoi(*recordIterator);
					break;
				}
				index++;
			}
			numberOfRecords++;
		}

		is.close();
	}
	catch (ifstream::failure e)
	{
		cout << "Exception Open/Read/Close file";
		return false;
	}
	return true;
}

bool readDelimiter(string input, std::vector<string>& output, char delimiter)
{
	string acc = "";
	
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == delimiter)
		{
			output.push_back(acc);
			acc = "";
		}
		else
		{
			acc += input[i];
		}
	}
	if (acc.size() != 0)
		output.push_back(acc);
	else
	{
		if( input.size() == 0 )
			return false;
	}
	return true;
}