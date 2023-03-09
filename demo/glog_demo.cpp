#include <glog/logging.h>
#include <gtest/gtest.h>

class DemoTest : public testing::Test {
};

TEST_F(DemoTest, demo1) {
  LOG(INFO) << "in demo1: HELLO, WORLD";
  LOG(WARNING) << "in demo1: HELLO, WORLD";
  LOG(ERROR) << "in demo1: HELLO, WORLD";
  // LOG(FATAL) << "HELLO, WORLD";
}


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

