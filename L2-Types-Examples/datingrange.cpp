#include <utility>

enum class Hello {FUN, TODAY};

struct DatingRange {
    int min;
    int max;

};

void datingRange(int age, int& min, int& max) {
    min = age / 2 + 7;
    max = (age - 7) * 2;
}

std::pair<int, int> datingRangePair(int age) {
    int min = age / 2 + 7;
    int max = (age - 7) * 2;
    return std::make_pair(min, max);
}

DatingRange datingRangeStruct(int age) {
    int min = age / 2 + 7;
    int max = (age - 7) * 2;
    return DatingRange{min, max};
}
