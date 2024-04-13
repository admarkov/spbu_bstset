#include <iostream>
#include "btset.h"
using namespace std;
using namespace spbu;

int main() {
    BTSet<int> set;
    assert(!set.contains(1));
    set.add(1);
    assert(set.contains(1));
    set.add(2);
    assert(set.contains(1));
    assert(set.contains(2));
    set.remove(2);
    assert(!set.contains(2));
    assert(!set.contains(0));
    set.add(0);
    assert(set.contains(0));
    set.remove(0);
    assert(!set.contains(0));
    set.add(1);
    assert(set.contains(1));
    assert(!set.contains(5));
    return 0;
}