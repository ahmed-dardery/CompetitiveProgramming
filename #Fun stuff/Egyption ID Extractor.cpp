#include <iostream>
#include <string>
using namespace std;

int CheckDigit(string& myid)
{
	int power = 2;
	int sum = 0;
	for (int i = myid.length() - 1 - 1; i >= 0; i--)		//loops backwards
	{
		sum += (myid[i] - '0') * power;
		if (++power > 7) power = 2;
	}
	int res = 11 - (sum % 11);
	if (res > 9) res -= 10;  //11 corresponds to 1, and 10 corresponds to 0
	return (res);
}

inline int tonumber(const char& x) { return (x - '0'); }
inline int tonumber(const char& x, const char& y) { return (x - '0') * 10 + (y - '0'); }


int main()
{
	int centuryvalue, yearvalue, monthvalue, dayvalue, birthvalue, gendervalue;

	cout << "Please enter an Egyptian ID to verify:\n";
	string myid;
	getline(cin, myid);
	if (myid.length() != 14)
	{
		cout << "The ID you inputted is not 14 digits, please check it.\n";
		cin.get();
		return 0;
	}
	int chkd = CheckDigit(myid);
	if (chkd != (myid[13] - '0'))
	{
		cout << "The ID you inputted is not a genuine ID. A genuine one would have ended in a(n) " << chkd << " instead.\nDo you want to proceed anyway? (y/n)\n";
		string myanswer;
		getline(cin, myanswer);
		if (myanswer != "y") return 0;
	}
	else cout << "Verified!\n";

	centuryvalue = tonumber(myid[0]);
	yearvalue = tonumber(myid[1], myid[2]);
	monthvalue = tonumber(myid[3], myid[4]);
	dayvalue = tonumber(myid[5], myid[6]);
	birthvalue = tonumber(myid[7], myid[8]);
	gendervalue = tonumber(myid[12]);

	string birthlocation;
	switch (birthvalue)
	{
		case 29: birthlocation = "Luxor"; break;
		case 02: birthlocation = "Alexandria"; break;
		case 19: birthlocation = "Ismailia"; break;
		case 18: birthlocation = "Bohera"; break;
		case 21: birthlocation = "Giza"; break;
		case 12: birthlocation = "Dakahlia"; break;
		case 13: birthlocation = "Sharkeia"; break;
		case 16: birthlocation = "Gharbeia"; break;
		case 01: birthlocation = "Cairo"; break;
		case 14: birthlocation = "Kalyobia"; break;
		case 17: birthlocation = "Monofia"; break;
		case 24: birthlocation = "Minya"; break;
		case 28: birthlocation = "Aswan"; break;
		case 25: birthlocation = "Asyut"; break;
		case 22: birthlocation = "Bani Swef"; break;
		case 26: birthlocation = "Sohag"; break;
		case 27: birthlocation = "Kena"; break;
		case 15: birthlocation = "Kafr El Sheik"; break;
		case 33: birthlocation = "Matrouh"; break;
		case 88: birthlocation = "Outside Egypt"; break;
		default: birthlocation = "Unknown"; break;
	}
	cout << "\nDate of birth: " << dayvalue << "/" << monthvalue << "/" << 17 + centuryvalue << yearvalue;
	cout << "\nPlace of birth: " << birthlocation;
	cout << "\nGender: " << ((gendervalue % 2 == 0) ? "Female" : "Male");


	cin.get();
}

