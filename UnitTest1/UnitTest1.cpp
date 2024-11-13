#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\admin\source\repos\Project_10.2.А\Project_10.2.А\lab_10.2.a.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestSortStudents)
		{
			
			Student students[] = {
				{"Ivanov", 2, COMPUTER_SCIENCE, 90, 85, 75},
				{"Petrov", 1, MATHEMATICS, 80, 90, 70},
				{"Sidorov", 3, COMPUTER_SCIENCE, 75, 60, 85}
			};

			
			Student expectedStudents[] = {
				{"Ivanov", 2, COMPUTER_SCIENCE, 90, 85, 75},
				{"Sidorov", 3, COMPUTER_SCIENCE, 75, 60, 85},
				{"Petrov", 1, MATHEMATICS, 80, 90, 70}
			};

			
			SortStudents(students, 3);

			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedStudents[i].surname, students[i].surname, L"Surname mismatch");
				Assert::AreEqual(expectedStudents[i].course, students[i].course, L"Course mismatch");
				Assert::AreEqual(static_cast<int>(expectedStudents[i].specialization), static_cast<int>(students[i].specialization), L"Specialization mismatch");
			}
		}

		TEST_METHOD(TestIndexSort)
		{
			Student students[] = {
				{"Ivanov", 2, COMPUTER_SCIENCE, 90, 85, 75},
				{"Petrov", 1, MATHEMATICS, 80, 90, 70},
				{"Sidorov", 3, COMPUTER_SCIENCE, 75, 60, 85}
			};
			int indexArray[3];

			
			int expectedIndexArray[] = { 0, 2, 1 };

			
			IndexSort(indexArray, students, 3);

			
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedIndexArray[i], indexArray[i], L"Index array mismatch");
			}
		}

		TEST_METHOD(TestBinarySearch)
		{
			Student students[] = {
				{"Ivanov", 2, COMPUTER_SCIENCE, 90, 85, 75},
				{"Petrov", 1, MATHEMATICS, 80, 90, 70},
				{"Sidorov", 3, COMPUTER_SCIENCE, 75, 60, 85}
			};
			int indexArray[3];
			IndexSort(indexArray, students, 3);

			
			int pos = BinarySearch(students, indexArray, 3, "Ivanov", COMPUTER_SCIENCE, 2);
			Assert::AreEqual(0, pos, L"Student Ivanov not found at the expected position");

			
			pos = BinarySearch(students, indexArray, 3, "Smirnov", PHYSICS, 1);
			Assert::AreEqual(-1, pos, L"Nonexistent student found");
		}
	};
}
