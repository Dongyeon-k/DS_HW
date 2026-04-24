#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "bankaccount.hpp"

void printTransactionHistory(const std::vector<Transaction>& history) {
    std::cout << "Transaction History:" << std::endl;
    for (const auto& transaction : history) {
        std::cout << " -> "
                  << "Deposit: " << transaction.deposit << ", "
                  << "Withdraw: " << transaction.withdraw << ", "
                  << "Balance: " << transaction.balance << std::endl;
    }
}

void compare(double expected, double actual) {
    std::string result = expected == actual ? "PASS" : "FAIL";
    std::cout << "[" << result << "]" << " "
              << "Expected: " << expected << ", "
              << "Actual: " << actual << std::endl;
}

int main() {
    /** SavingsAccount */
    std::cout << "::Test SavingsAccount::" << std::endl;

    std::shared_ptr<SavingsAccount> savings =
        std::make_shared<SavingsAccount>(1000.0, 0.05);
    savings->deposit(200);
    double savingsBalance = 1000 + 200 * (1 + 0.05);
    compare(savingsBalance, savings->getBalance());

    printTransactionHistory(savings->getTransactionHistory());
    std::cout << std::endl;

    /** CheckingAccount */
    std::cout << "::Test CheckingAccount::" << std::endl;

    std::shared_ptr<CheckingAccount> checking =
        std::make_shared<CheckingAccount>(500.0, 1.5);
    checking->withdraw(100);
    double checkingBalance = 500 - (100 + 1.5);
    compare(checkingBalance, checking->getBalance());
    checking->withdraw(600);
    compare(checkingBalance, checking->getBalance());

    printTransactionHistory(checking->getTransactionHistory());
    std::cout << std::endl;

    /** BusinessAccount */
    std::cout << "::Test BusinessAccount::" << std::endl;

    std::shared_ptr<BusinessAccount> business =
        std::make_shared<BusinessAccount>(2000.0, 5000.0);
    business->withdraw(4000);
    double businessBalance = 2000 - 4000;
    compare(businessBalance, business->getBalance());
    business->withdraw(8000);
    compare(businessBalance, business->getBalance());

    printTransactionHistory(business->getTransactionHistory());
    std::cout << std::endl;

    /** AccountManager */
    std::cout << "::Test AccountManager::" << std::endl;

    AccountManager manager;
    manager.addAccount(savings);
    manager.addAccount(checking);
    manager.addAccount(business);

    manager.transferFunds(0, 1, 100);  // transfer 100 from savings to checking
    savingsBalance -= 100;
    checkingBalance += 100;
    compare(savingsBalance, manager.getAccount(0)->getBalance());
    compare(checkingBalance, manager.getAccount(1)->getBalance());

    std::cout << "SavingsAccount ";
    printTransactionHistory(manager.getAccount(0)->getTransactionHistory());
    std::cout << "CheckingAccount ";
    printTransactionHistory(manager.getAccount(1)->getTransactionHistory());
    std::cout << std::endl;

    return 0;
}
