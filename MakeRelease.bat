@echo off
rem #  Build a PinAffinity release
rem #
rem #  Before running this script, load the solution in Visual Studio
rem #  and do a full rebuild of the release versions:
rem #
rem #  Select configuration Release | x86
rem #  Build > Clean Solution
rem #  Build > Build Solution
rem #  Select configuration Release | x64
rem #  Build > Clean Solution
rem #  Build > Build Solution
rem #

rem #  Path configuration
set BuildsDir=Builds
set Release32=release
set Release64=x64\release

rem #  Release files
set FileList=PinAffinity.exe README.txt License.txt AffinityTypes.txt SavedProcesses.txt 

rem #  Date suffix YYYY-MM-DD
set datesuffix=%DATE:~10,4%-%DATE:~7,2%-%DATE:~4,2%

rem #  Build the 32-bit release
set zip32=%BuildsDir%\PinAffinity32-%datesuffix%.zip
echo 32-bit release -^> %zip32%
if exist "%zip32%" del "%zip32%"
for %%f in (%FileList%) do (
    zip -j "%zip32%" "%Release32%\%%f"
)
echo.

rem #  Build the 64-bit release
set zip64=%BuildsDir%\PinAffinity64-%datesuffix%.zip
echo 64-bit release -^> %zip64%
if exist "%zip64%" del "%zip64%"
for %%f in (%FileList%) do (
    zip -j "%zip64%" "%Release64%\%%f"
)
echo.
