#include "Generic.hpp"
#include <vector>

struct Point
{
	int x=666, y=666;
	Point(){}
	Point(int x, int y) : x(x), y(y){}

	friend ostream& operator<<(ostream& out, const Point& pt)
	{
		return out << "(" << pt.x << " " << pt.y << ")";
	}

	friend istream& operator>>(istream& in, Point& pt)
	{
		return in >> pt.x >> pt.y;
	}

	Point operator+(const Point& pt)
	{
		return Point(pt.x + x, pt.y + y);
	}

	Point operator-(const Point& pt)
	{
		return Point(pt.x - x, pt.y - y);
	}

	void hello()
	{
		cout << "AH" << endl;
	}
};


int main(int argc, char const *argv[])
{
	Generic v = 3.14;
	

	v = Point(5, 10);

	v = v + v;
	v.ref<Point>().hello();

	cout << v << endl;
	v = v * Point(5,5);


	cout << v << endl;

	

	return 0;
}
