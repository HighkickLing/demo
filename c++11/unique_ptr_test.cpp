#include <gtest/gtest.h>
#include <memory>
#include <stdio.h>

class UniquePtrTestClass
{
public:
    UniquePtrTestClass() {
        printf("UniquePtrTestClass::UniquePtrTestClass()\n");
    }
    ~UniquePtrTestClass() {
        printf("UniquePtrTestClass::~UniquePtrTestClass()\n");
    }
};


TEST(unique_ptr_test, release)
{
    std::unique_ptr<UniquePtrTestClass> ptr(new UniquePtrTestClass());
    ptr.release();
}

TEST(unique_ptr_test, reset)
{
    std::unique_ptr<UniquePtrTestClass> ptr(new UniquePtrTestClass());
    ptr.reset(nullptr);
}
