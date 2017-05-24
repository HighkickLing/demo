#include <gtest/gtest.h>

TEST(lambda, simple)
{
	int girls = 3;
	int boys = 4;
	auto totalChild = [](int x, int y) -> int {return x + y;};
	ASSERT_EQ(totalChild(girls, boys), 7);
}

TEST(lambda, capture)
{
	int girls = 3;
	int boys = 4;
	auto totalChild = [girls, boys]() -> int {return girls + boys;};
	ASSERT_EQ(totalChild(), 7);
}

TEST(lambda, capture_value)
{
	int girls = 3;
	int boys = 4;
	auto totalChild = [=]() -> int {return girls + boys;};
	ASSERT_EQ(totalChild(), 7);
}

TEST(lambda, capture_reference)
{
	int girls = 3;
	int boys = 4;
	auto totalChild = [&]() -> int {return girls + boys;};
	ASSERT_EQ(totalChild(), 7);
}

class CaptureClass
{
public:
	CaptureClass(int girls, int boys)
		:girls_(girls),
		 boys_(boys)
	{

	}
	int capture_this()
	{
		auto totalChild = [=]() -> int {return girls_ + boys_;};
		return totalChild();
	}
	int capture_this_short()
	{
		auto totalChild = [=] {return girls_ + boys_;};
		return totalChild();
	}
	int capture_this_decltype()
	{
		auto totalChild = [=]() -> decltype(girls_) {return girls_ + boys_;};
		return totalChild();
	}
	~CaptureClass()
	{

	}
private:
	int girls_;
	int boys_;
};

TEST(lambda, capture_this)
{
	CaptureClass c(3, 4);
	ASSERT_EQ(c.capture_this(), 7);
}

TEST(lambda, capture_this_short)
{
	CaptureClass c(3, 4);
	ASSERT_EQ(c.capture_this_short(), 7);
}

TEST(lambda, capture_this_decltype)
{
	CaptureClass c(3, 4);
	ASSERT_EQ(c.capture_this_decltype(), 7);
}
