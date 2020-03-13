#include "Command.hpp"
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
	Command c("hello");
	c.setAction(3, [](Args args)
	{
		String s = args;
		int i = args;
		double d = args;
		cout << s << " " << i << " " << d << endl;
		return "";
	});
	
	try
	{
		c.setChild("world");
		c.setChild("world");
		c.check("ahah ha");
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
