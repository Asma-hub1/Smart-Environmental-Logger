project(
  'PowerControl-test',
  'cpp',
  version : '0.1', 
)

add_global_arguments(language : ['cpp'])

gtestDependency = dependency('gtest')
gmockDependency = dependency('gmock')

outpostRtosIncludePath0 = include_directories('../../../ext/outpost-core/modules/rtos/arch/common/posix')
outpostRtosIncludePath1 = include_directories('../../../ext/outpost-core/modules/rtos/arch/posix')
outpostRtosSrcIncludePath = include_directories('../../../ext/outpost-core/modules/rtos/src')
outpostTimeIncludePath = include_directories('../../../ext/outpost-core/modules/time/src')
testUtilsIncludePath = include_directories('../../../ext/testUtils/include')

# for "sandbox/pwr"
targetIncludePath0 = include_directories('../../../modules/pwr/src')

# for "sandbox/hal"
targetIncludePath1 = include_directories('../../../modules/hal/src')


unittestFiles = files(
[
  # object under test
  '../../../modules/pwr/src/sandbox/pwr/power_control.cpp',

  # test cases
  'power_control/fake_test.cpp',
  'power_control/fake_test_parameterized.cpp',
  'power_control/actuators_mock_test.cpp',
  'power_control/fsm_actions.cpp',

  # RTOS library
  '../../../ext/outpost-core/modules/rtos/arch/common/posix/outpost/posix/mutex.cpp',
  '../../../ext/outpost-core/modules/rtos/arch/common/posix/outpost/posix/failure_handler.cpp',
  '../../../ext/outpost-core/modules/rtos/arch/common/posix/outpost/posix/internal/time.cpp',

  # gtest executable
  '../../../ext/testUtils/src/configurable_event_listener.cpp',
  'main.cpp'
]
)

buildArguments = [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
]

executable(
  'PowerControl-test.exe', 
  unittestFiles,
  include_directories : [
    outpostRtosIncludePath0, outpostRtosIncludePath1,
    outpostRtosSrcIncludePath,
    outpostTimeIncludePath,
    testUtilsIncludePath,
    targetIncludePath0, targetIncludePath1
  ],
  dependencies : [
    gtestDependency,
    gmockDependency
  ],
  link_with : [
  ],
  c_args : buildArguments
)
