@echo off
@call setvars.bat
mkdir ..\build
inform6 +include_path=.\,%I6PATH%\bin,%I6PATH%\contrib -~S -~D -~X ..\src\DrEgoAdv.inf ..\build\DrEgoAdv.z5