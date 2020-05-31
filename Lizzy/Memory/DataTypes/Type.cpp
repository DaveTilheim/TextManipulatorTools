#include "Type.hpp"

using namespace Lizzy;


Types Type::type(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return INTEGER_T;
	if(Float::is(constStrGenValue)) return FLOAT_T;
	if(Bool::is(constStrGenValue)) return BOOL_T;
	return STRING_T;
}

string Type::inferType(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return "Integer";
	if(Float::is(constStrGenValue)) return "Float";
	if(Bool::is(constStrGenValue)) return "Bool";
	return "String";
}

Data **Type::generateSlot(Data *data)
{
	return new Data*(data);
}

Data *Type::generatePrimitive(string value)
{
	if(Integer::is(value))
		return new Integer(atoi(value.c_str()));
	if(Float::is(value))
		return new Float(atof(value.c_str()));
	if(Bool::is(value))
		return new Bool(value == "true");
	return new String(value);
}


void Type::updateSlot(Slot *slot, string value)
{
	if(not slot->isFinal())
	{
		if(not slot->isConst())
		{
			delete *slot->get();
			*slot->get() = generatePrimitive(value);
		}
		else
		{
			throw Exception("Data is marked const, it can not be modified");
		}
	}
	else
	{
		(*slot->get())->setFromValue(value);
	}
}

void Type::updateSlot(Slot *slot, Data *data)
{
	if(*slot->get() == data)
	{
		throw Exception("Can not modify Data with its own value");
	}
	if(not slot->isFinal())
	{
		if(not slot->isConst())
		{
			delete *slot->get();
			*slot->get() = data->dup();
		}
		else
		{
			throw Exception("Data is marked const, it can not be modified");
		}
	}
	else
	{
		(*slot->get())->setFromData(data);
	}
}

long Type::extractIndex(Slot *slot)
{
	Data *data = *slot->get();
	if(dynamic_cast<Integer *>(data))
		return dynamic_cast<Integer *>(data)->get();
	if(dynamic_cast<Float *>(data))
		return (long)dynamic_cast<Float *>(data)->get();
	if(dynamic_cast<Bool *>(data))
		return (long)dynamic_cast<Bool *>(data)->get();
	throw Exception("can not extract index from " + data->type());
}

long Type::extractIndex(string value)
{
	if(Integer::is(value))
		return atoi(value.c_str());
	if(Float::is(value))
		return (long)atof(value.c_str());
	if(Bool::is(value))
		return (long)(value == "true");
	throw Exception("can not extract index from " + inferType(value));
}


void Type::setField(Slot *tableSlot, string fieldname, Slot *value)
{
	Table *tableData = dynamic_cast<Table *>(*tableSlot->get());
	auto& table = tableData->getTable();
	if(not tableSlot->isConst())
	{
		tableData->setField(fieldname, value);
	}
	else
	{
		throw Exception("Table is marked const, can not set new field");
	}
}


string Type::operation(string v1, string v2, string (*ope)(Data *, Data *))
{
	string buf;
	Data *d1 = generatePrimitive(v1);
	Data *d2 = generatePrimitive(v2);
	try
	{
		buf = ope(d1, d2);
	}
	catch(const Exception& e)
	{
		delete d1;
		delete d2;
		throw e;
	}
	delete d1;
	delete d2;
	return buf;
}

string Type::operation(Slot *v1, string v2, string (*ope)(Data *, Data *))
{
	string buf;
	Data *d2 = generatePrimitive(v2);
	try
	{
		buf = ope((*v1->get()), d2);
	}
	catch(const Exception& e)
	{
		delete d2;
		throw e;
	}
	delete d2;
	return buf;
}

string Type::operation(string v1, Slot *v2, string (*ope)(Data *, Data *))
{
	string buf;
	Data *d1 = generatePrimitive(v1);
	try
	{
		buf = ope(d1, (*v2->get()));
	}
	catch(const Exception& e)
	{
		delete d1;
		throw e;
	}
	delete d1;
	return buf;
}

string Type::operation(Slot *v1, Slot *v2, string (*ope)(Data *, Data *))
{
	return ope((*v1->get()), (*v2->get()));
}


string Type::operation(string v1, string (*ope)(Data *))
{
	string buf;
	Data *d1 = generatePrimitive(v1);
	try
	{
		buf = ope(d1);
	}
	catch(const Exception& e)
	{
		delete d1;
		throw e;
	}
	delete d1;
	return buf;
}

string Type::operation(Slot *v1, string (*ope)(Data *))
{
	return ope((*v1->get()));
}


string Type::add(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() + dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() + dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() + dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() + dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() + dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() + dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() + dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() + dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() + dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::sub(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() - dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() - dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() - dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() - dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() - dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() - dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() - dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() - dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() - dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::mul(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() * dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() * dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() * dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() * dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() * dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() * dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() * dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() * dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() * dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::div(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() / dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() / dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() / dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() / dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() / dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Float *>(d1)->get() / dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() / dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() / dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() / dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::mod(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() % dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() % dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() % dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() % dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}


string Type::land(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() & dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() & dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() & dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() & dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::lor(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() | dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() | dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() | dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() | dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}


string Type::lxor(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() ^ dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() ^ dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() ^ dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() ^ dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::lnot(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		return to_string(~dynamic_cast<Integer *>(d1)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		return to_string(~dynamic_cast<Bool *>(d1)->get());
	}
	throw Exception(d1->type() + " can not be operate");
}


string Type::pre_inc(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		dynamic_cast<Integer *>(d1)->set(dynamic_cast<Integer *>(d1)->get() + 1);
		return d1->toString();
	}
	if(dynamic_cast<Float *>(d1))
	{
		dynamic_cast<Float *>(d1)->set(dynamic_cast<Float *>(d1)->get() + 1.0);
		return d1->toString();
	}
	if(dynamic_cast<Bool *>(d1))
	{
		dynamic_cast<Bool *>(d1)->set(dynamic_cast<Bool *>(d1)->get() + 1);
		return d1->toString();
	}
	throw Exception(d1->type() + " can not be operate");
}

string Type::post_inc(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		auto i = dynamic_cast<Integer *>(d1)->get();
		dynamic_cast<Integer *>(d1)->set(i + 1);
		return to_string(i);
	}
	if(dynamic_cast<Float *>(d1))
	{
		auto i = dynamic_cast<Float *>(d1)->get();
		dynamic_cast<Float *>(d1)->set(i + 1.0);
		return to_string(i);
	}
	if(dynamic_cast<Bool *>(d1))
	{
		auto i = dynamic_cast<Bool *>(d1)->get();
		dynamic_cast<Bool *>(d1)->set(i + 1);
		return to_string(i);
	}
	throw Exception(d1->type() + " can not be operate");
}

string Type::pre_dec(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		dynamic_cast<Integer *>(d1)->set(dynamic_cast<Integer *>(d1)->get() - 1);
		return d1->toString();
	}
	if(dynamic_cast<Float *>(d1))
	{
		dynamic_cast<Float *>(d1)->set(dynamic_cast<Float *>(d1)->get() - 1.0);
		return d1->toString();
	}
	if(dynamic_cast<Bool *>(d1))
	{
		dynamic_cast<Bool *>(d1)->set(dynamic_cast<Bool *>(d1)->get() - 1);
		return d1->toString();
	}
	throw Exception(d1->type() + " can not be operate");
}

string Type::post_dec(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		auto i = dynamic_cast<Integer *>(d1)->get();
		dynamic_cast<Integer *>(d1)->set(i - 1);
		return to_string(i);
	}
	if(dynamic_cast<Float *>(d1))
	{
		auto i = dynamic_cast<Float *>(d1)->get();
		dynamic_cast<Float *>(d1)->set(i - 1.0);
		return to_string(i);
	}
	if(dynamic_cast<Bool *>(d1))
	{
		auto i = dynamic_cast<Bool *>(d1)->get();
		dynamic_cast<Bool *>(d1)->set(i - 1);
		return to_string(i);
	}
	throw Exception(d1->type() + " can not be operate");
}





string Type::cand(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() and dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() and dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() and dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() and dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() and dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() and dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() and dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() and dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() and dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::cor(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() or dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() or dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() or dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() or dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() or dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() or dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() or dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() or dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() or dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}


string Type::cnot(Data *d1)
{
	if(dynamic_cast<Integer *>(d1))
	{
		return boolean(not dynamic_cast<Integer *>(d1)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		return boolean(not dynamic_cast<Float *>(d1)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		return boolean(not dynamic_cast<Bool *>(d1)->get());
	}
	throw Exception(d1->type() + " can not be operate");
}


string Type::rshift(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() >> dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() >> dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() >> dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() >> dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::lshift(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() << dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Integer *>(d1)->get() << dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() << dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return to_string(dynamic_cast<Bool *>(d1)->get() << dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}



string Type::equal(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() == dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() == dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() == dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() == dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() == dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() == dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() == dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() == dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() == dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::not_equal(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() != dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() != dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() != dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() != dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() != dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() != dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() != dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() != dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() != dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::lesser(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() < dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() < dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() < dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() < dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() < dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() < dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() < dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() < dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() < dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}

string Type::bigger(Data *d1, Data *d2)
{
	if(dynamic_cast<Integer *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() > dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() > dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Integer *>(d1)->get() > dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Float *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() > dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() > dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Float *>(d1)->get() > dynamic_cast<Bool *>(d2)->get());
	}
	if(dynamic_cast<Bool *>(d1))
	{
		if(dynamic_cast<Integer *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() > dynamic_cast<Integer *>(d2)->get());
		if(dynamic_cast<Float *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() > dynamic_cast<Float *>(d2)->get());
		if(dynamic_cast<Bool *>(d2)) return boolean(dynamic_cast<Bool *>(d1)->get() > dynamic_cast<Bool *>(d2)->get());
	}
	throw Exception(d1->type() + " can not be operate with " + d2->type());
}





string Type::cast(Data *d1, Types type)
{
	if(dynamic_cast<Integer *>(d1))
	{
		switch(type)
		{
			case STRING_T:
			case INTEGER_T: return d1->toString();
			case FLOAT_T: return to_string((double)dynamic_cast<Integer *>(d1)->get());
			case BOOL_T: return (bool)dynamic_cast<Integer *>(d1)->get() ? "true" : "false";
		}
	}
	else if(dynamic_cast<Float *>(d1))
	{
		switch(type)
		{
			case INTEGER_T: return to_string((long)dynamic_cast<Float *>(d1)->get());
			case STRING_T:
			case FLOAT_T: return d1->toString();
			case BOOL_T: return (bool)dynamic_cast<Float *>(d1)->get() ? "true" : "false";
		}
	}
	else if(dynamic_cast<Bool *>(d1))
	{
		switch(type)
		{
			case INTEGER_T: return to_string((long)dynamic_cast<Bool *>(d1)->get());
			case FLOAT_T: return to_string((double)dynamic_cast<Bool *>(d1)->get());
			case STRING_T:
			case BOOL_T: return d1->toString();
		}
	}
	else if(dynamic_cast<String *>(d1))
	{
		string tmp = dynamic_cast<String *>(d1)->get();
		switch(type)
		{
			case INTEGER_T: return (Data::isInteger(tmp) or Data::isFloat(tmp)) ? to_string(atoi(tmp.c_str())) : throw Exception("String can not be cast in Integer");
			case FLOAT_T: return  (Data::isFloat(tmp)) ? to_string(atof(tmp.c_str())) : throw Exception("String can not be cast in Float");
			case BOOL_T:
				if(Data::isInteger(tmp) or Data::isFloat(tmp)) return (bool)atof(tmp.c_str()) ? "true" : "false";
				if(Data::isBool(tmp)) return tmp;
				throw Exception("String can not be cast in Bool");
			case STRING_T: return d1->toString();
		}
	}
	throw Exception(d1->type() + " casting error");
}



bool Type::evaluate(Data *d)
{
	if(dynamic_cast<Bool *>(d)) return dynamic_cast<Bool *>(d)->get();
	if(dynamic_cast<Integer *>(d)) return dynamic_cast<Integer *>(d)->get();
	if(dynamic_cast<Float *>(d)) return dynamic_cast<Float *>(d)->get();
	throw Exception("can not evaluate a " + d->type() + " expression");
}

bool Type::evaluate(string v)
{
	Data *d = generatePrimitive(v);
	bool res = false;
	try
	{
		res = evaluate(d);
	}
	catch(const Exception& e)
	{
		delete d;
		throw e;
	}
	delete d;
	return res;
}
