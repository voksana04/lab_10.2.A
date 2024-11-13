#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <algorithm>

using namespace std;

// ������ ��������������
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, BIOLOGY };
string specializationStr[] = { "����'����� �����", "����������", "Գ����", "��������", "�������" };

// ��������� ��� ������������� ��������
struct Student {
    string surname;
    unsigned course;
    Specialization specialization;
    int physics;
    int mathematics;
    int informatics;
};

// ��������� �������
void InputStudents(Student* students, int N);
void PrintStudents(const Student* students, int N);
void SortStudents(Student* students, int N);
void IndexSort(int* indexArray, const Student* students, int N);
int BinarySearch(const Student* students, int* indexArray, int N, const string& surname, Specialization spec, unsigned course);
void PrintTableHeader();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int numStudents;
    cout << "������ ������� ��������: ";
    cin >> numStudents;

    Student* students = new Student[numStudents];
    int* indexArray = new int[numStudents];

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� ����� ��������\n";
        cout << "2 - ���� ����� ��������\n";
        cout << "3 - Գ����� ���������� ��������\n";
        cout << "4 - �������� ���������� ��������\n";
        cout << "5 - ����� ��������\n";
        cout << "0 - �����\n";
        cout << "������� ��: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            InputStudents(students, numStudents);
            break;
        case 2:
            PrintStudents(students, numStudents);
            break;
        case 3:
            SortStudents(students, numStudents);
            cout << "������ �������� ����������� �������.\n";
            break;
        case 4:
            IndexSort(indexArray, students, numStudents);
            cout << "�������� ���������� ��������.\n";
            PrintStudents(students, numStudents);
            break;
        case 5:
        {
            string surname;
            int spec, course;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): ";
            cin >> spec;
            cout << "������ ����: ";
            cin >> course;

            int pos = BinarySearch(students, indexArray, numStudents, surname, static_cast<Specialization>(spec), course);
            if (pos != -1) {
                cout << "������� ���������:\n";
                cout << students[indexArray[pos]].surname << ", ���� " << students[indexArray[pos]].course
                    << ", ������������ " << specializationStr[students[indexArray[pos]].specialization] << "\n";
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] indexArray;
    return 0;
}

void InputStudents(Student* students, int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        cin.ignore();
        cout << " �������: "; getline(cin, students[i].surname);
        cout << " ����: "; cin >> students[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): ";
        cin >> spec;
        students[i].specialization = static_cast<Specialization>(spec);
        cout << " ������ � ������: "; cin >> students[i].physics;
        cout << " ������ � ����������: "; cin >> students[i].mathematics;
        cout << " ������ � �����������: "; cin >> students[i].informatics;
    }
}

void PrintTableHeader() {
    cout << "=============================================================================================\n";
    cout << "| � | �������         | ���� | ������������           | Գ���� | ���������� | ����������� |\n";
    cout << "---------------------------------------------------------------------------------------------\n";
}

void PrintStudents(const Student* students, int N) {
    PrintTableHeader();
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << "| ";
        cout << setw(15) << left << students[i].surname;
        cout << "  | " << setw(4) << right << students[i].course;
        cout << " | " << setw(21) << left << specializationStr[students[i].specialization];
        cout << "   | " << setw(6) << right << students[i].physics;
        cout << " | " << setw(10) << right << students[i].mathematics;
        cout << " | " << setw(11) << right << students[i].informatics << " |\n";
    }
    cout << "=============================================================================================\n";
}

void SortStudents(Student* students, int N) {
    sort(students, students + N, [](const Student& a, const Student& b) {
        if (a.specialization != b.specialization) return a.specialization < b.specialization;
        if (a.course != b.course) return a.course < b.course;
        return a.surname < b.surname;
        });
}

void IndexSort(int* indexArray, const Student* students, int N) {
    for (int i = 0; i < N; i++) indexArray[i] = i;

    sort(indexArray, indexArray + N, [&](int a, int b) {
        if (students[a].specialization != students[b].specialization)
            return students[a].specialization < students[b].specialization;
        if (students[a].course != students[b].course)
            return students[a].course < students[b].course;
        return students[a].surname < students[b].surname;
        });
}

int BinarySearch(const Student* students, int* indexArray, int N, const string& surname, Specialization spec, unsigned course) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Student& s = students[indexArray[mid]];

        if (s.surname == surname && s.specialization == spec && s.course == course) return mid;

        if (s.specialization < spec || (s.specialization == spec && s.course < course) ||
            (s.specialization == spec && s.course == course && s.surname < surname)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
