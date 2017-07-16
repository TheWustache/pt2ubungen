#include <string>
#include <cassert>
#include <cmath>
//for tests
#include <iostream>
#include <cassert>
#include <vector>


enum Tax {
	NORMAL = 19, REDUCED = 13//in %

};

class Amount
{
public:
	enum Currency {
		EUR, USD
	};
	/*Amount(double amount, Tax t = NORMAL, Currency c = EUR) :
		netto{ amount },
		description{ "" },
		currentCurrency{ c },
		taxRate{ NORMAL },
		taxAmount{ netto * taxRate / 100.0 },
		brutto{ netto + taxAmount }
		{}
	Amount(double amount, Tax t) :
		netto { amount},
		description { ""},
		currentCurrency { EUR},
		taxRate { NORMAL},
		taxAmount { netto * taxRate / 100.0},
		brutto { netto + taxAmount}
		{}
	Amount(double amount, std::string des = "", Tax t = NORMAL) :
		netto { amount},
		description { des},
		currentCurrency { EUR},
		taxRate { NORMAL},
		taxAmount { netto * taxRate / 100.0},
		brutto { netto + taxAmount}
	{}
	Amount(double amount, std::string des = "", Currency c = EUR) :
		netto { amount},
		description { des},
		currentCurrency { c},
		taxRate { NORMAL},
		taxAmount { netto * taxRate / 100.0},
		brutto { netto + taxAmount}
		{}*/
	Amount(double amount, std::string des = "", Tax t = NORMAL, Currency c = EUR) :
		netto{ amount },
		description{ des },
		currentCurrency{ c },
		taxRate{ t }
	{
		taxAmount = netto * taxRate / 100.0;
		brutto = netto + taxAmount;
	}
	~Amount() {};
	void changeDescription(std::string des) {
		description = des;
	}
	std::string getDescription() const {
		return description;
	}
	//maybe add rounding
	double getNetto()const {
		return netto;
	}
	void setNetto(double n) {
		netto = n;
	}
	void addNetto(double n) {
		setNetto(netto + n);
	}
	double getBrutto() const {
		return brutto;
	}
	Currency getCurrency() const {
		return currentCurrency;
	}
	void setCurrency(Currency c) {
		if (currentCurrency != c) {
			if (currentCurrency == EUR)
				netto = netto * EURtoUSD;
			else
				netto = netto / EURtoUSD;
			taxAmount = netto * (taxRate / 100.0);
			brutto = netto + taxAmount;
			currentCurrency = c;
		}
	}
	void changeTax(Tax t) {
		taxRate = t;
	}
	Tax getTax() const {
		return taxRate;
	}
private:
	const double EURtoUSD = 1.5;
	double netto;
	double taxAmount;
	double brutto;
	std::string description;
	Tax taxRate;
	Currency currentCurrency;

};
std::ostream& operator<<(std::ostream& os, const Amount& a) {
	os << a.getDescription() << ": Netto:" << a.getNetto() << ", Brutto:" << a.getBrutto();
	return os;
}

void test()
{
	// Implement tests
	double a = 5.0, b = 7.5, c = 12.5;
	std::vector<Amount> testClasses;
	Amount a1 = Amount(b); testClasses.push_back(a1);
	Amount a2 = Amount(a, "a2"); testClasses.push_back(a2);
	Amount a3 = Amount(b, "a3", REDUCED); testClasses.push_back(a3);
	Amount a4 = Amount(c, "a4", REDUCED, Amount::USD); testClasses.push_back(a4);
	Amount a5 = Amount(c, "a4", REDUCED, Amount::EUR); testClasses.push_back(a5);
	for (Amount a : testClasses) {
		std::cout << a << ", Currency: " << a.getCurrency() << ", taxAmount: " << a.getBrutto() - a.getNetto() << ", taxRate: " << a.getTax();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (Amount a : testClasses) {
		a.setCurrency(Amount::EUR);
		std::cout << a <<std::endl;
	}
	std::cout << std::endl;
	for (Amount a : testClasses) {
		a.setCurrency(Amount::USD);
		std::cout << a << std::endl;
	}


}

int main()
{
	test();
	return 0;
}
