#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>

struct Foo {
    int i;
};

using FooPtr = std::shared_ptr<Foo>;
using Map = std::map<int, FooPtr>;

#if 0

#include <compare>

std::strong_ordering operator<=>(const Foo& left, const Foo& right)
{
    return left.i <=> right.i;
}

std::strong_ordering operator<=>(const FooPtr& left, const FooPtr& right)
{
    return *left <=> *right;
}

#else

bool operator<(const Foo& left, const Foo& right)
{
    return left.i < right.i;
}

bool operator<(const FooPtr& left, const FooPtr& right)
{
    return *left < *right;
}

#endif

int main(int argc, const char * argv[]) {

    // Create two shared pointers to Foo whose pointer addresses
    // compare inverse to their content
    
    auto p1 = std::make_shared<FooPtr::element_type>();
    auto p2 = std::make_shared<FooPtr::element_type>();
    
    auto& smallerAddress = (p1.get() < p2.get()) ? p1 : p2;
    auto& largerAddress = (p1.get() > p2.get()) ? p1 : p2;
    
    *smallerAddress = {2}; // assign larger value
    *largerAddress = {1}; // assign smaller value

    auto& smallerValue = largerAddress;
    auto& largerValue = smallerAddress;
    
    const auto smallerMap = Map{{ 0, smallerValue }};
    const auto largerMap = Map{{ 0, largerValue }};
    
    if (largerMap < smallerMap) {
        std::cerr << "WRONG result: smaller\n";
        //throw new std::runtime_error("Unexpected Comparison Result");
    } else {
        std::cerr << "CORRECT result: larger\n";
    }
    
    return 0;
}

