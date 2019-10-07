#ifndef _MOVIE_H
#define _MOVIE_H
#include <string>
enum MPAA_Rating {
	G, PG, PG13, R
};

class Movie {
private:
	static const int MAX_RATING = 5;

	std::string name;
	MPAA_Rating mpaa;
	int nRatings[MAX_RATING];
public:
	Movie(std::string n, MPAA_Rating rat);
	void set_name(std::string n);
	std::string get_name();
	MPAA_Rating get_MPAArating_int();
	std::string get_MPAArating();
	void set_MPAA_rating(MPAA_Rating rat);
	void add_rating(int rating, int n = 1);
	double get_average();
};
#endif