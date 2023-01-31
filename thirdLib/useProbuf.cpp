#include "useProbuf.h"
#include <fstream>
#include <string>
#include <iostream>

namespace test_pb {

    namespace {
        std::string PbLogPath = "/mnt/b/Learn/UbuntuCPP/CppProject/testThirdLib/thirdLib/pb_src/pb.log";
    }

    void test_pbW() {
        persion::Person p1;
        p1.set_name("hello");
        p1.set_age(50);
        p1.add_sex(false);
        p1.add_sex(true);
        std::fstream output(PbLogPath, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!p1.SerializeToOstream(&output)) {
            std::cerr << "Failed to write msg." << std::endl;
        }
    }

    void test_pbR() {
        persion::Person p1;
        std::fstream input(PbLogPath, std::ios::in | std::ios::binary);
        if (!p1.ParseFromIstream(&input)) {
            std::cerr << "Failed to parse address book." << std::endl;
        }
        std::cout << "name: " << p1.name() << ", age: " << p1.age() << ", sex: " << p1.sex(0) << " " << p1.sex(1) << std::endl;
    }

    void test_pb() {
        std::cout << "Write pb.log" << std::endl;
        test_pbW();
        std::cout << "Read pb.log" << std::endl;
        test_pbR();
    }
}
