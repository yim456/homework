#include "cuckoo.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include <cassert> // 用于断言检查

// 自定义哈希函数族
struct ImprovedHashFamily {
    // 返回哈希函数数量
    int getNumberOfFunctions() const { return 3; }

    // 哈希函数：根据索引生成不同的哈希值
    size_t hash(const std::string &key, int i) const {
        std::hash<std::string> hasher;
        return hasher(std::to_string(i) + key) ^ (std::hash<int>{}(i));
    }
};

// 测试插入性能
void measureInsertionPerformance(CuckooHashTable<std::string, ImprovedHashFamily> &table, const std::vector<std::string> &testData) {
    auto totalStart = std::chrono::high_resolution_clock::now(); // 总时间计时
    std::vector<double> insertTimes;

    for (const auto &item : testData) {
        auto start = std::chrono::high_resolution_clock::now();
        bool success = table.insert(item); // 插入数据
        auto end = std::chrono::high_resolution_clock::now();

        // 验证插入是否成功
        assert(success && "插入失败：可能是重哈希次数超限或数据冲突过多");

        std::chrono::duration<double, std::micro> elapsed = end - start; // 计算插入耗时（微秒级）
        insertTimes.push_back(elapsed.count());
    }

    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalElapsed = totalEnd - totalStart;

    double averageTime = 0.0;
    for (const auto &time : insertTimes) {
        averageTime += time;
    }
    averageTime /= testData.size();

    std::cout << "插入了 " << testData.size() << " 个元素，总耗时 " << totalElapsed.count() << " 秒" << std::endl;
    std::cout << "每次插入的平均耗时为 " << averageTime << " 微秒" << std::endl;
}

// 随机生成测试数据
std::vector<std::string> generateRandomStrings(int count, int length) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis('a', 'z');
    std::vector<std::string> testData;

    for (int i = 0; i < count; ++i) {
        std::string s(length, ' ');
        std::generate(s.begin(), s.end(), [&]() { return char(dis(gen)); });
        testData.push_back(s);
    }

    return testData;
}

int main() {
    int tableSize = 1009; // 初始化哈希表大小（选择一个素数）
    std::vector<double> loadFactors = {0.1, 0.2, 0.3, 0.4, 0.45};

    std::cout << std::fixed << std::setprecision(2);

    for (double loadFactor : loadFactors) {
        // 初始化哈希表
        CuckooHashTable<std::string, ImprovedHashFamily> table(tableSize);

        // 计算需要插入的元素数量
        int numElements = static_cast<int>(tableSize * loadFactor);

        // 打印测试信息
        std::cout << "\n测试装载率: " << loadFactor << ", 表大小: " << tableSize << ", 插入数据量: " << numElements << std::endl;

        // 生成测试数据
        auto testData = generateRandomStrings(numElements, 10);

        // 测试插入性能
        measureInsertionPerformance(table, testData);

        // 验证表中元素数量是否正确
        assert(table.size() == numElements && "表中元素数量不匹配，可能有插入失败");

        std::cout << "----------------------------------------" << std::endl;
    }

    return 0;
}
