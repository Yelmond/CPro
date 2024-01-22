project( ui_test )

add_executable( ui_test ui_test_widget.cpp  "ui_test_enums.cpp")

find_package( GTest CONFIG REQUIRED )

target_link_libraries( ui_test PRIVATE GTest::gtest GTest::gtest_main ui )

include( GoogleTest )
gtest_discover_tests( ui_test )
