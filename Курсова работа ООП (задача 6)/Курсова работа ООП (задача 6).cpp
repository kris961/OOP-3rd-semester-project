#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>

using namespace std;

//Кристиян Михнев 2к 1б 21621353 задача 6

class TV {
private:
	string producer;
	int screenSize;
	bool isSmart;

public:
	TV() {
		this->producer = "";
		this->screenSize = 0;
		this->isSmart = false;
	}
	TV(string producer,int size) {
		this->producer = producer;
		this->screenSize = size;
	}
	TV(int size) {
		this->screenSize = size;
		this->producer = "unknown";
	}
	TV(const TV& TV) {
		this->producer = TV.producer;
		this->screenSize = TV.screenSize;
		this->isSmart = TV.isSmart;
	}
	void setIsSmart(bool isSmart) {
		this->isSmart = isSmart;
	}

	int GetScreenSize()const {
		return this->screenSize;
	}
	string GetProducer()const {
		return this->producer;
	}
	bool GetSmart()const {
		return this->isSmart;
	}
	friend ostream& operator<<(ostream& out,const TV& TV) {
		out << "Producer: " << TV.producer << "ScreenSize: " << TV.screenSize<<"Smart: "<<TV.isSmart << endl;
		return out;
	}

	friend istream& operator>>(istream& in,TV& TV) {
		in >> TV.producer >> TV.screenSize;
		return in;
	}



	TV& operator=(const TV& TV) {
		this->producer = TV.producer;
		this->screenSize = TV.screenSize;
		this->isSmart = TV.isSmart;
		return *this;
	}

	bool operator<(const TV& TV) {
		if (this->screenSize < TV.screenSize) {
			return true;
		}
		return false;
	}
	bool operator==(const TV& TV) {
		bool same = false;
		if (this->screenSize == TV.screenSize) {
			same = true;
		}
		return same;
	}

};

class TVShop {
private:
	vector<TV> sales;
public:
	TVShop()
	{
	}
	TVShop(string fileName) {
		ifstream file;
		file.open(fileName);
		if (file.is_open()) {
			string prod;
			int size;
			string isSmart;
			TV temp;
			while (!file.eof()) {
				file >> temp;
				file >> isSmart;
				if (isSmart == "Smart") {
					temp.setIsSmart(true);
				}
				else {
					temp.setIsSmart(false);
				}
				this->sales.push_back(temp);
			}
		}
		else {
			throw new exception("File failed");
		}
	}
	TVShop(const vector<TV>& tvs) {
		this->sales = tvs;
	}

	friend istream& operator>>(istream& in, TVShop& shop) {
		TV temp("", 0);
		in >> temp;
		shop.sales.push_back(temp);
	}

	friend ostream& operator<<(ostream& out, const TVShop& shop) {
		for (int i = 0; i < shop.sales.size(); i++)
		{
			out << shop.sales[i];
		}
	}

	map<string, int>countSalesByProducer() {
		map<string, int> salesByP;
		for (int i = 0; i < sales.size(); i++)
		{
			string temp = sales[i].GetProducer();

			if (salesByP.count(temp)==0) {
				salesByP.insert({ temp, 1 });
			}
			else {
				salesByP[temp]++;
			}
		}
		return salesByP;
	}

	map<int, int>countSalesBySize() {
		map<int, int> salesByS;
		for (int i = 0; i < sales.size(); i++)
		{
			int temp = sales[i].GetScreenSize();

			if (salesByS.count(temp) == 0) {
				salesByS.insert({ temp, 1 });
			}
			else {
				salesByS[temp]++;
			}
		}
		return salesByS;
	}

	void MaxSalesByP(string& producer, int& num) {
		map<string, int>::iterator it;
		map<string, int> sales = countSalesByProducer();
		string producertemp;
		int sold=0;
		for (it=sales.begin();it!=sales.end();it++)
		{
			if (it->second > sold) {
				producertemp = it->first;
				sold = it->second;
			}
		}

		producer = producertemp;
		num = sold;
	}

	void MaxSalesByS(int& screen, int& num) {
		map<int, int>::iterator it;
		map<int, int> sales = countSalesBySize();
		int sizetemp=0;
		int sold = 0;
		for (it = sales.begin(); it != sales.end(); it++)
		{
			if (it->second > sold) {
				sizetemp = it->first;
				sold = it->second;
			}
		}

		screen = sizetemp;
		num = sold;
	}

	string compareSalesByProducer(string producer1, string producer2) {
		map<string, int> sales = countSalesByProducer();
		if (sales[producer1] == sales[producer2]) {
			return "Same amount of sales";
		}
		else if (sales[producer1] > sales[producer2]) {
			return producer1 + " has more sales";
		}
		else {
			return producer2 + " has more sales";
		}
	}

	string compareSalesBySize(int size1, int size2) {
		map<int, int> sales = countSalesBySize();
		if (sales[size1] == sales[size2]) {
			return "Same amount of sales";
		}
		else if (sales[size1] > sales[size2]) {
			return to_string(size1)+" has more sales";
		}
		else {
			return to_string(size2) + " has more sales";
		}
	}
};

void main()
{

	string filename = "input.txt";
	TVShop shop(filename);


	map<string, int> sales = shop.countSalesByProducer();
	map<string, int>::iterator it;
	for (it = sales.begin(); it != sales.end(); it++)
	{
		cout << it->first << " " << it->second<<endl;
	}

	map<int, int> salesS = shop.countSalesBySize();

	map<int, int>::iterator it1;
	for (it1 = salesS.begin(); it1 != salesS.end(); it1++)
	{
		cout << it1->first << " " << it1->second<<endl;
	}

	//max sales
	string producer;
	int sold;
	shop.MaxSalesByP(producer,sold);
	cout << "Max Sales By Producer: " << producer << " " << sold<<endl;

	int size;
	shop.MaxSalesByS(size, sold);
	cout << "Max Sales By Size: " << size << " " << sold<<endl;
	//compare by sales
	cout<<shop.compareSalesByProducer("Sony", "Samsung")<<endl;
	cout << shop.compareSalesBySize(55, 50);
}