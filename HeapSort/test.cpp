#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "HeapSort.h"

// check函数，检测每⼀次排序的正确性
template <typename T>
bool check(const std::vector<T>& arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

std::vector<int> generateRandom(int n)                                   // 生成随机序列
{
    std::vector<int> arr(n);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 1000000);
    for (int& x : arr) x = dist(gen);
    return arr;
}

std::vector<int> Order(int n)                                   // 生成有序序列
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    return arr;
}

std::vector<int> Reverse(int n)                                     // 生成逆序序列
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return arr;
}

std::vector<int> Repeat(int n)                                  // 生成部分重复元素序列
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i % 10; // 每10个元素重复
    return arr;
}

void print50(const std::vector<int>& arr, const std::string& title)         // 打印序列的前50个元素
{
    std::cout << title << "前50个元素:\n";
    for (int i = 0; i < 50 && i < arr.size(); ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";
}

// 测试函数
void testSorting(const std::vector<int>& arr, const std::string& sequenceType)
{
    std::vector<int> testArr = arr;

    print50(testArr, "尚未排序的");  // 打印未排序的前50个元素

    // 记录 heapSort 的时间
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(testArr);
    auto end = std::chrono::high_resolution_clock::now();
    double heapSortTime = std::chrono::duration<double>(end - start).count();
    std::cout << "heapSort 耗时: " << heapSortTime << " 秒\n";

    //检查正确性,利用三元运算符输出通过或者失败
    bool isRight1 = check(testArr);
    std::cout << "heapSort 正确性: " << (isRight1 ? "通过" : "失败") << "\n";

    // 打印已排序的前50个元素
    print50(testArr, "heapSort排序后的");

    // 记录 std::sort_heap 的时间
    testArr = arr;
    std::make_heap(testArr.begin(), testArr.end());
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(testArr.begin(), testArr.end());
    end = std::chrono::high_resolution_clock::now();
    double sortHeapTime = std::chrono::duration<double>(end - start).count();
    std::cout << "std::sort_heap 耗时: " << sortHeapTime << " 秒\n";

    // 检查std::sort_heap的正确性，同heapSort的情形
    bool isRight2 = check(testArr);
    std::cout << "std::sort_heap 正确性: " << (isRight2 ? "通过" : "失败") << "\n";

    // 打印std::sort_heap排序后的前50个元素
    print50(testArr, "std::sort_heap排序后的");

    std::cout << "------------------------------\n\n";
}

int main()
{
    // 定义序列长度n=1000000
    const int n = 1000000;
    std::cout << "输出排序前后的随机数列的元素（方便起见，输出前50个为例）\n\n";

    // 随机序列
    std::cout << "随机序列:\n";
    std::vector<int> randomNum = generateRandom(n);
    testSorting(randomNum, "随机");

    // 有序序列
    std::cout << "有序序列:\n";
    std::vector<int> orderNum = Order(n);
    testSorting(orderNum, "有序");

    // 逆序序列
    std::cout << "逆序序列:\n";
    std::vector<int> reverseNum = Reverse(n);
    testSorting(reverseNum, "逆序");

    // 部分重复序列
    std::cout << "部分重复序列:\n";
    std::vector<int> repeatNum = Repeat(n);
    testSorting(repeatNum, "部分重复");

    return 0;
}
