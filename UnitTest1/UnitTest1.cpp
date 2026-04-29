#include "CppUnitTest.h"
#include "D:\Project\OOP_6.7\OOP_6.7\main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestEraseCopy
{
    TEST_CLASS(TestEraseCopy)
    {
    public:

        // Видалення значення, що зустрічається кілька разів
        TEST_METHOD(RemovesAllOccurrencesOfValue)
        {
            int a[] = { 10, -5, 3, -1, 7, 3, 8 };
            int b[7] = { 0 };
            int newSize = erase_copy(a, a + 7, b, 3);

            Assert::AreEqual(5, newSize);
            int expected[] = { 10, -5, -1, 7, 8 };
            for (int i = 0; i < newSize; i++)
                Assert::AreEqual(expected[i], b[i]);
        }

        // Значення відсутнє — масив копіюється повністю
        TEST_METHOD(ValueNotPresent_CopiesAll)
        {
            int a[] = { 1, 2, 4, 5 };
            int b[4] = { 0 };
            int newSize = erase_copy(a, a + 4, b, 99);

            Assert::AreEqual(4, newSize);
            for (int i = 0; i < 4; i++)
                Assert::AreEqual(a[i], b[i]);
        }

        // Усі елементи рівні значенню — результат порожній
        TEST_METHOD(AllElementsEqual_ReturnsZero)
        {
            int a[] = { 2, 2, 2, 2 };
            int b[4] = { 0 };
            int newSize = erase_copy(a, a + 4, b, 2);

            Assert::AreEqual(0, newSize);
        }

        // Видалення від'ємного значення
        TEST_METHOD(RemovesNegativeValue)
        {
            int a[] = { -7, 3, -7, 5 };
            int b[4] = { 0 };
            int newSize = erase_copy(a, a + 4, b, -7);

            Assert::AreEqual(2, newSize);
            Assert::AreEqual(3, b[0]);
            Assert::AreEqual(5, b[1]);
        }

        // Один елемент збігається — результат порожній
        TEST_METHOD(SingleElementRemoved)
        {
            int a[] = { 5 };
            int b[1] = { 0 };
            int newSize = erase_copy(a, a + 1, b, 5);

            Assert::AreEqual(0, newSize);
        }

        // Один елемент не збігається — залишається
        TEST_METHOD(SingleElementKept)
        {
            int a[] = { 5 };
            int b[1] = { 0 };
            int newSize = erase_copy(a, a + 1, b, 9);

            Assert::AreEqual(1, newSize);
            Assert::AreEqual(5, b[0]);
        }
    };

    // ============================================================
    // Тести для erase_copy_if  (предикат Negative<int>)
    // ============================================================
    TEST_CLASS(TestEraseCopyIf)
    {
    public:

        // Змішаний масив — від'ємні видаляються
        TEST_METHOD(RemovesNegatives_MixedArray)
        {
            int a[] = { 10, -5, 3, -1, 7, 3, 8 };
            int b[7] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 7, b, isNeg);

            Assert::AreEqual(5, newSize);
            int expected[] = { 10, 3, 7, 3, 8 };
            for (int i = 0; i < newSize; i++)
                Assert::AreEqual(expected[i], b[i]);
        }

        // Усі додатні — нічого не видаляється
        TEST_METHOD(NoNegatives_CopiesAll)
        {
            int a[] = { 1, 2, 3, 4 };
            int b[4] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 4, b, isNeg);

            Assert::AreEqual(4, newSize);
            for (int i = 0; i < 4; i++)
                Assert::AreEqual(a[i], b[i]);
        }

        // Усі від'ємні — результат порожній
        TEST_METHOD(AllNegatives_ReturnsZero)
        {
            int a[] = { -3, -1, -7 };
            int b[3] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 3, b, isNeg);

            Assert::AreEqual(0, newSize);
        }

        // Нуль — не від'ємний, залишається
        TEST_METHOD(ZeroIsKept)
        {
            int a[] = { -2, 0, -4, 1 };
            int b[4] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 4, b, isNeg);

            Assert::AreEqual(2, newSize);
            Assert::AreEqual(0, b[0]);
            Assert::AreEqual(1, b[1]);
        }

        // Один від'ємний елемент — видаляється
        TEST_METHOD(SingleNegativeRemoved)
        {
            int a[] = { -9 };
            int b[1] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 1, b, isNeg);

            Assert::AreEqual(0, newSize);
        }

        // Один додатній елемент — залишається
        TEST_METHOD(SinglePositiveKept)
        {
            int a[] = { 42 };
            int b[1] = { 0 };
            Negative<int> isNeg;
            int newSize = erase_copy_if(a, a + 1, b, isNeg);

            Assert::AreEqual(1, newSize);
            Assert::AreEqual(42, b[0]);
        }
    };
}