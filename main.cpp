#include "Generic.hpp"


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


	
	cout << GenericMethod<Point>::has_add_operator << endl;
	

	return 0;
}
