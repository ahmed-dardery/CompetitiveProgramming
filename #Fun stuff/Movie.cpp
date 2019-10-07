#include "Movie.h"

Movie::Movie(std::string n, MPAA_Rating rat) {
	name = n;
	mpaa = rat;
	for (int i = 0; i < MAX_RATING; ++i)
		nRatings[i] = 0;
}
void Movie::set_name(std::string n) {
	name = n;
}
std::string Movie::get_name() {
	return name;
}
MPAA_Rating Movie::get_MPAArating_int() {
	return mpaa;
}
std::string Movie::get_MPAArating() {
	const std::string arr[] = { "G","PG","PG-13","r" };
	return arr[mpaa];
}
void Movie::set_MPAA_rating(MPAA_Rating rat) {
	mpaa = rat;
}
void Movie::add_rating(int rating, int n) {
	if (rating > 0 && rating <= MAX_RATING)
		nRatings[rating - 1] += n;
}
double Movie::get_average() {
	double sum = 0;
	long long count = 0;
	for (int i = 0; i < MAX_RATING; ++i) {
		sum += (nRatings[i] * (i + 1));
		count += nRatings[i];
	}
	return sum / count;
}