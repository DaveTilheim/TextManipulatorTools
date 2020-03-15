
create user => 1 name
{
	cout << "User created: " << name << endl;
	return name;
}

create database => 0
{
	cout << "Database created" << endl;
	return "";
}

create database => 1 location
{
	cout << "Database created at " << location << endl;
	return location;
}
