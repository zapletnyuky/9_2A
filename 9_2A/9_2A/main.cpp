#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
enum Spec { KN, IT, MATH, PHYSICS, TRYDN };
enum Curs { FIRST, SECOND, THIRD, FOURTH };
string cursStr[] = { "I", "II", "III", "IV" };
string specStr[] = { "КомпНауки", "Інформ", "Мат+Ек", "Фіз+Інф", "ТрудНавч" };
struct Student
{
    string prizv;
    Curs curs;
    Spec spec;
    struct
    {
        int physic;
        int math;
        int inform;
    };
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int inform);

int main()
{

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];
    int ispec;
    Spec spec;
    string prizv;
    int inform = 0;
    int found;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем/спеціальністю/профільною оцінкою " << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            break;
        case 4:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
                
            cout << " Прізвище: ";
                cin >> prizv;
                cout << endl;

            cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> ispec;
            spec = (Spec)ispec;
//            cin.get();
//            cin.sync();
            cout << endl;
            
            cout << "третя оцінка: ";
            cin >> inform;
            cout << endl;

            if ((found = BinSearch(p, N, prizv, spec, inform)) != -1)
                cout << "Знайдено cтудента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
//        default:
//            cout << "Ви ввели помилкове значення! "
//                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);
    return 0;

}
void Create(Student* p, const int N)
{
    int spec;
    int curs;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
        cout << " прізвище: ";
        getline(cin, p[i].prizv);
        cout << " курс (0 - I, 1 - II, 2 - III, 3 - IV): ";
        cin >> curs;
        cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        cout << " оцінка з фізики : "; cin >> p[i].physic;
        cout << " оцінка з математики : "; cin >> p[i].math;
        cout << " оцінка з інформатики : "; cin >> p[i].inform;
        p[i].spec = (Spec)spec;
        p[i].curs = (Curs)curs;
    }
}
void Print(Student* p, const int N)
{
    cout << "======================================================================================================="
        << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з інформатики |"
        << endl;
    cout << "-------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1;
        cout << "| " << setw(9) << p[i].prizv;
        cout << "| " << setw(5) << cursStr[p[i].curs];
        cout << "| " << setw(14) << specStr[p[i].spec];
        cout << "| " << setw(16) << p[i].physic;
        cout << "| " << setw(20) << p[i].math;
        cout << "| " << setw(21) << p[i].inform << "|";
        cout << endl;
    }
    cout << "======================================================================================================="
        << endl;
    cout << endl;
}
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].spec > p[i1 + 1].spec)
                ||
                (p[i1].spec == p[i1 + 1].spec &&
                    p[i1].inform > p[i1 + 1].inform)
                ||
                ((p[i1].spec == p[i1 + 1].spec &&
                    p[i1].inform == p[i1 + 1].inform) &&
                    p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}
int* IndexSort(Student* p, const int N)
{ // використовуємо метод вставки для формування індексного масиву

  /*int i, j, value;
  for (i = 1; i < length; i++) {
  value = a[i];
  for (j = i - 1; j >= 0 && a[j] > value; j--) {
  a[j + 1] = a[j];
  }
  a[j + 1] = value;
  }*/
    int* I = new int[N]; // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i; // заповнили його початковими даними
    int i, j, value; // починаємо сортувати масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((p[I[j]].spec < p[value].spec)
                ||
                (p[I[j]].curs == p[value].curs &&
                    p[I[j]].inform < p[value].inform)
                ||
                ((p[I[j]].spec == p[value].spec &&
                    p[I[j]].inform == p[value].inform) &&
                    p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
    cout << "======================================================================================================="
        << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з інформатики |"
        << endl;
    cout << "-------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1;
        cout << "| " << setw(9) << p[I[i]].prizv;
        cout << "| " << setw(5) << cursStr[p[I[i]].curs];
        cout << "| " << setw(14) << specStr[p[I[i]].spec];
        cout << "| " << setw(16) << p[I[i]].physic;
        cout << "| " << setw(20) << p[I[i]].math;
        cout << "| " << setw(21) << p[I[i]].inform << "|";
        cout << endl;
    }
    cout << "======================================================================================================="
        << endl;
    cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int inform)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].spec == spec && p[m].inform == inform)
            return m;
        if ((p[m].prizv < prizv)
            ||
            (p[m].prizv == prizv &&
                p[m].spec < spec)
            ||
            ((p[m].prizv == prizv &&
                p[m].spec == spec) &&
                p[m].inform < inform))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
