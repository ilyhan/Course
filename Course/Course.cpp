#include <iostream>
#include <cstring>
using namespace std;

struct Student_in {
	char name[21];
	char surname[21];
	int marks[5];
	float rank;
	float sum_marks = 0;
};

struct Student_out {
	char surname[21];
	float average_score;

};

void rank_student(Student_in* students, int n) {
	int mx = 2, mn = 5;
	for (int i = 0; i < 5; i++) {
		if (students[n].marks[i] < mn) mn = students[n].marks[i];
		if (students[n].marks[i] > mx) mx = students[n].marks[i];
	}
	if (mx == 5 && (mx - mn) == 0) students[n].rank = 5;
	else if (mx == 5 && (mx - mn) == 1) students[n].rank = 4.5;
	else if (mx == 4 && (mx - mn) == 0) students[n].rank = 4;
	else students[n].rank = 3;

}

void sortStudentByRank(Student_in* students, int n) {
	Student_in temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (students[i].rank > students[j].rank) {
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}
}


void sortStudentByName(Student_in* students, int n) {
	Student_in temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (strcmp(students[i].surname, students[j].surname) < 0 && (students[i].rank == students[j].rank)) {
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "Ru"); 
	int n;
	cout << "Введите количество студентов" << endl;
	cin >> n;
	Student_in temp;
	Student_in* students = new Student_in[n];
	Student_out* sort_stud = new Student_out[n];

	cout << "Введите Фамилии и Имена студентов, а также их оценки по 5 предметам" << endl;
	for (int i = 0; i < n; i++) {
		cin >> students[i].name >> students[i].surname;
		for (int j = 0; j < 5; j++) {
			cin >> students[i].marks[j];
			students[i].sum_marks += students[i].marks[j];
		}
		rank_student(students, i);
	}

	sortStudentByRank(students, n);
	sortStudentByName(students, n);

	for (int i = 0; i < n; i++) {
		strcpy_s(sort_stud[i].surname, students[i].surname);
		sort_stud[i].average_score = (float)students[i].sum_marks / 5.0;
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (students[i].sum_marks > students[j].sum_marks) {
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}
	cout << "Cтуденты в лексикографическом порядке" << endl;
	for (int i = 0; i < n; i++) {
		cout << sort_stud[i].surname << " " << sort_stud[i].average_score << endl;
	}
	cout << "Cтуденты, имеющиее наивысший средний былл" << endl;
	int i = 0;
	while (students[i].sum_marks == students[0].sum_marks) {
		cout << students[i].surname << " | ";
		for (int j = 0; j < 5; j++) {
			cout << students[i].marks[j] << " ";
		}
		cout << endl;
		i++;
	}
}
