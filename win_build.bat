@echo on

git clone https://github.com/Microsoft/php-sdk-binary-tools.git php-sdk
cd ./php-sdk

vswhere
@REM  -nologo -version "[15,16)" -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath -format text

./phpsdk-vc15-x64.bat