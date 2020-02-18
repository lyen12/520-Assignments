#include "gtest/gtest.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "test_process.h"
#include "elma/elma.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>      // std::accumulate

#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

namespace {

  using namespace std;

  TEST(Process, stopwatch) {

    Stopwatch w; // should set the stopwatch to 0 seconds
    w.start(); 
    SLEEP;
    w.stop();    
    std::cout << "Total time is " << w.get_seconds() << "\n"; // about 1.5
    SLEEP;
    std::cout << "Total time is " << w.get_seconds() << "\n"; // still about 1.5
    w.start(); 
    SLEEP;
    w.stop();    
    std::cout << "Total time is " << w.get_seconds() << "\n"; // about 3.0
    w.reset();
    std::cout << "Reset time is " << w.get_seconds() << "\n"; // 0.0
  }

  TEST(Process, random_process) {
    elma::Manager m;

    //RandomProcess r("random numbers");
    TestProcess t("test numbers");
    Filter f("filter");
    elma::Channel link("link");

    m.schedule(t, 5_ms)
     .schedule(f, 5_ms)
     .add_channel(link)
     .init()
     .run(100_ms);
    f.value();
  }

}
