#ifndef USE_GLOG_H
#define USE_GLOG_H

#include <string>

#include <glog/logging.h>

class GlogPack {
public:
    GlogPack(std::string& log_name);
    ~GlogPack();
};

void test_useGlog();

#endif