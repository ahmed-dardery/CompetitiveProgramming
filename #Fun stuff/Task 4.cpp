#include <iostream>
using namespace std;

//Task 4: Define a Book class. Every book must have the following attributes: 
//Title, Author, Price, Genre, and ISBN. Define a variable bookCount
//to keep track of the number of book objects created in your program; this variable should be defined inside the class.

class Book {
	string title , author , genre;
	double price;
	long ISBN;
	static int bookCount;
public : 
	Book(string t = "NAS" , string a = "NAS" , string g = "NAS" , double p = NAN , long i = -1){
		bookCount++;
		title = t, author = a, genre = g;
		price = p;
		ISBN = i;		
	}
	static int getCoun()
	{
		return bookCount;
	}

};
int Book::bookCount = 0;

int main()
{
	Book a, b, c;
	cout << Book::getCoun();

	return 0;
}