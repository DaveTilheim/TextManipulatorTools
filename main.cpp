#include "Generic.hpp"
#include <vector>

struct Point
{
	int x, y;

	Point(int x, int y) : x(x), y(y){}

	friend ostream& operator<<(ostream& out, const Point& pt)
	{
		return out << "(" << pt.x << " " << pt.y << ")";
	}

	Point operator+(const Point& pt)
	{
		return Point(pt.x + x, pt.y + y);
	}
};


int main(int argc, char const *argv[])
{
	Generic v = 3.14;

	v = Point(5, 10);

	//v = vector<int>();

	//cout << GenericMethod<Point>::printable << endl;
	cout << v << endl;

	return 0;
}
