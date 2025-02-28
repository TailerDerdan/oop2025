@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% test_data\allSymbols.txt "%TEMP%\invalid.txt" 18 > "%TEMP%\invalid0.txt" && goto err
fc test_data\invalid_count_arg.txt "%TEMP%\invalid0.txt" > nul || goto err
echo Test 1 passed

%MyProgram% test_data\allSymbols.txt "%TEMP%\invalid.txt" crypt ma > "%TEMP%\invalid0.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\invalid0.txt" > nul || goto err
echo Test 2 passed

%MyProgram% test_data\allSymbols.txt "%TEMP%\invalid.txt" crypt -209 > "%TEMP%\invalid0.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\invalid0.txt" > nul || goto err
echo Test 3 passed

%MyProgram% test_data\allSymbols.txt "%TEMP%\invalid.txt" crypt 300 > "%TEMP%\invalid0.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\invalid0.txt" > nul || goto err
echo Test 4 passed

%MyProgram% test_data\allSymbols.txt "%TEMP%\invalid.txt" smth 300 > "%TEMP%\invalid0.txt" && goto err
fc test_data\incorrect_data.txt "%TEMP%\invalid0.txt" > nul || goto err
echo Test 5 passed

%MyProgram% test_data\allSymbols.txt "%TEMP%\output.txt" crypt 18 || goto err
fc test_data\allSymbols_crypt.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

%MyProgram% "%TEMP%\output.txt" "%TEMP%\output0.txt" decrypt 18 || goto err
fc test_data\allSymbols.txt "%TEMP%\output0.txt" > nul || goto err
echo Test 7 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1