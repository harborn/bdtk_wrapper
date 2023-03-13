
#include <folly/init/Init.h>
#include "TpchQ6Task.h"
#include "velox/vector/arrow/Bridge.h"

class TpchQ6DummyTaskTest : public testing::Test {};

TEST_F(TpchQ6DummyTaskTest, test) {
  auto task = trino::velox::TpchQ6Task::Make();
  while (!task->isFinished()) {
    struct ArrowArray* output_array;
    struct ArrowSchema* output_schema;
    task->nextBatch(output_schema, output_array);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  folly::init(&argc, &argv, false);
  return RUN_ALL_TESTS();
}
