#include <gtest/gtest.h>

#include <vector>
using namespace std;

template <typename T>
const T* find1(const vector<T> &vec, const T &value) {
    for (const auto &item : vec) {
        if (item == value) {
            return &item;
        }
    }
    return nullptr;
}

TEST(essential_chapter_3, find1_test) {
    vector<int> vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    const int *result = find1(vec, 2);
    ASSERT_TRUE(result != nullptr);
    ASSERT_EQ(*result, 2);

    // not suitable for array
}

///////////////////////////////////////////////////////

template <typename T>
const T* find2(const T* first, const T* last, const T &value) {
    for (auto it = first; it != last; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return nullptr;
}

TEST(essential_chapter_3, find2_test) {
    vector<int> vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    const int *result = find2(&vec[0], &vec[vec.size()], 2);
    ASSERT_TRUE(result != nullptr);
    ASSERT_EQ(*result, 2);

    int array[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    result = find2(array + 0, array + sizeof(array)/sizeof(array[0]), 2);
    ASSERT_TRUE(result != array + sizeof(array)/sizeof(array[0]));
    ASSERT_EQ(*result, 2);
}

///////////////////////////////////////////////////////

template <typename Iterator, typename T>
Iterator find3(const Iterator &it_begin, const Iterator &it_end, const T &value) {
    for (auto it = it_begin; it != it_end; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return it_end;
}

TEST(essential_chapter_3, find3_test) {
    vector<int> vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    vector<int>::iterator result1 = find3(vec.begin(), vec.end(), 2);
    ASSERT_TRUE(result1 != vec.end());
    ASSERT_EQ(*result1, 2);

    int array[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int *result2 = find3(array + 0, array + sizeof(array)/sizeof(array[0]), 2);
    ASSERT_TRUE(result2 != array + sizeof(array)/sizeof(array[0]));
    ASSERT_EQ(*result2, 2);
}

///////////////////////////////////////////////////////
template <typename Comp>
vector<int> filter1(const vector<int> &vec, Comp pred) {
    vector<int> out;
    for (const auto &item : vec) {
        if (pred(item)) {
            out.push_back(item);
        }
    }
    return out;
}

TEST(essential_chapter_3, filter1_test) {
    vector<int> vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 11};
    vector<int> result = filter1(vec, [=](int item) {return item < 10;});
    for (auto item : result) {
        printf("%d\n", item);
    }
}
