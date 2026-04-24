#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct Transaction {
    double deposit;
    double withdraw;
    double balance;

    Transaction(double d, double w, double b): deposit(d), withdraw(w), balance(b){}
};

class BankAccount {
   protected:
    double balance;
    std::vector<Transaction> transactionHistory;

   public:
    /*============================= 1.1.1. =============================*/
    BankAccount(double initialBalance):balance(initialBalance){}

    /*============================= 1.1.2. =============================*/
    virtual void deposit(double amount){
        if (amount <=0){
            return;
        }
        balance = balance + amount;
        transactionHistory.push_back(Transaction(amount, 0, balance));
        return;
    }

    /*============================= 1.1.3. =============================*/
    virtual void withdraw(double amount){
        if (amount <=0){
            return;
        }
        if(balance < amount){
            transactionHistory.push_back(Transaction(0, 0, balance));
        }
        else{
            balance = balance - amount;
            transactionHistory.push_back(Transaction(0, amount, balance));
        }
        return;        
    }

    /*============================= 1.1.4. =============================*/
    virtual double getBalance(){
        return balance;
    }

    /*============================= 1.1.5. =============================*/
    const std::vector<Transaction>& getTransactionHistory(){
        return transactionHistory;
    }

    // Do not modify this section.
    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
   private:
    double interestRate;

   public:
    /*============================= 1.2.1. =============================*/
    SavingsAccount(double initialBalance, double interestRate):BankAccount(initialBalance), interestRate(interestRate){}

    /*============================= 1.2.2. =============================*/
    void deposit(double amount) override{
        if (amount <=0){
            return;
        }
        double total_deposit = amount * (1 + interestRate);
        balance = balance + total_deposit;
        transactionHistory.push_back(Transaction(total_deposit, 0, balance));
        return;
    }

    /*============================= 1.2.3. =============================*/
    ~SavingsAccount() override{
        std::cout << "SavingsAccount closed" << std::endl;
    }
};

class CheckingAccount : public BankAccount {
   private:
    double transactionFee;

   public:
    /*============================= 1.3.1. =============================*/
    CheckingAccount(double initialBalance, double transactionFee): BankAccount(initialBalance), transactionFee(transactionFee){}

    /*============================= 1.3.2. =============================*/
    void withdraw(double amount) override{
        if (amount <=0){
            return;
        }
        double total_withdrawal = amount + transactionFee;

        if(balance < total_withdrawal){
            transactionHistory.push_back(Transaction(0, 0, balance));
        }
        else{
            balance = balance - total_withdrawal;
            transactionHistory.push_back(Transaction(0, total_withdrawal, balance));
        }
        return;
    }

    /*============================= 1.3.3. =============================*/
    ~CheckingAccount() override{
        std::cout << "CheckingAccount closed" << std::endl;
    }
};

class BusinessAccount : public BankAccount {
   private:
    double creditLine;

   public:
    /*============================= 1.4.1. =============================*/
    BusinessAccount(double initialBalance, double creditLine):BankAccount(initialBalance), creditLine(creditLine){}

    /*============================= 1.4.2. =============================*/
    void withdraw(double amount) override{
        if (amount <=0){
            return;
        }
        if(balance + creditLine < amount){
            transactionHistory.push_back(Transaction(0, 0, balance));
        }
        else{
            balance = balance - amount;
            transactionHistory.push_back(Transaction(0, amount, balance));
        }
        return;        
    }

    /*============================= 1.4.3. =============================*/
    ~BusinessAccount() override{
        std::cout << "BusinessAccount closed" << std::endl;
    }
};

class AccountManager {
   private:
    std::vector<std::shared_ptr<BankAccount>> accounts;

    bool check_valid_index(int idx){
        if (idx <0 ){
            return false;
        }
        else if (idx >= accounts.size()){
            return false;
        }
        else return true;
    }

   public:
    /*============================= 1.5.1. =============================*/
    void addAccount(const std::shared_ptr<BankAccount>& account){
        accounts.push_back(account);
    }

    /*============================= 1.5.2. =============================*/
    void transferFunds(int fromIndex, int toIndex, double amount){
        if(!check_valid_index(fromIndex) || !check_valid_index(toIndex)){
            throw std::runtime_error("Invalid account index");
        }
        else{
            accounts[fromIndex]->withdraw(amount);
            if(accounts[fromIndex]->getTransactionHistory().back().withdraw != 0){
                // withdraw success
                accounts[toIndex]->deposit(amount);
            }
        }
    }

    /*============================= 1.5.3. =============================*/
    std::shared_ptr<BankAccount> getAccount(int index){
        if (!check_valid_index(index)){
            throw std::runtime_error("Invalid account index");
        }
        else{
            return accounts[index];
        }
    }
};
