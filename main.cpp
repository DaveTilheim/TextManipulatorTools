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
	Command print("print");

	Action action([](Args args)
	{
		cout << "Hello " << args.use("user") << endl;
		return "";
	});
	action.setNamed("user");
	print.setAction(1, action);


	print.exe("\"user=Arthur Detrembleur\"");






	return 0;
}
