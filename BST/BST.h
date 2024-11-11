#ifndef BST_H
#define BST_H
#include <algorithm>
#include <iostream>
#include <utility>

template <typename Comparable>
class BinarySearchTree {
protected:

    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;

        BinaryNode(const Comparable &ele, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        BinaryNode(Comparable&& ele, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

    BinaryNode *root;

    int height(BinaryNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    void insert(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr, 0};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
        t->height = 1 + std::max(height(t->left), height(t->right));
        balance(t);
    }

    void insert(Comparable &&x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr, 0};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }
        t->height = 1 + std::max(height(t->left), height(t->right));
        balance(t);
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            return;
        }

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else {
            if (t->left != nullptr && t->right != nullptr) {
                BinaryNode *minNode = findMin(t->right);
                t->element = std::move(minNode->element);
                remove(t->element, t->right);
            } else {
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }

        if (t != nullptr) {
            t->height = 1 + std::max(height(t->left), height(t->right));
            balance(t);
        }
    }

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    void balance(BinaryNode *&t) {
        if (t == nullptr) {
            return;
        }

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }

        t->height = 1 + std::max(height(t->left), height(t->right));
    }

    void rotateWithLeftChild(BinaryNode *&k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = 1 + std::max(height(k2->left), height(k2->right));
        k1->height = 1 + std::max(height(k1->left), height(k1->right));
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *&k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = 1 + std::max(height(k1->left), height(k1->right));
        k2->height = 1 + std::max(height(k2->left), height(k2->right));
        k1 = k2;
    }

    void doubleWithLeftChild(BinaryNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(BinaryNode *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

public:
    BinarySearchTree() : root{nullptr} {}

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    void printTree() const {
        if (root == nullptr) {
            std::cout << "Empty tree" << std::endl;
        } else {
            printTree(root);
        }
    }

private:
    void printTree(BinaryNode *t) const {
        if (t != nullptr) {
            printTree(t->left);
            std::cout << t->element << " ";
            printTree(t->right);
        }
    }
};

#endif // BST_H
