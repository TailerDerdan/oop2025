@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% 1F > "%TEMP%\invalid.txt" && goto err
fc test_data\invalid_arg_count.txt "%TEMP%\invalid.txt" > nul || goto err
echo Test 2 passed

%MyProgram% 16 10 > "%TEMP%\invalid.txt" && goto err
fc test_data\invalid_arg_count.txt "%TEMP%\invalid.txt" > nul || goto err
echo Test 3 passed

%MyProgram% 0 10 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 4 passed

%MyProgram% 16 0 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 5 passed

%MyProgram% 16 38 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 6 passed

%MyProgram% 38 10 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 7 passed

%MyProgram% 10 16 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 8 passed

%MyProgram% ab 10 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 9 passed

%MyProgram% 16 ab 1F > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 10 passed

%MyProgram% 16 10 #! > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 11 passed

%MyProgram% 10 16 2147483648 > "%TEMP%\incorrect.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\incorrect.txt" > nul || goto err
echo Test 12 passed

%MyProgram% 10 16 2147483647 > "%TEMP%\output.txt" || goto err
fc test_data\radix_int_max.txt "%TEMP%\output.txt" > nul || goto err
echo Test 13 passed

%MyProgram% 10 16 -2147483647 > "%TEMP%\output.txt" || goto err
fc test_data\radix_int_min.txt "%TEMP%\output.txt" > nul || goto err
echo Test 14 passed

%MyProgram% 10 2 20 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_2_20.txt "%TEMP%\output.txt" > nul || goto err
echo Test 15 passed

%MyProgram% 10 36 623714775 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_36_623714775.txt "%TEMP%\output.txt" > nul || goto err
echo Test 16 passed

%MyProgram% 10 36 996877461 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_36_996877461.txt "%TEMP%\output.txt" > nul || goto err
echo Test 17 passed

%MyProgram% 10 36 1370040147 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_36_1370040147.txt "%TEMP%\output.txt" > nul || goto err
echo Test 18 passed

%MyProgram% 10 36 1743202833 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_36_1743202833.txt "%TEMP%\output.txt" > nul || goto err
echo Test 19 passed

%MyProgram% 10 36 1259 > "%TEMP%\output.txt" || goto err
fc test_data\radix_10_36_1259.txt "%TEMP%\output.txt" > nul || goto err
echo Test 20 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1