#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <algorithm>

using namespace std;

// Перелік спеціальностей
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, BIOLOGY };
string specializationStr[] = { "Комп'ютерні науки", "Математика", "Фізика", "Інженерія", "Біологія" };

// Структура для представлення студента
struct Student {
    string surname;
    unsigned course;
    Specialization specialization;
    int physics;
    int mathematics;
    int informatics;
};

// Прототипи функцій
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
    cout << "Введіть кількість студентів: ";
    cin >> numStudents;

    Student* students = new Student[numStudents];
    int* indexArray = new int[numStudents];

    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Введення даних студентів\n";
        cout << "2 - Вивід даних студентів\n";
        cout << "3 - Фізичне сортування студентів\n";
        cout << "4 - Індексне сортування студентів\n";
        cout << "5 - Пошук студента\n";
        cout << "0 - Вихід\n";
        cout << "Виберіть дію: ";
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
            cout << "Список студентів відсортовано фізично.\n";
            break;
        case 4:
            IndexSort(indexArray, students, numStudents);
            cout << "Індексне сортування виконано.\n";
            PrintStudents(students, numStudents);
            break;
        case 5:
        {
            string surname;
            int spec, course;
            cout << "Введіть прізвище для пошуку: ";
            cin >> surname;
            cout << "Введіть спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): ";
            cin >> spec;
            cout << "Введіть курс: ";
            cin >> course;

            int pos = BinarySearch(students, indexArray, numStudents, surname, static_cast<Specialization>(spec), course);
            if (pos != -1) {
                cout << "Студент знайдений:\n";
                cout << students[indexArray[pos]].surname << ", курс " << students[indexArray[pos]].course
                    << ", спеціальність " << specializationStr[students[indexArray[pos]].specialization] << "\n";
            }
            else {
                cout << "Студента не знайдено.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] indexArray;
    return 0;
}

void InputStudents(Student* students, int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":\n";
        cin.ignore();
        cout << " Прізвище: "; getline(cin, students[i].surname);
        cout << " Курс: "; cin >> students[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): ";
        cin >> spec;
        students[i].specialization = static_cast<Specialization>(spec);
        cout << " Оцінка з фізики: "; cin >> students[i].physics;
        cout << " Оцінка з математики: "; cin >> students[i].mathematics;
        cout << " Оцінка з інформатики: "; cin >> students[i].informatics;
    }
}

void PrintTableHeader() {
    cout << "=============================================================================================\n";
    cout << "| № | Прізвище         | Курс | Спеціальність           | Фізика | Математика | Інформатика |\n";
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
