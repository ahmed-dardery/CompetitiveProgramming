#include <iostream>
using namespace std;
typedef long long ll;

class Time {
private:
	int hours, minutes, seconds;
public:
	int getHours() { return hours; }
	int getMinutes() { return minutes; }
	int getSeconds() { return seconds; }

	void setHours(int h) {
		hours = h;
	}
	void setMinutes(int m) {
		int tmp = m / 60;
		setHours(hours + tmp);
		minutes = m % 60;
	}
	void setSeconds(int s) {
		int tmp = s / 60;
		setMinutes(minutes + tmp);
		seconds = s % 60;
	}
};
ostream& operator <<(ostream& out, Time t) {
	return (out << t.getHours() << ":" << t.getMinutes() << ":" << t.getSeconds());
}

int main() {
	Time t;
	t.setHours(3);
	t.setMinutes(59);
	t.setSeconds(70);

	cout << t;
}