#include <iostream>
#include <cstring>

class Chicken {
private:
    int age = 24;
    char *name = nullptr;

public:
    Chicken() : age(0) {}

    Chicken(int _age) : age(_age) {}

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
        if (_name == nullptr) {
            delete[] name;
            name = nullptr;
            return;
        }
        delete[] name;
        int len = strlen(_name) + 1;
        name = new char[len];
        strcpy(name, _name);
    }

    const char *getName() const {
        return name ? name : "Unnamed";
    }

    const int &getAge() const {
        return age;
    }
};

int main() {
    auto print = [](const Chicken &c) {
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old." << std::endl;
    };

    Chicken c(24, "Kunkun");
    print(c);

    Chicken d;
    d = c;
    print(d);

    Chicken a = c;
    print(a);

    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d);

    Chicken b;
    b = d = c;
    print(b);
    print(d);

    return 0;
}
