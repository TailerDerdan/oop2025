@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% && goto err
echo Test 1 passed

%MyProgram% empty.txt "%TEMP%\empty.txt" 1 2 && goto err
echo Test 2 passed

%MyProgram% tests\song.txt "%TEMP%\song.txt" "" square || goto err
fc tests\song.txt "%TEMP%\song.txt" > nul || goto err
echo Test 3 passed

%MyProgram% tests\song.txt "%TEMP%\song.txt" a "" || goto err
fc tests\song-replace-a-empty.txt "%TEMP%\song.txt" > nul || goto err
echo Test 4 passed

%MyProgram% tests\song.txt "%TEMP%\song.txt" line square || goto err
fc tests\song-replace-line-square.txt "%TEMP%\song.txt" > nul || goto err
echo Test 5 passed

%MyProgram% tests\song.txt "%TEMP%\song.txt" 1234 square || goto err
fc tests\song.txt "%TEMP%\song.txt" > nul || goto err
echo Test 6 passed

%MyProgram% tests\repeatSymbols.txt "%TEMP%\repeatSymbols.txt" qweqwe qwe || goto err
fc tests\repeatSymbols-replace-qweqwe-qwe.txt "%TEMP%\repeatSymbols.txt" > nul || goto err
echo Test 7 passed

%MyProgram% tests\mother.txt "%TEMP%\mother.txt" ma mama || goto err
fc tests\mother-ma-mama.txt "%TEMP%\mother.txt" > nul || goto err
echo Test 8 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1