@echo off
@call setvars.bat
mkdir ..\build
inform6 +include_path=%I6PATH%\bin,%I6PATH%\contrib,..\src -~S -~D -~X -s ..\src\DrEgoAdv.inf ..\build\DrEgoAdv.z5