add_executable(EquationRoot4Tests
        EquationRoot4Tests.cpp)

target_link_libraries(EquationRoot4Tests PRIVATE EquationRoot4Lib)
target_link_libraries(EquationRoot4Tests PRIVATE Catch2::Catch2WithMain)