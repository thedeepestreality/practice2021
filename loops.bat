@echo off
REM basic examples on FOR loop
REM see https://ss64.com/nt/for.html

REM iterate through the list
echo SIMPLE FOR LOOP:
for %%i in (1, abc, 1.2) do (
    echo %%i
)

REM echo newline
echo/

REM FOR tries to interpret list values as filenames
REM the code below should print all the .bat-file names
echo/ & echo BAT FILES IN THE CURRENT FOLDER:
for %%i in (*.bat) do (
    echo %%i
)
REM /R flag allow to search files in the all subfolders recursively
echo/ & echo BAT FILES IN THE CURRENT FOLDER AND ALL SUBFOLDERS:
for /R %%i in (*.bat) do (
    echo %%i
)

REM /D will interpret list as FOLDER names
echo/ & echo FOLDERS:
for /D %%i in (*) do (
    echo %%i
)

REM range-base for-loop with /L flag
REM list syntax: (start, step, end)
echo/ & echo RANGE-BASED FOR:
for /L %%i in (1,2,10) do (
    echo %%i
)

REM loop for file contents
echo/ & echo FOR-File:
for /F "tokens=1,2" %%i in (check_arg.bat) do (
    echo %%i %%j
)

REM loop for string contents
echo/ & echo FOR-String:
for /F "tokens=1,2" %%i in ("first second") do (
    echo %%i %%j
)

REM loop for command result
echo/ & echo FOR-Command:
for /F "tokens=1,2" %%i in ('echo first second') do (
    echo %%i %%j
)
