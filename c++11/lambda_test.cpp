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

TEST(lambda, capture_complex)
{
	int j = 12;
	auto by_val_lambda = [=] {return j + 1;};
	auto by_ref_lambda = [&] {return j + 1;};
	ASSERT_EQ(by_val_lambda(), 13);
	ASSERT_EQ(by_ref_lambda(), 13);

	j++;
	ASSERT_EQ(by_val_lambda(), 13);
	ASSERT_EQ(by_ref_lambda(), 14);
	auto by_val_lambda2 = [=] {return j + 1;};
	ASSERT_EQ(by_val_lambda2(), 14);
}

TEST(lambda, capture_mutable)
{
	int val = 0;
	//auto const_val_lambda = [=] {val = 3;};
	auto mutable_val_lambda = [=]() mutable {val = 3;};
	auto const_ref_lambda = [&] {val = 3;};
	auto const_param_lambda = [&](int v) {v = 3;};
	const_param_lambda(val);
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
		auto totalChild = [=]() -> decltype(girls_ + boys_) {return girls_ + boys_;};
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

//New function declarator syntax support in GCC 4.4
template<typename T>
auto auto_sum(const T &a, const T &b)
-> T
{
	return a + b;
}

TEST(lambda, template_test)
{
	int girls = 3;
	int boys = 4;
	ASSERT_EQ(auto_sum(girls, boys), 7);
}
