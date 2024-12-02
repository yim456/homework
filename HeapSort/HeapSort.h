#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>
#include <functional>

//将数组 arr 转换为最大堆
template <typename T>
void heapify(std::vector<T>& arr, int n, int i)
{
    int largest = i; // 初始化最大值为根节点
    int left = 2 * i + 1; // 左子节点索引
    int right = 2 * i + 2; // 右子节点索引

    if (left < n && arr[left] > arr[largest])    // 如果左子节点存在且大于根节点，更新最大值
        largest = left;

    if (right < n && arr[right] > arr[largest])  // 如果右子节点存在且大于当前最大值，更新最大值
        largest = right;

    if (largest != i)                            // 如果最大值不是根节点，交换并递归
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

//heapSort函数
template <typename T>
void heapSort(std::vector<T>& arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)    //从最后一个非叶子节点向前遍历每个节点，利用heapify函数来确保子树满足最大堆的性质
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i)         //通过循环，逐步将堆中的最大元素移到数组末尾
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

#endif // HEAPSORT_H
