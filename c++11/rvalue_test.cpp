#include <gtest/gtest.h>
#include <stdio.h>

static void Print(const char *msg) {
	printf("%s\n", msg);
}

class RAIIPrint
{
public:
	explicit RAIIPrint(const char *msg) :msg_(msg) {
		printf("enter %s\n", msg_);
	}
	~RAIIPrint() {
		printf("exit %s\n", msg_);
	}
private:
	const char *msg_;
};

class CopyMem
{
public:
	CopyMem() : d(new int(0)) {
		Print("Construct");
	}
	CopyMem(const CopyMem & h) : d(new int(*h.d)) {
		Print("======Copy construct");
	}
	~CopyMem() {
		delete d;
		Print("Destruct");
	}
	CopyMem &setValue(int value) {
		printf("setValue %d\n", value);
		*d = value;
		return *this;
	}
	int getValue() const {
		return *d;
	}
private:
	int *d;
};

class MoveMem
{
public:
	MoveMem() : d(new int(0)) {
		Print("Construct");
	}
	MoveMem(const MoveMem & h) : d(new int(*h.d)) {
		Print("======Copy construct");
	}
	MoveMem(MoveMem && h) : d(h.d) {
		h.d = NULL;
		Print("======Move construct");
	}
	~MoveMem() {
		delete d;
		Print("Destruct");
	}
	MoveMem &setValue(int value) {
		printf("setValue %d\n", value);
		*d = value;
		return *this;
	}
	int getValue() const {
		return *d;
	}
private:
	int *d;
};

CopyMem GetCopyMemOptimize()
{
	RAIIPrint guard("GetCopyMemOptimize");
	return CopyMem();
}

CopyMem GetCopyMemSetValue()
{
	RAIIPrint guard("GetCopyMemSetValue");
	return CopyMem().setValue(5);
}

MoveMem GetMoveMemOptimize()
{
	RAIIPrint guard("GetMoveMemOptimize");
	return MoveMem();
}

MoveMem GetMoveMemSetValue()
{
	RAIIPrint guard("GetMoveMemSetValue");
	return MoveMem().setValue(5);
}

TEST(rvalue, CopyConstructNone1)
{
	CopyMem a = GetCopyMemOptimize();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructNone2)
{
	const CopyMem &a = GetCopyMemOptimize();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructNone3)
{
	const CopyMem &a = GetCopyMemOptimize().setValue(10);
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructOnce1)
{
	CopyMem a = GetCopyMemOptimize().setValue(10);
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructOnce2)
{
	CopyMem a = GetCopyMemSetValue();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructOnce3)
{
	const CopyMem &a = GetCopyMemSetValue();
	printf("a %d\n", a.getValue());
}


TEST(rvalue, CopyConstructOnce4)
{
	const CopyMem &a = GetCopyMemSetValue().setValue(10);
	printf("a %d\n", a.getValue());
}

TEST(rvalue, CopyConstructTwice1)
{
	CopyMem a = GetCopyMemSetValue().setValue(10);
	printf("a %d\n", a.getValue());
}

/////////////////////////////////////////////////////////////////

TEST(rvalue, MoveConstructNone1)
{
	MoveMem a = GetMoveMemOptimize();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructNone2)
{
	const MoveMem &a = GetMoveMemOptimize();
	printf("a %d\n", a.getValue());
}

//new
TEST(rvalue, MoveConstructNone3)
{
	MoveMem &&a = GetMoveMemOptimize();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructNone4)
{
	const MoveMem &a = GetMoveMemOptimize().setValue(10);
	printf("a %d\n", a.getValue());
}

//new
TEST(rvalue, MoveConstructNone5)
{
	MoveMem &&a = std::move(GetMoveMemOptimize().setValue(10));
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructOnce1)
{
	MoveMem a = GetMoveMemOptimize().setValue(10);
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructOnce2)
{
	MoveMem a = GetMoveMemSetValue();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructOnce3)
{
	const MoveMem &a = GetMoveMemSetValue();
	printf("a %d\n", a.getValue());
}

//new
TEST(rvalue, MoveConstructOnce4)
{
	MoveMem &&a = GetMoveMemSetValue();
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructOnce5)
{
	const MoveMem &a = GetMoveMemSetValue().setValue(10);
	printf("a %d\n", a.getValue());
}

//new
TEST(rvalue, MoveConstructOnce6)
{
	MoveMem &&a = std::move(GetMoveMemSetValue().setValue(10));
	printf("a %d\n", a.getValue());
}

TEST(rvalue, MoveConstructTwice1)
{
	MoveMem a = GetMoveMemSetValue().setValue(10);
	printf("a %d\n", a.getValue());
}
