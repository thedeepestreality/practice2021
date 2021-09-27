@echo off
REM basic functions (subroutines) examples
REM see https://ss64.com/nt/call.html
REM see https://ss64.com/nt/shift.html

REM no args passed
call :global_return
echo %result%

REM one arg used for return val also
call :named_return retval
echo %retval%

REM passing all the console arguments
call :iterateargs %*
REM arguments are shifted only locally
echo command name unchanged: %0
exit /b

:global_return
echo hello
set result=global_ok
exit /b

:named_return
echo named_return passed arg value: %1
REM set the return value
set %1=named_ok
exit /b

:iterateargs
echo started iterate_args func
:iterateargs_cycle
if "%1"=="" (
	REM numbered arguments are shifted
	REM but %* notation is unchanged!
	echo initial args: ^(%*^)
    exit /b
)
echo arg %1
REM shifting args by 1
shift
goto iterateargs_cycle
