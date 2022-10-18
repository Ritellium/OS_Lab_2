#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <process.h>

/*
Написать программу для консольного процесса, 
который состоит из трех потоков: main, min_max и average
*/

struct Data {
    int Size;
    double* Arr;
    double min_elem;
    double max_elem;
    double average_elem;
};

DWORD WINAPI Min_Max(LPVOID data) {

    Data *Array = static_cast<Data*>(data);

    double min = Array->Arr[0];
    double max = Array->Arr[0];

    for (int i = 0; i < Array->Size; i++) {
        if (Array->Arr[i] < min)
        {
            Sleep(7);
            min = Array->Arr[i];
        }
        if (Array->Arr[i] > max)
        {
            Sleep(7);
            max = Array->Arr[i];
        }
    }

    printf("Min Element: %d \n", static_cast<int>(min));
    printf("Max Element: %d \n", static_cast<int>(max));

    Array->min_elem = min;
    Array->max_elem = max;

    ExitThread(0);
}

DWORD WINAPI Average(LPVOID data) {

    Data *Array = static_cast<Data*>(data);

    double Summ = 0;
    for (int i = 0; i < Array->Size; ++i) {
        Summ += Array->Arr[i];
        Sleep(12);
    }
    
    double average = Summ / static_cast<double>(Array->Size);

    printf("Average value of Array: %f \n", average);

    Array->average_elem = average;

    ExitThread(0);
}

int main() {

    HANDLE hThread_MinMax;
    HANDLE hThread_Average;

    double* Array;
    int Size;

    printf("Enter number of elements: ");
    scanf_s("%d", &Size);
    Array = new double[Size];

    printf("Enter elements: \n");
    for (int i = 0; i < Size; i++) 
    {
        printf("element %d: ", i);
        int elem;
        scanf_s("%d", &elem);
        Array[i] = static_cast<double>(elem);
    }

    Data data;
    data.Arr = Array;
    data.Size = Size;

    hThread_MinMax = CreateThread(nullptr, 0, Min_Max, &data, 0, nullptr);
    WaitForSingleObject(hThread_MinMax, INFINITE);

    hThread_Average = CreateThread(nullptr, 0, Average, &data, 0, nullptr);
    WaitForSingleObject(hThread_Average, INFINITE);

    printf("Array with all min/max elements to average: \n");
    for (int i = 0; i < Size; i++) // Changes !All! min/max elements in Array
    {
        if (static_cast<int>(Array[i]) == static_cast<int>(data.min_elem)
            || static_cast<int>(Array[i]) == static_cast<int>(data.max_elem))
        {
            Array[i] = data.average_elem;
            printf("{%f} ", Array[i]);
        }
        else
        {
            printf("%d ", static_cast<int>(Array[i]));
        }
    }

    return 0;

}