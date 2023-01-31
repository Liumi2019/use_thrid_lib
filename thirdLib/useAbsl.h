#ifndef USE_ABSL_H
#define USE_ABSL_H

#include <string>
#include <vector>

class useAbslString {
public:
    std::string uesStrJoin(std::vector<std::string>&& strs, std::string&& chr);
    useAbslString() = default;
    ~useAbslString() = default;
};

namespace test_absl {
    void test_absl_str_join();
}


#endif