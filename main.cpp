#include "Command.hpp"


struct Point
{
	int x, y;

	Point(int x, int y) : x(x), y(y){}

	friend ostream& operator<<(ostream& out, const Point& pt)
	{
		return out << "(" << pt.x << " " << pt.y << ")";
	}
};


int main(int argc, char const *argv[])
{
	Value v = vector<string>();

	v.ref<vector<string>>().push_back("Hello");
	v.ref<vector<string>>().push_back("world!");

	

	Value s = "Hello";
	
	cout << s << " " << (string&)s << endl;

	
	

	return 0;
}
