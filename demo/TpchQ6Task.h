
#include "velox/common/base/tests/GTestUtils.h"
#include "velox/common/file/FileSystems.h"
#include "velox/common/testutil/TestValue.h"
#include "velox/connectors/hive/HiveConnector.h"
#include "velox/connectors/tpch/TpchConnector.h"
#include "velox/exec/Task.h"
#include "velox/exec/tests/utils/Cursor.h"
#include "velox/exec/tests/utils/HiveConnectorTestBase.h"
#include "velox/exec/tests/utils/PlanBuilder.h"
#include "velox/functions/prestosql/registration/RegistrationFunctions.h"
#include "velox/parse/TypeResolver.h"

using namespace facebook::velox;
using namespace facebook::velox::exec::test;

namespace trino::velox {
class TpchQ6Task {
 public:
  ~TpchQ6Task() = default;

  static std::shared_ptr<TpchQ6Task> Make();

  virtual void nextBatch(ArrowSchema* c_schema, ArrowArray* c_array) = 0;

  virtual bool isFinished() = 0;

  virtual void close() = 0;
};
}  // namespace trino::velox
