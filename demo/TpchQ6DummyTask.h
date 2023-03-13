#include "TpchQ6Task.h"

using namespace facebook::velox;
using namespace facebook::velox::exec::test;
namespace trino::velox {

class TpchQ6DummyTask : public TpchQ6Task {
 public:
  explicit TpchQ6DummyTask();
  void nextBatch(ArrowSchema* c_schema, ArrowArray* c_array) override;
  bool isFinished() override;
  void close() override;
 private:
  std::shared_ptr<exec::Task> task_;
  bool is_finished_ = false;
};

}  // namespace trino::velox
