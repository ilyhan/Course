#include <iostream>
#include <cstring>
#include <Windows.h>
#include <iomanip>
using namespace std;

struct Student_in {
	char name[21]; // имя студента 
	char surname[21]; // фамилия студента
	int marks[5]; // 5 оценок
	int rank;
	float sum_marks = 0; // сумма оценок
};

struct Student_out {
	char surname[21];
	float average_score; // средний балл
	int rank;
};

//функция меняющая указатели на структуры местами
void swap_in(Student_in*& a, Student_in*& b) {
	Student_in* c = a;
	a = b;
	b = c;
}

// функция для определения rank-a студента. 
// Нужна для дальнейшей сортировки студентов по успеваемости
// сначала идут отличники, потом студенты, 
//у которых и 5 и 4, затем хорошисты и в конце троичники
void rank_student(Student_in** students, int n) {
	int mx = 2, mn = 5;
	for (int i = 0; i < 5; i++) {
		if (students[n]->marks[i] < mn) mn = students[n]->marks[i];
		if (students[n]->marks[i] > mx) mx = students[n]->marks[i];
	}
	if (mx == 5 && (mx - mn) == 0) students[n]->rank = 5;
	else if ((mx == 5 && (mx - mn) == 1) || (mx == 4 && (mx - mn) == 0)) students[n]->rank = 4;
	else if ((mx == 4 && (mx - mn) == 1) || (mx == 3 && (mx - mn) == 0)) students[n]->rank = 3;
	else students[n]->rank = 2;
}

// функция сортировки студентов по rank-y
void sortStudentByRank(Student_in** students, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (students[i]->rank > students[j]->rank) {
				swap_in(students[i], students[j]);
			}
		}
	}
}

//функция для сортировки студентов в лексикографическом порядке
void sortStudentByName(Student_in** students, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (strcmp(students[i]->surname, students[j]->surname) < 0 && (students[i]->rank == students[j]->rank))
			{
				cout << students[i]->name << " ";
				swap_in(students[i], students[j]);
				cout << students[i]->name << endl;
			}

			if (strcmp(students[i]->surname, students[j]->surname) == 0 && strcmp(students[i]->name, students[j]->name) < 0 && (students[i]->rank == students[j]->rank))
			{
				swap_in(students[i], students[j]);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);  //Установка кодировки 1251 для работы с Кириллицей
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введите количество студентов" << endl;
	cin >> n;
	Student_in** students = new Student_in * [n];
	Student_out** sort_stud = new Student_out * [n];

	cout << "Введите Фамилии и Имена студентов, а также их оценки по 5 предметам" << endl;
	// инициализация массива структур Student_in
	for (int i = 0; i < n; i++) {
		students[i] = new Student_in;
		cin >> students[i]->name >> students[i]->surname;
		for (int j = 0; j < 5; j++) {
			cin >> students[i]->marks[j];
			students[i]->sum_marks += students[i]->marks[j];
		}
		rank_student(students, i);
	}

	sortStudentByRank(students, n);
	sortStudentByName(students, n);

	// инициализация массива структур Student_out
	for (int i = 0; i < n; i++) {
		sort_stud[i] = new Student_out;
		strcpy_s(sort_stud[i]->surname, students[i]->surname);
		sort_stud[i]->average_score = (float)students[i]->sum_marks / 5.0;
		sort_stud[i]->rank = students[i]->rank;
	}

	// сортировка по сумме баллов
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (students[i]->sum_marks > students[j]->sum_marks) {
				swap_in(students[i], students[j]);
			}
		}
	}

	// Первая часть вывода. На экран выводится список студентов
	cout << endl << "Cтуденты в лексикографическом порядке" << endl;
	cout << setw(20) << "Фамилия" << setw(15) << "средний балл" << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(20) << sort_stud[i]->surname << setw(10) << sort_stud[i]->average_score << endl;
	}

	// Вторая часть вывода. На экран выводятся студенты, имеющие наивысший средний балл, и их оценки 
	cout << endl << "Cтуденты, имеющиее наивысший средний былл" << endl;
	cout << setw(20) << "Фамилия" << setw(10) << "оценки" << endl;
	int i = 0;
	for (int i = 0; i < n; i++) {
		if (sort_stud[i]->average_score == sort_stud[0]->average_score) {
			cout << setw(20) << students[i]->surname << " | ";
			for (int j = 0; j < 5; j++) {
				cout << students[i]->marks[j] << " ";
			}
			cout << endl;
		}
		else break;
	}

	// освобождение памяти 
	for (int i = 0; i < n; i++) {
		delete students[i];
		delete sort_stud[i];
	}
	delete[] students;
	delete[] sort_stud;
}
