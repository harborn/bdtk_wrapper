
#include <memory>
#include <folly/init/Init.h>

#include "velox/dwio/common/tests/utils/BatchMaker.h"
#include "velox/exec/tests/utils/OperatorTestBase.h"
#include "velox/exec/tests/utils/PlanBuilder.h"
#include "velox/substrait/VeloxToSubstraitPlan.h"

#include "BDTK/cpp/src/cider-velox/src/CiderVeloxPluginCtx.h"
#include "BDTK/cpp/src/cider-velox/src/CiderPlanNode.h"

using namespace facebook::velox;
using namespace facebook::velox::exec;
using namespace facebook::velox::exec::test;
using namespace facebook::velox::plugin;
using namespace facebook::velox::substrait;

using facebook::velox::test::BatchMaker;

class CiderPlanNodeTest : public OperatorTestBase {
 protected:
  std::shared_ptr<const RowType> rowType_{
      ROW({"l_quantity", "l_extendedprice", "l_discount", "l_shipdate"},
          {DOUBLE(), DOUBLE(), DOUBLE(), DOUBLE()})};
};

TEST_F(CiderPlanNodeTest, filter) {
  std::vector<RowVectorPtr> vectors;
  for (int32_t i = 0; i < 10; ++i) {
    auto vector = std::dynamic_pointer_cast<RowVector>(
        BatchMaker::createBatch(rowType_, 100, *pool_));
    vectors.push_back(vector);
  }
  createDuckDbTable(vectors);

  const std::string filter =
      "l_shipdate >= 8765.666666666667 and l_shipdate < 9130.666666666667 and "
      "l_discount between 0.05 and 0.07 and l_quantity < 24.0";
  auto veloxPlan = PlanBuilder().values(vectors).filter(filter).planNode();

  std::shared_ptr<VeloxToSubstraitPlanConvertor> v2SPlanConvertor =
      std::make_shared<VeloxToSubstraitPlanConvertor>();
  google::protobuf::Arena arena;
  auto plan = std::make_shared<::substrait::Plan>(
      v2SPlanConvertor->toSubstrait(arena, veloxPlan));
  auto source = PlanBuilder().values(vectors).planNode();
  auto ciderPlanNode =
      std::make_shared<CiderPlanNode>("100", source, veloxPlan->outputType(), *plan);
}

TEST_F(CiderPlanNodeTest, project) {
  std::vector<RowVectorPtr> vectors;
  for (int32_t i = 0; i < 10; ++i) {
    auto vector = std::dynamic_pointer_cast<RowVector>(
        BatchMaker::createBatch(rowType_, 100, *pool_));
    vectors.push_back(vector);
  }
  createDuckDbTable(vectors);

  auto veloxPlan = PlanBuilder()
                       .values(vectors)
                       .project({"l_extendedprice * l_discount as revenue"})
                       .planNode();

  std::shared_ptr<VeloxToSubstraitPlanConvertor> v2SPlanConvertor =
      std::make_shared<VeloxToSubstraitPlanConvertor>();

  google::protobuf::Arena arena;
  auto plan = std::make_shared<::substrait::Plan>(
      v2SPlanConvertor->toSubstrait(arena, veloxPlan));
  auto source = PlanBuilder().values(vectors).planNode();
  auto ciderPlanNode =
      std::make_shared<CiderPlanNode>("100", source, veloxPlan->outputType(), *plan);

  std::cout << ciderPlanNode->toString() << std::endl;
  std::cout << veloxPlan->toString();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  folly::init(&argc, &argv, false);
  return RUN_ALL_TESTS();
}
