#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "mydeque.hpp"

std::string capture_display(const MyDeque<int>& q, bool reversed) {
    std::ostringstream oss;
    std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());
    if (reversed) {
        q.display_reversed();
    } else {
        q.display();
    }
    std::cout.rdbuf(old_buf);
    return oss.str();
}

void test_basic_and_wrap() {
    MyDeque<int> Q(4);
    assert(Q.empty());
    assert(!Q.full());
    assert(Q.size() == 0);
    assert(Q.max_size() == 4);

    Q.push_back(11);
    Q.push_back(22);
    Q.push_front(33);
    Q.push_front(44);
    assert(Q.full());
    assert(Q.size() == 4);
    assert(Q.front() == 44);
    assert(Q.back() == 22);
    assert(capture_display(Q, false) == "44 33 11 22 \n");
    assert(capture_display(Q, true) == "22 11 33 44 \n");

    Q.pop_front();
    assert(!Q.full());
    assert(Q.front() == 33);
    Q.pop_back();
    assert(Q.back() == 11);
    assert(Q.size() == 2);

    Q.clear();
    assert(Q.empty());
    assert(Q.size() == 0);
}

void test_copy_and_move() {
    MyDeque<int> Q1(6);
    for (int item : {1, 3, 5}) Q1.push_front(item);
    for (int item : {2, 4, 6}) Q1.push_back(item);
    assert(Q1.front() == 5);
    assert(Q1.back() == 6);
    assert(Q1.size() == 6);

    MyDeque<int> Q2(Q1);
    assert(Q2.size() == 6);
    assert(capture_display(Q2, false) == "5 3 1 2 4 6 \n");
    Q2.front() = 55;
    Q2.back() = 66;
    assert(Q1.front() == 5);
    assert(Q1.back() == 6);

    MyDeque<int> Q3(2);
    Q3 = Q2;
    assert(Q3.max_size() == 6);
    assert(Q3.front() == 55);
    assert(Q3.back() == 66);

    MyDeque<int> Q4(std::move(Q2));
    assert(Q4.size() == 6);
    assert(Q2.empty());
    assert(Q2.max_size() == 0);

    MyDeque<int> Q5(3);
    Q5 = std::move(Q4);
    assert(Q5.size() == 6);
    assert(Q4.empty());
    assert(Q4.max_size() == 0);
}

void test_indexed_operations() {
    MyDeque<int> Q(6);
    Q.insert(0, 20);
    int v10 = 10;
    Q.insert(0, v10);
    Q.insert(Q.size(), 40);
    int v30 = 30;
    Q.insert(2, v30);
    assert(Q.size() == 4);
    assert(Q[0] == 10 && Q[1] == 20 && Q[2] == 30 && Q[3] == 40);

    const MyDeque<int>& cQ = Q;
    assert(cQ[2] == 30);

    Q[2] = 35;
    assert(Q.index(10) == 0);
    assert(Q.index(35) == 2);
    assert(Q.index(99) == -1);

    Q.erase(1);
    assert(Q.size() == 3);
    assert(capture_display(Q, false) == "10 35 40 \n");
    Q.erase(0);
    Q.erase(Q.size() - 1);
    assert(Q.size() == 1);
    assert(Q.front() == 35);
}

int main() {
    test_basic_and_wrap();
    test_copy_and_move();
    test_indexed_operations();

    MyDeque<int> demo(5);
    demo.push_back(11);
    demo.push_back(22);
    demo.push_front(33);
    std::cout << "Wszystkie testy zakonczone sukcesem!\n";
    demo.display();
    demo.display_reversed();
    return 0;
}
