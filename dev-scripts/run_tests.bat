@echo on
setlocal


set "PHP_BINARY=php"

if not "%~1"=="" (
  set "PHP_BINARY=%~1"
)

set "script_dir=%~dp0"
set "work_dir=%script_dir%/.."
cd %work_dir%

composer update
call %PHP_BINARY% -c php-win.ini vendor/bin/phpunit tests --debug

endlocal
