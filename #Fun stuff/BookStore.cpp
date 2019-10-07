#include "BookStore.h"
#include <vector>
#include <string>
BookStore::BookStore()
{

}
void BookStore::AddBook(const Book& b)
{
	data.push_back(b);
}
void BookStore::ListBooks(std::ostream& out)
{
	std::vector <Book> sorted(data);
	std::sort(sorted.begin(), sorted.end(), [](const Book& a, const Book& b)
	{
		return a.name < b.name;
	});
	for (auto item : sorted) out << &item;
}
Book* BookStore::SearchbyAuthor(std::string a)
{
	for (auto& item : data) if (item.author == a) return &item;
	return 0;
}
Book* BookStore::SearchbyName(std::string n)
{
	for (auto& item : data) if (item.name == n) return &item;
	return 0;
}
Book* BookStore::FindHighest()
{
	int maximum = data[0].versions;
	int idx = 0;
	for (int i = 0; i < (int)data.size(); ++i)
	{
		if (data[i].versions > maximum)
		{
			maximum = data[i].versions;
			idx = i;
		}
	}
	return &data[idx];
}
void BookStore::Update(Book* upd, int v)
{
	upd->versions = v;
}
BookStore::~BookStore()
{
	//dtor
}
void BookStore::PrintMenu(std::ostream& out, std::istream& in)
{
	int c;
	Book* b;
	while (true)
	{
		b = new Book("", "", 0);
		out << "0- Exit\n1- Add Book\n2- Search by Author\n3- Search by Name\n4- List Books\n5- Update Book by name\n";
		in >> c;
		in.ignore();
		switch (c)
		{
		case 0:
			delete b;
			return;
		case 1:
			out << "Enter Name : ";
			getline(in, b->name);
			out << "Enter Author : ";
			getline(in, b->author);
			out << "Enter Year : ";
			in >> b->year;
			AddBook(*b);
			out << "Book is added successfully\n\n";
			break;
		case 2:
			out << "Enter Author : ";
			getline(in, b->author);
			b = SearchbyAuthor(b->author);
			if (!b) out << "Book is not found\n\n";
			else out << "\n" << b;
			break;
		case 3:
			out << "Enter Name : ";
			getline(in, b->name);
			b = SearchbyName(b->name);
			if (!b) out << "Book is not found\n\n";
			else out << "\n" << b;
			break;
		case 4:
			ListBooks(out);
			break;
		case 5:
		{

			out << "Enter Name : ";
			getline(in, b->name);
			Book* upd = SearchbyName(b->name);
			if (!upd)
			{
				out << "Book is not found\n";
				break;
			}
			out << "Enter versions : ";
			in >> b->versions;
			Update(upd, b->versions);
			out << "Book is updated successfully\n\n";
			break;
		}
		case 6:
			out << FindHighest();
			break;
		}
	}
}
