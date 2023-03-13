
add_library(
  q6_dummy_task
  TpchQ6DummyTask.cpp)

add_executable(q6_demo q6_demo.cpp)

target_link_libraries(
  q6_demo
  q6_dummy_task

  velox_core
  velox_vector
  velox_exec
  velox_time
  velox_type

  velox_plugin

  velox_exec_test_lib
  velox_vector_test_lib
  velox_temp_path
  velox_tpch_connector
  velox_dwio_parquet_reader
  velox_dwio_dwrf_writer
  velox_dwio_dwrf_reader
  velox_dwio_duckdb_parquet_reader
  velox_dwio_native_parquet_reader
  velox_dwio_parquet_thrift
  velox_dwio_common_test_utils
  velox_dwio_common
  velox_parse_parser
  velox_presto_serializer
  velox_functions_prestosql
  velox_duckdb_allocator

  cider
  cider_function
  cider_processor
  nextgen
  jitlib
  cider_plan_substrait
  cider_plan_parser
  cider_type_plan
  cider_func_lkup
  velox_arrow_bridge

  duckdb

  QueryEngine

  velox_plan_transformer
  cider_plan_transformer
  velox_substrait_convertor
  velox_substrait_plan_converter
  cider_util
  substrait
  substrait_function
  substrait_type
  substrait_common
  yaml-cpp
  thrift
  LLVM
  protobuf
  gtest
  )

