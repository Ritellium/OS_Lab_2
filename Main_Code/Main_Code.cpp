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
    int* Arr;
};

DWORD WINAPI Min_Max(LPVOID data) {

    Data Array = *(static_cast<Data*>(data));

    int min = Array.Arr[0];
    int max = Array.Arr[0];

    for (int i = 0; i < Array.Size; i++) {
        if (Array.Arr[i] < min)
        {
            Sleep(7);
            min = Array.Arr[i];
        }
        if (Array.Arr[i] > max)
        {
            Sleep(7);
            max = Array.Arr[i];
        }
    }

    printf("Min Element: %d \n", min);
    printf("Max Element: %d \n", max);

    ExitThread(0);
}

DWORD WINAPI Average(LPVOID data) {

    Data Array = *(static_cast<Data*>(data));

    int Summ = 0;
    for (int i = 0; i < Array.Size; ++i) {
        Summ += Array.Arr[i];
        Sleep(12);
    }
    
    double average = static_cast<double>(Summ) / static_cast<double>(Array.Size);

    printf("Average value of Array: %f \n", average);

    ExitThread(0);
}

int main() {

    HANDLE hThread_MinMax;
    HANDLE hThread_Average;

    int* Array;
    int Size;

    printf("Enter number of elements: ");
    scanf_s("%d", &Size);
    Array = new int[Size];

    printf("Enter elements: \n");
    for (int i = 0; i < Size; i++) 
    {
        printf("element %d: ", i);
        scanf_s("%d", &Array[i]);
    }

    Data data;
    data.Arr = Array;
    data.Size = Size;

    hThread_MinMax = CreateThread(nullptr, 0, Min_Max, &data, 0, nullptr);
    WaitForSingleObject(hThread_MinMax, INFINITE);

    hThread_Average = CreateThread(nullptr, 0, Average, &data, 0, nullptr);
    WaitForSingleObject(hThread_Average, INFINITE);

    return 0;

}