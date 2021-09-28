@echo off
call :power 2 4
echo %result%
REM Prints 16, determined as 2 * 2 * 2 * 2
goto :eof

REM Function power
REM Arguments: %1 and %2
:power
setlocal
set counter=%2
set accum=%1
:power_loop
if %counter% GTR 1 (
  set /A accum=accum * %1
  set /A counter=counter - 1
  goto :power_loop
)
endlocal & set result=%accum%
goto :eof
