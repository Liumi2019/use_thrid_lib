#include "useAbsl.h"
#include <string>
#include <vector>
#include <iostream>

#include <absl/strings/str_join.h>
#include <absl/strings/string_view.h>
#include <absl/container/btree_map.h>

std::string useAbslString::uesStrJoin(std::vector<std::string>&& strs, std::string&& chr) {
    std::string str(absl::StrJoin(strs, chr)); 
    absl::btree_map<std::string, int> bmap = {{"120", 120}, {"34", 34}, {"1", 1}};
    auto i = bmap.at("34");
    std::cout << "i " << i << std::endl;

    return str;
}

namespace test_absl {

    void test_absl_str_join() {
        useAbslString abslStr;
        std::string str(abslStr.uesStrJoin({ "hello,", "wecome", "to", "here" }, " "));
        std::cout << str << std::endl;
    }
}
