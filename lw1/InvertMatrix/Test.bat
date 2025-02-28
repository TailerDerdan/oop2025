@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% test_data\empty.txt > "%TEMP%\empty.txt" && goto err
fc test_data\invalid_matrix_format.txt "%TEMP%\empty.txt" > nul || goto err
echo Test 1 passed

%MyProgram% test_data\matrix_with_letters.txt > "%TEMP%\output.txt" && goto err
fc test_data\invalid_matrix.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

%MyProgram% test_data\matrix_2x2.txt > "%TEMP%\output.txt" && goto err
fc test_data\invalid_matrix_format.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% test_data\matrix_4x4.txt > "%TEMP%\output.txt" && goto err
fc test_data\invalid_matrix_format.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

%MyProgram% test_data\matrix_det0.txt > "%TEMP%\output.txt" && goto err
fc test_data\non-invertible.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

%MyProgram% test_data\identity_matrix.txt > "%TEMP%\output.txt" || goto err
fc test_data\identity_matrix.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

%MyProgram% test_data\good_matrix_3x3.txt > "%TEMP%\output.txt" || goto err
fc test_data\invert_good_matrix_3x3.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 passed

REM %MyProgram% test_data\invert_good_matrix_3x3.txt > "%TEMP%\output.txt" || goto err
REM fc test_data\good_matrix_3x3.txt "%TEMP%\output.txt" > nul || goto err
REM echo Test 8 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1