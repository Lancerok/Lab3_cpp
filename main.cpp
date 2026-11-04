#include <iostream>
#include <limits>
#include <string>

#include "labb3.h"

namespace {

    struct MenuItem {
        int id;
        const char* title;
        void (*run)();
    };

    void RunTask12();
    void RunTask13();
    void RunTask22();
    void RunTask23();
    void RunTask3();
    void RunTask45();
    void RunTask46();
    void RunTask5();

    const MenuItem kMenu[] = {
        {1, "Задание 1 - задача 2: Человек", RunTask12},
        {2, "Задание 1 - задача 3: Имя", RunTask13},
        {3, "Задание 2 - задача 2: Человек с именем", RunTask22},
        {4, "Задание 2 - задача 3: Человек с родителем", RunTask23},
        {5, "Задание 3: Города", RunTask3},
        {6, "Задание 4 - задача 5: Создаем имена", RunTask45},
        {7, "Задание 4 - задача 6: Создаем человека", RunTask46},
        {8, "Задание 5: Кот мяукает", RunTask5},
    };

    void PrintMenu() {
        console::PrintLine("\n=== Меню ===");
        for (const MenuItem& item : kMenu) {
            console::PrintLine(std::to_string(item.id) + ". " + item.title);
        }
        console::PrintLine("0. Выход");
    }

    void PrintPerson(const Person& person) {
        console::PrintLine(person.ToString());
    }

    // Сохраняет формат вывода из задания 1.2 для старых пунктов меню.
    void PrintPersonLegacy(const Person& person) {
        console::PrintLine(person.name().ToString() + ", рост: " +
            std::to_string(person.height()));
    }

    void PrintCity(const City& city) {
        console::PrintLine(city.ToString());
    }

    bool RunMenuItem(int id) {
        for (const MenuItem& item : kMenu) {
            if (item.id == id) {
                item.run();
                return true;
            }
        }
        return false;
    }

    void WaitForEnter() {
        console::Print("\nНажмите Enter, чтобы вернуться в меню...");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    void RunTask12() {
        console::PrintLine("\n[Задание 1, задача 2: Человек]");
        const Person cleopatra(Name("Клеопатра"), 152);
        const Person pushkin(Name("Пушкин"), 167);
        const Person vladimir(Name("Владимир"), 189);

        PrintPersonLegacy(cleopatra);
        PrintPersonLegacy(pushkin);
        PrintPersonLegacy(vladimir);
    }

    void RunTask13() {
        console::PrintLine("\n[Задание 1, задача 3: Имя]");
        const Name cleopatra("Клеопатра");
        const Name pushkin("Александр", "Пушкин", "Сергеевич");
        const Name mayakovsky("Владимир", "Маяковский");

        console::PrintLine(cleopatra.ToString());
        console::PrintLine(pushkin.ToString());
        console::PrintLine(mayakovsky.ToString());
    }

    void RunTask22() {
        console::PrintLine("\n[Задание 2, задача 2: Человек с именем]");
        const Person cleopatra(Name("Клеопатра"), 152);
        const Person pushkin(
            Name("Александр", "Пушкин", "Сергеевич"), 167);
        const Person mayakovsky(Name("Владимир", "Маяковский"), 189);

        PrintPersonLegacy(cleopatra);
        PrintPersonLegacy(pushkin);
        PrintPersonLegacy(mayakovsky);
    }

    void RunTask23() {
        console::PrintLine("\n[Задание 2, задача 3: Человек с родителем]");
        const Person ivan(Name("Иван", "Чудов"), 180);
        const Person peter(Name("Пётр", "Чудов"), 175, &ivan);
        const Person boris(Name("Борис"), 120, &peter);

        PrintPersonLegacy(ivan);
        PrintPersonLegacy(peter);
        PrintPersonLegacy(boris);
    }

    void RunTask3() {
        console::PrintLine("\n[Задание 3: Города]");
        City a("A");
        City b("B");
        City c("C");
        City d("D");
        City e("E");
        City f("F");

        a.AddPath(b, 5);
        a.AddPath(f, 1);
        a.AddPath(d, 6);

        b.AddPath(a, 5);
        b.AddPath(c, 3);

        c.AddPath(b, 3);
        c.AddPath(d, 4);

        d.AddPath(a, 6);
        d.AddPath(c, 4);
        d.AddPath(e, 2);

        e.AddPath(d, 2);
        e.AddPath(f, 2);

        f.AddPath(b, 1);
        f.AddPath(e, 2);

        PrintCity(a);
        PrintCity(b);
        PrintCity(c);
        PrintCity(d);
        PrintCity(e);
        PrintCity(f);
    }

    void RunTask45() {
        console::PrintLine("\n[Задание 4, задача 5: Создаем имена]");
        const Name cleopatra("Клеопатра");
        const Name pushkin("Александр", "Пушкин", "Сергеевич");
        const Name mayakovsky("Владимир", "Маяковский");
        const Name bonifatievich("Христофор", "Бонифатьевич");

        console::PrintLine(cleopatra.ToString());
        console::PrintLine(pushkin.ToString());
        console::PrintLine(mayakovsky.ToString());
        console::PrintLine(bonifatievich.ToString());
    }

    void RunTask46() {
        console::PrintLine("\n[Задание 4, задача 6: Создаем человека]");
        const Person lev("Лев", 170);
        const Person sergey(Name("Сергей", "Пушкин"), 168, &lev);
        const Person alexander("Александр", 167, &sergey);

        PrintPerson(lev);
        PrintPerson(sergey);
        PrintPerson(alexander);
    }

    void RunTask5() {
        console::PrintLine("\n[Задание 5: Кот мяукает]");
        const Cat barsik("Барсик");

        console::PrintLine(barsik.ToString());
        barsik.Meow();
        barsik.Meow(3);
    }

}  // namespace

int main() {
    console::Init();

    while (true) {
        PrintMenu();
        console::Print("Выберите пункт: ");

        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            console::PrintLine("Ошибка: нужно ввести число.");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            console::PrintLine("Выход.");
            break;
        }

        if (!RunMenuItem(choice)) {
            console::PrintLine("Такого пункта нет.");
        }
        if (std::cin.eof()) {
            break;
        }
        WaitForEnter();
        if (std::cin.eof()) {
            break;
        }
    }
}
