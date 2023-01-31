#include <iostream>

#include "useGlog.h"

GlogPack::GlogPack(std::string& log_name) {
    std::cout << "init glog ..." << std::endl;
    google::InitGoogleLogging(log_name.c_str());
}

GlogPack::~GlogPack() {
    std::cout << "glog shut down!" << std::endl;
    google::ShutdownGoogleLogging();
}

void test_useGlog() {

    std::string log_name = "testThirdLib";
    GlogPack glog(log_name);

    LOG(INFO) << "test third lib info";
    LOG(WARNING) << "test third lib warning";
    LOG(ERROR) << "test third lib error";
}
