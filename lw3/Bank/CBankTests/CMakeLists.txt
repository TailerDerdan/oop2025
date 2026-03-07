add_executable(TestsBank
        BankTests.cpp)

target_link_libraries(TestsBank PRIVATE BankLib)
target_link_libraries(TestsBank PRIVATE Catch2::Catch2WithMain)