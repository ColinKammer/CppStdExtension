// inspired by example in CompilerExplorer

#include <array>
#include <stdexcept>
#include <utility>

namespace cjk {
template <typename Key, typename Value, std::size_t Size>
struct ConstexprMap {
    std::array<std::pair<Key, Value>, Size> data;

    [[nodiscard]] constexpr Value at(const Key& key) const
    {
        // no algorithm to avoid include
        for (const auto& v : data) {
            if (v.first == key)
                return v.second;
        }
        throw std::range_error("Not Found");
    }
};
}

/* Example usage

static constexpr std::array<std::pair<int, float>, 4> mapContent{
    {{ 3, 3.14},
     { 4, 4.2},
     { 5, 5.0},
     { 6, 6.0}}
};
...
{
  static constexpr auto myMap = ConstexprMap{ mapContent };
  myMap.at(4) == 4.2;
}

*/