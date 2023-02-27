@echo on
setlocal


set "PHP_BINARY=php"

if not "%~1"=="" (
  set "PHP_BINARY=%~1"
)

set "script_dir=%~dp0"
set "work_dir=%script_dir%/.."
cd %work_dir%

set vendor_path=vendor
REM Run command to get composer_dir
set "composer_dir="
for /f "usebackq delims=" %%i in (`where composer.phar`) do set "composer_dir=%%i"

if not exist "%vendor_path%" (
  REM Check if composer_dir was found
  if "%composer_dir%"=="" (
    echo No composer found.
    exit /b 1
  )
  call %PHP_BINARY% -c php-win.ini %composer_dir% update
)

call %PHP_BINARY% -c php-win.ini vendor/bin/phpunit tests --debug

endlocal
