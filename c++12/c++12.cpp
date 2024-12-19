#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Violation {
    string description;
    string date;

    Violation(const string& desc, const string& d) : description(desc), date(d) {}
};

struct TreeNode {
    string carNumber;
    vector<Violation> violations;
    TreeNode* left, * right;

    TreeNode(const string& carNum) : carNumber(carNum), left(nullptr), right(nullptr) {}
};

class ViolationDatabase {
private:
    TreeNode* root;

    void addViolation(TreeNode*& node, const string& carNumber, const Violation& violation) {
        if (node == nullptr) {
            node = new TreeNode(carNumber);
            node->violations.push_back(violation);
        }
        else if (carNumber < node->carNumber) {
            addViolation(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber) {
            addViolation(node->right, carNumber, violation);
        }
        else {
            node->violations.push_back(violation); 
        }
    }

    void printDatabase(TreeNode* node) const {
        if (node == nullptr) return;
        printDatabase(node->left);
        cout << "Номер машины: " << node->carNumber << "\nПравонарушения:\n";
        for (const auto& violation : node->violations) {
            cout << "  Описание: " << violation.description << ", Дата: " << violation.date << "\n";
        }
        cout << endl;
        printDatabase(node->right);
    }

    TreeNode* searchByCarNumber(TreeNode* node, const string& carNumber) const {
        if (node == nullptr || node->carNumber == carNumber) {
            return node;
        }
        if (carNumber < node->carNumber) {
            return searchByCarNumber(node->left, carNumber);
        }
        else {
            return searchByCarNumber(node->right, carNumber);
        }
    }

    void printByRange(TreeNode* node, const string& start, const string& end) const {
        if (node == nullptr) return;
        if (node->carNumber >= start) {
            printByRange(node->left, start, end);
            if (node->carNumber <= end) {
                cout << "Номер машины: " << node->carNumber << "\nПравонарушения:\n";
                for (const auto& violation : node->violations) {
                    cout << "  Описание: " << violation.description << ", Дата: " << violation.date << "\n";
                }
                cout << endl;
            }
            printByRange(node->right, start, end);
        }
        else {
            printByRange(node->right, start, end);
        }
    }

public:
    ViolationDatabase() : root(nullptr) {}

    void addViolation(const string& carNumber, const Violation& violation) {
        addViolation(root, carNumber, violation);
    }

    void printDatabase() const {
        printDatabase(root);
    }

    void printByCarNumber(const string& carNumber) const {
        TreeNode* node = searchByCarNumber(root, carNumber);
        if (node) {
            cout << "Номер машины: " << node->carNumber << "\nПравонарушения:\n";
            for (const auto& violation : node->violations) {
                cout << "  Описание: " << violation.description << ", Дата: " << violation.date << "\n";
            }
            cout << endl;
        }
        else {
            cout << "Машина с номером " << carNumber << " не найдена.\n";
        }
    }

    void printByRange(const string& start, const string& end) const {
        printByRange(root, start, end);
    }
};

int main() {
    ViolationDatabase database;

    database.addViolation("A123BC", Violation("Превышение скорости", "2024-12-15"));
    database.addViolation("B456CD", Violation("Невыполнение правила поворота", "2024-12-16"));
    database.addViolation("A123BC", Violation("Отсутствие страховки", "2024-12-17"));
    database.addViolation("C789EF", Violation("Проезд на красный", "2024-12-18"));

    cout << "Полная распечатка базы данных:\n";
    database.printDatabase();

    cout << "\nРаспечатка по номеру A123BC:\n";
    database.printByCarNumber("A123BC");

    cout << "\nРаспечатка по диапазону номеров (A123BC - C789EF):\n";
    database.printByRange("A123BC", "C789EF");

    return 0;
}
