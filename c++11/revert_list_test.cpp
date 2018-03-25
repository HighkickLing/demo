#include <gtest/gtest.h>

struct Node
{
    struct Node *next;
    int val;
    explicit Node(int v)
        : next(nullptr),val(v) {}
};

struct Node *revert(struct Node *pHead) {
    if (pHead == nullptr || pHead->next == nullptr) {
        return pHead;
    }
    struct Node *pFirst = pHead;
    struct Node *pNext = pHead->next;
    pHead->next = nullptr; //clear the last pointer

    while (pNext != nullptr) {
        struct Node *pNextNext = pNext->next;
        pNext->next = pFirst;
        pFirst = pNext;
        pNext = pNextNext;
    }
    return pFirst;
}

void revert_recursive(struct Node *pCur, struct Node *&pHead) {
    if (pCur == nullptr || pCur->next == nullptr) {
        pHead = pCur;
        return;
    }
    revert_recursive(pCur->next, pHead);
    pCur->next->next = pCur;
    pCur->next = nullptr;
}

TEST(revert_test, loop)
{
    struct Node *pHead = new Node(0);
    struct Node *pCur = pHead;
    for (int i = 1; i < 10; i++) {
        struct Node *pNext = new Node(i);
        pCur->next = pNext;
        pCur = pNext;
    }

    pHead = revert(pHead);

    pCur = pHead;
    while (pCur != nullptr) {
        printf("%d\n", pCur->val);
        struct Node *pNext = pCur->next;
        delete(pCur);
        pCur = pNext;
    }
}

TEST(revert_test, recursive)
{
    struct Node *pHead = new Node(0);
    struct Node *pCur = pHead;
    for (int i = 1; i < 10; i++) {
        struct Node *pNext = new Node(i);
        pCur->next = pNext;
        pCur = pNext;
    }

    revert_recursive(pHead, pHead);

    pCur = pHead;
    while (pCur != nullptr) {
        printf("%d\n", pCur->val);
        struct Node *pNext = pCur->next;
        delete(pCur);
        pCur = pNext;
    }
}
