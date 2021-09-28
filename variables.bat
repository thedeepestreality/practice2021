@echo off
REM basic examples on variables
REM see https://ss64.com/nt/set.html
REM see https://ss64.com/nt/setlocal.html
REM see https://ss64.com/nt/syntax-substring.html
REM see https://ss64.com/nt/syntax-replace.html

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

REM string operations
set str=abcdef
echo [str] = %str%
echo [str:~0,3] = %str:~0,3%
echo [str:~3] = %str:~3%
echo [str:~-2] = %str:~-2%
echo [str:~1,-1] = %str:~1,-1%
set url=http://ya.ru
if %url:~0,4%==http echo %url% is url

REM remove all 'c' symbols
echo [str:c=] = %str:c=%
REM replace all 'c' symbols with B
echo [str:c=B] = %str:c=B%
REM replce all substring ending with 'c' symbol to empty string
echo [str:*c=] = %str:*c=%

REM global var
set glob_var=global
REM local scope
setlocal
	set glob_var=local
	echo [setlocal] glob_var = %glob_var%
endlocal
REM local changes doesn't affect global variables
echo [endlocal] glob_var = %glob_var%
