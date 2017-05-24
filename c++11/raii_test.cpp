#include <gtest/gtest.h>

class NormalHolder
{
public:
	NormalHolder()
	{

	}
	~NormalHolder()
	{

	}
private:
	void *operator new(std::size_t);
};

class DeleteHolder
{
public:
	DeleteHolder()
	{

	}
	~DeleteHolder()
	{

	}
	void *operator new(std::size_t) = delete;
};

class NewHolder
{
	//void *operator new(std::size_t size, void *ptr); //cannot be overloaded
private:
	~NewHolder();
};

TEST(raii, NormalHolder)
{
	NormalHolder a;
	//NormalHolder *b = new NormalHolder();
}

TEST(raii, DeleteHolder)
{
	DeleteHolder a;
	//DeleteHolder *b = new DeleteHolder();
}

TEST(raii, NewHolderTest)
{
	char a[ sizeof(NewHolder) ];
	new (a) NewHolder();

	//NewHolder b;
}
