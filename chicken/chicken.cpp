#include <iostream>
#include <cstring>

class Chicken {
private:
    int age = 24;
    char *name = nullptr;

public:
    Chicken() : age(0), name(nullptr) {}

    Chicken(int _age) : age(_age), name(nullptr) {}

    Chicken(int _age, const char *_name) : age(_age) {
        if (_name) {
            int len = strlen(_name) + 1;
            name = new char[len];
            strcpy(name, _name);
        }
    }

    Chicken(const Chicken &other) : age(other.age) {
        if (other.name) {
            int len = strlen(other.name) + 1;
            name = new char[len];
            strcpy(name, other.name);
        }
    }

    Chicken &operator=(const Chicken &other) {
        if (this != &other) {
            delete[] name;
            age = other.age;
            if (other.name) {
                int len = strlen(other.name) + 1;
                name = new char[len];
                strcpy(name, other.name);
            } else {
                name = nullptr;
            }
        }
        return *this;
    }

    Chicken(Chicken &&other) noexcept : age(other.age), name(other.name) {
        other.name = nullptr;
    }

    Chicken &operator=(Chicken &&other) noexcept {
        if (this != &other) {
            delete[] name;
            age = other.age;
            name = other.name;
            other.name = nullptr;
        }
        return *this;
    }

    ~Chicken() {
        delete[] name;
    }

    void setAge(int _age) {
        age = _age;
    }

    void setName(const char *_name) {
        delete[] name;
        if (_name) {
            int len = strlen(_name) + 1;
            name = new char[len];
            strcpy(name, _name);
        } else {
            name = nullptr;
        }
    }

    const char *getName() const {
        return name ? name : "Unnamed";
    }

    const int &getAge() const {
        return age;
    }
};

int main() {
    Chicken c1(24, "Kunkun");
    std::cout << "Hi, everyone! My name is " << c1.getName() << ", I am " << c1.getAge() << " years old." << std::endl;

    Chicken c2 = c1;
    std::cout << "Copying: My name is " << c2.getName() << ", I am " << c2.getAge() << " years old." << std::endl;

    Chicken c3;
    c3 = c1;
    std::cout << "Assigning: My name is " << c3.getName() << ", I am " << c3.getAge() << " years old." << std::endl;

    Chicken c4 = std::move(c1);
    std::cout << "Moving: My name is " << c4.getName() << ", I am " << c4.getAge() << " years old." << std::endl;

    return 0;
}
