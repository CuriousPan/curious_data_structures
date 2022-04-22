#include "LRUCache.h"
#include "LFUCache.h"
#include <vector>

#define LRU

struct Page {
    const char* text;
    int number;
};

std::ostream& operator<<(std::ostream& stream, const Page& page)
{
    //stream << page.number << " " << page.text << "|";
    stream << page.number << " ";
}

int main()
{

    #if defined(LFU)
    LFUCache<int, Page> cache(4);
    std::cout << "Using LFU stratagy.\n" << std::endl;

    #elif defined(LRU)
    LRUCache<int, Page> cache(4);
    std::cout << "Using LRU stratagy.\n" << std::endl;

    #endif

    std::vector<Page> input =
    { 
        Page{"1 text", 1},
        Page{"4 text", 4},
        Page{"2 text", 2},
        Page{"1 text", 1},
        Page{"2 text", 2},
        Page{"4 text", 4},
        Page{"6 text", 6},
        Page{"1 text", 1},
        Page{"2 text", 2},
        Page{"5 text", 5},
        Page{"4 text", 4},
        Page{"2 text", 2},
        Page{"3 text", 3},
        Page{"5 text", 5},
        Page{"5 text", 5},
        Page{"5 text", 5},
        Page{"6 text", 6},
        Page{"5 text", 5},
        Page{"5 text", 5},
        Page{"2 text", 2},
        Page{"6 text", 6},
        Page{"5 text", 5},
        Page{"1 text", 1},
        Page{"5 text", 5},
        Page{"7 text", 7},
        Page{"8 text", 8},
        Page{"3 text", 3},
        Page{"4 text", 4}
    };

    int misses = 0;
    int hits = 0;

    for (auto page : input) {
        if (cache.contains(page.number)) {
            auto result = cache.get(page.number);
            ++hits;
        } else {
            cache.set(page.number, page);
            ++misses;
        }
        cache.display();
    }

    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: " << misses << std::endl;
    return 0;
}
