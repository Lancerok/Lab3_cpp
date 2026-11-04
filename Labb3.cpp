#include "labb3.h"

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif  // NOMINMAX
#include <windows.h>
#endif  // _WIN32

namespace {

#ifdef _WIN32
    // Кодировка, которую использует консоль Visual Studio.
    constexpr int kConsoleCodePage = 1251;

    // Кодировка, в которой компилятор создал строковые литералы.
    int SourceCodePage() {
#if defined(_MSVC_EXECUTION_CHARACTER_SET)
        return _MSVC_EXECUTION_CHARACTER_SET;
#elif defined(_MSC_VER)
        return static_cast<int>(GetACP());
#else
        return 65001;
#endif
    }

    std::wstring ToWide(const std::string& text, int code_page) {
        if (text.empty()) {
            return std::wstring();
        }
        const int length = MultiByteToWideChar(
            code_page, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
        if (length <= 0) {
            return std::wstring();
        }
        std::wstring result(static_cast<std::size_t>(length), L'\0');
        MultiByteToWideChar(code_page, 0, text.data(),
            static_cast<int>(text.size()), &result[0], length);
        return result;
    }

    std::string ToNarrow(const std::wstring& text, int code_page) {
        if (text.empty()) {
            return std::string();
        }
        const int length = WideCharToMultiByte(
            code_page, 0, text.data(), static_cast<int>(text.size()),
            nullptr, 0, nullptr, nullptr);
        if (length <= 0) {
            return std::string();
        }
        std::string result(static_cast<std::size_t>(length), '\0');
        WideCharToMultiByte(code_page, 0, text.data(),
            static_cast<int>(text.size()), &result[0], length,
            nullptr, nullptr);
        return result;
    }
#endif  // _WIN32

    bool EndsWith(const std::string& text, const std::string& suffix) {
        return text.size() >= suffix.size() &&
            text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    std::string DropSuffix(const std::string& text, const std::string& suffix) {
        return text.substr(0, text.size() - suffix.size());
    }

    // Образует мужское отчество от личного имени.
    std::string MakePatronymic(const std::string& given_name) {
        if (given_name.empty()) {
            return "";
        }
        if (given_name == "Пётр" || given_name == "Петр") {
            return "Петрович";
        }
        if (given_name == "Павел") {
            return "Павлович";
        }
        if (given_name == "Лев") {
            return "Львович";
        }
        if (given_name == "Яков") {
            return "Яковлевич";
        }
        if (given_name == "Михаил") {
            return "Михайлович";
        }
        if (given_name == "Дмитрий") {
            return "Дмитриевич";
        }
        if (given_name == "Данила" || given_name == "Гаврила") {
            return DropSuffix(given_name, "а") + "ович";
        }
        if (EndsWith(given_name, "ий")) {
            return DropSuffix(given_name, "ий") + "ьевич";
        }
        if (EndsWith(given_name, "й")) {
            return DropSuffix(given_name, "й") + "евич";
        }
        if (EndsWith(given_name, "ь")) {
            return DropSuffix(given_name, "ь") + "евич";
        }
        if (EndsWith(given_name, "а")) {
            return DropSuffix(given_name, "а") + "ич";
        }
        if (EndsWith(given_name, "я")) {
            return DropSuffix(given_name, "я") + "ич";
        }
        return given_name + "ович";
    }

}  // namespace

namespace console {

    void Init() {
#ifdef _WIN32
        SetConsoleOutputCP(kConsoleCodePage);
#endif
    }

    // Для консоли используется Unicode-вывод, для pipe — CP1251.
    void Print(const std::string& text) {
#ifdef _WIN32
        const std::wstring wide = ToWide(text, SourceCodePage());
        if (!wide.empty()) {
            std::wstring console_text;
            console_text.reserve(wide.size() + 2);
            for (wchar_t ch : wide) {
                if (ch == L'\n') {
                    console_text += L"\r\n";
                }
                else {
                    console_text += ch;
                }
            }
            const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD written = 0;
            if (handle != INVALID_HANDLE_VALUE &&
                WriteConsoleW(handle, console_text.data(),
                    static_cast<DWORD>(console_text.size()),
                    &written, nullptr)) {
                return;
            }
            std::cout << ToNarrow(wide, kConsoleCodePage);
            return;
        }
        std::cout << text;
#else
        std::cout << text;
#endif
    }

    void PrintLine(const std::string& text) { Print(text + "\n"); }

}  // namespace console

Name::Name(std::string given_name) : given_name_(std::move(given_name)) {}

Name::Name(std::string given_name, std::string surname)
    : surname_(std::move(surname)),
    given_name_(std::move(given_name)) {
}

Name::Name(std::string given_name, std::string surname,
    std::string patronymic)
    : surname_(std::move(surname)),
    given_name_(std::move(given_name)),
    patronymic_(std::move(patronymic)) {
}

std::string Name::ToString() const {
    std::string result;
    const auto append_part = [&result](const std::string& part) {
        if (part.empty()) {
            return;
        }
        if (!result.empty()) {
            result.push_back(' ');
        }
        result += part;
        };

    append_part(surname_);
    append_part(given_name_);
    append_part(patronymic_);
    return result;
}

Person::Person(std::string name, int height)
    : Person(Name(std::move(name)), height) {
}

Person::Person(std::string name, int height, const Person* father)
    : Person(Name(std::move(name)), height, father) {
}

Person::Person(Name name, int height)
    : Person(std::move(name), height, nullptr) {
}

// Остальные конструкторы делегируют сюда, поэтому присваивания
// выполняются только в этом конструкторе.
Person::Person(Name name, int height, const Person* father)
    : name_(std::move(name)), height_(height), father_(father) {
    if (father_ == nullptr) {
        return;
    }
    if (!name_.has_surname() && father_->name().has_surname()) {
        name_.set_surname(father_->name().surname());
    }
    if (!name_.has_patronymic() && father_->name().has_given_name()) {
        name_.set_patronymic(MakePatronymic(father_->name().given_name()));
    }
}

std::string Person::ToString() const {
    return name_.ToString() + ", " + std::to_string(height_);
}

City::City(std::string name) : name_(std::move(name)) {}

void City::AddPath(const City& city, int cost) {
    paths_.push_back(Path{ &city, cost });
}

std::string City::ToString() const {
    std::string result = name_ + ":";
    bool first = true;
    for (const Path& path : paths_) {
        result += first ? " " : ", ";
        first = false;
        result += path.destination->name();
        result += ":";
        result += std::to_string(path.cost);
    }
    return result;
}

Cat::Cat(std::string name) : name_(std::move(name)) {}

std::string Cat::ToString() const {
    return "кот: " + name_;
}

void Cat::Meow() const { Meow(1); }

void Cat::Meow(int count) const {
    if (count <= 0) {
        return;
    }
    std::string result = name_ + ": ";
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            result += '-';
        }
        result += "мяу";
    }
    result += '!';
    console::PrintLine(result);
}