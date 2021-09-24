@echo off
rem infinite cycle with goto

set answer=%1
:begin
if %answer%==42 (
	goto end
) else (
	echo wrong answer %answer%
	goto ask
)
:ask
set /p answer="enter new value: "
goto begin
:end
echo answer is right, finished
