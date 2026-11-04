#ifndef CPP_TASKS_LABB3_H_
#define CPP_TASKS_LABB3_H_

#include <string>
#include <vector>

namespace console {
    void Init();
    void Print(const std::string& text);
    void PrintLine(const std::string& text);
}

class Name {
public:
    Name() = default;

    explicit Name(std::string given_name);

    Name(std::string given_name, std::string surname);

    Name(std::string given_name, std::string surname,
        std::string patronymic);

    bool has_surname() const { return !surname_.empty(); }
    bool has_given_name() const { return !given_name_.empty(); }
    bool has_patronymic() const { return !patronymic_.empty(); }

    const std::string& surname() const { return surname_; }
    const std::string& given_name() const { return given_name_; }
    const std::string& patronymic() const { return patronymic_; }

    void set_surname(const std::string& surname) { surname_ = surname; }
    void set_patronymic(const std::string& patronymic) {
        patronymic_ = patronymic;
    }

    std::string ToString() const;

private:
    std::string surname_;
    std::string given_name_;
    std::string patronymic_;
};

class Person {
public:
    Person(std::string name, int height);
    Person(std::string name, int height, const Person* father);

    Person(Name name, int height);
    Person(Name name, int height, const Person* father);

    const Name& name() const { return name_; }
    int height() const { return height_; }
    const Person* father() const { return father_; }

    std::string ToString() const;

private:
    Name name_;
    int height_;
    const Person* father_;
};

class City {
public:
    struct Path {
        const City* destination;
        int cost;
    };

    explicit City(std::string name);

    const std::string& name() const { return name_; }
    const std::vector<Path>& paths() const { return paths_; }

    void AddPath(const City& city, int cost);

    std::string ToString() const;

private:
    std::string name_;
    std::vector<Path> paths_;
};

class Cat {
public:
    explicit Cat(std::string name);

    const std::string& name() const { return name_; }

    std::string ToString() const;

    void Meow() const;

    void Meow(int count) const;

private:
    std::string name_;
};

#endif  // CPP_TASKS_LABB3_H_
