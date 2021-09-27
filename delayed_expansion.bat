@echo off
REM examples on the Delayed Expansion
REM see https://ss64.com/nt/delayedexpansion.html

REM inner IF will not work
REM because it is in fact on the same line
REM with the outer IF and VAR value read only once
set VAR=old_val
if %VAR% == old_val (
    echo old_val worked!
    set VAR=new_val
    if %VAR% == new_val echo new_val worked!
)

REM this IF will work, because this is new line
if %VAR% == new_val (
    echo new_val on the new line worked!
)

REM here LIST is supposed to grow
REM but again %LIST% in the loop body will be empty
set LIST=
for %%i in (1,2,3) do (
    set LIST=%LIST% %%i
)
echo list without delayed expansion: (%LIST%)

REM echo newline
echo/

REM and now we enable delayed expansion...
setlocal enabledelayedexpansion
set VAR=old_val
if %VAR% == old_val (
	echo old_val worked^!
    set VAR=new_val
    if !VAR! == new_val echo new_val with delayed expansion worked^!
)

set LIST=
for %%i in (1,2,3) do (
    set LIST=!LIST! %%i
)
echo list with delayed expansion: (%LIST%)