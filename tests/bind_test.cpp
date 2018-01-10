//
// Created by finefenng on 2018/1/5.
//

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>

class Foo
{
public:
	typedef boost::function<void(int)> Callback;
	void setCallback(const Callback& cb) { cb_ = cb; }
	void execute()
	{
		cb_(2);
	}
private:
	Callback cb_;
};

class Boo
{
public:
	Boo(Foo* foo)
	:foo_(foo)
	{
		foo_->setCallback(boost::bind(&Boo::print, this, _1));
	}
	void print(int a)
	{
		std::cout << "hello world" << a << std::endl;
	}
private:
	Foo* foo_;
};

int main()
{
	Foo foo;
	Boo boo(&foo);
	foo.execute();

	return  0;
}






