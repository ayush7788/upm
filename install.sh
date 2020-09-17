#You must have g++ to install upm
echo Compiling..
g++ -o upm main.cpp
echo Enter password to contnue installation..
sudo mv upm /bin/upm
echo upm is ready to be used!
