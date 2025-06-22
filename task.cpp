// Вариант 25 Банковский кредит сортировка по ставке
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>

class Credit {
    std::string name;
    double amount;
    std::string currency;
    double stake;

public:
    Credit(std::string n = "", double a = 0, std::string c = "", double r = 0)
        : name(n), amount(a), currency(c), stake(r) {}

    // Для сортировки в set
    bool operator<(const Credit& other) const {
        return stake < other.stake;
    }

    // Для unordered_set
    bool operator==(const Credit& other) const {
        return name == other.name && 
               amount == other.amount &&
               currency == other.currency &&
               stake == other.stake;
    }

    // Хэш-функция
    struct Hash {
        int operator()(const Credit& credit) const {
            return std::hash<std::string>()(credit.name) ^
                   std::hash<double>()(credit.amount) ^
                   std::hash<std::string>()(credit.currency) ^
                   std::hash<double>()(credit.stake);
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Credit& credit) {
        os << "Name: " << credit.name << "\n"
           << "Sum: " << credit.amount << "\n"
           << "Currency: " << credit.currency << "\n"
           << "Stake: " << credit.stake << "\n";
        return os;
    }
};

int main() {
    std::ifstream input("input.txt");

    std::set<Credit> creditSet;
    std::unordered_set<Credit, Credit::Hash> creditUnorderedSet;

    std::string name, currency;
    double amount, rate;

    // Чтение данных из файла
    while (std::getline(input, name)) {
        input >> amount;
        input.ignore();
        std::getline(input, currency);
        input >> rate;
        input.ignore();

        Credit credit(name, amount, currency, rate);
        creditSet.insert(credit);
        creditUnorderedSet.insert(credit);
    }

    input.close();

    // Вывод set
    std::cout << "set" << std::endl;
    for (const auto& credit : creditSet) {
        std::cout << credit << std::endl;
    }

    // Вывод unordered_set
    std::cout << "\nunordered_set" << std::endl;
    for (const auto& credit : creditUnorderedSet) {
        std::cout << credit << std::endl;
    }

    return 0;
}
