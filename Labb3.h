#ifndef CPP_TASKS_LABB3_H_
#define CPP_TASKS_LABB3_H_

#include <string>
#include <vector>

// Вывод строк в кодировке текущей консоли.
namespace console {
    void Init();
    void Print(const std::string& text);
    void PrintLine(const std::string& text);
}  // namespace console

// Полное имя, состоящее из фамилии, личного имени и отчества.
// Любая из частей может отсутствовать.
class Name {
public:
    Name() = default;

    // Создаёт имя только из личного имени.
    explicit Name(std::string given_name);

    // Создаёт имя из личного имени и фамилии.
    Name(std::string given_name, std::string surname);

    // Создаёт имя из личного имени, фамилии и отчества.
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

    // Возвращает строку вида "Фамилия Имя Отчество".
    // Отсутствующие части пропускаются.
    std::string ToString() const;

private:
    std::string surname_;
    std::string given_name_;
    std::string patronymic_;
};

// Человек с именем, ростом и необязательным отцом.
class Person {
public:
    // Создаёт человека; строка задаёт только личное имя.
    Person(std::string name, int height);
    Person(std::string name, int height, const Person* father);

    // Создаёт человека из готового имени.
    Person(Name name, int height);
    Person(Name name, int height, const Person* father);

    const Name& name() const { return name_; }
    int height() const { return height_; }
    const Person* father() const { return father_; }

    // Возвращает строку вида "Имя, рост".
    std::string ToString() const;

private:
    Name name_;
    int height_;
    const Person* father_;
};

// Город и исходящие из него пути к другим городам.
class City {
public:
    struct Path {
        const City* destination;
        int cost;
    };

    explicit City(std::string name);

    const std::string& name() const { return name_; }
    const std::vector<Path>& paths() const { return paths_; }

    // Добавляет путь к городу. City не владеет городом назначения.
    void AddPath(const City& city, int cost);

    // Возвращает строку вида "A: B:5, F:1".
    std::string ToString() const;

private:
    std::string name_;
    std::vector<Path> paths_;
};

// Кот с именем, который умеет мяукать.
class Cat {
public:
    explicit Cat(std::string name);

    const std::string& name() const { return name_; }

    // Возвращает строку вида "кот: Барсик".
    std::string ToString() const;

    // Выводит "Имя: мяу!".
    void Meow() const;

    // Выводит "Имя: мяу-мяу-...-мяу!" с count повторами.
    void Meow(int count) const;

private:
    std::string name_;
};

#endif  // CPP_TASKS_LABB3_H_