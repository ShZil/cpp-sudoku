@echo off
cls
@echo on
g++ main.cpp functions.cpp -o main.exe
@echo off
IF %ERRORLEVEL% NEQ 0 (
    set /p input= Run the latest good build? [Enter]
)
echo.
@echo on
main.exe
@echo off
echo.
echo | set /p dummyName=Process finished with exit code %ERRORLEVEL%. 
pause
