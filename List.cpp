#include "List.h"
#include <iostream>
#include <cassert> // 用于测试断言
using namespace std;

/**
 * @brief 打印 List 的所有元素
 */
template <typename T>
void printList(const List<T>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    // 1. 测试默认构造函数和初始化列表构造函数
    List<int> lst1;  // 默认构造函数
    List<int> lst2 = {1, 2, 3, 4, 5};  // 初始化列表构造
    assert(lst2.size() == 5); // 断言测试
    printList(lst2);  // 输出: 1 2 3 4 5

    // 2. 测试拷贝构造函数
    List<int> lst3 = lst2;
    assert(lst3.size() == 5);
    printList(lst3);  // 输出: 1 2 3 4 5

    // 3. 测试移动构造函数
    List<int> lst4 = std::move(lst3);
    assert(lst4.size() == 5);  // lst4 应该成功接管 lst3 的数据
    assert(lst3.size() == 0);  // lst3 应该为空
    printList(lst4);  // 输出: 1 2 3 4 5

    // 4. 测试插入元素
    lst1.push_back(10);
    lst1.push_front(20);
    assert(lst1.size() == 2);
    printList(lst1);  // 输出: 20 10

    // 5. 测试删除元素
    lst1.pop_front();
    assert(lst1.size() == 1);
    printList(lst1);  // 输出: 10

    lst1.pop_back();
    assert(lst1.empty());  // 列表应该为空
    printList(lst1);  // 输出: (空行)

    // 6. 测试赋值运算符
    lst1 = lst4;
    assert(lst1.size() == 5);
    printList(lst1);  // 输出: 1 2 3 4 5

    // 7. 测试右值引用赋值
    lst1 = List<int>{6, 7, 8};
    assert(lst1.size() == 3);
    printList(lst1);  // 输出: 6 7 8

    // 8. 测试迭代器的正确性
    auto it = lst1.begin();
    assert(*it == 6);
    ++it;
    assert(*it == 7);
    ++it;
    assert(*it == 8);
    // 测试前置和后置自减运算符 (--it 和 it--)
    --it;  // 回到元素 7
    assert(*it == 7);
    cout << "前置自减测试通过: " << *it << endl;

    it--;  // 回到元素 6
    assert(*it == 6);
    cout << "后置自减测试通过: " << *it << endl;
    // 9. 测试边界条件：在空列表中插入和删除
    List<int> emptyList;
    emptyList.push_back(42);
    assert(emptyList.size() == 1);
    printList(emptyList);  // 输出: 42
    emptyList.pop_back();
    assert(emptyList.empty());

    // 10. 测试清空列表
    lst2.clear();
    assert(lst2.empty());  // 列表应该为空
    printList(lst2);  // 输出: (空行)

    cout << "所有测试用例通过！" << endl;
    return 0;
}
