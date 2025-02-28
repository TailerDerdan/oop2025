@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% && goto err
echo Test 1 passed

%MyProgram% test_data\empty.txt "%TEMP%\empty.txt" || goto err
fc test_data\out_empty.txt "%TEMP%\empty.txt" > nul || goto err
echo Test 2 passed

%MyProgram% test_data\without_start_point.txt "%TEMP%\output.txt" || goto err
fc test_data\out_without_start_point.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% test_data\many_start_point.txt "%TEMP%\output.txt" || goto err
fc test_data\out_many_start_point.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

%MyProgram% test_data\one_start_point.txt "%TEMP%\output.txt" || goto err
fc test_data\out_one_start_point.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

%MyProgram% test_data\start_point_outdoor.txt "%TEMP%\output.txt" || goto err
fc test_data\out_start_point_outdoor.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

%MyProgram% test_data\many_start_point_indoor.txt "%TEMP%\output.txt" || goto err
fc test_data\out_many_start_point_indoor.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1