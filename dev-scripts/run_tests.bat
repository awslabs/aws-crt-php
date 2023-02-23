@echo on
setlocal

REM Run command to get composer_dir
set "composer_dir="
for /f "usebackq delims=" %%i in (`where composer.phar`) do set "composer_dir=%%i"

REM Check if composer_dir was found
if "%composer_dir%"=="" (
  echo No composer found.
  exit /b 1
) else (
  cd ..
  php -c php-win.ini %composer_dir% update
  php -c php-win.ini vendor/bin/phpunit tests --debug
)

endlocal