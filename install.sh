#You must have g++ to install upm
echo Installing Universal Package Manager \"Wrapper\"
echo Run the scripts as root if not running as root...
echo Compiling...
g++ -o upm main.cpp
echo Installing...
mv upm /usr/bin/upm
echo upm is ready to be used!