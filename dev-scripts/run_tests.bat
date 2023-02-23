@echo off
setlocal

REM Run command to get composer_dir
set "composer_dir="
for /f "usebackq delims=" %%i in (`where composer.phar`) do set "composer_dir=%%i"

REM Check if composer_dir was found
if "%composer_dir%"=="" (
  echo No composer found.
  exit /b 1
) else (
  set "script_dir=%~dp0"
  set "work_dir=%script_dir%/.."
  cd %work_dir%
  echo %work_dir%
  ls x64\Release

  php -c php-win.ini %composer_dir% update
  if %errorlevel% neq 0 (
    echo An error occurred while using composer to get dependence
    exit /b %errorlevel%
  )

  php -c php-win.ini vendor/bin/phpunit tests --debug
  if %errorlevel% neq 0 (
    echo An error occurred while running unittests
    exit /b %errorlevel%
  )
)

endlocal