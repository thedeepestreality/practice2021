@echo off
REM basic examples on variables
REM see https://ss64.com/nt/set.html

REM string variable
set var=hello
echo var=%var%
REM unset variable
set var=
REM check if variable is set
if "%var%"=="" echo not set
REM or like this
if [%var%]==[] echo not set
REM concatenate two strings
set var1=hello
set var2=world
set result=%var1% %var2%
echo concatenated: %result%

REM set variable from the user input
set /P var="Enter value: "
echo you set var=%var%

set num1=13
set num2=29
REM set variable from evaluation of the arithmetic expression
REM /A flag also allows to omit % signs
set /A result=num1+num2
echo evaluated result: %result%
REM but after the evaluation it is usual variable
set "newvar=%result% is the answer"
echo newvar=%newvar%
