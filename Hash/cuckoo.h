#ifndef CUCKOO_HASH_TABLE_H
#define CUCKOO_HASH_TABLE_H

#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cassert>
#include <iostream> // 用于调试信息输出

// 模板类实现布谷鸟哈希表
template <typename AnyType, typename HashFamily>
class CuckooHashTable {
public:
    // 构造函数：初始化哈希表
    explicit CuckooHashTable(int size = 101)
        : array(size), currentSize{0}, numHashFunctions{hashFunctions.getNumberOfFunctions()}, rehashes{0} {
        if (size <= 1) throw std::invalid_argument("哈希表大小必须大于1");
    }

    // 清空哈希表
    void makeEmpty() {
        currentSize = 0;
        std::fill(array.begin(), array.end(), HashEntry());
    }

    // 检查是否包含某元素
    bool contains(const AnyType &x) const {
        for (int i = 0; i < numHashFunctions; ++i) {
            int pos = myhash(x, i);
            if (isActive(pos) && array[pos].element == x) return true;
        }
        return false;
    }

    // 删除元素
    bool remove(const AnyType &x) {
        for (int i = 0; i < numHashFunctions; ++i) {
            int pos = myhash(x, i);
            if (isActive(pos) && array[pos].element == x) {
                array[pos].isActive = false;
                --currentSize;
                return true;
            }
        }
        return false;
    }

    // 插入元素（传值）
    bool insert(const AnyType &x) {
        if (contains(x)) return false; // 避免重复插入
        return insertHelper(x);
    }

    // 插入元素（移动语义）
    bool insert(AnyType &&x) {
        if (contains(x)) return false;
        return insertHelper(std::move(x));
    }

    // 返回当前表中元素数量
    int size() const {
        return currentSize;
    }

private:
    // 哈希表的每个槽位结构
    struct HashEntry {
        AnyType element;
        bool isActive;

        // 构造函数
        HashEntry(const AnyType &e = AnyType(), bool a = false) : element{e}, isActive{a} {}
        HashEntry(AnyType &&e, bool a = false) : element{std::move(e)}, isActive{a} {}
    };

    // 插入元素的辅助函数（传值版本）
    bool insertHelper(const AnyType &x) {
        const int MAX_DISPLACEMENTS = 10;
        AnyType temp = x;

        for (int count = 0; count < MAX_DISPLACEMENTS; ++count) {
            for (int i = 0; i < numHashFunctions; ++i) {
                int pos = myhash(temp, i);
                if (!isActive(pos)) {
                    array[pos] = HashEntry(temp, true);
                    ++currentSize;
                    return true;
                }
                std::swap(temp, array[pos].element);
            }
        }
        rehash();
        return insertHelper(std::move(temp));
    }

    // 插入元素的辅助函数（移动语义版本）
    bool insertHelper(AnyType &&x) {
        const int MAX_DISPLACEMENTS = 10;
        AnyType temp = std::move(x);

        for (int count = 0; count < MAX_DISPLACEMENTS; ++count) {
            for (int i = 0; i < numHashFunctions; ++i) {
                int pos = myhash(temp, i);
                if (!isActive(pos)) {
                    array[pos] = HashEntry(std::move(temp), true);
                    ++currentSize;
                    return true;
                }
                std::swap(temp, array[pos].element);
            }
        }
        rehash();
        return insertHelper(std::move(temp));
    }

    // 检查槽位是否被占用
    bool isActive(int currentPos) const {
        return currentPos >= 0 && currentPos < static_cast<int>(array.size()) && array[currentPos].isActive;
    }

    // 哈希函数
    size_t myhash(const AnyType &x, int which) const {
        size_t hashValue = hashFunctions.hash(x, which);
        return hashValue % array.size(); // 确保索引合法
    }

    // 重新哈希
    void rehash() {
        std::vector<HashEntry> oldArray = array;

        // 扩展为下一素数大小
        array.assign(nextPrime(2 * oldArray.size()), HashEntry());
        currentSize = 0;

        for (auto &entry : oldArray) {
            if (entry.isActive) {
                insert(std::move(entry.element));
            }
        }
    }

    // 判断一个数是否为素数
    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // 找到下一个素数
    int nextPrime(int n) const {
        while (!isPrime(n)) ++n;
        return n;
    }

    std::vector<HashEntry> array;  // 哈希表数组
    int currentSize;               // 当前元素数量
    int numHashFunctions;          // 哈希函数数量
    int rehashes;                  // 已发生的重哈希次数
    HashFamily hashFunctions;      // 哈希函数族
};

#endif // CUCKOO_HASH_TABLE_H
