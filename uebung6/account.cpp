#include <iostream>
#include <cassert>
#include <list>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


class Account {
public:
	Account(long accountNo, double balance, double limit, bool locked);
	~Account();

	long accountNo() const { return accountNo_; }

	virtual void setLimit(double limit) { limit_ = limit; }
	double getLimit() const { return limit_; }

	virtual bool credit(double amount);
	virtual bool debit(double amount);
	double balance() const { return balance_; }

	void setLock(bool locked) { locked_ = locked; }
	bool getLock() const { return locked_; }

private:
	long accountNo_;
	double balance_;
	double limit_;
	bool locked_;
};

Account::Account(long accountNo, double balance, double limit, bool locked) :
	accountNo_{ accountNo },
	balance_{ balance },
	limit_(limit),
	locked_{ locked }
{}

Account::~Account() {}

bool Account::credit(double amount)
{
	assert(amount >= 0.0);

	// cannot use locked account
	if (locked_) return false;

	balance_ = balance_ + amount;
	return true;
}

bool Account::debit(double amount)
{
	assert(amount >= 0.0);

	// cannot use locked account
	if (locked_) return false;

	// check if limit is hit
	if (balance_ - amount < limit_) return false;

	// change balance
	balance_ = balance_ - amount;
	return true;
}
//--------------------------------------------------------------------------------------------
//Start of LoggedAccount
class LoggedAccount :public Account {
private:
	vector<pair<string, double>> transactionList;
	double initBalance;
public:
	LoggedAccount(long accountNo, double balance, double limit, bool locked);
	~LoggedAccount() {};
	vector<pair<string, double>> transactions();
	virtual bool credit(double amount) override;
	virtual bool debit(double amount) override;
	virtual void setLimit(double limit) override;
};
//-------------------------------------------------------------------------------------------
//methods of LoggedAccount


double initBalance;
LoggedAccount::LoggedAccount(long accountNo, double balance, double limit, bool locked) :Account(accountNo, balance, limit, locked), initBalance{ balance }, transactionList{}
{
	transactionList.insert(transactionList.begin(), make_pair("**initial balance**", initBalance));
}

vector<pair<string, double>> LoggedAccount::transactions() {
	vector<pair<string, double>> tempTransaction{ transactionList };
	//make_pair("initial balance", initBalance)
	tempTransaction.push_back(make_pair("**current balance**", balance()));
	return tempTransaction;
}

bool LoggedAccount::credit(double amount) {
	bool success = Account::credit(amount);
	if (success)
		transactionList.push_back(make_pair("credit", amount));
	return success;
}
bool LoggedAccount::debit(double amount) {
	bool success = Account::debit(amount);
	if (success)
		transactionList.push_back(make_pair("debit", amount));
	return success;
}
void LoggedAccount::setLimit(double limit) {
	Account::setLimit(limit);
	transactionList.push_back(make_pair("setLimit", limit));

}


int main(int argc, char** argv)
{
	Account A1(19920, 0.0, -1000.0, false);
	LoggedAccount A2(20020, 0.0, -1000.0, false);

	A1.credit(500.0);
	A2.credit(500.0);
	A2.debit(100.0);
	A2.setLimit(-2000.);

	for (const auto& x : A2.transactions())
	{
		cout << x.first << ": " << x.second << endl;
	}

	return 0;
}

