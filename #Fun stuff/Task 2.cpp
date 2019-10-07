#include <iostream>

using namespace std;

class Box
{
private:
	double length; // Length of a box
	double width; // width of a box
	double height; // Height of a box
public:
	Box(double l, double w, double h) {
		length = l;
		width = w;
		height = h;
	}
	double getVolume() {
		return length * width*height;
	}
};

int main() {
	Box box1(4.0, 6.0, 3.0), box2(10.0, 12.0, 13.0);
	cout << "Box 1's volume is: " << box1.getVolume() << endl;
	cout << "Box 2's volume is: " << box2.getVolume() << endl;
}
