@echo off
@call setvars.bat
mkdir ..\build
inform6 +include_path=%I6PATH%\bin,%I6PATH%\contrib,..\src -SDX ..\src\DrEgoAdv.inf ..\build\Debug.z5 $MAX_LABELS=1500