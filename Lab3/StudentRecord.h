#pragma once
#include <string>

using namespace std;

enum RecordType { NAME, QUIZ1, QUIZ2, MIDTERM, FINALEXAM };

struct StudentRecord
{
	string name;
	int quiz1;
	int quiz2;
	int midterm;
	int finalexam;
};
