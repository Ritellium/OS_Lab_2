#include <iostream>
#include <thread>
#include <vector>

/*
Написать программу для консольного процесса, 
который состоит из трех потоков: main, min_max и average
*/

struct Data {
    double* Arr;
    double min_elem;
    double max_elem;
    double average_elem;
};

void Min_Max(std::vector<double> &Array, std::pair<double, double> &minmax) 
{
    double min = Array[0];
    double max = Array[0];

    for (int i = 0; i < Array.size(); i++) {
        if (Array[i] < min)
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(7));
            min = Array[i];
        }
        if (Array[i] > max)
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(7));
            max = Array[i];
        }
    }

    std::cout << "Min Element: " << static_cast<int>(min) << std::endl;
    std::cout << "Max Element: " << static_cast<int>(max) << std::endl;

    minmax.first = min;
    minmax.second = max;

    return;
}

void Average(std::vector<double> &Array, double &average)
{
    double Summ = 0;
    for (int i = 0; i < Array.size(); ++i) {
        Summ += Array[i];
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(12));
    }
    
    average = Summ / static_cast<double>(Array.size());
    std::cout << "Average value of Array: " << average << std::endl;

    return;
}

int main() 
{
    std::cout << std::fixed;
    std::cout.precision(3);
    int Size;

    std::cout << "Enter number of elements: ";
    std::cin >> Size;
    std::vector<double> Array(Size, static_cast<double>(0));
    std::pair<double, double> minmax;
    double average;

    std::cout << "Enter elements:" << std::endl;
    for (int i = 0; i < Size; i++) 
    {
        std::cout << "element " << i << ": ";
        int elem;
        std::cin >>elem;
        Array[i] = static_cast<double>(elem);
    }

    std::thread ThreadMinMax(Min_Max, std::ref(Array), std::ref(minmax));
    ThreadMinMax.join();

    std::thread ThreadAverage(Average, std::ref(Array), std::ref(average));
    ThreadAverage.join();

    std::cout << "Array with all min/max elements to average:" << std::endl;
    for (int i = 0; i < Array.size(); i++) // Changes !All! min/max elements in Array
    {
        if (static_cast<int>(Array[i]) == static_cast<int>(minmax.first)
            || static_cast<int>(Array[i]) == static_cast<int>(minmax.second))
        {
            Array[i] = average;
            std::cout << "{" << Array[i] << "} ";
        }
        else
        {
            std::cout << static_cast<int>(Array[i]) << " ";
        }
    }

    return 0;
}