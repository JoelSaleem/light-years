#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_set>

namespace ly
{
    template <typename T>
    using unique = std::unique_ptr<T>;

    template <typename T>
    using shared = std::shared_ptr<T>;

    template <typename T>
    using weak = std::weak_ptr<T>;

    template <typename T>
    using List = std::vector<T>;

    template <typename keyType, typename valType>
    using Map = std::map<keyType, valType>;

    template <typename keyType, typename valType>
    using Dictionary = std::unordered_map<keyType, valType>;

    template <typename T>
    using Set = std::unordered_set<T>;

    using uint8 =  unsigned char;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}