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
