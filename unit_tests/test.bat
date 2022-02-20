@echo off

call :Test

:Trim
SetLocal EnableDelayedExpansion
set Params=%*
for /f "tokens=1*" %%a in ("!Params!") do EndLocal & set %1=%%b
exit /b

:Test
FOR /F "tokens=* USEBACKQ" %%F IN (`shift_array`) DO (
SET var=%%F
)
ECHO [%var%]

call :Trim var %var%

ECHO [%var%]

if "%var%" == "5 1 2 3 4" (
	ECHO PASSED
) else (
	echo FAILED
)
exit /b