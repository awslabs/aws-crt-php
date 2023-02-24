@echo on
setlocal

REM Run command to get composer_dir
set "composer_dir="
for /f "usebackq delims=" %%i in (`where composer.phar`) do set "composer_dir=%%i"

set "PHP_BINARY=php"

if not "%~1"=="" (
  set "PHP_BINARY=%~1"
)


REM Check if composer_dir was found
if "%composer_dir%"=="" (
  echo No composer found.
  exit /b 1
) else (
  set "script_dir=%~dp0"
  set "work_dir=%script_dir%/.."
  cd %work_dir%
  echo %work_dir%
  ls x64\

  %PHP_BINARY% -c php-win.ini %composer_dir% update
  if %errorlevel% neq 0 (
    echo An error occurred while using composer to get dependence
    exit /b %errorlevel%
  )

  %PHP_BINARY% -c php-win.ini vendor/bin/phpunit tests --debug
  if %errorlevel% neq 0 (
    echo An error occurred while running unittests
    exit /b %errorlevel%
  )
)

endlocal